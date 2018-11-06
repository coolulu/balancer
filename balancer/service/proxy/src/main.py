# -*- coding: utf-8 -*-

import sys
import getopt

from config import config
from log import log


def main(argv):

    config_file = ''

    try:
        opts, args = getopt.getopt(argv, 'f:', ['config_file='])
    except getopt.GetoptError:
        print('python bin/proxy -f conf/proxy_0.json')
        sys.exit(-1)

    for opt, arg in opts:
        if opt in ("-i", "--ifile"):
            config_file = arg


    with open('./conf/proxy_0.json') as fd:
        str = fd.read(1024 * 1024)

    c = config.Config()
    b = c.load(str)

    b = c.reload(str)
    print(c)

    log.logger(c)
    log.info('11111')

    
    
    pass







