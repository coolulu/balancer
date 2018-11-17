# -*- coding: utf-8 -*-

import time


class Task:
    def __init__(self, conn_id, data):
        self.conn_id = conn_id
        self.data = data
        self.create_time = time.time()