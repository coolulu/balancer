# -*- coding: utf-8 -*-

from config import config
from log import log



def main():

    with open('./conf/proxy_0.json') as fd:
        str = fd.read(1024 * 1024)

    c = config.Config()
    b = c.load(str)

    b = c.reload(str)
    print(c)

    log.logger(c)
    log.info('11111')

    pass







