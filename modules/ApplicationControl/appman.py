#!/usr/bin/python

import os
import re
import copy
import itertools as it
from glob import glob
from ConfigParser import SafeConfigParser
import subprocess as sp
import stat
from argparse import ArgumentParser
import platform
from PyDragonfly import Dragonfly_Module, MT_EXIT
import pid
import platform

CONFIG_DIR   = os.environ['BCI_CONFIG']
SRC_DIR      = os.environ['BCI_MODULES']
SCRIPT_FILE  = CONFIG_DIR + '/start_script'
LAST_FILE    = CONFIG_DIR + '/last_app.txt'
APPMAN_FILE  = 'appman.conf'
DEFAULT_HOST = platform.uname()[1]


def _convert_camel(name):
    '''
    Converts camel case name to underscored, lower case.
    '''
    s1 = re.sub('([^_])([A-Z][a-z]+)', r'\1_\2', name)
    return re.sub('([a-z0-9])([A-Z])', r'\1_\2', s1)


def _collect_files(locations, filenames):
    '''
    Makes a list of files matching any of `filenames` in any of `locations`.
    '''
    found_files = []
    for loc in locations:
        for f in filenames:
            found_files.extend(glob(loc + '/' + f))
    return found_files



def _prune_files(files):
    '''
    Removes any files ending with ~.
    '''
    files = copy.copy(files)
    i = 0
    while i < len(files):
        if files[i][-1] == '~':
            files.pop(i)
        else:
            i += 1
    return list(set(files))



def _detect_directory(module, verbose=False):
    '''
    Detect module directory based on its name
    '''
    #print "module", module
    directory = os.path.abspath(os.path.join(SRC_DIR, module))
    if not os.path.isdir(directory):
        raise ValueError("Failed to guess directory name" \
            "for module %s" % (module))
        #print "Warning: Failed to guess directory name for module %s" % (module)
    if verbose:
        print "Found directory: %s" % (directory)
    return directory



def _raise_no_files(search_string):
    '''
    '''
    msg_str = "No potential module files found\n." \
        "Looked for %s" % (search_string)
    raise ValueError(msg_str)



def _raise_too_many_files(potential_files):
    '''
    '''
    msg_str = "More than one potential file:\n"
    msg_str += '\n'.join(potential_files)
    raise ValueError(msg_str)



def _detect_module_file_and_type(module, directory, verbose=False):
    '''
    Detect module file based on its name. Return only basename (i.e. filename
    without directory).
    '''
    basepath = os.path.join(directory, module)

    # need to do two searches - one for module.*,
    # and one for * with no extension - to catch executable files

    # search_string needs to not have a '.' in order to match executables
    search_string = basepath + '.*'
    potential_module_files = glob(search_string)

    search_string = basepath
    potential_executables = glob(search_string)
    if len(potential_executables) > 0:
        potential_module_files.extend(glob(search_string))

    potential_module_files = _prune_files(potential_module_files)

    if len(potential_module_files) < 1:
        _raise_no_files(search_string)

    else: # have at least one potential file
        # try to find types of files, put in a dictionary
        typed_module_files = {}
        for f in potential_module_files:
            mtype = _detect_type(f)
            if mtype != None:
                typed_module_files[f] = mtype

        if len(typed_module_files) < 1:
            _raise_no_files(search_string)
        elif len(typed_module_files) > 1:
            _raise_too_many_files(potential_module_files)
        else:
            module_file = typed_module_files.keys()[0]
            module_type = typed_module_files.values()[0]
    if verbose:
        print "Found module file: %s" % (module_file)
    return os.path.basename(module_file), module_type



def _detect_type(module_file, fail_hard=False):
    ext = os.path.splitext(module_file)[1]
    if ext == '.py':
        return 'python'
    elif ext == '.m':
        return 'MATLAB'
    elif ext == '':
        return 'exe'
    else:
        if fail_hard:
            raise ValueError('Type not known for file %s' % (module_file))
        return None



def _detect_conf_file(module, app, verbose=False):
    '''
    Detect the config file based on naming convention.

    The convention is that the config file name will be all lower case,
    with underscores separating name parts, and with '.conf'
    (.ini-style files) or '.config' (structured text files) extension,
    and will be in the `app` or `default` directory.
    '''
    okay_exts = ['.conf', '.config']
    okay_bases = [module, _convert_camel(module)]
    if platform.system() == 'Linux':
        okay_bases.append(_convert_camel(module).lower())
    okay_file_names = [''.join(x) for x in it.product(okay_bases, okay_exts)]
    app_dir = os.path.join(CONFIG_DIR, app)
    default_dir = CONFIG_DIR + '/default'

    potential_conf_files = _collect_files([app_dir, default_dir],
                                          okay_file_names)
    potential_conf_files = _prune_files(potential_conf_files)

    if len(potential_conf_files) < 1:
        raise ValueError("No potential config files found.\n" \
                             "Searched for %s" % (okay_file_names))
    if len(potential_conf_files) > 1:
        msg_str = "Failed to identify config file.\n Potential files:\n"
        msg_str += "\n".join(potential_conf_files)
        raise ValueError(msg_str)
    return potential_conf_files[0]



def _detect_config(module, app, config, verbose=False):
    '''
    Automatic detection of several module configuration parameters:
        source directory, script/executable file, type, config file
    '''
    if not config.has_key('directory'):
        config['directory'] = _detect_directory(module, verbose=verbose)
    else:
        config['directory'] = os.path.expandvars(config['directory'])

    if not config.has_key('module_file'):
        module_file, module_type = \
            _detect_module_file_and_type(module, config['directory'])
        config['module_file'] = module_file
        config['type'] = module_type

    config.setdefault('type', \
        _detect_type(config['module_file'], fail_hard=True))

    # copy from config_file if it's present
    if config.has_key('config_file') and not config.has_key('conf_file'):
        config['conf_file'] = config['config_file']
        del config['config_file']
    if config.has_key('conf_file'):
        if config['conf_file'] != 'None':
            # if conf_file parameter starts with '/' in it, it is a full path
            # otherwise prepend app directory
            if config['conf_file'][0] != '/':
                app_dir = os.path.join(CONFIG_DIR, app)
                config['conf_file'] = os.path.join(app_dir, config['conf_file'])

            # bug out if file does not exist
            if not os.path.exists(config['conf_file']):
                raise ValueError('specified config file %s does not exist' % \
                    (config['conf_file']))
    else:
        config['conf_file'] = _detect_conf_file(module, app, verbose=verbose)
    config.setdefault('use_screen', True)



def _compose_line(module, app, config):
    '''
    Launch a module with a full config dictionary.
    '''
    killtag = config['killtag']
    mfile   = config['module_file'] # this is just file name (not + directory)
    mtype   = config['type']
    server  = config['server']
    conf_file = config['conf_file']
    directory = config['directory']
    matlab_env = config['matlab_env']
    use_screen = False if config['use_screen'] == 'False' else True     # use_screen=True means start minimized (default)

    os_name = platform.system()

    if mtype == 'python':
        if conf_file == '': conf_file = 'None'
        full_mfile = os.path.join(directory, mfile)

        if os_name == "Windows":
            cmd = 'start'
            if use_screen == True:
                cmd += ' /MIN '
            cmdline_items = [killtag, cmd, mtype, '"%s"' % full_mfile, '"%s"' % conf_file, server]

        else:
            cmdline_items = [killtag, mtype, full_mfile, conf_file, server]
        
    if mtype == 'MATLAB':
        if os_name == "Windows":
            cd = 'cd /D "%s" && ' % directory
        else:
            cd = 'cd %s;' % directory

        # extract .m file basename from `mfile`
        fn_name = os.path.splitext(mfile)[0]
        mline = '-r "%s(\'%s\', \'%s\')"' % (fn_name, conf_file, server)

        if os_name == "Windows":
        
            cmd = 'start matlab -nosplash'
            if use_screen == True:
                cmd += ' -minimize'
        
            cmdline_items = [cd, matlab_env, killtag, cmd, mline]
        else:
            cmdline_items = [cd, matlab_env, killtag, 'matlab-shell', mline]

    if mtype == 'exe':
        cmdline_items = [killtag, module, conf_file, server]

    cmdline = ' '.join(cmdline_items)

    if os_name == "Linux":
        # need to escape double-quotes for putting in screen argument
        cmdline = re.sub('"', r'\"', cmdline)
        cmdline = 'screen -d -m -t %s -S %s bash -i -c "%s"' % (module, module, cmdline)

        if use_screen == False:
            cmdline = "%s; gnome-terminal -e \"screen -r %s\" &" % (cmdline, module)

    return cmdline


def create_script(app, host, appman_file=None, \
                  mod=None, script_file=SCRIPT_FILE, \
                  config_dir=CONFIG_DIR):
    '''
    Generates a command line startup script from an appman.conf file

    Parameters
    ----------
    app : string
      name of the application to run
      this is the subdirectory of rp3/config
    config_dir : string
      path to config dir containing dir `app`
    module : string
      name of a single module to start

    '''

    if appman_file is None:
        appman_file = 'appman.conf'
    
    conf_file = os.path.join(config_dir, app, appman_file)
    parser = SafeConfigParser()
    if not os.path.isfile(conf_file):
        raise ValueError('%s not found' % (conf_file))
    parser.read(conf_file)

    script_file = script_file + '_' + host

    os_name = platform.system()
    if os_name == "Windows":
        script_file = script_file +  '.bat'
    else:
        script_file = script_file + '.sh'

    script = open(script_file, 'w')
    done_module = False
    for section in parser.sections():
        if section[:7] == 'module ':
            module = section[7:]
            if (module == mod) or (mod == None):
                done_module = True
                config = dict(parser.items(section))
                if 'host' not in config:
                    config['host'] = DEFAULT_HOST
                if config['host'] == host:
                    _detect_config(module, app, config)
                    line = _compose_line(module, app, config)
                    script.write(line + '\n')

    if (module != None) and (not done_module):
        raise ValueError('module %s not found' % (mod))
    script.close()

    #  set script file to be user readable, executable, and writable
    os.chmod(script_file, stat.S_IRUSR | stat.S_IXUSR | stat.S_IWUSR)
    #write_last(app)


def run_script(host, script_file=SCRIPT_FILE, config_dir=CONFIG_DIR):

    script_file = script_file + '_' + host

    os_name = platform.system()
    if os_name == "Linux":
        script_file = script_file + '.sh'
        #print 'Running %s' % (script_file)
        sp.Popen(['/bin/bash', script_file])

    elif os_name == "Windows":
        script_file = script_file + '.bat'
        #print 'Running %s' % (script_file)
        sp.Popen(script_file)


def get_host_modules(app, host_name=None, appman_file=None, config_dir=CONFIG_DIR):
    '''
    Get a list of all hosts in the appman.conf file, and a list of modules
    to start on each host. If a specific host is queried, return a list
    just for that host
    '''

    hosts = {}

    if appman_file is None:
        appman_file = 'appman.conf'

    conf_file = os.path.join(config_dir, app, appman_file)
    parser = SafeConfigParser()
    if not os.path.isfile(conf_file):
        raise ValueError('%s not found' % (conf_file))
    parser.read(conf_file)

    for section in parser.sections():
        if section[:7] == 'module ':
            module = section[7:]
            config = dict(parser.items(section))
            host = DEFAULT_HOST
            if 'host' in config:
                host = config['host']

            if host_name is not None:
                if host != host_name:
                    continue

            if host not in hosts:
                hosts[host] = []

            hosts[host].append(module)

    return hosts


def stop_modules(dragonfly):
    dragonfly.SendSignal(MT_EXIT)


def kill_modules():
    os_name = platform.system()
    if os_name == "Linux":
        pid.kill_all()


def write_last(app, last_file=LAST_FILE):
    f = open(last_file, 'w')
    f.write(app)
    f.close()


def get_last(last_file=LAST_FILE):
    try:
        f = open(last_file, 'r')
        app = f.read()
        f.close()
    except (OSError, IOError) as e:
        app = None

    if app is not None:
        app_dir = os.path.join(CONFIG_DIR, app)
        if not os.path.exists(app_dir):
            app = None

    return app

# command-line interface #####################################################

if __name__ == "__main__":
    os_name = platform.system()
    if os_name == "Windows":
        #print "running on windows"
        pass
    elif os_name == "Linux":
        #print "running on linux"
        pass
    else:
        print "ERROR: Unknown platform '{0}'!".format(os_name)

    parser = ArgumentParser(description="Create and run script for starting rp3 modules")

    okay_actions = ['start', 'stop', 'restart', 'kill']
    parser.add_argument(dest='action', choices=okay_actions, nargs='?')

    parser.add_argument('--mm-ip', type=str, default=None)
    parser.add_argument('--script-file', dest='script_file', type=str, default=SCRIPT_FILE)
    parser.add_argument('--last-file', dest='last_file', type=str, default=LAST_FILE)
    parser.add_argument('--appman-file', dest='appman_file', type=str)
    parser.add_argument('--host', dest='host', type=str, default=None)
    parser.add_argument(type=str, dest='others', nargs='*')
    args = parser.parse_args()

    #print '\n'.join(['  %s : %s' % (k, v) for k, v in args.__dict__.iteritems()])

    if args.action == 'start':
        if len(args.others) < 1:
            raise ValueError('start action requires at least one argument.')
        if len(args.others) >= 1:
            if args.others[0] == 'last':
                last_app = get_last(args.last_file)
                if last_app is None:
                    raise ValueError('Invalid last app (it no longer exists)')
                args.app = last_app
            else:
                args.app = args.others[0]
        if len(args.others) == 1:
            args.mod = None
        if len(args.others) > 1:
            args.mod = args.others[1]
        if len(args.others) > 2:
            raise ValueError('start action requires no more ' \
                'than two arguments.')

    elif args.action == 'restart':
        args.app = get_last(args.last_file)
        if len(args.others) == 0:
            args.mod = None
        if len(args.others) == 1:
            args.mod = args.others[0]
        if len(args.others) > 1:
            raise ValueError('restart action takes at most one argument')

    elif args.action == 'stop':
        if len(args.others) > 1:
            raise ValueError('stop action takes at most one argument')

    elif args.action == 'kill':
        if len(args.others) != 0:
            raise ValueError('kill action takes no arguments')

    if args.action in ['start', 'restart']:
        current_host = args.host
        if current_host is None:
            current_host = platform.uname()[1]

        create_script(args.app, current_host, appman_file=args.appman_file, script_file=args.script_file, mod=args.mod)
        write_last(args.app)
        run_script(current_host, script_file=args.script_file)

    elif args.action == 'stop':
        if args.mm_ip is None:
            raise ValueError('You need to specify Dragonfly server ip to stop modules (use --mm-ip)')

        mod = Dragonfly_Module(0, 0)
        mod.ConnectToMMM(args.mm_ip)
        stop_modules(mod)
        mod.DisconnectFromMMM()


    elif args.action == 'kill':
        kill_modules()




# ############################################################################
