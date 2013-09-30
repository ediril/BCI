import copy
import numpy as np
import Dragonfly_config as rc
from argparse import ArgumentParser
from ConfigParser import SafeConfigParser
from PyDragonfly import Dragonfly_Module, CMessage, copy_to_msg, copy_from_msg, MT_EXIT
import Dragonfly_config as rc
from time import time
from dragonfly_utils import respond_to_ping


class TrialStatus(object):

    def __init__(self, config_file, server):
        self.load_config(config_file)
        self.msg_nums = [eval('rc.MT_%s' % (x)) for x in self.msg_types]
        self.trial_sync = 0
        self.num_trials = 0
        self.num_trials_postcalib = 0
        self.num_trial_started_postcalib = 0
        self.num_trial_successful_postcalib = 0
        self.num_trial_givenup_postcalib = 0
        self.success_window = []
        self.started_window = []
        self.givenup_window = []
        self.shadow_num_trial_started_postcalib = 0
        self.shadow_num_trial_successful_postcalib = 0
        self.shadow_num_trial_givenup_postcalib = 0
        self.shadow_success_window = []
        self.shadow_started_window = []
        self.shadow_givenup_window = []

        self.last_time = time()
        self.setup_dragonfly(server)

        #self.rewards_given = 0
        #self.prev_rewards_given = 0
        self.run()

    def load_config(self, config_file):
        self.config = SafeConfigParser()
        self.config.read(config_file)
        self.msg_types = ['END_TASK_STATE', 'SESSION_CONFIG', 'EM_DECODER_CONFIGURATION']  #'GIVE_REWARD'
        self.msg_types.sort()
        self.window_len = self.config.getint('general', 'window_len')
        self.task_state_codes = {}
        for k, v in self.config.items('task state codes'):
            self.task_state_codes[k] = int(v)

    def setup_dragonfly(self, server):
        self.mod = Dragonfly_Module(0, 0)
        self.mod.ConnectToMMM(server)
        self.mod.Subscribe(MT_EXIT)
        self.mod.Subscribe(rc.MT_PING)
        for i in self.msg_types:
            self.mod.Subscribe(eval('rc.MT_%s' % (i)))
        self.mod.SendModuleReady()
        print "Connected to RTMA at", server

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
                    respond_to_ping(self.mod, msg, 'TrialStatus')
                else:
                    self.process_message(msg)

            this_time = time()
            self.diff_time = this_time - self.last_time
            if self.diff_time > 1.:
                self.last_time = this_time
                self.write()

    def reset_counters(self):
        self.trial_sync = 0
        self.num_trials_postcalib = 0
        self.num_trial_started_postcalib = 0
        self.num_trial_givenup_postcalib = 0
        self.num_trial_successful_postcalib = 0
        self.shadow_num_trial_started_postcalib = 0
        self.shadow_num_trial_givenup_postcalib = 0
        self.shadow_num_trial_successful_postcalib = 0
        self.started_window = []
        self.givenup_window = []
        self.success_window = []
        self.shadow_started_window = []
        self.shadow_givenup_window = []
        self.shadow_success_window = []


    def process_message(self, in_msg):
        msg_type = in_msg.GetHeader().msg_type
        if not msg_type in self.msg_nums:
            return

        # SESSION_CONFIG => start of session
        if msg_type == rc.MT_SESSION_CONFIG:
            self.num_trials = 0
            self.reset_counters()

        # EM_DECODER_CONFIGURATION => end of an adaptation round
        elif msg_type == rc.MT_EM_DECODER_CONFIGURATION:
            self.reset_counters()

        # END_TASK_STATE => end of a task
        elif msg_type == rc.MT_END_TASK_STATE:
            mdf = rc.MDF_END_TASK_STATE()
            copy_from_msg(mdf, in_msg)

            # need to know:
            #    begin task state code
            #    final task state code
            #    intertrial state code

            if (mdf.id == 1):
                self.trial_sync = 1
                self.shadow_started_window.append(0)

            if (mdf.id == self.task_state_codes['begin']) & (mdf.outcome == 1):
                if self.trial_sync:
                    #print "*** trial started ***"
                    #self.rewards_given += 1
                    self.shadow_num_trial_started_postcalib += 1
                    self.shadow_success_window.append(0)
                    self.shadow_givenup_window.append(0)
                    self.shadow_started_window[-1] = 1

            if mdf.reason == "JV_IDLE_TIMEOUT":
                if self.trial_sync:
                    self.shadow_num_trial_givenup_postcalib += 1
                    self.shadow_givenup_window[-1] = 1

            if (mdf.id == self.task_state_codes['final']) & (mdf.outcome == 1):
                if self.trial_sync:
                    #print "*** trial complete and successful"
                    self.shadow_num_trial_successful_postcalib += 1
                    self.shadow_success_window[-1] = 1

            if (mdf.id == self.task_state_codes['intertrial']):
                if self.trial_sync:
                    # do end-of-trial stuff here
                    self.num_trials += 1
                    self.num_trials_postcalib += 1
                    self.num_trial_started_postcalib = self.shadow_num_trial_started_postcalib
                    self.num_trial_successful_postcalib = self.shadow_num_trial_successful_postcalib
                    self.num_trial_givenup_postcalib = self.shadow_num_trial_givenup_postcalib

                    if len(self.shadow_success_window) > self.window_len:
                        self.shadow_success_window.pop(0)

                    if len(self.shadow_givenup_window) > self.window_len:
                        self.shadow_givenup_window.pop(0)

                    if len(self.shadow_started_window) > self.window_len:
                        self.shadow_started_window.pop(0)

                    self.success_window = copy.deepcopy(self.shadow_success_window)
                    self.started_window = copy.deepcopy(self.shadow_started_window)
                    self.givenup_window = copy.deepcopy(self.shadow_givenup_window)


    def write(self):
        percent_start = percent_success = percent_givenup = 0
        percent_success_window = num_success_window = 0
        percent_started_window = num_started_window = 0
        percent_givenup_window = num_givenup_window = 0

        if self.num_trials_postcalib > 0:
            percent_start = 100 * self.num_trial_started_postcalib / self.num_trials_postcalib
            percent_givenup = 100 * self.num_trial_givenup_postcalib / self.num_trials_postcalib
            percent_success = 100 * self.num_trial_successful_postcalib / self.num_trials_postcalib

        if len(self.success_window) > 0:
            num_success_window = np.sum(self.success_window)
            percent_success_window = 100 * num_success_window / len(self.success_window)

        if len(self.started_window) > 0:
            num_started_window = np.sum(self.started_window)
            percent_started_window = 100 * num_started_window / len(self.started_window)

        if len(self.givenup_window) > 0:
            num_givenup_window = np.sum(self.givenup_window)
            percent_givenup_window = 100 * num_givenup_window / len(self.givenup_window)

        print "All trials : %d\n" % (self.num_trials_postcalib)
        print "Started trials  : %d (%0.0f%%)"  % (self.num_trial_started_postcalib, percent_start)
        print "Given-up trials : %d (%0.0f%%)" % (self.num_trial_givenup_postcalib, percent_givenup)
        print "Success trials  : %d (%0.0f%%)\n" % (self.num_trial_successful_postcalib, percent_success)
        print "Started trials out of last %d\t\t: %d (%0.0f%%)" % (len(self.started_window), num_started_window, percent_started_window)
        print "Given-up trials out of last started %d\t: %d (%0.0f%%)" % (len(self.givenup_window), num_givenup_window, percent_givenup_window)
        print "Success trials out of last started %d\t: %d (%0.0f%%)" % (len(self.success_window), num_success_window, percent_success_window)
        print ""

if __name__ == "__main__":
    parser = ArgumentParser(description = "Display information about trial status")
    parser.add_argument('config', metavar='config_file', type=str)
    parser.add_argument(type=str, dest='mm_ip', nargs='?', default='')
    args = parser.parse_args()
    print("Using config file=%s, MM IP=%s" % (args.config, args.mm_ip))
    mw = TrialStatus(args.config, args.mm_ip)
