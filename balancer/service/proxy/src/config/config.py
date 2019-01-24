# -*- coding: utf-8 -*-

import json
from src.tool import util


class Listen:
    def __init__(self):
        self.ip = ''
        self.port = 0


class Net:
    def __init__(self):
        self.tcp = Listen()
        self.http = Listen()


class Log:
    def __init__(self):
        self.module = ''
        self.path = ''
        self.size = 0
        self.level = ''


class Proc:
    def __init__(self):
        self.tcp_server_idle = 0
        self.tcp_server_recv_packet_len_max = 0
        self.tcp_server_send_packet_len_max = 0
        self.tcp_server_recv_size = 0


class Mysql:
    def __init__(self):
        self.host = ''
        self.port = 0
        self.user = ''
        self.passwd = ''
        self.db = ''


class Redis:
    def __init__(self):
        self.host = ''
        self.port = 0
        self.passwd = ''


class Mongodb:
    def __init__(self):
        self.host = ''
        self.port = 0
        self.username = ''
        self.password = ''
        self.authSource = ''


class Proxy:
    def __init__(self):
        self.thread_size = 0
        self.mysql = Mysql()
        self.redis = Redis()
        self.mongodb = Mongodb()


class Config:
    def __init__(self):
        self.net = Net()
        self.log = Log()
        self.proc = Proc()
        self.proxy = Proxy()

    def __str__(self):
        str = 'Config.to_string'
        str += ', net.tcp.ip=%s' % self.net.tcp.ip
        str += ', net.tcp.port=%d' % self.net.tcp.port
        str += '  net.http.ip=%s' % self.net.http.ip
        str += ', net.http.port=%d' % self.net.http.port

        str += ', self.log.module=%s' % self.log.module
        str += ', self.log.path=%s' % self.log.path
        str += ', self.log.size=%d' % self.log.size
        str += ', self.log.level=%s' % self.log.level

        str += ', proc.tcp_server_idle=%d' % self.proc.tcp_server_idle
        str += ', proc.tcp_server_recv_packet_len_max=%d' % self.proc.tcp_server_recv_packet_len_max
        str += ', proc.tcp_server_send_packet_len_max=%d' % self.proc.tcp_server_send_packet_len_max
        str += ', proc.tcp_server_recv_size=%d' % self.proc.tcp_server_recv_size

        str += ', proxy.thread_size=%d' % self.proxy.thread_size

        str += ', proxy.mysql.host=%s' % self.proxy.mysql.host
        str += ', proxy.mysql.port=%d' % self.proxy.mysql.port
        str += ', proxy.mysql.user=%s' % self.proxy.mysql.user
        str += ', proxy.mysql.passwd=%s' % self.proxy.mysql.passwd
        str += ', proxy.mysql.db=%s' % self.proxy.mysql.db

        str += ', proxy.redis.host=%s' % self.proxy.redis.host
        str += ', proxy.redis.port=%d' % self.proxy.redis.port
        str += ', proxy.redis.passwd=%s' % self.proxy.redis.passwd

        str += ', proxy.mongodb.host=%s' % self.proxy.mongodb.host
        str += ', proxy.mongodb.port=%d' % self.proxy.mongodb.port
        str += ', proxy.mongodb.username=%s' % self.proxy.mongodb.username
        str += ', proxy.mongodb.password=%s' % self.proxy.mongodb.password
        str += ', proxy.mongodb.authSource=%s' % self.proxy.mongodb.authSource

        return str

    def load(self, str):
        jo = json.loads(str, object_hook=util.JsonObject)

        try:
            self.net.tcp.ip = jo.net.tcp.ip
            self.net.tcp.port = jo.net.tcp.port
            self.net.http.ip = jo.net.http.ip
            self.net.http.port = jo.net.http.port

            self.log.module = jo.log.module
            self.log.path = jo.log.path
            self.log.size = jo.log.size
            self.log.level = jo.log.level

            self.proc.tcp_server_idle = jo.proc.tcp_server_idle
            self.proc.tcp_server_recv_packet_len_max = jo.proc.tcp_server_recv_packet_len_max
            self.proc.tcp_server_send_packet_len_max = jo.proc.tcp_server_send_packet_len_max
            self.proc.tcp_server_recv_size = jo.proc.tcp_server_recv_size

            self.proxy.thread_size = jo.proxy.thread_size

            self.proxy.mysql.host = jo.proxy.mysql.host
            self.proxy.mysql.port = jo.proxy.mysql.port
            self.proxy.mysql.user = jo.proxy.mysql.user
            self.proxy.mysql.passwd = jo.proxy.mysql.passwd
            self.proxy.mysql.db = jo.proxy.mysql.db

            self.proxy.redis.host = jo.proxy.redis.host
            self.proxy.redis.port = jo.proxy.redis.port
            self.proxy.redis.passwd = jo.proxy.redis.passwd

            self.proxy.mongodb.host = jo.proxy.mongodb.host
            self.proxy.mongodb.port = jo.proxy.mongodb.port
            self.proxy.mongodb.username = jo.proxy.mongodb.username
            self.proxy.mongodb.password = jo.proxy.mongodb.password
            self.proxy.mongodb.authSource = jo.proxy.mongodb.authSource

        except Exception as e:
            print(e)
            return False
        return self.check()

    def reload(self, str):
        c = Config()
        b = c.load(str)
        if b:
            # self.log = c.log # 日志不支持reload
            self.proc = c.proc
        return b

    def check(self):
        c = Config()
        if type(self.net.tcp.ip) != type(c.net.tcp.ip) or self.net.tcp.ip == c.net.tcp.ip:
            return False
        if type(self.net.tcp.port) != type(c.net.tcp.port) or self.net.tcp.port == c.net.tcp.port:
            return False
        if type(self.net.http.ip) != type(c.net.http.ip) or self.net.http.ip == c.net.http.ip:
            return False
        if type(self.net.http.port) != type(c.net.http.port) or self.net.http.port == c.net.http.port:
            return False

        if type(self.log.module) != type(c.log.module) or self.log.module == c.log.module:
            return False
        if type(self.log.path) != type(c.log.path) or self.log.path == c.log.path:
            return False
        if type(self.log.size) != type(c.log.size) or self.log.size == c.log.size:
            return False
        if type(self.log.level) != type(c.log.level) or self.log.level == c.log.level:
            return False

        if type(self.proc.tcp_server_idle) != type(c.proc.tcp_server_idle) or \
                self.proc.tcp_server_idle == c.proc.tcp_server_idle:
            return False
        if type(self.proc.tcp_server_recv_packet_len_max) != type(c.proc.tcp_server_recv_packet_len_max) or \
                self.proc.tcp_server_recv_packet_len_max == c.proc.tcp_server_recv_packet_len_max:
            return False
        if type(self.proc.tcp_server_send_packet_len_max) != type(c.proc.tcp_server_send_packet_len_max) or \
                self.proc.tcp_server_send_packet_len_max == c.proc.tcp_server_send_packet_len_max:
            return False
        if type(self.proc.tcp_server_recv_size) != type(c.proc.tcp_server_recv_size) or \
                self.proc.tcp_server_recv_size == c.proc.tcp_server_recv_size:
            return False

        if type(self.proxy.thread_size) != type(c.proxy.thread_size) or self.proxy.thread_size == c.proxy.thread_size:
            return False

        if type(self.proxy.mysql.host) != type(c.proxy.mysql.host) or self.proxy.mysql.host == c.proxy.mysql.host:
            return False
        if type(self.proxy.mysql.port) != type(c.proxy.mysql.port) or self.proxy.mysql.port == c.proxy.mysql.port:
            return False
        if type(self.proxy.mysql.user) != type(c.proxy.mysql.user) or self.proxy.mysql.user == c.proxy.mysql.user:
            return False
        if type(self.proxy.mysql.passwd) != type(c.proxy.mysql.passwd) or self.proxy.mysql.passwd == c.proxy.mysql.passwd:
            return False
        if type(self.proxy.mysql.db) != type(c.proxy.mysql.db) or self.proxy.mysql.db == c.proxy.mysql.db:
            return False
        
        if type(self.proxy.redis.host) != type(c.proxy.redis.host) or self.proxy.redis.host == c.proxy.redis.host:
            return False
        if type(self.proxy.redis.port) != type(c.proxy.redis.port) or self.proxy.redis.port == c.proxy.redis.port:
            return False
        if type(self.proxy.redis.passwd) != type(c.proxy.redis.passwd) or self.proxy.redis.passwd == c.proxy.redis.passwd:
            return False

        if type(self.proxy.mongodb.host) != type(c.proxy.mongodb.host) or \
                self.proxy.mongodb.host == c.proxy.mongodb.host:
            return False
        if type(self.proxy.mongodb.port) != type(c.proxy.mongodb.port) or \
                self.proxy.mongodb.port == c.proxy.mongodb.port:
            return False
        if type(self.proxy.mongodb.username) != type(c.proxy.mongodb.username) or \
                self.proxy.mongodb.username == c.proxy.mongodb.username:
            return False
        if type(self.proxy.mongodb.password) != type(c.proxy.mongodb.password) or \
                self.proxy.mongodb.password == c.proxy.mongodb.password:
            return False
        if type(self.proxy.mongodb.authSource) != type(c.proxy.mongodb.authSource) or \
                self.proxy.mongodb.authSource == c.proxy.mongodb.authSource:
            return False

        return True




