# -*- coding: utf-8 -*-

import sys
import getopt

from src.log import log
from src.core.signal_handle import SignalHandle
from src.core.proc import Proc

def main(argv):
    try:
        opts, args = getopt.getopt(argv, 'f:', ['config_file='])
    except getopt.GetoptError:
        print('nohup python bin/proxy -f conf/proxy_0.json > /dev/null 2 > &1 &')
        sys.exit(-10)

    config_file = ''
    for opt, arg in opts:
        if opt in ("-f", "config_file"):
            config_file = arg

    if config_file == 'config_file is empty':
        print()
        sys.exit(-20)

    print('config_file={}'.format(config_file))

    SignalHandle.init_signal()

    proc = Proc(config_file)
    ret = proc.init()
    if ret != 0:
        print('proc init error, ret={}'.format(ret))
        sys.exit(ret)

    proc.logging()
    proc.start()
    proc.looping()

    log.g_logger.error('stop end')

    sys.exit(0)








