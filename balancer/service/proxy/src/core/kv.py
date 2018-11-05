# -*- coding: utf-8 -*-


class Kv:

    timeout = 'timeout'
    env = 'env'

    def __init__(self):
        self.timeout = 0
        self.env = ''

    def load_kv(self, kv_map):
        b = True

        self.get_uint(kv_map, Kv.timeout, self.timeout, b)
        self.get_str(kv_map, Kv.env, self.env, b)

        return b

    def get_str(self, kv_map, key, str, b):
        val = kv_map.get(key)
        if val is None:
            b = False
            return

        if len(val) == 0:
            b = False
            return

        str = val

    def get_uint(self, kv_map, key, i, b):
        val = kv_map.get(key)
        if val is None:
            b = False
            return

        if len(val) == 0:
            b = False
            return

        for s in val:
            if s < '0' or s > '9':
                b = False
                return

        i = int(val)




