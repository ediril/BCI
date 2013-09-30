#!/usr/bin/python

from PyRTMA import RTMA_Module, CMessage, copy_from_msg, copy_to_msg, read_msg_data, MT_EXIT
import RTMA_config as rc
from argparse import ArgumentParser
#from configobj import ConfigObj
import numpy as np
import sys
import copy
from rtma_utils import respond_to_ping
from ctypes import *
from scipy.io import loadmat

import matplotlib
matplotlib.use('Qt4Agg')
from matplotlib.backends.backend_qt4agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.figure import Figure
import matplotlib.patches as patches
from matplotlib.patches import Polygon

from PyQt4 import QtCore, QtGui


#QtCore.pyqtRemoveInputHook()
#import ipdb; ipdb.set_trace()

def nan_array(shape, dtype=float):
    a = np.empty(shape, dtype)
    a.fill(np.NAN)
    return a


class MplCanvas(FigureCanvas):
    subscriptions = [MT_EXIT,
                     rc.MT_PING, 
                     rc.MT_SPM_SPIKECOUNT,
                     rc.MT_SAMPLE_GENERATED]  
    #rc.MT_SPM_SPIKECOUNT,
    #rc.MT_RAW_SPIKECOUNT,

    def __init__(self, parent=None, width=8, height=10, dpi=80):
        self.parent = parent
        self.paused = False
        self.LiveData = None

        self.figure = Figure(figsize=(width, height), dpi=dpi)
        FigureCanvas.__init__(self, self.figure)

        self.setParent(parent)

        FigureCanvas.setSizePolicy(self,
                                   QtGui.QSizePolicy.Expanding,
                                   QtGui.QSizePolicy.Expanding)
        FigureCanvas.updateGeometry(self)


    def run(self, config_file, server):
        self.mod = RTMA_Module(0, 0)
        self.mod.ConnectToMMM(server)
        for sub in self.subscriptions:
            self.mod.Subscribe(sub)
        self.mod.SendModuleReady()
        print "Connected to RTMA at", server

        self.init_vars()
        self.init_plot()
        
        #self.set_active_chans()

        timer = QtCore.QTimer(self)
        QtCore.QObject.connect(timer, QtCore.SIGNAL("timeout()"), self.timer_event)
        timer.start(10)


    def set_active_chans(self):
        #self.nActive = np.hstack([np.arange(1,380,6), (np.arange(96*6, 120*6, 6) + 1)])
        #self.nActive = np.hstack([np.arange(0,576,6), np.arange(1,576, 6)])
        self.nActive = np.arange(self.nDim)
        print self.nActive
        print "[D] active cells count = " + str(len(self.nActive))


    def init_vars(self):
        self.xN = 300
        self.nDim = 576      # max number of neurons we can plot
        #self.nActive = []
        self.LiveSpikeData = nan_array((self.nDim, self.xN))


    def init_plot(self):
        self.figure.subplots_adjust(bottom=.05, right=.98, left=.08, top=.98, hspace=0.06)
        self.ax = self.figure.add_subplot(111)
        self.reset_axis()
        self.draw()

        self.spike_data = []
        self.old_size = (self.ax.bbox.width, self.ax.bbox.height)
        self.ax_bkg   = self.copy_from_bbox(self.ax.bbox)

        for d in np.arange(self.nDim / 6):
            line, = self.ax.plot([], [], 'k.', lw=1.0, animated=True, aa=None)
            line.set_xdata(range(self.xN))
            self.spike_data.append(line)
            self.draw()


    def reset_axis(self):
        self.ax.set_xlim(0, self.xN-1)
        self.ax.set_ylim(0, 1.0)
        self.ax.set_autoscale_on(False)
        #self.ax.set_ylabel('Spikes')
        self.ax.get_xaxis().set_ticks([])
        self.ax.get_yaxis().set_ticks([])


    def update_judging_data(self, counts):
        new_spikes = np.array(counts[0:self.nDim])
        temp = nan_array((self.nDim, 1))
        temp[new_spikes > 0] = 1
        new_spikes = temp
        temp2 = np.concatenate((self.LiveSpikeData, new_spikes), axis=1)
        self.LiveSpikeData = np.delete(temp2, 0, axis=1)


    def load_config(self):
        self.config = ConfigObj(self.config_file, unrepr=True)

    def reload_config(self):
        self.load_config()
        self.init_legend()


    def timer_event(self):
        done = False
        while not done:
            msg = CMessage()
            rcv = self.mod.ReadMessage(msg, 0)
            if rcv == 1:
                msg_type = msg.GetHeader().msg_type

                if msg_type == rc.MT_SPM_SPIKECOUNT: #rc.MT_RAW_SPIKECOUNT: #rc.MT_SPM_SPIKECOUNT:
                    mdf = rc.MDF_SPM_SPIKECOUNT()
                    copy_from_msg(mdf, msg)
                    self.update_judging_data(mdf.counts)
                
                elif msg_type == rc.MT_PING:
                    respond_to_ping(self.mod, msg, 'SpikePlotter')

                #elif msg_type == MT_EXIT:
                #    self.exit()
                #    done = True

            else:
                done = True

        self.update_plot()


    def update_plot(self):
        if self.paused == False:
            LiveSpikeData = self.LiveSpikeData
        else:
            LiveSpikeData = self.PausedSpikeData

        current_size = self.ax.bbox.width, self.ax.bbox.height
        if self.old_size != current_size:
            self.old_size = current_size
            self.draw()
            self.ax_bkg = self.copy_from_bbox(self.ax.bbox)

        self.restore_region(self.ax_bkg)

        num_chans = self.nDim/6
        incr = 1.0/num_chans

        for ch in np.arange(num_chans):
            data = LiveSpikeData[ch*6]
            for u in np.arange(1,6):
                unit = LiveSpikeData[ch*6 + u, :]
                data[unit > 0] = 1
                
            self.spike_data[ch].set_ydata(data * incr * ch)
            self.ax.draw_artist(self.spike_data[ch])

        self.blit(self.ax.bbox)


    def pause(self, pause_state):
        self.paused = pause_state
        self.PausedSpikeData = copy.deepcopy(self.LiveSpikeData)


    def exit(self):
        print "exiting"
        self.parent.exit_app()


    def stop(self):
        print 'disconnecting'
        self.mod.SendSignal(rc.MT_EXIT_ACK)
        self.mod.DisconnectFromMMM()


class MainWindow(QtGui.QMainWindow):
    def __init__(self, config, mm_ip):

        self.paused = False

        QtGui.QMainWindow.__init__(self)

        self.setAttribute(QtCore.Qt.WA_DeleteOnClose)
        self.setWindowTitle("SpikePlotter")
        self.setGeometry(500,160,960,700)

        main_widget = QtGui.QWidget(self)
        self.mpl = MplCanvas(self)
        self.pb = QtGui.QPushButton("Pause", self)
        #self.rc = QtGui.QPushButton("Reload Config", self)

        vbox = QtGui.QVBoxLayout(main_widget)
        vbox.addWidget(self.mpl)
        hbox = QtGui.QHBoxLayout(main_widget)
        hbox.addWidget(self.pb)
        #hbox.addWidget(self.rc)
        hbox.addStretch()
        vbox.addLayout(hbox)

        main_widget.setFocus()
        self.setCentralWidget(main_widget)

        self.pb.clicked.connect(self.pause_plot)
        #self.rc.clicked.connect(self.reload_config)

        self.mpl.run(config, mm_ip)


    #def reload_config(self):
    #    self.mpl.reload_config()

    def pause_plot(self):
        if self.paused == True:
            self.paused = False
            self.pb.setText('Pause')
        else:
            self.paused = True
            self.pb.setText('Unpause')
        self.mpl.pause(self.paused)

    def exit_app(self):
        self.close()

    def closeEvent(self, ce):
        self.mpl.stop()
        self.close()


if __name__ == "__main__":
    parser = ArgumentParser(description = "Visualizes Spike Data")
    parser.add_argument(type=str, dest='config')
    parser.add_argument(type=str, dest='mm_ip', nargs='?', default='')
    args = parser.parse_args()
    print("Using config file=%s, MM IP=%s" % (args.config, args.mm_ip))

    qApp = QtGui.QApplication(sys.argv)
    frame = MainWindow(args.config, args.mm_ip)
    frame.show()
    sys.exit(qApp.exec_())


