# -*- coding: utf-8 -*-

import signal

from core import proc


class SignalHandle:

    @staticmethod
    def init_signal():
        if hasattr(signal, 'SIGPIPE'):
            signal.signal(getattr(signal, 'SIGPIPE'), signal.SIG_IGN)

        if hasattr(signal, 'SIGUSR1'):
            signal.signal(getattr(signal, 'SIGUSR1'), SignalHandle.set_reload_flag)

        if hasattr(signal, 'SIGUSR2'):
            signal.signal(getattr(signal, 'SIGUSR2'), SignalHandle.set_stop_flag)

    @staticmethod
    def set_reload_flag(sig, frame):
        proc.Proc.set_reload(True)

    @staticmethod
    def set_stop_flag(sig, frame):
        proc.Proc.set_stop(True)


