# -*- coding: utf-8 -*-

import time
import asyncio
from concurrent import futures

from define import Define
from log import log
from config import config
from config import service_config
from core import seq
from core import timer
from core import owner
from core import inservice_service
from core import tcp_server

g_proc = None


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
        global g_proc
        g_proc = self

        self._conn_map = {}
        self._loop = None
        self._pool = None

        self._config_file = config_file
        self._config = config.Config()
        self._sc = service_config.ServiceConfig()
        self._seq = seq.Seq()
        self._owner = owner.Owner()
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
        if self._pool is None:
            self._pool = futures.ThreadPoolExecutor(self._config.proxy.thread_size)

        if self._loop is None:
            self._loop = asyncio.get_event_loop()
            self._loop.call_later(0, timer.Timer.check_timeout, self)

    def quit(self):
        log.info('quit')
        self._loop.stop()

    def loop(self):
        log.info('loop')
        coro = asyncio.start_server(tcp_server.on_connection,
                                    self._config.net.tcp.ip,
                                    self._config.net.tcp.port,
                                    loop=self._loop)
        server = self._loop.run_until_complete(coro)
        log.info('Serving on {}'.format(server.sockets[0].getsockname()))

        # Server requests until Ctrl+C is pressed
        try:
            self._loop.run_forever()
        except KeyboardInterrupt:
            pass

        # Close the server
        server.close()
        self._loop.run_until_complete(server.wait_closed())
        self._loop.close()

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
            log.error('stop start')
            self.quit()

    def reload(self):
        with open(self._config_file) as fd:
            config_json = fd.read(Define.BUFFER_SIZE)
        b = self._config.reload(config_json)
        if not b:
            log.error('config load err')
            return False

        log.info(self._config)
        return True

    def on_check_idle(self):
        now = time.time()
        timeout_list = []
        for k, v in self._conn_map.items():
            if now - v.update_time >= self._config.proc.tcp_server_idle:
                if v.close():
                    timeout_list.append(k)

        for l in timeout_list:
            self._conn_map.pop(l)
