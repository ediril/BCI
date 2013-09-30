#!/usr/bin/python

from PyDragonfly import Dragonfly_Module, CMessage, copy_from_msg, copy_to_msg, MT_EXIT
import Dragonfly_config as rc
from dragonfly_utils import respond_to_ping

from argparse import ArgumentParser
from ConfigParser import SafeConfigParser
import numpy as np
import sys
import copy

import matplotlib
matplotlib.use('Qt4Agg')
from matplotlib.backends.backend_qt4agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.figure import Figure
import matplotlib.patches as patches
from matplotlib.patches import Polygon
from matplotlib.ticker import FormatStrFormatter, MaxNLocator, MultipleLocator

from PyQt4 import QtCore, QtGui

#QtCore.pyqtRemoveInputHook(); import ipdb; ipdb.set_trace()


def nan_array(shape, dtype=float):
    a = np.empty(shape, dtype)
    a.fill(np.NAN)
    return a


class MplCanvas(FigureCanvas):
    def __init__(self, parent=None, width=8, height=10, dpi=80):
        self.parent = parent
        self.redraw_yticks = True

        self.figure = Figure(figsize=(width, height), dpi=dpi, facecolor='#bbbbbb')
        FigureCanvas.__init__(self, self.figure)

        self.setParent(parent)

        FigureCanvas.setSizePolicy(self,
                                   QtGui.QSizePolicy.Expanding,
                                   QtGui.QSizePolicy.Expanding)
        FigureCanvas.updateGeometry(self)


    def run(self, config_file, server):
        self.mod = Dragonfly_Module(0, 0)
        self.mod.ConnectToMMM(server)
        self.msg_types = ['END_TASK_STATE', 'SESSION_CONFIG', 'EM_DECODER_CONFIGURATION']
        self.msg_types.sort()
        self.mod.Subscribe(MT_EXIT)
        self.mod.Subscribe(rc.MT_PING)
        for i in self.msg_types:
            self.mod.Subscribe(eval('rc.MT_%s' % (i)))
        self.mod.SendModuleReady()
        print "Connected to Dragonfly at", server
        print "mod_id = ", self.mod.GetModuleID()

        self.config_file = config_file
        self.load_config()
        self.init_vars()
        self.init_plot()
        self.init_legend()

        timer = QtCore.QTimer(self)
        QtCore.QObject.connect(timer, QtCore.SIGNAL("timeout()"), self.timer_event)
        timer.start(10)


    def init_vars(self):
        self.num_trials = 0
        self.reset_counters()
        self.msg_cnt = 0
        self.console_disp_cnt = 0


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
        self.percent_start = 0
        self.percent_success = 0
        self.percent_givenup = 0
        self.hist_narrow_SUR = []
        self.hist_narrow_GUR = []
        self.hist_narrow_STR = []

        self.hist_wide_SUR = []
        self.hist_wide_GUR = []
        self.hist_wide_STR = []

    def update_gui_label_data(self):
        self.parent.GALL.setText("%d" % self.num_trials_postcalib)
        self.parent.GSTR.setText("%d" % self.num_trial_started_postcalib) 
        self.parent.GGUR.setText("%d" % self.num_trial_givenup_postcalib) 
        self.parent.GSUR.setText("%d" % self.num_trial_successful_postcalib) 


    #def reload_config(self):
    #    self.load_config()
    #    for ax in self.figure.axes:
    #        self.figure.delaxes(ax)
    #    self.figure.clear()
    #    self.draw()
    #    self.init_plot(True)
    #    self.init_legend()
    #    self.redraw_yticks = True

    #def load_config(self):
    #    self.config = ConfigObj(self.config_file, unrepr=True)

    def load_config(self):
        self.config = SafeConfigParser()
        self.config.read(self.config_file)
        self.window_narrow = self.config.getint('general', 'window_narrow')
        self.window_wide = self.config.getint('general', 'window_wide')
        self.task_state_codes = {}
        for k, v in self.config.items('task state codes'):
            self.task_state_codes[k] = int(v)


    def init_plot(self, clear=False):
        self.nDims = 3

        self.figure.subplots_adjust(bottom=.05, right=.98, left=.08, top=.98, hspace=0.07)

        self.ax = []
        self.old_size = []
        self.ax_bkg = []
        self.lines = []

        ax = self.figure.add_subplot(1,1,1)

        box = ax.get_position()
        ax.set_position([box.x0, box.y0, box.width * 0.85, box.height])

        self.reset_axis(ax)
        self.draw()

        bbox_width = ax.bbox.width
        bbox_height = ax.bbox.height
        if clear == True:   # force to redraw
            bbox_width = 0
            bbox_height = 0

        self.old_size.append( (bbox_width, bbox_height) )
        self.ax_bkg.append(self.copy_from_bbox(ax.bbox))

        self.colors = ['k', 'r', 'g']
        self.styles = ['-', '-', '--']

        for d in range(self.nDims):
            for m in range(3):
                line, = ax.plot([], [], self.colors[d]+self.styles[m], lw=1.5, aa=True, animated=True)
                line.set_ydata([0, 0])
                line.set_xdata([0, 1])
                self.lines.append(line)
                self.draw()

        self.ax.append(ax)


    def reset_axis(self, ax): #, label):
        ax.grid(True)
        ax.set_ylim(-1, 101)
        ax.set_autoscale_on(False)
        ax.get_xaxis().set_ticks([])
        for tick in ax.get_yticklabels():
            tick.set_fontsize(9)


    def init_legend(self):
        legnd = []

        for d in range(self.nDims):
            for m in range(3):
                line = matplotlib.lines.Line2D([0,0], [0,0], color=self.colors[d], ls=self.styles[m], lw=1.5)
                legnd.append(line)

        legend_text = []
        legend_text.append('STR')
        legend_text.append('STR%d' % self.window_narrow)
        legend_text.append('STR%d' % self.window_wide)
        legend_text.append('GUR')
        legend_text.append('GUR%d' % self.window_narrow)
        legend_text.append('GUR%d' % self.window_wide)
        legend_text.append('SUR')
        legend_text.append('SUR%d' % self.window_narrow)
        legend_text.append('SUR%d' % self.window_wide)

        self.figure.legend(legnd, legend_text, loc = 'right', bbox_to_anchor=(1, 0.5),
                           frameon=False, labelspacing=1.5, prop={'size':'11'})
        self.draw()


    def timer_event(self):
        done = False
        while not done:
            msg = CMessage()
            rcv = self.mod.ReadMessage(msg, 0)
            if rcv == 1:
                msg_type = msg.GetHeader().msg_type

                # SESSION_CONFIG => start of session
                if msg_type == rc.MT_SESSION_CONFIG:
                    #self.msg_cnt += 1
                    self.num_trials = 0
                    self.reset_counters()
                    self.update_gui_label_data()


                # EM_DECODER_CONFIGURATION => end of an adaptation round
                elif msg_type == rc.MT_EM_DECODER_CONFIGURATION:
                    #self.msg_cnt += 1
                    self.reset_counters()
                    self.update_gui_label_data()

                # END_TASK_STATE => end of a task
                elif msg_type == rc.MT_END_TASK_STATE:
                    #self.msg_cnt += 1
                    mdf = rc.MDF_END_TASK_STATE()
                    copy_from_msg(mdf, msg)

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

                            if len(self.shadow_success_window) > self.window_wide: #self.window_narrow:
                                self.shadow_success_window.pop(0)

                            if len(self.shadow_givenup_window) > self.window_wide: #self.window_narrow:
                                self.shadow_givenup_window.pop(0)

                            if len(self.shadow_started_window) > self.window_wide: #self.window_narrow:
                                self.shadow_started_window.pop(0)

                            self.success_window = copy.deepcopy(self.shadow_success_window)
                            self.started_window = copy.deepcopy(self.shadow_started_window)
                            self.givenup_window = copy.deepcopy(self.shadow_givenup_window)

                            if self.num_trials_postcalib > 0:
                                self.percent_start = 100 * self.num_trial_started_postcalib / self.num_trials_postcalib
                                self.percent_givenup = 100 * self.num_trial_givenup_postcalib / self.num_trials_postcalib
                                self.percent_success = 100 * self.num_trial_successful_postcalib / self.num_trials_postcalib


                            percent_success_wide_window = np.NAN
                            if len(self.success_window) >= self.window_wide:
                                num_success_window = np.sum(self.success_window)
                                percent_success_wide_window = 100 * num_success_window / len(self.success_window)

                            percent_givenup_wide_window = np.NAN
                            if len(self.givenup_window) >= self.window_wide:
                                num_givenup_window = np.sum(self.givenup_window)
                                percent_givenup_wide_window = 100 * num_givenup_window / len(self.givenup_window)

                            percent_started_wide_window = np.NAN
                            if len(self.started_window) >= self.window_wide:
                                num_started_window = np.sum(self.started_window)
                                percent_started_wide_window = 100 * num_started_window / len(self.started_window)

                            percent_success_narrow_window = np.NAN
                            if len(self.success_window) >= self.window_narrow:
                                success_window_narrow = self.success_window[len(self.success_window)-self.window_narrow:]
                                num_success_window = np.sum(success_window_narrow)
                                percent_success_narrow_window = 100 * num_success_window / len(success_window_narrow)

                            percent_givenup_narrow_window = np.NAN
                            if len(self.givenup_window) >= self.window_narrow:
                                givenup_window_narrow = self.givenup_window[len(self.givenup_window)-self.window_narrow:]
                                num_givenup_window = np.sum(givenup_window_narrow)
                                percent_givenup_narrow_window = 100 * num_givenup_window / len(givenup_window_narrow)

                            if len(self.started_window) >= self.window_narrow:
                                started_window_narrow = self.started_window[len(self.started_window)-self.window_narrow:]
                                num_started_window = np.sum(started_window_narrow)
                                percent_started_narrow_window = 100 * num_started_window / len(started_window_narrow)
                                self.hist_narrow_STR.append(percent_started_narrow_window)
                                self.hist_narrow_SUR.append(percent_success_narrow_window)
                                self.hist_narrow_GUR.append(percent_givenup_narrow_window)

                                self.hist_wide_STR.append(percent_started_wide_window)
                                self.hist_wide_SUR.append(percent_success_wide_window)
                                self.hist_wide_GUR.append(percent_givenup_wide_window)

                            self.update_gui_label_data()


                elif msg_type == rc.MT_PING:
                    respond_to_ping(self.mod, msg, 'TrialStatusDisplay')

                elif msg_type == MT_EXIT:
                    self.exit()
                    done = True

            else:
                done = True

                self.console_disp_cnt += 1
                if self.console_disp_cnt == 50:
                    self.update_plot()
                    self.console_disp_cnt = 0


    def update_plot(self):

        #print "All trials : %d" % (self.num_trials_postcalib)
        #print ""
        #print "GSTR: ", self.percent_start
        #print "GGUR: ", self.percent_givenup
        #print "GSUR: ", self.percent_success
        #print ""
        #print "STR win: ", self.started_window
        #print "GUP win: ", self.givenup_window
        #print "SUC win: ", self.success_window
        #print ""
        #print "nSTR: ", self.hist_narrow_STR
        #print "nGUR: ", self.hist_narrow_GUR
        #print "nSUR :", self.hist_narrow_SUR
        #print ""
        #print "wSTR: ", self.hist_wide_STR
        #print "wGUR: ", self.hist_wide_GUR
        #print "wSUR :", self.hist_wide_SUR
        #print ""
        #print "Msg cnt    : %d" % (self.msg_cnt)
        #print "\n ----------------------- \n"

        i = 0
        ax = self.ax[i]
        current_size = ax.bbox.width, ax.bbox.height
        if self.old_size[i] != current_size:
            self.old_size[i] = current_size
            self.draw()
            self.ax_bkg[i] = self.copy_from_bbox(ax.bbox)
        self.restore_region(self.ax_bkg[i])

        #if len(self.hist_narrow_STR) > 1:
        if not self.hist_narrow_STR:
            self.lines[0].set_ydata([self.percent_start, self.percent_start])
            self.lines[0].set_xdata([0, 1])
            ax.draw_artist(self.lines[0])

            self.lines[3].set_ydata([self.percent_givenup, self.percent_givenup])
            self.lines[3].set_xdata([0, 1])
            ax.draw_artist(self.lines[3])

            self.lines[6].set_ydata([self.percent_success, self.percent_success])
            self.lines[6].set_xdata([0, 1])
            ax.draw_artist(self.lines[6])

        else:
            ax.set_xlim(0, len(self.hist_narrow_STR)-1)

            for k in range(0,9):
                self.lines[k].set_xdata(range(len(self.hist_narrow_STR)))

            self.lines[0].set_ydata([self.percent_start, self.percent_start])
            self.lines[0].set_xdata([0, len(self.hist_narrow_STR)])
            self.lines[1].set_ydata(self.hist_narrow_STR)
            self.lines[2].set_ydata(self.hist_wide_STR)

            ###

            self.lines[3].set_ydata([self.percent_givenup, self.percent_givenup])
            self.lines[3].set_xdata([0, len(self.hist_narrow_STR)])
            self.lines[4].set_ydata(self.hist_narrow_GUR)
            self.lines[5].set_ydata(self.hist_wide_GUR)

            ###

            self.lines[6].set_ydata([self.percent_success, self.percent_success])
            self.lines[6].set_xdata([0, len(self.hist_narrow_STR)])
            self.lines[7].set_ydata(self.hist_narrow_SUR)
            self.lines[8].set_ydata(self.hist_wide_SUR)

            for k in range(0,9):
                ax.draw_artist(self.lines[k])

        self.blit(ax.bbox)

        # need to redraw once to update y-ticks
        if self.redraw_yticks == True:
            self.draw()
            self.redraw_yticks = False


    def exit(self):
        print "exiting"
        self.parent.exit_app()

    def stop(self):
        print 'disconnecting'
        self.mod.SendSignal(rc.MT_EXIT_ACK)
        self.mod.DisconnectFromMMM()


class MainWindow(QtGui.QMainWindow):
    def __init__(self, config, mm_ip):

        QtGui.QMainWindow.__init__(self)

        self.setAttribute(QtCore.Qt.WA_DeleteOnClose)
        self.setWindowTitle("TrialStatusDisplay")
        self.setGeometry(500,160,960,700)

        main_widget = QtGui.QWidget(self)
        self.mpl = MplCanvas(self)

        # --- GALL ---
        self.lbl_GALL = QtGui.QLabel(self)
        self.lbl_GALL.setStyleSheet("QLabel { background-color : #cccccc; font: 16px;}")
        self.lbl_GALL.setText("All trials")
        self.lbl_GALL.setFrameStyle(QtGui.QFrame.Panel)
        self.GALL = QtGui.QLabel(self)
        self.GALL.setStyleSheet("QLabel { font: 16px; margin-right:50px;}")
        self.GALL.setText("0")


        # --- GSTR ---
        self.lbl_GSTR = QtGui.QLabel(self)
        self.lbl_GSTR.setStyleSheet("QLabel { background-color : #cccccc; font: 16px;}")
        self.lbl_GSTR.setText("Started trials")
        self.lbl_GSTR.setFrameStyle(QtGui.QFrame.Panel)
        self.GSTR = QtGui.QLabel(self)
        self.GSTR.setStyleSheet("QLabel { font: 16px; margin-right:50px;}")
        self.GSTR.setText("0")
        
        # --- GGUR ---
        self.lbl_GGUR = QtGui.QLabel(self)
        self.lbl_GGUR.setStyleSheet("QLabel { background-color : #cccccc; font: 16px;}")
        self.lbl_GGUR.setText("Given-up trials")
        self.lbl_GGUR.setFrameStyle(QtGui.QFrame.Panel)
        self.GGUR = QtGui.QLabel(self)
        self.GGUR.setStyleSheet("QLabel { font: 16px; margin-right:50px;}")
        self.GGUR.setText("0")

        # --- GSUR ---
        self.lbl_GSUR = QtGui.QLabel(self)
        self.lbl_GSUR.setStyleSheet("QLabel { background-color : #cccccc; font: 16px;}")
        self.lbl_GSUR.setText("Success trials")
        self.lbl_GSUR.setFrameStyle(QtGui.QFrame.Panel)
        self.GSUR = QtGui.QLabel(self)
        self.GSUR.setStyleSheet("QLabel { font: 16px; margin-right:50px;}")
        self.GSUR.setText("0")

        vbox = QtGui.QVBoxLayout()
        vbox.addWidget(self.mpl)
        hbox = QtGui.QHBoxLayout()
        hbox.addWidget(self.lbl_GALL)
        hbox.addWidget(self.GALL)
        hbox.addWidget(self.lbl_GSTR)
        hbox.addWidget(self.GSTR)
        hbox.addWidget(self.lbl_GGUR)
        hbox.addWidget(self.GGUR)
        hbox.addWidget(self.lbl_GSUR)
        hbox.addWidget(self.GSUR)
        hbox.addStretch()
        
        vbox.addLayout(hbox)
        main_widget.setLayout(vbox)
        main_widget.setFocus()
        self.setCentralWidget(main_widget)

        self.mpl.run(config, mm_ip)


    def reload_config(self):
        self.mpl.reload_config()

    def exit_app(self):
        self.close()

    def closeEvent(self, ce):
        self.mpl.stop()
        self.close()


if __name__ == "__main__":
    parser = ArgumentParser(description = "Visualizes TrialStatus information")
    parser.add_argument(type=str, dest='config')
    parser.add_argument(type=str, dest='mm_ip', nargs='?', default='')
    args = parser.parse_args()
    print("Using config file=%s, MM IP=%s" % (args.config, args.mm_ip))

    qApp = QtGui.QApplication(sys.argv)
    frame = MainWindow(args.config, args.mm_ip)
    frame.show()
    sys.exit(qApp.exec_())


