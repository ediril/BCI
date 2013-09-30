import sys
import os
import wx
from enthought.traits.api import Str, HasTraits, DelegatesTo, List, This, \
Dict, Any, Instance, Enum
from enthought.traits.ui.api import View, Item, TreeEditor, TreeNode, Group
import subprocess
from argparse import ArgumentParser
from ConfigParser import SafeConfigParser
import appman

def parse_multiline(f):
    line = f.readline().strip()
    items = []
    while line != '}':
        items.append(line)
        line = f.readline().strip()
    return items

def parse_XM_config(filename):
    f = open(filename, 'r')
    data = {}
    line = f.readline().strip()

    # get config: line
    while line[-1] != ':':
        line = f.readline().strip()

    # until last line
    line = f.readline().strip()
    while line[-1] != ';':
        # check for multiline
        items = [x.strip() for x in line.split()]
        if len(items) > 1:
            k = items[0]
            if (len(items) == 2) and (items[1] == '{'):
                data[k] = parse_multiline(f)
            else:
                if (len(items) == 2):
                    data[k] = items[1]
                else:
                    data[k] = items[1:]
        line = f.readline().strip()
    return data

def parse_appman(filename, app):
    print filename
    parser = SafeConfigParser()
    parser.read(filename)

    # data has to be a dictionary of descriptions (keys) and filenames (values)
    data = {'module_config_files': set()}
    modules = []
    for section in parser.sections():
        if section[:7] == 'module ':
            module = section[7:]

            config = dict(parser.items(section))
            appman._detect_config(module, app, config)
            if config['conf_file'] != 'None':
                data['module_config_files'].add(config['conf_file'])
    return data

def openFile(node):
    name = node.directory + '/' + node.name
    editor = os.environ['EDITOR']
    subprocess.Popen([editor, name])

class CfgFile(HasTraits):
    name = Str
    parent = Any
    directory = DelegatesTo('parent')
    descendents = List(This)
    config_type = Enum('appman', 'XM', 'PVA', 'task_state',
                       'target_positions', 'start_positions',
                       'auto_control_config', 'grasp_event',
                       'auto_pilot', 'module_config', 'tool_change')

    def _descendents_default(self):
        if self.config_type == 'XM':
            fd = parse_XM_config(self.directory + '/' + self.name)
            task_state_config_files = fd['task_state_config_files']
            l = []
            for kid in task_state_config_files:
                l.append(CfgFile(name=kid, config_type='task_state',
                                 parent=self))
            if fd.has_key('tool_change_config_files'):
                tool_change_config_files = fd['tool_change_config_files']
                for kid in tool_change_config_files:
                    l.append(CfgFile(name=kid, config_type='tool_change',
                                     parent=self))

        elif self.config_type == 'task_state':
            fd = parse_XM_config(self.directory + '/' + self.name)
            l = [CfgFile(name=fd['target_configurations_file'],
                         config_type='target_positions', parent=self)]
        elif self.config_type == 'appman':
            fd = parse_appman(self.directory + '/' + self.name, self.parent.name)
            kids = fd['module_config_files']
            l = []
            for kid in kids:
                l.append(CfgFile(name=os.path.relpath(kid, self.directory),
                                 config_type='module_config', parent=self))
        else:
            l = []
        return l

class Session(HasTraits):
    name = Str
    directory = Str
    files = Dict
    descendents = List(CfgFile)

    def _descendents_default(self):
        return [CfgFile(name=v, config_type=k, parent=self, ) \
                    for k,v in self.files.iteritems()]

class ModuleManager(HasTraits):
    text = Str

    view = View(
                Item(name='text', show_label=False, style='readonly', resizable=True)
               )

class MainWindow(wx.Frame):
    def __init__(self, parent, id, text, callback):
        wx.Frame.__init__(self, parent, id, 'Module List', size=(800,400))
        self.module_manager = ModuleManager(text = text)
        self.control = self.module_manager.edit_traits(parent=self, kind='subpanel').control
        self.closing_callback = callback
        self.Show(True)
        self.Bind(wx.EVT_CLOSE, self.OnCloseWindow)

    def update_text(self, new_text):
        print "yeeey"
        self.module_manager.text = new_text

    def OnCloseWindow(self, event):
        self.closing_callback()
        self.Destroy()

#if __name__ == "__main__":
#    try:
#        robot_config = os.environ.get('ROBOT_CONFIG')
#    except KeyError:
#        raise ValueError("Environment variable ROBOTDATA is not set.")
#
#    parser = ArgumentParser( \
#        description="Manage config file tree for "
#        "robot brain control experiment.")
#
#    parser.add_argument('session', type=str, action='store')
#    parser.add_argument('-x', '--xmfile',
#                      dest='xm_file_name', default='XM.config',
#                      metavar='xm_config_file name')
#    parser.add_argument('-p', '--pvafile',
#                      dest='pva_file_name', default='Extraction.conf',
#                      metavar='pva_config_file name')
#    parser.add_argument('-a', '--appman_file',
#                        dest='appman_file_name', default='appman.conf',
#                        metavar='appman_file_name')
#    parser.add_argument('-r', '--root',
#                      dest='config_dir', default=robot_config,
#                      metavar='/path/to/config/dir/root')
#    args = parser.parse_args()
#
#    #print "Loading from: %s\nXM file:  %s; \nPVA file: %s" % \
#    #    (directory, options.xm_file_name, options.pva_file_name)
#
#    root_files = {'XM'     : args.xm_file_name,
#                  'PVA'    : args.pva_file_name,
#                  'appman' : args.appman_file_name}
#
#    app = wx.PySimpleApp()
#    frame = MainWindow(None, wx.ID_ANY, args.config_dir, args.session, root_files)
#    app.MainLoop()
