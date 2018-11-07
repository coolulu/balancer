# -*- coding: utf-8 -*-


class Timer:

    @staticmethod
    def check_timeout(proc):
        proc.check_flag()
        proc.on_check_idle()

        proc._loop.call_later(0.1, Timer.check_timeout, proc)

