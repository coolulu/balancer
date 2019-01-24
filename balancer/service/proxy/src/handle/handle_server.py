# -*- coding: utf-8 -*-

import time

from src.log import log
from src.core import proc


def handle_request(task):

    proc.g_proc.loop.call_soon_threadsafe(handle_request_send, task)


def handle_request_send(task):
    end = time.time()
    log.g_logger.info('time end: ' + str(end) + ', diff: ' + str(end - task.create_time))
    conn = proc.g_proc.conn_map.get(task.conn_id)
    if conn is not None:
        log.g_logger.info('Send: %r' % task.data)
        conn.write(task.data)
    else:
        log.g_logger.info('conn_id is None: %d' % task.conn_id)