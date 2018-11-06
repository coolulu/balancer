# -*- coding: utf-8 -*-

from define import Define
from log import log
from config import config
from config import service_config
from core import seq
from core import timer
from core import owner
from core import inservice_service


class Proc:

    s_reload_flag = False
    s_stop_flag = False

    @staticmethod
    def set_reload(b):
        Proc.s_reload_flag = b

    @staticmethod
    def set_stop(b):
        Proc.s_stop_flag = b

    def __init__(self, config_file):
        self._config_file = config_file
        self._config = config.Config()
        self._sc = service_config.ServiceConfig()
        self._seq = seq.Seq()
        self._timer = timer.Timer(self)
        self._timer = owner.Owner()
        self._inservice_service = inservice_service.InserviceService()

    def init(self):
        with open(self._config_file) as fd:
            config_json = fd.read(Define.BUFFER_SIZE)
        b = self._config.load(config_json)
        if not b:
            print('config load err')
            return -100

        print(self._config)
        return 0

    def start(self):
        log.info('start')

        pass

    def quit(self):
        log.info('quit')

        pass

    def loop(self):
        log.info('loop')

        pass

    def logging(self):
        log.logger(self._config)

    def check_flag(self):
        if Proc.s_reload_flag:
            Proc.s_reload_flag = False
            log.error('reload start')
            if self.reload():
                log.error('reload end')
            else:
                log.error('reload failed')

        if Proc.s_stop_flag:
            Proc.s_stop_flag = False
            log.error('reload start')
            self.quit()

    def reload(self):
        pass