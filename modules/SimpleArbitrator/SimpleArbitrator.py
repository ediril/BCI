#!/usr/bin/python

import numpy as np
import Dragonfly_config as rc
from argparse import ArgumentParser
from ConfigParser import SafeConfigParser
from PyDragonfly import Dragonfly_Module, CMessage, copy_to_msg, copy_from_msg, MT_EXIT
import Dragonfly_config as rc
import os
from dragonfly_utils import respond_to_ping


subscriptions = ['EM_MOVEMENT_COMMAND',
                 'OPERATOR_MOVEMENT_COMMAND',
                 'PLANNER_MOVEMENT_COMMAND',
                 'ROBOT_CONTROL_CONFIG',
                 'FIXTURED_MOVEMENT_COMMAND',
                 'IDLE',
                 'IDLE_DETECTION_ENDED',
                 'TASK_STATE_CONFIG',
                 'PING']

class SimpleArbitrator(object):
    debug = True
    vel = np.zeros(rc.MAX_CONTROL_DIMS)
    #pos = np.zeros(rc.MAX_CONTROL_DIMS)
    autoVelControlFraction = \
        np.ones_like(rc.MDF_ROBOT_CONTROL_CONFIG().autoVelControlFraction)
    extrinsic_vel = np.zeros_like(rc.MDF_COMPOSITE_MOVEMENT_COMMAND().vel)
    intrinsic_vel = np.zeros_like(rc.MDF_COMPOSITE_MOVEMENT_COMMAND().vel)

    def __init__(self, config_file, server):
        self.load_config(config_file)
        self.setup_dragonfly(server)
        self.run()

    def load_config(self, config_file):
        self.config = SafeConfigParser()
        self.config.read(config_file)
        self.timer_tag = self.config.get('main', 'timer_tag')
        self.extrinsic_tags = self.config.get('main', 'extrinsic_tags').split()
        self.intrinsic_tags = self.config.get('main', 'intrinsic_tags').split()
        default_auto = float(self.config.get('main', 'default_auto'))
        self.autoVelControlFraction[:] = default_auto
        self.gate = 1.              # default value
        self.idle_gateable = 0.     # default value

    def setup_dragonfly(self, server):
        self.mod = Dragonfly_Module(rc.MID_SIMPLE_ARBITRATOR, 0)
        self.mod.ConnectToMMM(server)
        self.mod.Subscribe(MT_EXIT)
        for sub in subscriptions:
            self.mod.Subscribe(eval('rc.MT_%s' % (sub)))
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
                    respond_to_ping(self.mod, msg, 'SimpleArbitrator')
                else:
                    self.process_message(msg)

    def process_message(self, msg):
        '''
        Needs to:
        1) combine non-conflicting controlledDims e.g. from
        OPERATOR_MOVEMENT_COMMANDs, into either extrinsic or
        intrinsic commands
        2) combine intrinsic and extrinsic commands into final command
        '''
        msg_type = msg.GetHeader().msg_type
        if msg_type in [rc.MT_OPERATOR_MOVEMENT_COMMAND,
                        rc.MT_PLANNER_MOVEMENT_COMMAND,
                        rc.MT_EM_MOVEMENT_COMMAND,
                        rc.MT_FIXTURED_MOVEMENT_COMMAND]:

            if msg_type == rc.MT_OPERATOR_MOVEMENT_COMMAND:
                mdf = rc.MDF_OPERATOR_MOVEMENT_COMMAND()

            elif msg_type == rc.MT_PLANNER_MOVEMENT_COMMAND:
                mdf = rc.MDF_PLANNER_MOVEMENT_COMMAND()

            elif msg_type == rc.MT_EM_MOVEMENT_COMMAND:
                mdf = rc.MDF_EM_MOVEMENT_COMMAND()

            elif msg_type == rc.MT_FIXTURED_MOVEMENT_COMMAND:
                mdf = rc.MDF_FIXTURED_MOVEMENT_COMMAND()

            # MOVEMENT_COMMAND
            # ----------------
            # controlledDims
            # pos
            # sample_header
            # sample_interval
            # tag
            # vel
            # ----------------

            copy_from_msg(mdf, msg)
            tag = mdf.tag
            #if not tag in self.accepted_tags:
            #    return
            dim = np.asarray(mdf.controlledDims, dtype=bool) #.astype(bool)
            if mdf.tag in self.intrinsic_tags:
                # intrinsic is AUTO command
                self.intrinsic_vel[dim] = np.asarray(mdf.vel, dtype=float)[dim]
                #print "intr_vel = " + " ".join(["%5.2f" % (x) for x in self.intrinsic_vel])
            elif mdf.tag in self.extrinsic_tags:
                #print "!"
                # extrinsic is non-AUTO, i.e. EM, command
                self.extrinsic_vel[dim] = np.asarray(mdf.vel, dtype=float)[dim]
                #self.extrinsic_vel[:8] *= self.gate

            if tag == self.timer_tag:
                self.send_output(mdf.sample_header)
        elif msg_type == rc.MT_ROBOT_CONTROL_CONFIG:
            mdf = rc.MDF_ROBOT_CONTROL_CONFIG()
            copy_from_msg(mdf, msg)
            self.autoVelControlFraction[:] = mdf.autoVelControlFraction
        elif msg_type == rc.MT_IDLE:
            mdf = rc.MDF_IDLE()
            copy_from_msg(mdf, msg)
            self.gate = float(np.asarray(mdf.gain, dtype=float).item())
        elif msg_type == rc.MT_IDLE_DETECTION_ENDED:
            self.gate = 1.0
        elif msg_type == rc.MT_TASK_STATE_CONFIG:
            mdf = rc.MDF_TASK_STATE_CONFIG()
            copy_from_msg(mdf, msg)
            self.idle_gateable = mdf.idle_gateable


    def get_combined_command(self):
        C = 1 - self.autoVelControlFraction # extrinsic fraction
        d = self.intrinsic_vel
        u = self.extrinsic_vel
        combined = C * u + (1 - C) * d
        print "--------------------------------------"
        print "C" + " ".join(["%0.2f" % (x) for x in C])
        print "d" + " ".join(["%0.2f" % (x) for x in d])
        print "u" + " ".join(["%0.2f" % (x) for x in u])
        print "+" + " ".join(["%0.2f" % (x) for x in combined])
        print "gain: ", self.gate
        print "gateable: ", self.idle_gateable
        return combined

    def send_output(self, sample_header):
        mdf = rc.MDF_COMPOSITE_MOVEMENT_COMMAND()
        mdf.tag = 'composite'
        vel = np.zeros_like(mdf.vel)
        vel[:] = self.get_combined_command()
        if self.idle_gateable == 1:
            vel[:8] *= self.gate
        mdf.vel[:] = vel
        mdf.sample_header = sample_header
        msg = CMessage(rc.MT_COMPOSITE_MOVEMENT_COMMAND)
        copy_to_msg(mdf, msg)
        self.mod.SendMessage(msg)

if __name__ == "__main__":
    parser = ArgumentParser(description = "Transform INPUT_DOF_DATA to "
                            "OPERATOR_MOVEMENT_COMMANDs")
    parser.add_argument(type=str, dest='config')
    parser.add_argument(type=str, dest='mm_ip', nargs='?', default='')
    args = parser.parse_args()
    print("Using config file=%s, MM IP=%s" % (args.config, args.mm_ip))
    sa = SimpleArbitrator(args.config, args.mm_ip)
