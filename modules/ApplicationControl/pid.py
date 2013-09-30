import os
import sys
#print os.setpgid(0, 0)
from subprocess import Popen, PIPE
import shlex
import re

def find_all(username='vr', envar='DRAGONFLY_KILLTAG'):
    '''
    Kill all processes with a particular environment variable set.
    '''
    search_line = 'find /proc/ -name environ -maxdepth 2 -user %s -exec grep -l --binary-files=text %s {} \;' \
        % (username, envar)
    # maxdepth enforces find only to search pid (and neighbouring) directories, and not deeper
    # shlex isn't strictly necessary here, but does smarter splitting than the default
    args = shlex.split(search_line)

    # piping to /dev/null gets rid of error messages
    null = open('/dev/null')

    # run the find command
    sp = Popen(args, stdout=PIPE, stderr=null)

    # ... and collect its output
    output = sp.communicate()[0]
    null.close()

    # find instances of /proc/#### in result string and return only the pid #s
    # wrapping in a python set removes non-unique occurrences
    pids = [int(x) for x in set(re.findall('(?<=/proc/)\d+', output))]
    return pids


def kill_all(username='vr', envar='DRAGONFLY_KILLTAG'):

    pids = find_all(username=username, envar=envar)

    for pid in pids:
        #print "Killing %d" % (pid)
        # kill by pid with signal number 9, SIGKILL
        # (use 15 = SIGTERM to really kill)
        os.kill(pid, 9)
