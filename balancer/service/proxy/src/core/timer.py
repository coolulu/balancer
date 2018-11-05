# -*- coding: utf-8 -*-


class Timer:

    def __init__(self, proc):
        self._proc = proc

    def check_timeout(self):
        self._proc.check_flag()


