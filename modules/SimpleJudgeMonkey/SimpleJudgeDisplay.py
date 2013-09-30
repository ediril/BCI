#!/usr/bin/python

from PyRTMA import RTMA_Module, CMessage, copy_from_msg, copy_to_msg, MT_EXIT
import RTMA_config as rc
from argparse import ArgumentParser
from configobj import ConfigObj
import numpy as np
import sys
import copy
from rtma_utils import respond_to_ping
from motorlab.rp3.rotations import rotmat2rotvec

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
    subscriptions = [rc.MT_PING, MT_EXIT,
                     rc.MT_TASK_STATE_CONFIG,
                     rc.MT_ROBOT_CONTROL_SPACE_ACTUAL_STATE,
                     rc.MT_GROBOT_SEGMENT_PERCEPTS,
                     rc.MT_GROBOT_RAW_FEEDBACK,
                     rc.MT_END_TASK_STATE]

    def __init__(self, parent=None, width=8, height=10, dpi=80):
        self.parent = parent
        self.paused = False
        self.LiveData = None
        self.fdbk_actual_pos = None
        self.fdbk_actual_cori = None
        self.tsc_mdf = None
        self.ets_mdf = None
        self.fdbk_percepts = [0] * 16
        self.fdbk_torques = [0] * 16
        self.redraw_yticks = True

        self.figure = Figure(figsize=(width, height), dpi=dpi, facecolor='#bbbbbb')
        FigureCanvas.__init__(self, self.figure)

        self.setParent(parent)

        FigureCanvas.setSizePolicy(self,
                                   QtGui.QSizePolicy.Expanding,
                                   QtGui.QSizePolicy.Expanding)
        FigureCanvas.updateGeometry(self)
        

    def init_judge_display(self):
        N = self.config['config']['number_of_data_points']

        self.LiveData = {'ActualPos': {},
                         'ThreshUpper': {},
                         'ThreshLower': {},
                         'JudgingMethod': {},
                         'JudgingPolarity': {},
                         'max_scale': {},
                         'min_scale': {} }
        
        allDims = 1 + 1 + 10 + 15 + 28  # trans + ori + finger + force + torque
        
        for d in range(allDims):
            self.LiveData['ActualPos'][d] = np.zeros(N)
            self.LiveData['ThreshUpper'][d] = nan_array(N)
            self.LiveData['ThreshLower'][d] = nan_array(N)
            self.LiveData['JudgingMethod'][d] = nan_array(N)
            self.LiveData['JudgingPolarity'][d] = nan_array(N)
            self.LiveData['max_scale'][d] = np.finfo(float).eps
            self.LiveData['min_scale'][d] = -np.finfo(float).eps #

        self.LiveData['TaskStateNo'] = np.zeros(N)
        self.LiveData['TaskStateVerdict'] = np.ones(N)

    def run(self, config_file, server):
        self.mod = RTMA_Module(0, 0)
        self.mod.ConnectToMMM(server)
        for sub in self.subscriptions:
            self.mod.Subscribe(sub)
        self.mod.SendModuleReady()
        print "Connected to RTMA at", server

        self.config_file = config_file
        self.load_config()

        self.init_judge_display()
        self.init_plot()
        self.init_legend()

        timer = QtCore.QTimer(self)
        QtCore.QObject.connect(timer, QtCore.SIGNAL("timeout()"), self.timer_event)
        timer.start(10)     

    def update_scales(self, d):
        min_data = np.nanmin(self.LiveData['ActualPos'][d])
        if min_data < self.LiveData['min_scale'][d]:
            self.LiveData['min_scale'][d] = min_data;

        max_data = np.nanmax(self.LiveData['ActualPos'][d])
        if max_data > self.LiveData['max_scale'][d]:
            self.LiveData['max_scale'][d] = max_data;
    
    
    def update_judging_data(self):
        # this loop is so we can update finger pos data even if we haven't
        # received any TASK_STATE_CONFIG msg
        for i in range(self.nDims):
            d = self.dims[i] - 1
            if d > 1:        # fingers
                finger_idx = d-2
                actual_pos = self.fdbk_actual_pos[8+finger_idx];
                self.LiveData['ActualPos'][d] = self.add_to_windowed_array(self.LiveData['ActualPos'][d], actual_pos)
                self.update_scales(d)

        if self.tsc_mdf is None:
            return

        trans_thresh = self.tsc_mdf.trans_threshold
        ori_threshold = self.tsc_mdf.ori_threshold
        finger_thresh = np.array(self.tsc_mdf.finger_threshold, dtype=float)
        finger_dofs_to_judge = np.where(~np.isnan(finger_thresh)==True)[0]

        for i in range(self.nDims):
            d = self.dims[i] - 1

            threshU = np.NAN
            threshL = np.NAN
            method = np.NAN
            polarity = np.NAN

            if d == 0:   # trans
                tgt_pos = np.array(self.tsc_mdf.target[0:3])
                act_pos = np.array(self.fdbk_actual_pos[0:3])
                tgt_disp = tgt_pos - act_pos;
                tgt_dist = np.sqrt(np.sum(np.power(tgt_disp,2)))

                self.LiveData['ActualPos'][d] = self.add_to_windowed_array(self.LiveData['ActualPos'][d], tgt_dist)
                self.update_scales(d)
                
                threshU = trans_thresh
                threshL = -trans_thresh
                method = 1      # dist
                polarity = 2    # less than (inverted)

            elif d == 1: # ori
            
                tgt_cori = np.array(self.tsc_mdf.coriMatrix).reshape((3,3)).T
                act_cori = np.array(self.fdbk_actual_cori).reshape((3,3)).T
                cori_diff_matrix = tgt_cori * act_cori.T
                [diff_rotaxis, diff_angle] = rotmat2rotvec( cori_diff_matrix)

                self.LiveData['ActualPos'][d] = self.add_to_windowed_array(self.LiveData['ActualPos'][d], diff_angle)
                self.update_scales(d)
                
                print diff_angle
                print ori_threshold
                print "-----"

                threshU = ori_threshold
                threshL = -ori_threshold
                method = 1      # dist
                polarity = 2    # less than (inverted)

            else:        # fingers
                finger_idx = d-2
                if np.where(finger_dofs_to_judge == finger_idx)[0].size > 0:

                    thresh = self.tsc_mdf.finger_threshold[finger_idx]
                    method = self.tsc_mdf.finger_threshold_judging_method[finger_idx]
                    polarity = self.tsc_mdf.finger_threshold_judging_polarity[finger_idx]

                    # invert polarities (because we plot "keep out" zones)
                    if (polarity > 0) and (self.tsc_mdf.timed_out_conseq == 0):
                        polarity = ~polarity & 3;

                    # finger_threshold_judging_method: 1=distance (default), 2=absolute
                    if method == 1:  # dist
                        target = self.tsc_mdf.target[8+finger_idx]
                        threshU = target + thresh
                        threshL = target - thresh
                    else:            # abs
                        threshU = thresh
                
            # insert new data to plotting arrays
            self.LiveData['ThreshUpper'][d] = self.add_to_windowed_array(self.LiveData['ThreshUpper'][d], threshU)
            self.LiveData['ThreshLower'][d] = self.add_to_windowed_array(self.LiveData['ThreshLower'][d], threshL)
            self.LiveData['JudgingMethod'][d] = self.add_to_windowed_array(self.LiveData['JudgingMethod'][d], method)
            self.LiveData['JudgingPolarity'][d] = self.add_to_windowed_array(self.LiveData['JudgingPolarity'][d], polarity)

        self.LiveData['TaskStateNo'] = self.add_to_windowed_array(self.LiveData['TaskStateNo'], self.tsc_mdf.id)

        if self.ets_mdf is not None:
            self.LiveData['TaskStateVerdict'][-2] = self.ets_mdf.outcome
            self.LiveData['TaskStateVerdict'][-1] = self.ets_mdf.outcome
            self.LiveData['TaskStateVerdict'] = self.add_to_windowed_array(self.LiveData['TaskStateVerdict'], self.ets_mdf.outcome)
            self.ets_mdf = None
        else:
            self.LiveData['TaskStateVerdict'] = self.add_to_windowed_array(self.LiveData['TaskStateVerdict'], 1)

    def add_to_windowed_array(self, arr, data):
        arr = np.append(arr, data)
        arr = np.delete(arr, 0)
        return arr

    def load_config(self):
        self.config = ConfigObj(self.config_file, unrepr=True)

    def reload_config(self):
        self.load_config()
        for ax in self.figure.axes:
            self.figure.delaxes(ax)
        self.figure.clear()
        self.draw()
        self.init_plot(True)
        self.init_legend()
        self.redraw_yticks = True

 
    def init_plot(self, clear=False):
        self.figure.subplots_adjust(bottom=.05, right=.98, left=.08, top=.98, hspace=0.07)
        
        trans_dim = 0
        if 'plot_translation' in self.config['config']:
            trans_dim = self.config['config']['plot_translation']
       
        ori_dim = 0
        if 'plot_orientation' in self.config['config']:
            ori_dim = self.config['config']['plot_orientation']
            
        finger_dims = []
        if 'active_finger_dims' in self.config['config']:
            finger_dims = self.config['config']['active_finger_dims'] 
        
        force_dims = []
        if 'active_force_dims' in self.config['config']:
            force_dims = self.config['config']['active_force_dims'] 

        torque_dims = []
        if 'active_torque_dims' in self.config['config']:
            torque_dims = self.config['config']['active_torque_dims'] 
        
        axis_labels = []
        self.dims = []
        if trans_dim == 1:
            self.dims.append(1)
            axis_labels.extend(['XYZ tgt dist'])
        if ori_dim == 1:
            self.dims.append(2)
            axis_labels.extend(['ORI tgt dist'])
        if finger_dims:
            for f in finger_dims:
                if (f>0) and (f<=10):
                    self.dims.extend([f+2])
                    axis_labels.extend(['finger #%d' % f])
                else:
                    print "Warning: invalid finger dim specified: %f, skipping.." % f
        if force_dims:
            force_labels = ['ifx', 'ify', 'ifz', 'mfx', 'mfy', 'mfz', 'rfx', \
                            'rfy', 'rfz', 'lfx', 'lfy', 'lfz', 'tfx', 'tfy', 'tfz']
            for f in force_dims:
                if (f>0) and (f<=15):
                    self.dims.extend([f+12])
                    axis_labels.extend(['force #%d (%s)' % (f, force_labels[f-1])])
                else:
                    print "Warning: invalid force dim specified: %d, skipping.." % f
        if torque_dims:
            for f in torque_dims:
                if (f>0) and (f<=28):
                    self.dims.extend([f+27])
                    axis_labels.extend(['trq #%d' % f])
                else:
                    print "Warning: invalid torque dim specified: %d, skipping.." % f
      
        self.nDims = trans_dim + ori_dim + len(finger_dims) + len(force_dims) + len(torque_dims)
        self.xN = self.config['config']['number_of_data_points']
        self.bg = self.config['marked_task_states'].keys()

        self.max_scale = self.config['config']['max_scale']
        if len(self.max_scale) < self.nDims:
            self.max_scale.extend([np.finfo(float).eps] * (self.nDims - len(self.max_scale)))
        
        self.min_scale = self.config['config']['min_scale']
        if len(self.min_scale) < self.nDims:
            self.min_scale.extend([-np.finfo(float).eps] * (self.nDims - len(self.min_scale)))
        

        self.ax = []
        self.old_size = []
        self.ax_bkg = []
        self.finger_pos = []
        self.zones = {}
        self.zone_idx = []

        for d in range(self.nDims):
            ax = self.figure.add_subplot(self.nDims,1,d+1)
            self.reset_axis(ax, axis_labels[d])
            self.draw()
            
            bbox_width = ax.bbox.width
            bbox_height = ax.bbox.height
            if clear == True:
                # force to redraw
                bbox_width = 0  
                bbox_height = 0

            self.old_size.append( (bbox_width, bbox_height) )
            self.ax_bkg.append(self.copy_from_bbox(ax.bbox))

            line, = ax.plot([], [], 'k-', lw=1.0, aa=None, animated=True)
            line.set_xdata(range(self.xN))
            line.set_ydata([0.0]*self.xN)
            self.finger_pos.append(line)
            self.draw()
    
            self.zones[d] = []
            self.zone_idx.append(0)
            for z in range(60):
                patch = ax.add_patch(Polygon([[0, 1e-12],[1e-12, 0],[1e-12, 1e-12],[0, 1e-12]], fc='none', ec='none', fill=True, closed=True, aa=None, animated=True))
                self.zones[d].append(patch)
                self.draw()

            self.ax.append(ax)


    def reset_axis(self, ax, label):
        ax.grid(True)
        ax.set_xlim(0, self.xN-1)
        ax.set_autoscale_on(False)
        ax.set_ylabel(label, fontsize='small')
        ax.get_xaxis().set_ticks([])
        ax.yaxis.set_major_formatter(FormatStrFormatter('%.02f'))
        for tick in ax.get_yticklabels():
            tick.set_fontsize(9) 

        
    def init_legend(self):
        legnd = []

        line = matplotlib.lines.Line2D([0,0], [0,0], color='k')
        legnd.append(line)

        for d in range(len(self.bg)):
            b_color = self.config['marked_task_states'][self.bg[d]]['color']
            patch = Polygon([[0,0],[0, 0],[0, 0],[0, 0]], fc=b_color, ec='none', fill=True, closed=True, alpha=0.65)
            legnd.append(patch)

        self.figure.legend(legnd, ['Position']+self.bg, loc='lower center', frameon=False, ncol=20, prop={'size':'11'}, columnspacing=.5)
        self.draw()
        
        
    def plot_bg_mask(self, ax, idx, x, mask, ylim, fc, ec, hatch, alpha):
        # Find starts and ends of contiguous regions of true values in mask because
        # we want just one patch object per contiguous region
        _mask = np.asarray(np.insert(mask, 0, 0), dtype=int)
        begin_indices = np.where( np.diff( _mask) == 1)[0]

        _mask = np.asarray(np.append(mask, 0), dtype=int)
        end_indices = np.where( np.diff( _mask) == -1)[0]

        # Get DeltaX
        dx = np.mean( np.diff(x))

        # Get YLim if it was not given
        if len(ylim) == 0:
            ylim = ax.get_ylim()

        z = self.zones[idx]
        a = self.zone_idx[idx]

        for i in range(len( begin_indices)):
            b = begin_indices[i]
            e = end_indices[i]
            xb = x[b] - dx/2;
            xe = x[e] + dx/2;
            
            patch = z[a]
            patch.set_xy([[xb, ylim[0]],[xe, ylim[0]],[xe, ylim[1]],[xb, ylim[1]]])
            patch.set_edgecolor(ec)
            patch.set_facecolor(fc)
            patch.set_hatch(hatch)
            patch.set_alpha(alpha)

            ax.draw_artist(patch)
            a = a + 1
            
        self.zone_idx[idx] = a


    def timer_event(self):
        done = False
        while not done:
            msg = CMessage()
            rcv = self.mod.ReadMessage(msg, 0)
            if rcv == 1:
                msg_type = msg.GetHeader().msg_type

                if msg_type == rc.MT_TASK_STATE_CONFIG:
                    self.tsc_mdf = rc.MDF_TASK_STATE_CONFIG()
                    copy_from_msg(self.tsc_mdf, msg)

                elif msg_type == rc.MT_ROBOT_CONTROL_SPACE_ACTUAL_STATE:
                    mdf = rc.MDF_ROBOT_CONTROL_SPACE_ACTUAL_STATE()
                    copy_from_msg(mdf, msg)

                    self.fdbk_actual_cori = mdf.CoriMatrix

                    self.fdbk_actual_pos = []
                    self.fdbk_actual_pos.extend(mdf.pos)
                    self.fdbk_actual_pos.extend(self.fdbk_percepts)
                    self.fdbk_actual_pos.extend(self.fdbk_torques)
                   
                    self.update_judging_data()

                elif msg_type == rc.MT_GROBOT_SEGMENT_PERCEPTS:
                    mdf = rc.MDF_GROBOT_SEGMENT_PERCEPTS()
                    copy_from_msg(mdf, msg)
                    self.fdbk_percepts = []
                    self.fdbk_percepts.extend(mdf.ind_force[:])
                    self.fdbk_percepts.extend(mdf.mid_force[:]) 
                    self.fdbk_percepts.extend(mdf.rng_force[:]) 
                    self.fdbk_percepts.extend(mdf.lit_force[:]) 
                    self.fdbk_percepts.extend(mdf.thb_force[:])

                elif msg_type == rc.MT_GROBOT_RAW_FEEDBACK:
                    mdf = rc.MDF_GROBOT_RAW_FEEDBACK()
                    copy_from_msg(mdf, msg)
                    self.fdbk_torques = mdf.j_trq
                    
                elif msg_type == rc.MT_END_TASK_STATE:
                    self.ets_mdf = rc.MDF_END_TASK_STATE()
                    copy_from_msg(self.ets_mdf, msg)

                elif msg_type == rc.MT_PING:
                    respond_to_ping(self.mod, msg, 'SimpleJudgeDisplay')

                elif msg_type == MT_EXIT:
                    self.exit()
                    done = True
                    
            else:
                done = True

        self.update_plot()
        
        
        
    def update_plot(self):
        if self.paused == False:
            LiveData = self.LiveData
        else:
            LiveData = self.PausedData

        for i in range(self.nDims):
            ax = self.ax[i]
            d = self.dims[i] - 1

            current_size = ax.bbox.width, ax.bbox.height
            if self.old_size[i] != current_size:
                self.old_size[i] = current_size
                self.draw()
                self.ax_bkg[i] = self.copy_from_bbox(ax.bbox)

            self.restore_region(self.ax_bkg[i])

            self.zone_idx[i] = 0
            
            min_scale = LiveData['min_scale'][d];
            if 'min_scale' in self.config['config']:
                min_scale = self.min_scale[i]
            max_scale = LiveData['max_scale'][d];
            if 'max_scale' in self.config['config']:
                max_scale = self.max_scale[i]
            ax.set_ylim(min_scale, max_scale)
            yLimG = ax.get_ylim()

            for b in range(len(self.bg)):
                b_id = self.config['marked_task_states'][self.bg[b]]['id']
                b_color = self.config['marked_task_states'][self.bg[b]]['color']

                mask = np.where(LiveData['TaskStateNo']==b_id, 1, 0)
                if np.sum(mask) > 0:
                    self.plot_bg_mask(ax, i, range(self.xN), mask, [], b_color, 'none', None, 0.65)
                else:
                    # always draw patch for all colors so that they will always show up in the legend
                    z = self.zones[i]
                    patch = z[self.zone_idx[i]]
                    patch.set_xy([[0, 0],[0, 0],[0, 0],[0, 0]])
                    ax.draw_artist(patch)
                    self.zone_idx[i] = self.zone_idx[i] + 1


            # finger_threshold_judging_method: 1=distance, 2=absolute
            # finger threshold_judging_polarity: 1 = <, 2 = >
            methods = ~np.isnan(LiveData['JudgingMethod'][d])
            if np.sum(methods) > 0:
                methods = np.unique(LiveData['JudgingMethod'][d][methods])
                for m in range(len(methods)):
                    method = methods[m]
                    met_mask = np.where(LiveData['JudgingMethod'][d] == method, True, False)
                    polaritys = np.unique(LiveData['JudgingPolarity'][d][met_mask])

                    for p in range(len(polaritys)):
                        polarity = polaritys[p]
                        pol_mask = np.where(LiveData['JudgingPolarity'][d] == polarity, True, False)
                        mask = met_mask & pol_mask

                        yLimUs = np.unique(LiveData['ThreshUpper'][d][mask])

                        for b in range(len(yLimUs)):
                            yLimU = yLimUs[b]
                            submask = np.where(LiveData['ThreshUpper'][d] == yLimU, True, False) & mask

                            if method == 1: # dist
                                yLimLs = np.unique(LiveData['ThreshLower'][d][submask])

                                for k in range(len(yLimLs)):
                                    yLimL = yLimLs[k]
                                    submask2 = np.where(LiveData['ThreshLower'][d] == yLimL, True, False) & submask

                                    if polarity == 1:  # <
                                        self.plot_bg_mask(ax, i, range(self.xN), submask2, [yLimL, yLimU], 'none', 'black', '//', 1)
                                    else:
                                        self.plot_bg_mask(ax, i, range(self.xN), submask2, [yLimG[0], yLimL], 'none', 'black', '//', 1)
                                        self.plot_bg_mask(ax, i, range(self.xN), submask2, [yLimU, yLimG[1]], 'none', 'black', '//', 1)

                            else:           # abs
                                if polarity == 1: # <
                                    self.plot_bg_mask(ax, i, range(self.xN), submask, [yLimG[0], yLimU], 'none', 'black', '//', 1)
                                else:
                                    self.plot_bg_mask(ax, i, range(self.xN), submask, [yLimU, yLimG[1]], 'none', 'black', '//', 1)

            fail_mask = np.where(LiveData['TaskStateVerdict']==0, True, False)
            self.plot_bg_mask(ax, i, range(self.xN), fail_mask, [], 'red', 'none', None, 0.65)

            self.finger_pos[i].set_ydata(LiveData['ActualPos'][d])
            ax.draw_artist(self.finger_pos[i])

            self.blit(ax.bbox)

            if self.zone_idx[i] > 60:
                print "ERROR: too many zones! Increase number of preallocated patches"

        # need to redraw once to update y-ticks
        if self.redraw_yticks == True:
            self.draw() 
            self.redraw_yticks = False


    def pause(self, pause_state):
        self.paused = pause_state
        self.PausedData = copy.deepcopy(self.LiveData)


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
        self.setWindowTitle("SimpleJudgeDisplay")
        self.setGeometry(500,160,960,700)

        main_widget = QtGui.QWidget(self)
        self.mpl = MplCanvas(self)
        self.pb = QtGui.QPushButton("Pause", self)
        self.rc = QtGui.QPushButton("Reload Config", self)
        
        vbox = QtGui.QVBoxLayout()
        vbox.addWidget(self.mpl)
        hbox = QtGui.QHBoxLayout()
        hbox.addWidget(self.pb)
        hbox.addWidget(self.rc)
        hbox.addStretch()
        vbox.addLayout(hbox)

        main_widget.setLayout(vbox)
        main_widget.setFocus()
        self.setCentralWidget(main_widget)

        self.pb.clicked.connect(self.pause_plot)
        self.rc.clicked.connect(self.reload_config)
        
        self.mpl.run(config, mm_ip)
    
    
    def reload_config(self):
        self.mpl.reload_config()
    
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
    parser = ArgumentParser(description = "Visualizes SimpleJudge information")
    parser.add_argument(type=str, dest='config')
    parser.add_argument(type=str, dest='mm_ip', nargs='?', default='')
    args = parser.parse_args()
    print("Using config file=%s, MM IP=%s" % (args.config, args.mm_ip))

    qApp = QtGui.QApplication(sys.argv)
    frame = MainWindow(args.config, args.mm_ip)
    frame.show()
    sys.exit(qApp.exec_())
    

