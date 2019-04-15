#!/usr/bin/python

import os
import appman
import confman
import subprocess as sp
from argparse import ArgumentParser
from ConfigParser import SafeConfigParser
from PyDragonfly import Dragonfly_Module, CMessage, copy_from_msg, copy_to_msg, MT_EXIT, MT_KILL
from time import sleep
import threading
import Dragonfly_config as rc
import re
import wx
import platform

from traits.api import HasTraits, Bool, Enum, Float, Str, List, File, \
     Button, String, Instance
from traitsui.api import Handler, View, Item, UItem, StatusItem, \
     Group, HGroup, VGroup, spring, EnumEditor, ButtonEditor, TextEditor, InstanceEditor
from traitsui.wx.animated_gif_editor import AnimatedGIFEditor
from output_stream import OutputStream


SRC_DIR = os.environ['BCI_MODULES']
CONFIG_DIR = os.environ['BCI_CONFIG']
DATA_DIR = os.environ['BCI_DATA']


def get_dirs(root, exclude=['attic']):
    dirs = []
    for x in os.listdir(root):
        if os.path.isdir(root + '/' + x) and (x[0] != '.'):
            dirs.append(x)
    dirs.sort()
    for dropper in exclude:
        if dropper in dirs:
            dirs.remove(dropper)
    return dirs


class Dragonfly_Read_Thread(threading.Thread):

    def __init__(self, mod, subs, data, callback, timeout):
        super(Dragonfly_Read_Thread, self).__init__()
        self.mod = mod
        self.subs = subs
        self.data = data
        self.callback = callback
        self.timeout = timeout
        self.stoprequest = threading.Event()
        self.result = 0

    def get_result(self):
        return self.result

    def stop(self):
        #print "Dragonfly_Read_Thread: Done, exiting.."
        self.stoprequest.set()

    def run(self):
        if self.timeout > 0:
            timeout = self.timeout

        while not self.stoprequest.isSet():
            msg = CMessage()
            rcv = self.mod.ReadMessage(msg, 0)
            if rcv == 1:
                if msg.GetHeader().msg_type in self.subs:
                    self.result = self.callback(msg, self.data)

                if self.result == 1:
                    self.stop()

            sleep(.010)
            if self.timeout > 0:
                timeout = timeout - 1
                if timeout == 0:
                    #print "Timout reached"
                    self.stoprequest.set()


class SessionManager(HasTraits):
    parent = Instance(wx.Frame)

    config_dirs = get_dirs(CONFIG_DIR, exclude=['default', 'attic'])
    configs = Enum(*config_dirs)

    #monkey_dirs = get_dirs(DATA_DIR, exclude=['VideoLoggerData', 'KingKong'])
    #monkeys = Enum(*monkey_dirs)
    monkeys = Enum(['KingKong', 'Sim'])

    calib_options = {1:'New Calibration', 2:'From Previous Session', 3:'From Specific Session'}
    calib_opts = Enum(calib_options.keys())

    calib_session = Str
    calib_session_list = List

    monkey_label = Str('Monkey:')
    config_label = Str('Configuration:')
    calib_label = Str('Calibration:')
    session_label = Str('Session:')

    rd_thread = Instance(Dragonfly_Read_Thread)

    monkeys_enabled = Bool(True)
    configs_enabled = Bool(True)
    calib_opts_enabled = Bool(True)
    calib_opts_visible = Bool(True)
    calib_session_enabled = Bool(True)
    calib_session_visible = Bool(False)

    start = Button()
    stop = Button()
    config = Button()
    modules = Button()
    kill = Button()

    statusbar_text = output = OutputStream(max_len=3000) #Instance(OutputStream) #Str("Ready")

    start_button_label = Str('Start')

    start_enabled = Bool(True)
    stop_enabled = Bool(True)
    config_enabled = Bool(True)
    modules_enabled = Bool(True)
    kill_enabled = Bool(True)

    session_num = None
    module_id_list = None
    host_id_list = None
    multi_task_config = Bool(False)
    multi_task_file = None

    subscriptions = [rc.MT_PING_ACK, rc.MT_APP_START_COMPLETE, rc.MT_SESSION_CONFIG,
                     rc.MT_EXIT_ACK, rc.MT_XM_END_OF_SESSION]

    busy_anim_file = File(SRC_DIR + '/ApplicationControl/busy.gif')
    appman_busy = Bool(False)
    error_icon_file = File(SRC_DIR + '/ApplicationControl/error.gif')
    error_flag = Bool(False)
    running_icon_file = File(SRC_DIR + '/ApplicationControl/running.gif')

    session_starting = Bool(False)
    session_running = Bool(False)
    session_ending = Bool(False)
    session_interrupted = Bool(False)

    #modman_frame = None

    view = View(VGroup(
                 HGroup(
                  HGroup(
                     VGroup(Item(name='config_label', show_label=False, style='readonly'),
                            Item(name='configs', label='Session', show_label=False, enabled_when='configs_enabled')),
                     VGroup(Item(name='monkey_label', show_label=False, style='readonly'),
                            Item(name='monkeys', label='Monkey', show_label=False, enabled_when='monkeys_enabled')),
                     VGroup(Item(name='calib_label', show_label=False, style='readonly'),
                            Item(name='calib_opts', editor=EnumEditor(values=calib_options), enabled_when='calib_opts_enabled', label='CalibOpt', show_label=False),
                            visible_when='calib_opts_visible==True'),
                     VGroup(Item(name='session_label', show_label=False, style='readonly'),
                            Item(name='calib_session', width=175, editor = EnumEditor(name = 'calib_session_list'), enabled_when='calib_session_enabled', show_label=False),
                            visible_when='calib_session_visible==True'),
                     springy=True),

                     HGroup(
                       Item(name='start', editor=ButtonEditor(label_value='start_button_label'), show_label=False, enabled_when='start_enabled'),
                       Item(name='stop', show_label=False, enabled_when='stop_enabled', visible_when='stop_visible==True'),
                       Item(name='kill', show_label=False, enabled_when='kill_enabled'),
                       Item(name='config', show_label=False, enabled_when='config_enabled'),
                       #Item(name='modules', show_label=False, enabled_when='modules_enabled')
                     ),
                    ),
                    HGroup(Item(name='busy_anim_file', editor=AnimatedGIFEditor(), show_label=False, visible_when='appman_busy==True'),
                         Item(name='running_icon_file', editor=AnimatedGIFEditor(), show_label=False, visible_when='session_running==True'),
                         Item(name='error_icon_file', editor=AnimatedGIFEditor(), show_label=False, visible_when='error_flag==True'),
                         Item('statusbar_text', editor=InstanceEditor(), show_label=False, resizable=True, height=100, style='custom')) #springy=True,
                         #Item(name='statusbar_text', show_label=False, style='custom', resizable=True))
                 ))

    #def __init__(self, **traits):
    #    HasTraits.__init__(self, **traits)
    def __init__(self):
        super(SessionManager, self).__init__()

        last_app = appman.get_last()
        print last_app
        if last_app is not None:
            self.configs = last_app
        else:
            appman.write_last(self.configs)
            
        self.check_multi_task_config()
        self.get_last_subject()


    def _modules_fired(self):
        import modman
        self.modman_frame = modman.MainWindow(self.parent, -1, self.statusbar_text, self.modman_closing)

    def modman_closing(self):
        print "modman exiting..."
        self.modman_frame = None

    #def modman_update(self):
    #    if self.modman_frame is not None:
    #        self.modman_frame.update_text(status)

    def update_status(self, status):
        self.statusbar_text.write(status + '\n')
        print "%s" % status

    def _configs_changed(self):
        self.check_multi_task_config()
        self.get_last_subject()

    def _monkeys_changed(self):
        self.update_calib_sessions()

    def _calib_opts_changed(self):
        self.update_calib_sessions()


    def get_last_subject(self):
        last_subject_file = CONFIG_DIR + '/' + self.configs + '/last_subject.txt'
        if os.path.isfile(last_subject_file):
            f = open(last_subject_file, 'r')
            self.monkeys = f.read()
            f.close()

    def check_multi_task_config(self):
        self.multi_task_file = CONFIG_DIR + '/' + self.configs + '/multi_task.config'
        if os.path.isfile(self.multi_task_file):
            self.multi_task_config = True
            self.calib_opts_visible = False
            self.calib_session_visible = False
        else:
            self.multi_task_config = False
            self.calib_opts_visible = True
            self.multi_task_file = None
            self.update_calib_sessions()


    def get_calib_sessions(self):
        try:
            raw_folder = os.path.join(DATA_DIR, self.monkeys, "Raw")
            self.calib_session_list = get_dirs(raw_folder)
        except:
            self.calib_session = ""
            self.calib_session_list = []

    def update_calib_sessions(self):
        if (self.calib_options[self.calib_opts] == "From Previous Session") or \
           (self.calib_options[self.calib_opts] == "From Specific Session"):
            self.get_calib_sessions()

            if not self.calib_session_list:
                self.start_enabled = False
                self.calib_session_visible = False
            else:
                self.start_enabled = True
                self.calib_session_visible = True

                print self.calib_session

                if (self.calib_options[self.calib_opts] == "From Specific Session"):
                    self.calib_session_enabled = True

                    if self.calib_session not in self.calib_session_list:
                        print "here"
                        self.calib_session = self.calib_session_list[-1]

                else:
                    self.calib_session_enabled = False
                    self.calib_session = self.calib_session_list[-1]

        else:
            self.start_enabled = True
            self.calib_session_visible = False


    def connect(self, server):
        self.mod = Dragonfly_Module(0, 0)
        self.mod.ConnectToMMM(server)
        for sub in self.subscriptions:
            self.mod.Subscribe(sub)
        self.mod.SendModuleReady()
        print "Connected to Dragonfly at", server


    def disconnect(self):
        self.mod.DisconnectFromMMM()


    def proc_modules_PING_ACK(self, msg, data):
        result = 0
        mdf = rc.MDF_PING_ACK()
        copy_from_msg(mdf, msg)

        if mdf.module_name in data['module_list']:
            data['module_id_list'][msg.GetHeader().src_mod_id] = mdf.module_name
            data['module_list'].remove(mdf.module_name)

        if not data['module_list']:
            result = 1

        return result


    def proc_hosts_PING_ACK(self, msg, data):
        result = 0

        mdf = rc.MDF_PING_ACK()
        copy_from_msg(mdf, msg)

        module_info = mdf.module_name.split(':')
        
        print module_info
        
        if (module_info[0] == "AppStarter") and (module_info[1] in data['host_list']):
            data['host_id_list'][msg.GetHeader().src_mod_id] = module_info[1]
            data['host_list'].remove(module_info[1])

        if not data['host_list']:
            result = 1

        return result


    def proc_APP_START_COMPLETE(self, msg, data):
        result = 0

        module_id = msg.GetHeader().src_mod_id

        if module_id in data['host_id_list']:
            data['host_id_list'].remove(module_id)

        if not data['host_id_list']:
            result = 1

        return result


    def proc_modules_EXIT_ACK(self, msg, data):
        result = 0

        if msg.GetHeader().src_mod_id in data['module_id_list']:
            del data['module_id_list'][msg.GetHeader().src_mod_id]
        else:
            print "Unexpected module id: {0}".format(msg.GetHeader().src_mod_id)

        if not data['module_id_list']:
            result = 1

        return result

    def proc_MSG_RECEIVED(self, msg, data):
        return 1

    def proc_SESSION_CONFIG(self, msg, data):
        mdf = rc.MDF_SESSION_CONFIG()
        copy_from_msg(mdf, msg)
        m = re.match(".+\.[0]*(\d+)$", mdf.data_dir)
        if m:
            data['session_num'] = m.group(1)
        else:
            data['session_num'] = '???'
        return 1

    def subscribe_to_list(self, subs):
        for sub in subs:
            self.mod.Subscribe(sub)
        return subs

    def send_PING(self, module_name):
        mdf = rc.MDF_PING()
        mdf.module_name = module_name
        msg = CMessage(rc.MT_PING)
        copy_to_msg(mdf, msg)
        #return msg
        self.mod.SendMessage(msg);

    def send_APP_START(self, config):
        mdf = rc.MDF_APP_START()
        mdf.config = config
        msg = CMessage(rc.MT_APP_START)
        copy_to_msg(mdf, msg)
        self.mod.SendMessage(msg)

    def disable_gui(self):
        self.monkeys_enabled = False
        self.calib_session_enabled = False
        self.calib_opts_enabled = False
        self.configs_enabled = False

    def enable_gui(self):
        self.monkeys_enabled = True
        self.calib_opts_enabled = True
        self.configs_enabled = True

        if self.calib_options[self.calib_opts] != "From Previous Session":
            self.calib_session_enabled = True

    def wait_for_dragonfly_thread(self, raise_exception=True):
        while(self.rd_thread.isAlive()):
            wx.Yield()
            if (self.session_starting == False) and (self.session_ending == False) and \
               (self.session_running == False):
                self.rd_thread.stop()
                if raise_exception == True:
                    raise RuntimeError('Cancelled')
            sleep(0.010)

    def _config_fired(self):
        #self.modman_frame = None

        try:
            if self.multi_task_config == True:
                root_files = {'MT' : 'multi_task.config'}
            else:
                root_files = {'XM' : 'XM.config', 'appman' : 'appman.conf'}

            frame = confman.MainWindow(self.parent, -1, CONFIG_DIR, self.configs, root_files)

        except (ValueError, IOError) as e:
            self.update_status("%s" % e)
            self.error_flag = True


    def _kill_fired(self):
        dlg = wx.MessageDialog(self.parent,
            "Do you really want to kill all running modules?",
            "Confirm Kill", wx.OK|wx.CANCEL|wx.ICON_QUESTION)
        result = dlg.ShowModal()
        dlg.Destroy()
        if result == wx.ID_OK:
            self.mod.SendSignal(MT_KILL)
            self.error_flag = False
            self.start_enabled = True
            self.module_id_list = None
            #self.kill_enabled = False
            self.update_status("Modules killed")


    def do_stop_modules(self):
        try:
            self.disable_gui()
            self.appman_busy = True
            self.error_flag = False
            self.start_enabled = False
            self.session_running = False

            self.update_status("Stopping modules...")

            self.session_ending = True

            # prep Dragonfly read thread
            data = {'module_id_list': self.module_id_list}
            self.rd_thread = Dragonfly_Read_Thread(self.mod, [rc.MT_EXIT_ACK], data, self.proc_modules_EXIT_ACK, 300)
            self.rd_thread.start()

            appman.stop_modules(self.mod)

            self.wait_for_dragonfly_thread()

            result = self.rd_thread.get_result()
            if result == 0:
                self.kill_enabled = True
                self.update_status("Some modules did not respond: %s" % (', '.join(map(str, self.module_id_list.values()))))
                raise RuntimeError("!! Click KILL to close any modules still running !!")

            if self.session_num is not None:
                self.update_status("Session #%s is terminated" % self.session_num)
            else:
                self.update_status("Session is terminated")

            self.error_flag = False
            self.start_enabled = True

        except RuntimeError, e:
            self.update_status("%s" % e)
            self.error_flag = True

        finally:
            self.enable_gui()
            self.appman_busy = False
            self.session_ending = False
            self.module_id_list = None


    def _stop_fired(self):
        if self.module_id_list is None:
            appman.stop_modules(self.mod)
            self.error_flag = False
            self.start_enabled = True

        #elif (self.multi_task_config == True) and (self.session_running == True):
        elif (self.session_running == True):
            self.session_running = False
            self.session_interrupted = True

        else:
            self.do_stop_modules()


    def _start_fired(self):
        # advance to the next iteration of the multi_task
        if (self.multi_task_config == True) and (self.session_running == True):
            self.session_running = False

        # cancel starting session
        elif self.session_starting == True:
            self.session_starting = False

        # start new session
        else:
            try:
                self.disable_gui()
                self.appman_busy = True
                self.error_flag = False
                self.start_button_label = 'Cancel'
                self.stop_enabled = False
                #self.kill_enabled = False
                self.session_starting = True
                self.session_num = None
                self.session_interrupted = False

                self.statusbar_text.reset()
                self.update_status("Starting new session...")

                # prepare session parameters
                subject = self.monkeys
                config_list = []
                calib_session_id_list = []
                num_reps_list =[]

                self.update_calib_sessions()

                if self.multi_task_config == True:
                    parser = SafeConfigParser()
                    parser.read(self.multi_task_file)
                    config = dict(parser.items('config'))

                    config_list = re.sub(r"[\n\r]+", '', config['config_names']).split(',')
                    calib_session_id_list = re.sub(r"[\n\r]+", '', config['calibration_session_ids']).split(',')
                    num_reps_list = re.sub(r"[\n\r]+", '', config['num_reps']).split(',')

                else:
                    config_list.append(self.configs)
                    num_reps_list.append(0)

                    if (self.calib_options[self.calib_opts] == "From Specific Session"):
                        m = re.match("(\w+)\.DK\.[0]+(\d+)", self.calib_session)
                        calib_session_id = int(m.group(2))
                    elif (self.calib_options[self.calib_opts] == "From Previous Session"):
                        m = re.match("(\w+)\.DK\.[0]+(\d+)", self.calib_session_list[-1])
                        calib_session_id = int(m.group(2))
                    else:
                        calib_session_id = 0
                    calib_session_id_list.append(calib_session_id)


                #done = False       # put "done" back if you want to repeat forever
                #while not done:
                for c, config in enumerate(config_list):

                    hosts = appman.get_host_modules(config)

                    # ------------------------------------------------------------------------
                    # PING all AppStarter modules
                    # ------------------------------------------------------------------------
                    self.update_status("Pinging AppStarter modules...")

                    host_list = hosts.keys()
                    self.host_id_list = {};

                    print host_list

                    # prep Dragonfly read thread
                    data = {'host_list': host_list, 'host_id_list': self.host_id_list}
                    self.rd_thread = Dragonfly_Read_Thread(self.mod, [rc.MT_PING_ACK], data, self.proc_hosts_PING_ACK, 400)
                    self.rd_thread.start()

                    self.send_PING("AppStarter")

                    self.wait_for_dragonfly_thread()

                    result = self.rd_thread.get_result()
                    if result == 0:
                        raise RuntimeError('Did not receive response from AppStarter on hosts: %s' % (', '.join(map(str, host_list))))


                    # ------------------------------------------------------------------------
                    # Send APP_START signal to AppStarter modules
                    # ------------------------------------------------------------------------
                    self.update_status("Starting modules...")

                    # prep Dragonfly read thread
                    data = {'host_id_list': self.host_id_list.keys()}
                    self.rd_thread = Dragonfly_Read_Thread(self.mod, [rc.MT_APP_START_COMPLETE], data, self.proc_APP_START_COMPLETE, 300)
                    self.rd_thread.start()

                    self.send_APP_START(config)

                    self.wait_for_dragonfly_thread()

                    result = self.rd_thread.get_result()
                    if result == 0:
                        raise RuntimeError('Did not receive APP_START_COMPLETE from all hosts')


                    # ------------------------------------------------------------------------
                    # PING all modules, make sure they are all running and responding
                    # ------------------------------------------------------------------------
                    self.update_status("Pinging modules..")

                    num_retries = 50
                    self.module_id_list = {};
                    module_list = []
                    for h in hosts.keys():
                        module_list = module_list + hosts[h]

                    for r in reversed(range(num_retries)):
                        # prep Dragonfly read thread
                        data = {'module_list': module_list, 'module_id_list': self.module_id_list}
                        self.rd_thread = Dragonfly_Read_Thread(self.mod, [rc.MT_PING_ACK], data, self.proc_modules_PING_ACK, 75)
                        self.rd_thread.start()

                        self.send_PING("*")

                        self.wait_for_dragonfly_thread()

                        result = self.rd_thread.get_result()
                        if result == 0:
                            if r == 0:
                                raise RuntimeError("Did not receive response from modules: %s" % (', '.join(map(str, module_list))))
                        else:
                            break

                    # ------------------------------------------------------------------------
                    # wait for SESSION_CONFIG from executive if it's in appman.conf
                    # ------------------------------------------------------------------------
                    for m in self.module_id_list.values():
                        matched = re.search('^(executive)', m)
                        if matched:
                            break

                    if matched:
                        self.update_status("Waiting for SESSION_CONFIG from executive...")

                        # prep Dragonfly read thread
                        data = {'session_num': ''}
                        self.rd_thread = Dragonfly_Read_Thread(self.mod, [rc.MT_SESSION_CONFIG], data, self.proc_SESSION_CONFIG, -1)
                        self.rd_thread.start()

                        # send the executive extra params it needs
                        num_reps = int(num_reps_list[c])
                        calib_sess_id = int(calib_session_id_list[c])

                        mdf = rc.MDF_XM_START_SESSION()
                        mdf.subject_name = subject
                        if num_reps > 0:
                            mdf.num_reps = num_reps
                        if calib_sess_id > 0:
                            mdf.calib_session_id = calib_sess_id
                            mdf.load_calibration = 1
                        msg = CMessage(rc.MT_XM_START_SESSION)
                        copy_to_msg(mdf, msg)
                        self.mod.SendMessage(msg)

                        self.wait_for_dragonfly_thread()

                        result = self.rd_thread.get_result()
                        if result == 0:
                            raise RuntimeError('Did not receive SESSION_CONFIG from executive')

                        self.session_num = self.rd_thread.data['session_num']

                    #
                    # All steps were successful...
                    #
                    appman.write_last(self.configs)

                    if self.multi_task_config == True:
                        self.update_status("Multi task session: Session #%s, Config '%s', NumReps %s" % (self.session_num, config, num_reps_list[c]))

                        self.disable_gui()
                        self.session_running = True
                        #
                        self.appman_busy = False
                        self.start_button_label = 'Next'
                        self.session_starting = False
                        self.stop_enabled = True

                        # wait for session to end or user to hit cancel
                        self.rd_thread = Dragonfly_Read_Thread(self.mod, [rc.MT_XM_END_OF_SESSION], None, self.proc_MSG_RECEIVED, -1)
                        self.rd_thread.start()
                        self.wait_for_dragonfly_thread(False)

                        # stop all modules and move onto the next iteration
                        self.do_stop_modules()

                        if self.session_interrupted == True:
                            #done = True
                            self.update_status("Multi task session is terminated")
                            break;

                        # reinit variables for another iteration
                        self.appman_busy = True
                        self.session_running = False
                        self.session_starting = True
                        self.start_button_label = 'Cancel'
                        self.stop_enabled = False
                        #self.kill_enabled = False
                        self.session_num = None

                    else:
                        #done = True

                        if self.session_num is None:
                            self.update_status("Session is running")
                        else:
                            self.update_status("Session #%s is running" % self.session_num)

                        self.disable_gui()
                        self.session_running = True
                        self.start_enabled = False
                        self.appman_busy = False
                        self.session_starting = False
                        self.stop_enabled = True

                        # wait for session to end or user to hit stop
                        self.rd_thread = Dragonfly_Read_Thread(self.mod, [rc.MT_XM_END_OF_SESSION], None, self.proc_MSG_RECEIVED, -1)
                        self.rd_thread.start()
                        self.wait_for_dragonfly_thread(False)

                        if self.session_interrupted == True:
                            #done = True
                            break;

                if self.multi_task_config == True:
                    self.update_status("Multi task session is completed, terminating..")
                else:
                    if self.session_interrupted == False:
                        self.update_status("Session is completed, terminating..")

                    self.do_stop_modules()


            except (RuntimeError, ValueError) as e:
                self.update_status("%s" % e)
                self.error_flag = True

                if e.message == "Cancelled":
                    self.update_status("!! Click STOP or KILL to close any modules that already started running ..")
                    self.start_enabled = False
                    self.kill_enabled = True

            finally:
                self.enable_gui()
                self.appman_busy = False
                self.start_button_label = 'Start'
                self.session_starting = False
                self.stop_enabled = True
                self.session_running = False


class MainWindow(wx.Frame):
    def __init__(self, mm_ip): #, sm):
        wx.Frame.__init__(self, None, -1, 'Application Manager', wx.DefaultPosition, \
                          wx.DefaultSize, wx.CAPTION|wx.CLOSE_BOX|wx.SYSTEM_MENU|wx.RESIZE_BORDER|wx.MINIMIZE_BOX)
        self.sm = SessionManager()
        self.sm.connect(mm_ip)
        self.sm.parent = self
        self.sm.edit_traits(parent=self, kind='subpanel')
        self.Fit()
        self.Show(True)
        self.Bind(wx.EVT_CLOSE, self.OnClose)

    def OnClose(self, event):
        if self.sm.session_running == True:
            dlg = wx.MessageDialog(self,
                "There is a session running. Do you really want to exit?",
                "Confirm Exit", wx.OK|wx.CANCEL|wx.ICON_QUESTION)
            result = dlg.ShowModal()
            dlg.Destroy()
            if result == wx.ID_OK:
                self.doClose()
        else:
            self.doClose()

    def doClose(self):
        self.Destroy()
        self.sm.disconnect()



if __name__ == "__main__":
    parser = ArgumentParser(description = "Starts session modules")
    parser.add_argument(type=str, dest='mm_ip', nargs='?', default='127.0.0.1:7111')
    args = parser.parse_args()
    print("Using MM IP=%s" % (args.mm_ip))

    app = wx.App(False)
    frame = MainWindow(args.mm_ip)
    app.MainLoop()


