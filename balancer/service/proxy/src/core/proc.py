# -*- coding: utf-8 -*-


class Proc:

    s_reload_flag = False
    s_stop_flag = False

    @staticmethod
    def set_reload(b):
        Proc.s_reload_flag = b

    @staticmethod
    def set_stop(b):
        Proc.s_stop_flag = b

    def __init__(self):
        pass