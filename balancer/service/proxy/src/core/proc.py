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

        self.conn_map = {}
        self.loop = None
        self.pool = None

        self.config_file = config_file
        self.config = config.Config()
        self.sc = service_config.ServiceConfig()
        self.seq = seq.Seq()
        self.owner = owner.Owner()
        self.inservice_service = inservice_service.InserviceService()

    def init(self):
        with open(self.config_file) as fd:
            config_json = fd.read(Define.BUFFER_SIZE)
        b = self.config.load(config_json)
        if not b:
            print('config load err')
            return -100

        print(self.config)
        return 0

    def start(self):
        log.g_logger.info('start')
        if self.pool is None:
            self.pool = futures.ThreadPoolExecutor(self.config.proxy.thread_size)

        if self.loop is None:
            self.loop = asyncio.get_event_loop()
            self.loop.call_later(0, timer.Timer.check_timeout, self)

    def quit(self):
        log.g_logger.info('quit')
        self.loop.stop()

    def looping(self):
        log.g_logger.info('looping')
        coro = asyncio.start_server(tcp_server.on_connection,
                                    self.config.net.tcp.ip,
                                    self.config.net.tcp.port,
                                    loop=self.loop)
        server = self.loop.run_until_complete(coro)
        log.g_logger.info('Serving on {}'.format(server.sockets[0].getsockname()))

        # Server requests until Ctrl+C is pressed
        try:
            self.loop.run_forever()
        except KeyboardInterrupt:
            pass

        # Close the server
        server.close()
        self.loop.run_until_complete(server.wait_closed())
        self.loop.close()

    def logging(self):
        log.logger(self.config)

    def check_flag(self):
        if Proc.s_reload_flag:
            Proc.s_reload_flag = False
            log.g_logger.error('reload start')
            if self.reload():
                log.g_logger.error('reload end')
            else:
                log.g_logger.error('reload failed')

        if Proc.s_stop_flag:
            Proc.s_stop_flag = False
            log.g_logger.error('stop start')
            self.quit()

    def reload(self):
        with open(self.config_file) as fd:
            config_json = fd.read(Define.BUFFER_SIZE)
        b = self.config.reload(config_json)
        if not b:
            log.g_logger.error('config load err')
            return False

        log.g_logger.info(self.config)
        return True

    def on_check_idle(self):
        now = time.time()
        timeout_list = []
        for k, v in self.conn_map.items():
            if now - v.update_time >= self.config.proc.tcp_server_idle:
                if v.close():
                    timeout_list.append(k)

        for l in timeout_list:
            self.conn_map.pop(l)
