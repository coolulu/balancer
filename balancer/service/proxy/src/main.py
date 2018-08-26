# -*- coding: utf-8 -*-

from src.config.Config import Config

def main():

    with open('./conf/proxy_0.json') as fd:
        str = fd.read(1024 * 1024)

    c = Config()
    c.load(str)

    c.reload(str)
    pass


if __name__ == '__main__':
    main()


