# -*- coding: utf-8 -*-

import time

from log import log
from core import proc
from core import task
from handle import handle_server


async def on_connection(reader, writer):
    log.g_logger.info('on connect create')
    conn = Conn(proc.g_proc.seq.make_seq(), writer)
    proc.g_proc.conn_map[conn.conn_id] = conn

    while True:
        data = await reader.read(proc.g_proc.config.proc.tcp_server_recv_size)
        conn.update()
        if data is b'':
            log.g_logger.info('on connect close')
            if conn.close():
                proc.g_proc.conn_map.pop(conn.conn_id)
            break
        else:
            log.g_logger.info('Received %r from %r %r' % (data, conn.peername, conn.update_time))
            proc.g_proc.loop.run_in_executor(proc.g_proc.pool,
                                             handle_server.handle_request,
                                             task.Task(conn.conn_id, data))


class Conn:
    def __init__(self, conn_id, writer):
        self.conn_id = conn_id
        self.stream_buffer = b''
        self.writer = writer
        self.peername = writer.get_extra_info('peername')
        self.socket = writer.get_extra_info('socket')
        self.is_close = False
        self.create_time = time.time()
        self.update_time = self.create_time

    def update(self):
        self.update_time = time.time()

    def write(self, data):
        self.writer.write(data)
        self.update_time = time.time()

    def close(self):
        if not self.is_close:
            self.is_close = True
            self.writer.close()
            self.update_time = time.time()
            return True
        else:
            return False

    def append(self, data):
            self.stream_buffer += data