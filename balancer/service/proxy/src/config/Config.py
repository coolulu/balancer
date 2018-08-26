# -*- coding: utf-8 -*-

import json


class Listen:
    def __init__(self):
        self.ip = ''
        self.port = 0

    def __str__(self):
        return ', '.join(['%s=%s' % item for item in self.__dict__.items()])


class Net:
    def __init__(self):
        self.tcp = Listen()
        self.http = Listen()

    def __str__(self):
        return '\n'.join(['%s:%s' % item for item in self.__dict__.items()])


class Log:
    def __init__(self):
        self.module = ''
        self.path = ''
        self.size = 0
        self.level = ''

    def __str__(self):
        return ', '.join(['%s=%s' % item for item in self.__dict__.items()])


class Proc:
    def __init__(self):
        self.tcp_server_idle = 0
        self.tcp_server_recv_packet_len_max = 0
        self.tcp_server_send_packet_len_max = 0

    def __str__(self):
        return ', '.join(['%s=%s' % item for item in self.__dict__.items()])


class Mysql:
    def __init__(self):
        self.host = ''
        self.port = 0
        self.user = ''
        self.passwd = ''
        self.db = ''

    def __str__(self):
        return ', '.join(['%s=%s' % item for item in self.__dict__.items()])


class Redis:
    def __init__(self):
        self.host = ''
        self.port = 0
        self.passwd = ''

    def __str__(self):
        return ', '.join(['%s=%s' % item for item in self.__dict__.items()])


class Mongodb:
    def __init__(self):
        self.host = ''
        self.port = 0
        self.username = ''
        self.password = ''
        self.authSource = ''

    def __str__(self):
        return ', '.join(['%s=%s' % item for item in self.__dict__.items()])


class Proxy:
    def __init__(self):
        self.mysql = Mysql()
        self.redis = Redis()
        self.mongodb = Mongodb()

    def __str__(self):
        return '\n'.join(['%s:%s' % item for item in self.__dict__.items()])


class Config:
    def __init__(self):
        self.net = Net()
        self.log = Log()
        self.proc = Proc()
        self.proxy = Proxy()

    def __str__(self):
        return '\n'.join(['%s.%s' % item for item in self.__dict__.items()])

    def load(self, str):
        d = json.loads(str)
        try:
            self.net.tcp.ip = d['net']['tcp']['ip']
            self.net.tcp.port = d['net']['tcp']['port']
            self.net.http.ip = d['net']['http']['ip']
            self.net.http.port = d['net']['http']['port']

            self.log.module = d['log']['module']
            self.log.path = d['log']['path']
            self.log.size = d['log']['size']
            self.log.level = d['log']['level']

            self.proc.tcp_server_idle = d['proc']['tcp_server_idle']
            self.proc.tcp_server_recv_packet_len_max = d['proc']['tcp_server_recv_packet_len_max']
            self.proc.tcp_server_send_packet_len_max = d['proc']['tcp_server_send_packet_len_max']

            self.proxy.mysql.host = d['proxy']['mysql']['host']
            self.proxy.mysql.port = d['proxy']['mysql']['port']
            self.proxy.mysql.user = d['proxy']['mysql']['user']
            self.proxy.mysql.passwd = d['proxy']['mysql']['passwd']
            self.proxy.mysql.db = d['proxy']['mysql']['db']

            self.proxy.redis.host = d['proxy']['redis']['host']
            self.proxy.redis.port = d['proxy']['redis']['port']
            self.proxy.redis.passwd = d['proxy']['redis']['passwd']

            self.proxy.mongodb.host = d['proxy']['mongodb']['host']
            self.proxy.mongodb.port = d['proxy']['mongodb']['port']
            self.proxy.mongodb.username = d['proxy']['mongodb']['username']
            self.proxy.mongodb.password = d['proxy']['mongodb']['password']
            self.proxy.mongodb.authSource = d['proxy']['mongodb']['authSource']
        except:
            return False
        return self.check()

    def reload(self, str):
        c = Config()
        b = c.load(str)
        if b:
            self.log = c.log
            self.proc = c.proc
        return b

    def check(self):
        c = Config()
        if type(self.net.tcp.ip) != type(c.net.tcp.ip):
            return False
        if type(self.net.tcp.port) != type(c.net.tcp.port):
            return False
        if type(self.net.http.ip) != type(c.net.http.ip):
            return False
        if type(self.net.http.port) != type(c.net.http.port):
            return False

        if type(self.log.module) != type(c.log.module):
            return False
        if type(self.log.path) != type(c.log.path):
            return False
        if type(self.log.size) != type(c.log.size):
            return False
        if type(self.log.level) != type(c.log.level):
            return False

        if type(self.proc.tcp_server_idle) != type(c.proc.tcp_server_idle):
            return False
        if type(self.proc.tcp_server_recv_packet_len_max) != type(c.proc.tcp_server_recv_packet_len_max):
            return False
        if type(self.proc.tcp_server_send_packet_len_max) != type(c.proc.tcp_server_send_packet_len_max):
            return False

        if type(self.proxy.mysql.host) != type(c.proxy.mysql.host):
            return False
        if type(self.proxy.mysql.port) != type(c.proxy.mysql.port):
            return False
        if type(self.proxy.mysql.user) != type(c.proxy.mysql.user):
            return False
        if type(self.proxy.mysql.passwd) != type(c.proxy.mysql.passwd):
            return False
        if type(self.proxy.mysql.db) != type(c.proxy.mysql.db):
            return False
        
        if type(self.proxy.redis.host) != type(c.proxy.redis.host):
            return False
        if type(self.proxy.redis.port) != type(c.proxy.redis.port):
            return False
        if type(self.proxy.redis.passwd) != type(c.proxy.redis.passwd):
            return False

        if type(self.proxy.mongodb.host) != type(c.proxy.mongodb.host):
            return False
        if type(self.proxy.mongodb.port) != type(c.proxy.mongodb.port):
            return False
        if type(self.proxy.mongodb.username) != type(c.proxy.mongodb.username):
            return False
        if type(self.proxy.mongodb.password) != type(c.proxy.mongodb.password):
            return False
        if type(self.proxy.mongodb.authSource) != type(c.proxy.mongodb.authSource):
            return False

        return True

