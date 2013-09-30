
from PyDragonfly import Dragonfly_Module, CMessage, copy_from_msg, copy_to_msg, MT_EXIT
import Dragonfly_config as rc
from dragonfly_utils import respond_to_ping

from argparse import ArgumentParser
from ConfigParser import SafeConfigParser
from PyQt4 import QtGui, QtCore
from PyQt4.Qt import *
import sys
import random
import os

target_size = 32
target_offset = float(target_size / 2.0)
display_size = 500

class Cursor:
    def __init__(self, image):
        self.x = 0
        self.y = 0
        self.pix = QtGui.QPixmap(image) 
        
    def setPos(self, x, y):
        self.x = x
        self.y = y
        

class CursorDisplay(QtGui.QWidget):
    def __init__(self):
        super(CursorDisplay, self).__init__()

        self.cursor = Cursor(os.path.join(os.environ['BCI_MODULES'], "CursorDisplay", "cursor.png"))
        self.setCursorPos(0, 0)
        
        self.target = Cursor(os.path.join(os.environ['BCI_MODULES'], "CursorDisplay", "target.png"))
        self.setTargetPos(0, 0)

        self.move(300,300)
        self.setFixedSize(display_size, display_size)
        self.setWindowTitle('Cursor Display')

    def run(self, config_file, mm_ip):
        self.mod = Dragonfly_Module(0, 0)
        self.mod.ConnectToMMM(mm_ip)

        self.msg_types = ['TASK_STATE_CONFIG', 'ROBOT_CONTROL_SPACE_ACTUAL_STATE']
        self.msg_types.sort()
        self.mod.Subscribe(MT_EXIT)
        self.mod.Subscribe(rc.MT_PING)
        for i in self.msg_types:
            self.mod.Subscribe(eval('rc.MT_%s' % (i)))

        print "Connected to Dragonfly at", mm_ip
        #print "mod_id = ", self.mod.GetModuleID()
    
        self.timer = QtCore.QTimer()
        QtCore.QObject.connect(self.timer, QtCore.SIGNAL("timeout()"), self.timer_event)
        self.timer.start(50)     

        
    def timer_event(self):
        done = False
        while not done:
            msg = CMessage()
            rcv = self.mod.ReadMessage(msg, 0)
            if rcv == 1:
                msg_type = msg.GetHeader().msg_type
            
                if msg_type == rc.MT_TASK_STATE_CONFIG:
                    mdf = rc.MDF_TASK_STATE_CONFIG()
                    copy_from_msg(mdf, msg)
                    x = mdf.target[0]
                    y = mdf.target[1]
                    self.setTargetPos(x, y)

                    #print "x: ", x, "|", self.tgt2pix(x) , " y: ", y, "|", self.tgt2pix(y)
                
                elif msg_type == rc.MT_ROBOT_CONTROL_SPACE_ACTUAL_STATE:
                    mdf = rc.MDF_ROBOT_CONTROL_SPACE_ACTUAL_STATE()
                    copy_from_msg(mdf, msg)
                    x = mdf.pos[0]
                    y = mdf.pos[1]
                    self.setCursorPos(x, y)

                    #print "x: ", mdf.pos[0], "y: ", mdf.pos[1]
                
                elif msg_type == rc.MT_PING:
                    respond_to_ping(self.mod, msg, 'CursorDisplay')

                elif msg_type == MT_EXIT:
                    self.exit()
                    done = True
                
            else:
                done = True                
                
        
    def tgt2pix(self, tgt):
        return int(((tgt + 1.0) / 2.0) * 500)
        
    def setTargetPos(self, x, y):
        self.target.setPos(self.tgt2pix(x), self.tgt2pix(y))
        #print "target: ", self.target.x, self.target.y
        self.update()
        
    def setCursorPos(self, x, y):
        self.cursor.setPos(self.tgt2pix(x), self.tgt2pix(y))
        #print "cursor: ", self.cursor.x, self.cursor.y
        self.update()
        
    def exit(self):
        self.mod.SendSignal(rc.MT_EXIT_ACK)
        self.mod.DisconnectFromMMM()        
        self.close()

    def paintEvent(self, event):
        qp = QtGui.QPainter()
        qp.begin(self)
        
        qp.setPen(QtGui.QPen(Qt.black, 2, Qt.DotLine, Qt.RoundCap))
        
        qp.drawLine(display_size/2, 0, display_size/2, display_size)
        qp.drawLine(0, display_size/2, display_size, display_size/2)
        
        qp.drawPixmap(self.cursor.x - target_offset, self.cursor.y - target_offset, self.cursor.pix)
        qp.drawPixmap(self.target.x - target_offset, self.target.y - target_offset, self.target.pix)
        
        #print "target: ", self.target.x, self.target.y
        #print "cursor: ", self.cursor.x, self.cursor.y
        
        qp.end()


if __name__ == '__main__':
    parser = ArgumentParser(description = "Visualizes virtual_cursor module")
    parser.add_argument(type=str, dest='config')
    parser.add_argument(type=str, dest='mm_ip', nargs='?', default='')
    args = parser.parse_args()
    print("Using config file=%s, MM IP=%s" % (args.config, args.mm_ip))

    app = QtGui.QApplication(sys.argv)
    disp = CursorDisplay()
    disp.show()
    disp.run(args.config, args.mm_ip)
  
    sys.exit(app.exec_())    
    
    
    