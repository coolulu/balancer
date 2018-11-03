# -*- coding: utf-8 -*-

from config import config


def main():

    with open('./conf/proxy_0.json') as fd:
        str = fd.read(1024 * 1024)

    c = config.Config()
    b = c.load(str)

    b = c.reload(str)
    print(c)

    pass


if __name__ == '__main__':
    main()


