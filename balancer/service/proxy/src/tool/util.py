# -*- coding: UTF-8 -*-

import time

class JsonObject:
    def __init__(self, d):
        self.__dict__ = d


def now_s():
    return int(time.time())


def uiui2ull(high, low):
    return (high << 32) + low
