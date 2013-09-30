import numpy as np
import Dragonfly_config as rc
from argparse import ArgumentParser
from ConfigParser import SafeConfigParser
from PyDragonfly import Dragonfly_Module, CMessage, copy_to_msg, copy_from_msg
from time import time

class MessageWatcher(object):
    # msg_types = ['GROBOT_RAW_FEEDBACK',
    #              'GROBOT_FEEDBACK',
    #              'SAMPLE_GENERATED',
    #              'SPM_SPIKECOUNT',
    #              'EM_MOVEMENT_COMMAND',
    #              'COMPOSITE_MOVEMENT_COMMAND'
    #              ]
    
    def __init__(self, config_file):
        self.load_config(config_file)
        self.msg_nums = [eval('rc.MT_%s' % (x)) for x in self.msg_types]
        self.count = np.zeros((len(self.msg_nums)), dtype=int)
        self.last_time = time()
        self.setup_Dragonfly()
        self.run()
        
    def load_config(self, config_file):
        self.config = SafeConfigParser()
        self.config.read(config_file)
        self.msg_types = [x.upper() for x in self.config.options('messages')]
        self.msg_types.sort()

    def setup_Dragonfly(self):
        server = self.config.get('Dragonfly', 'server')
        self.mod = Dragonfly_Module(0, 0)
        self.mod.ConnectToMMM(server)
        for i in self.msg_types:
            self.mod.Subscribe(eval('rc.MT_%s' % (i)))
        self.mod.SendModuleReady()
        print "Connected to Dragonfly at", server
        
    def run(self):
        while True:
            msg = CMessage()
            rcv = self.mod.ReadMessage(msg, 0.1)
            if rcv == 1:
                self.process_message(msg)
                
            this_time = time()
            self.diff_time = this_time - self.last_time
            if self.diff_time > 1.:
                self.last_time = this_time
                self.write()
                self.count[:] = 0

    def process_message(self, in_msg):
        msg_type = in_msg.GetHeader().msg_type
        if not msg_type in self.msg_nums:
            return
        msg_idx = self.msg_nums.index(msg_type)
        self.count[msg_idx] += 1

    def write(self):
        for msg_type, c in zip(self.msg_types, self.count):
            rate = c / self.diff_time
            print "%40s %5.2f Hz" % (msg_type, rate)
            if (('GROBOT_RAW_FEEDBACK' in msg_type) and (rate < 48.0)):
                print "Raw feedback rate is too low!"
                print "Raw feedback rate is too low!"
                print "Raw feedback rate is too low!"
                print "Raw feedback rate is too low!"
        print "window was %0.3f seconds\n" % (self.diff_time)
        print ""
    
if __name__ == "__main__":
    parser = ArgumentParser(description = "Display information about message flow")
    parser.add_argument('config', metavar='config_file', type=str)
    args = parser.parse_args()
    print("Using config file %s" % args.config)
    mw = MessageWatcher(args.config)
