import os
from argparse import ArgumentParser
import numpy as np

from PyDragonfly import Dragonfly_Module, CMessage, copy_from_msg, copy_to_msg, MT_EXIT
import Dragonfly_config as rc
from ConfigParser import SafeConfigParser
import time
from dragonfly_utils import respond_to_ping


btn_threshold = 0.008
bounce_threshold = 0.05 # 100 ms
ncontrollers = 2
name_lookup = { rc.PS3_C_R1 : 'r1',
                rc.PS3_C_L1 : 'l1',
                rc.PS3_C_L2 : 'l2',
                rc.PS3_C_CIRCLE   : 'crc',
                rc.PS3_C_X        : 'x',
                rc.PS3_C_SQUARE   : 'sq',
                rc.PS3_C_TRIANGLE : 'trg' }

class ButtonDetector(object):
    debug = True
    bounce_start = np.zeros([ncontrollers, rc.MAX_INPUT_DOFS]) - 1
    was_pressed = np.zeros([ncontrollers, rc.MAX_INPUT_DOFS], dtype=bool)

    def __init__(self, config_file, server):
        self.load_config(config_file)
        self.get_inputs()
        self.setup_dragonfly(server)
        self.run()

    def load_config(self, config_file):
        self.config = SafeConfigParser()
        self.config.read(config_file)

    def setup_dragonfly(self, server):
        self.mod = Dragonfly_Module(0, 0)
        self.mod.ConnectToMMM(server)
        self.mod.Subscribe(MT_EXIT)
        self.mod.Subscribe(rc.MT_PING)
        self.mod.Subscribe(rc.MT_INPUT_DOF_DATA)
        self.mod.SendModuleReady()
        print "Connected to Dragonfly at", server

    def run(self):
        while True:
            msg = CMessage()
            rcv = self.mod.ReadMessage(msg, 0.1)
            if rcv == 1:
                msg_type = msg.GetHeader().msg_type
                dest_mod_id = msg.GetHeader().dest_mod_id
                if  msg_type == MT_EXIT:
                    if (dest_mod_id == 0) or (dest_mod_id == self.mod.GetModuleID()):
                        print 'Received MT_EXIT, disconnecting...'
                        self.mod.SendSignal(rc.MT_EXIT_ACK)
                        self.mod.DisconnectFromMMM()
                        break;
                elif msg_type == rc.MT_PING:
                    respond_to_ping(self.mod, msg, 'ButtonDetector')
                else:
                    self.process_message(msg)

    def get_inputs(self):
        sections = self.config.sections()
        self.inputs = {}
        for sec in sections:
            if 'input ' in sec:
                tag = self.config.get(sec, 'tag')
                self.inputs[tag] = {}

    def process_message(self, msg):
        msg_type = msg.GetHeader().msg_type
        if msg_type == rc.MT_INPUT_DOF_DATA:
            mdf = rc.MDF_INPUT_DOF_DATA()
            copy_from_msg(mdf, msg)
            tag = mdf.tag
            if tag in self.inputs.keys():
                dof_vals = np.asarray(mdf.dof_vals[:], dtype=float)
                cid = int(mdf.tag[-1])
                pressed = ~self.was_pressed[cid] & (dof_vals > btn_threshold)
                started = self.bounce_start[cid] > 0

                # start timers on previously unstarted counters
                self.bounce_start[cid, pressed & ~started] = time.time()

                dt = time.time() - self.bounce_start[cid]
                held = dt > bounce_threshold
                valid_held = pressed & held

                for vh in np.flatnonzero(valid_held):
                    if vh in name_lookup.keys():
                        self.was_pressed[cid, vh] = True
                        self.send_btn_press(name_lookup[vh], cid)

                released = self.was_pressed[cid] & (dof_vals < btn_threshold)
                valid_released = released & held & ~valid_held

                for vr in np.flatnonzero(valid_released):
                    if vr in name_lookup.keys():
                        self.was_pressed[cid, vr] = False
                        self.send_btn_release(name_lookup[vr], cid)
                        self.bounce_start[cid, vr] = -1

    def send_btn_press(self, btn, controller_id):
        print "controller_id %d sending button press %s" % (controller_id, btn)
        btn_map = {'l1' : rc.PS3_B_L1,
                   'l2' : rc.PS3_B_L2,
                   'r1' : rc.PS3_B_R1,
                   'x'  : rc.PS3_B_X,
                   'sq' : rc.PS3_B_SQUARE,
                   'crc': rc.PS3_B_CIRCLE,
                   'trg': rc.PS3_B_TRIANGLE}
        mdf_out = rc.MDF_PS3_BUTTON_PRESS()
        mdf_out.whichButton = btn_map[btn]
        mdf_out.controllerId = controller_id
        # make outgoing message data
        msg_out = CMessage(rc.MT_PS3_BUTTON_PRESS)
        copy_to_msg(mdf_out, msg_out)
        self.mod.SendMessage(msg_out)

    def send_btn_release(self, btn, controller_id):
        print "controller_id %d sending button release %s" % (controller_id, btn)
        btn_map = {'l1' : rc.PS3_B_L1,
                   'l2' : rc.PS3_B_L2,
                   'r1' : rc.PS3_B_R1,
                   'x'  : rc.PS3_B_X,
                   'sq' : rc.PS3_B_SQUARE,
                   'crc': rc.PS3_B_CIRCLE,
                   'trg': rc.PS3_B_TRIANGLE}
        mdf_out = rc.MDF_PS3_BUTTON_RELEASE()
        mdf_out.whichButton = btn_map[btn]
        mdf_out.controllerId = controller_id
        msg_out = CMessage(rc.MT_PS3_BUTTON_RELEASE)
        copy_to_msg(mdf_out, msg_out)
        self.mod.SendMessage(msg_out)

def print_state(dof_vals):
    np.array(dof_vals)
    d = {'X' : rc.PS3_C_X,
         '[]': rc.PS3_C_SQUARE,
         'O' : rc.PS3_C_CIRCLE,
         'R1': rc.PS3_C_R1}
    msg_str = ''
    for k,v in d.iteritems():
        msg_str += '%3s = %0.2g ' % (k, dof_vals[v])
    print msg_str


if __name__ == "__main__":
    parser = ArgumentParser(description = "Detect button presses from ps3RawModule")
    parser.add_argument(type=str, dest='config')
    parser.add_argument(type=str, dest='mm_ip', nargs='?', default='')
    args = parser.parse_args()
    print("Using config file=%s, MM IP=%s" % (args.config, args.mm_ip))
    itm = ButtonDetector(args.config, args.mm_ip)
