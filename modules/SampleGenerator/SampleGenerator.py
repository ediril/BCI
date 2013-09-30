#!/usr/bin/python

import time
import sys
import platform
from ConfigParser import SafeConfigParser
from PyDragonfly import Dragonfly_Module, CMessage, copy_to_msg, copy_from_msg, MT_EXIT
from argparse import ArgumentParser
from dragonfly_utils import respond_to_ping
import Dragonfly_config as rc

class SampleGenerator(object):
    def __init__(self, config_file, server):
        self.serial_no = 2
        self.freq = 50 # Hz
        self.load_config(config_file)
        self.setup_dragonfly(server)
        self.run()

    def load_config(self, config_file):
        self.config = SafeConfigParser()
        self.config.read(config_file)
        triggers = self.config.get('main','triggers').split()
        self.triggers = [eval('rc.MT_%s' % (x)) for x in triggers]
        if not triggers:
            freq = self.config.get('main','frequency')
            if freq != '':
                self.freq = self.config.getfloat('main','frequency')
            print "Freq: %.2f" % (self.freq)
        
    def setup_dragonfly(self, server):
        self.mod = Dragonfly_Module(rc.MID_SAMPLE_GENERATOR, 0)
        self.mod.ConnectToMMM(server)
        self.mod.Subscribe(MT_EXIT)
        self.mod.Subscribe(rc.MT_PING)
        self.mod.Subscribe(rc.MT_SPM_SPIKECOUNT)
        for trigger in self.triggers:
            self.mod.Subscribe(trigger)
        self.mod.SendModuleReady()
        print "Connected to Dragonfly at", server
        
        if platform.system() == "Windows":
            # On Windows, the best timer is time.clock()
            self.default_timer = time.clock
        else:
            # On most other platforms the best timer is time.time()
            self.default_timer = time.time

    def run(self):
        self.delta_time_calc = self.default_timer() #time.time()
        while True:
            msg = CMessage()
            rcv = self.mod.ReadMessage(msg, 0.001)
            if rcv == 1:
                hdr = msg.GetHeader()
                msg_type = hdr.msg_type
                dest_mod_id = hdr.dest_mod_id
                if  msg_type == MT_EXIT:
                    if (dest_mod_id == 0) or (dest_mod_id == self.mod.GetModuleID()):
                        print 'Received MT_EXIT, disconnecting...'
                        self.mod.SendSignal(rc.MT_EXIT_ACK)
                        self.mod.DisconnectFromMMM()
                        break;            
                elif msg_type == rc.MT_PING:
                    respond_to_ping(self.mod, msg, 'SampleGenerator')
                elif (msg_type == rc.MT_SPM_SPIKECOUNT):
                    msg_src_mod_id = hdr.src_mod_id
                    if msg_src_mod_id == rc.MID_SPM_MOD:
                        print "\n\n ** Detected SPM_SPIKECOUNT messages coming from SPM_MOD! Quitting..\n\n";
                        sys.exit(0);
                else:
                    if len(self.triggers) > 0:
                        self.process_msg(msg)
            else:
                # if no triggers...
                if len(self.triggers) == 0:
                    period = (1. / self.freq)
                    time_now = self.default_timer()
                    delta_time = period - (time_now - self.delta_time_calc)
                    #print "%f %f %f\n\n" % (time_now, self.delta_time_calc, delta_time)
                    if delta_time > 0:
                        time.sleep(delta_time)
                    self.delta_time_calc = self.delta_time_calc + period
                    self.send_sample_generated()

    def process_msg(self, msg):
        msg_type = msg.GetHeader().msg_type
        if msg_type in self.triggers:
            time_now = self.default_timer() #time.time()
            delta_time = time_now - self.delta_time_calc
            self.delta_time_calc = time_now 
            self.send_sample_generated()

    def send_sample_generated(self):
        sg = rc.MDF_SAMPLE_GENERATED()
        self.serial_no += 1
        sg.sample_header.SerialNo = self.serial_no
        sg.sample_header.Flags = 0
        sg.sample_header.DeltaTime = (1. / self.freq)
        sg.source_timestamp = self.default_timer() #time.time()
        sg_msg = CMessage(rc.MT_SAMPLE_GENERATED)
        copy_to_msg(sg, sg_msg)
        self.mod.SendMessage(sg_msg)
        sys.stdout.write('|')
        sys.stdout.flush()

if __name__ == "__main__":
    parser = ArgumentParser(description = 'Send SAMPLE_GENERATED messages' \
        ' under a range of conditions')
    parser.add_argument(type=str, dest='config')
    parser.add_argument(type=str, dest='mm_ip', nargs='?', default='')
    args = parser.parse_args()
    print("Using config file=%s, MM IP=%s" % (args.config, args.mm_ip))
    itm = SampleGenerator(args.config, args.mm_ip)
