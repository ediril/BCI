from time import sleep
from time import time
from subprocess import Popen, PIPE

def get_screen_list():
    Popen(['clear'])
    ps = Popen(['screen', '-ls'], stdout=PIPE)
    (stdout, stderr) = ps.communicate()
    print stdout


def loop():
    prev_time = time()

    while True:
        get_screen_list()
        
        this_time = time()
        diff_time = this_time - prev_time
        if diff_time < 1.:
            sleep(1. - diff_time)
        
        prev_time = this_time
        
        
if __name__ == "__main__":
    loop()
