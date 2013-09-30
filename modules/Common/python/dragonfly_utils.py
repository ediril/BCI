
from PyDragonfly import CMessage, copy_from_msg, copy_to_msg
import Dragonfly_config as rc
    
    
def respond_to_ping(mod, msg, module_name):
    dest_mod_id = msg.GetHeader().dest_mod_id
    p = rc.MDF_PING()
    copy_from_msg(p, msg)
    
    #print "PING received for '{0}'".format(p.module_name)

    if (p.module_name.lower() == module_name.lower()) or (p.module_name == "*") or \
        (dest_mod_id == mod.GetModuleID()):
        mdf = rc.MDF_PING_ACK()
        mdf.module_name = module_name
        msg_out = CMessage(rc.MT_PING_ACK)
        copy_to_msg(mdf, msg_out)
        mod.SendMessage(msg_out)
       