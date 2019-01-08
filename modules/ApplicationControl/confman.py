import sys
import os
import wx
import re
from traits.api import Str, HasTraits, DelegatesTo, List, This, \
                                Dict, Any, Instance, Enum
from traitsui.api import View, Item, TreeEditor, TreeNode, Group
import subprocess
from argparse import ArgumentParser
from ConfigParser import SafeConfigParser
import appman

CONFIG_DIR = os.environ['BCI_CONFIG']

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
    editor = os.path.expandvars(os.environ['EDITOR'])
    subprocess.Popen([editor, name])


class CfgFile(HasTraits):
    name = Str
    config_name = Str
    parent = Any
    directory = Str 
    descendents = List
    config_type = Enum('MT', 'appman', 'XM', 'PVA', 'task_state',
                       'target_positions', 'start_positions',
                       'auto_control_config', 'grasp_event',
                       'auto_pilot', 'module_config', 'tool_change')

        
    def _descendents_default(self):
        if self.config_type == 'MT':
            multi_task_file = self.directory + '/' + self.name
            parser = SafeConfigParser()
            parser.read(multi_task_file)
            mt_config = dict(parser.items('config'))
            mt_app_list = re.sub(r"[\n\r]+", '', mt_config['config_names']).split(',') 
            l = []
            files = {'XM' : 'XM.config', 'appman' : 'appman.conf'}
            for app in mt_app_list:
                app_dir = CONFIG_DIR + '/' + app
                l.append(SubSession(name=app, files=files, directory=app_dir, parent=self))
    
        elif self.config_type == 'XM':
            fd = parse_XM_config(self.directory + '/' + self.name)
            task_state_config_files = fd['task_state_config_files']
            l = []
            for kid in task_state_config_files:
                l.append(CfgFile(name=kid, config_type='task_state', directory=self.directory,
                                 parent=self))
            if fd.has_key('tool_change_config_files'):
                tool_change_config_files = fd['tool_change_config_files']
                for kid in tool_change_config_files:
                    l.append(CfgFile(name=kid, config_type='tool_change', directory=self.directory,
                                     parent=self))
                                     
        elif self.config_type == 'task_state':
            fd = parse_XM_config(self.directory + '/' + self.name)
            l = [CfgFile(name=fd['target_configurations_file'],
                         config_type='target_positions', parent=self, directory=self.directory)]
        
        elif self.config_type == 'appman':
            parent_name = self.parent.name
            if parent_name == 'multi_task.config':
                parent_name = self.config_name
            l = []
            try:
                fd = parse_appman(self.directory + '/' + self.name, parent_name)
                kids = fd['module_config_files']
                for kid in kids:
                    l.append(CfgFile(name=os.path.relpath(kid, self.directory),
                             config_type='module_config', parent=self, directory=self.directory))
            except (ValueError) as e:
                print "Error while reading 'appman.conf' file: ", e
        else:
            l = []

        return l


class SubSession(HasTraits):
    name = Str
    directory = Str
    files = Dict
    descendents = List(CfgFile)

    def _descendents_default(self):
        return [CfgFile(name=v, config_type=k, directory=self.directory, parent=self, ) \
                    for k,v in self.files.iteritems()]


class Session(HasTraits):
    name = Str
    directory = Str
    files = Dict
    descendents = List

    def _descendents_default(self):
        for type, name in self.files.iteritems():
            return [CfgFile(name=v, config_type=k, directory=self.directory, parent=self, ) \
                    for k,v in self.files.iteritems()]


class CfgFileManager(HasTraits):
    session = Instance(Session)
    directory = Str
    name = Str
    files = Dict

    def _session_default(self):
        return Session(name=self.name,
                       directory=self.directory,
                       files=self.files)

    tree_editor = TreeEditor(
        nodes = [TreeNode(node_for = [ Session ],
                          children = 'descendents',
                          label = 'name',
                          rename=False,
                          delete=False,
                          view=View()),
                 TreeNode(node_for = [ SubSession ],
                          children = 'descendents',
                          label = 'name',
                          rename=False,
                          delete=False,
                          view=View()),                          
                 TreeNode(node_for = [ CfgFile ],
                          children = 'descendents',
                          label = 'name',
                          on_dclick = openFile,
                          rename=False,
                          delete=False,
                          view=View()
                          )],
                    hide_root=True, editable=False)

    view = View(Item(name='directory', show_label=False, style='readonly'),
                Item(editor=tree_editor, name='session', id='session', resizable=True, show_label=False),
                 resizable=True)

class MainWindow(wx.Frame):
    def __init__(self, parent, id, config_dir, session, root_files):
        directory = '%s/%s' % (config_dir, session)
        wx.Frame.__init__(self, parent, id, 'Config file tree', size=(800,400))
        self.cfg_file_manager = CfgFileManager(name=session, files=root_files, directory=directory)
        self.control = self.cfg_file_manager.edit_traits(parent=self, kind='subpanel').control
        self.Show(True)


if __name__ == "__main__":
    try:
        bci_config = os.environ.get('BCI_CONFIG')
    except KeyError:
        raise ValueError("Environment variable BCI_CONFIG is not set.")

    parser = ArgumentParser( \
        description="Manage config file tree for "
        "robot brain control experiment.")

    parser.add_argument('session', type=str, action='store')
    parser.add_argument('-x', '--xmfile',
                      dest='xm_file_name', default='XM.config',
                      metavar='xm_config_file name')
    #parser.add_argument('-p', '--pvafile',
    #                  dest='pva_file_name', default='Extraction.conf',
    #                  metavar='pva_config_file name')
    parser.add_argument('-a', '--appman_file',
                        dest='appman_file_name', default='appman.conf',
                        metavar='appman_file_name')
    parser.add_argument('-r', '--root',
                      dest='config_dir', default=bci_config,
                      metavar='/path/to/config/dir/root')
    args = parser.parse_args()

    #print "Loading from: %s\nXM file:  %s; \nPVA file: %s" % \
    #    (directory, options.xm_file_name, options.pva_file_name)

    root_files = {'XM'     : args.xm_file_name,
                  #'PVA'    : args.pva_file_name,
                  'appman' : args.appman_file_name}

    app = wx.App(False)
    frame = MainWindow(None, wx.ID_ANY, args.config_dir, args.session, root_files)
    app.MainLoop()
