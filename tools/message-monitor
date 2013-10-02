#!/usr/bin/python

from PyDragonfly import Dragonfly_Module, CMessage, copy_from_msg
import Dragonfly_config as rc
import PyDragonfly
import sys
import numpy as np

server = 'localhost:7111'

msg_name = sys.argv[1]
if len(sys.argv) > 2:
    attr = sys.argv[2]
if len(sys.argv) > 3:
    vec_col = int(sys.argv[3])
else:
    vec_col = None

print "Starting..."
if rc.__dict__.has_key('MT_%s' % (msg_name)):
    msg_type = eval('rc.MT_%s' % msg_name)
    if rc.__dict__.has_key('MDF_%s' % (msg_name)):
        mdf_type = eval('rc.MDF_%s' % msg_name)
    else:
        mdf_type = None
elif PyDragonfly.__dict__.has_key('MT_%s' % (msg_name)):
    print "Found %s in PyDragonfly" % msg_name
    msg_type = eval('PyDragonfly.MT_%s' % msg_name)
    if PyDragonfly.__dict__.has_key('MDF_%s' % (msg_name)):
        mdf_type = eval('PyDragonfly.MDF_%s' % msg_name)
    else:
        mdf_type = None
else:
    raise ValueError('%s is not found.' % msg_name)

mod = Dragonfly_Module(0, 0)
mod.ConnectToMMM(server)
mod.Subscribe(msg_type)

count = 0
send_times = np.zeros(5)

while True:
    msg = CMessage()
    rcv = mod.ReadMessage(msg, 0.1)
    if rcv == 1:
        count += 1

        send_times[-1] = msg.GetHeader().send_time
        send_times = np.roll(send_times, -1)

        if count > 2:
            # message id
            msg_str = "->"

            if type(mdf_type) != type(None):
                mdf = mdf_type()
                copy_from_msg(mdf, msg)

                try:
                    tag = mdf.tag
                    msg_str += "t: %s " % (str(len(tag)))
                except:
                    pass

                try:
                    id = mdf.sample_header.SerialNo
                    msg_str += "s: %05d  " % (id)
                except:
                    pass

                try:
                    # data
                    inp = eval('mdf.%s' % (attr))
                    if type(eval('mdf.%s' % (attr))).__name__.lower().find("array") < 0:
                        inp = [inp]
                    data = np.array(inp)
                    
                    if vec_col is None:
                        msg_str += " ".join(["%6.3f" % (x) for x in data])
                    else:
                        msg_str += "%6.3f" % data[vec_col]
                except:
                    try:
                        msg_str = str(eval('mdf.%s' % (attr)))
                    except:
                        pass

            # message time interval
            if count > 7:
                msg_str += " |  %0.03f" % (np.diff(send_times[-3:-1]))
            print(msg_str)
