# -*- coding: utf-8 -*-

import time

from core import proc
from log import log


class Task:
    def __init__(self, conn_id, data):
        self.conn_id = conn_id
        self.data = data
        self.create_time = time.time()


class Conn:
    def __init__(self, conn_id, writer):
        self.conn_id = conn_id
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


async def on_connection(reader, writer):
    log.info('on connect create')
    conn = Conn(proc.g_proc._seq.make_seq(), writer)
    proc.g_proc._conn_map[conn.conn_id] = conn

    while True:
        data = await reader.read(proc.g_proc._config.proc.tcp_server_recv_size)
        conn.update()
        if data is b'':
            log.info('on connect close')
            if conn.close():
                proc.g_proc._conn_map.pop(conn.conn_id)
            break
        else:
            log.info('Received %r from %r %r' % (data, conn.peername, conn.update_time))
            proc.g_proc._loop.run_in_executor(proc.g_proc._pool,
                                              doing,
                                              Task(conn.conn_id, data))


def doing(task):

    proc.g_proc._loop.call_soon_threadsafe(done, task)


def done(task):
    end = time.time()
    log.info('time end: ' + str(end) + ', diff: ' + str(end - task.create_time))
    conn = proc.g_proc._conn_map.get(task.conn_id)
    if conn is not None:
        log.info('Send: %r' % task.data)
        conn.write(task.data)
    else:
        log.info('conn_id is None: %d' % task.conn_id)