#!/usr/bin/python

import os
import platform
from argparse import ArgumentParser
from PyDragonfly import Dragonfly_Module, CMessage, copy_from_msg, copy_to_msg, MT_EXIT, MT_KILL
import PyDragonfly
import Dragonfly_config as rc
from ConfigParser import SafeConfigParser
import appman
import platform

class AppStarter(object):
   
    def __init__(self, server):    
        self.setup_dragonfly(server)
        self.run()

    def setup_dragonfly(self, server):
        self.host_name = platform.uname()[1]
        self.host_os = platform.system()
        
        self.mod = Dragonfly_Module(0, 0)
        self.mod.ConnectToMMM(server)
        self.mod.Subscribe(rc.MT_APP_START)
        self.mod.Subscribe(rc.MT_PING)
        self.mod.Subscribe(MT_EXIT)
        self.mod.Subscribe(MT_KILL)

        self.mod.SendModuleReady()
        print "Connected to Dragonfly at", server

    # this one is slightly different than the one in Common/python, leave this one here
    def respond_to_ping(self, msg, module_name):
        #print "PING received for '{0}'".format(p.module_name)

        dest_mod_id = msg.GetHeader().dest_mod_id
        p = rc.MDF_PING()
        copy_from_msg(p, msg)

        if (p.module_name.lower() == module_name.lower()) or (p.module_name == "*") or \
            (dest_mod_id == self.mod.GetModuleID()):
            mdf = rc.MDF_PING_ACK()
            mdf.module_name = module_name + ":" + self.host_name # + ":" + self.host_os
            msg_out = CMessage(rc.MT_PING_ACK)
            copy_to_msg(mdf, msg_out)
            self.mod.SendMessage(msg_out)
            
    def run(self):
        while True:
            msg = CMessage()
            rcv = self.mod.ReadMessage(msg, 0.1)
            if rcv == 1:
                msg_type = msg.GetHeader().msg_type

                if msg_type == rc.MT_APP_START:

                    try:
                        mdf = rc.MDF_APP_START()
                        copy_from_msg(mdf, msg) 
                        config = mdf.config
                        
                        print "Config: %s" % config

                        # -- to do --
                        # get a list of all modules in appman.conf for this host
                        # see if any of the modules above are already/still running
                        # start non-running modules
                        # -- to do --
                        
                        print "Creating scripts"
                        appman.create_script(config, self.host_name)
                        print "Starting modules on host: %s" % self.host_name
                        appman.run_script(self.host_name)

                        self.mod.SendSignal(rc.MT_APP_START_COMPLETE)

                    except Exception, e:
                        print "ERROR: %s" % (e)
                    
                elif msg_type == rc.MT_PING:
                    print 'got ping'
                    self.respond_to_ping(msg, 'AppStarter')
                    
                # we use this msg to stop modules individually
                elif msg_type == MT_EXIT:
                    print 'got exit'
                    
                elif msg_type == MT_KILL:
                    print 'got kill'
                    appman.kill_modules()

        
if __name__ == "__main__":
    parser = ArgumentParser(description = "Starts session modules")
    parser.add_argument(type=str, dest='mm_ip', nargs='?', default='')
    args = parser.parse_args()
    
    if args.mm_ip == '':
        args.mm_ip = '127.0.0.1:7111'
        
    print("Using MM IP=%s" % (args.mm_ip))
    itm = AppStarter(args.mm_ip)
