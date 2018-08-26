# -*- coding: utf-8 -*-

import json


class Heartbeat:
    def __init__(self):
        self.heartbeat_enable = False
        self.heartbeat_gap = 0
        self.lose_time = 0
        self.recover_time = 0

    def load(self, d):
        self.heartbeat_enable = d['heartbeat_enable']
        self.heartbeat_gap = d['heartbeat_gap']
        self.lose_time = d['lose_time']
        self.recover_time = d['recover_time']

        heartbeat = Heartbeat()
        if type(heartbeat.heartbeat_enable) != type(self.heartbeat_enable):
            raise Exception('type failed')
        if type(heartbeat.heartbeat_gap) != type(self.heartbeat_gap):
            raise Exception('type failed')
        if type(heartbeat.lose_time) != type(self.lose_time):
            raise Exception('type failed')
        if type(heartbeat.recover_time) != type(self.recover_time):
            raise Exception('type failed')


class Depend:
    def __init__(self):
        self.depend_service_id = 0

    def load(self, d):
        self.depend_service_id = d['depend_service_id']

        depend = Depend()
        if type(depend.depend_service_id) != type(self.depend_service_id):
            raise Exception('type failed')


class KV:
    def __init__(self):
        self.key = ''
        self.val = ''

    def load(self, d):
        self.key = d['key']
        self.val = d['val']

        kv = KV()
        if type(kv.key) != type(self.key):
            raise Exception('type failed')
        if type(kv.val) != type(self.val):
            raise Exception('type failed')


class IPInfo:
    def __init__(self):
        self.proc_id = 0
        self.proc_des = ''
        self.in_ip = ''
        self.out_ip = ''
        self.port = 0

    def load(self, d):
        self.proc_id = d['proc_id']
        self.proc_des = d['proc_des']
        self.in_ip = d['in_ip']
        self.out_ip = d['out_ip']
        self.port = d['port']

        ip_info = IPInfo()
        if type(ip_info.proc_id) != type(self.proc_id):
            raise Exception('type failed')
        if type(ip_info.proc_des) != type(self.proc_des):
            raise Exception('type failed')
        if type(ip_info.in_ip) != type(self.in_ip):
            raise Exception('type failed')
        if type(ip_info.out_ip) != type(self.out_ip):
            raise Exception('type failed')
        if type(ip_info.port) != type(self.port):
            raise Exception('type failed')


class Service:
    def __init__(self):
        self.service_id = 0
        self.service_name = ''
        self.heartbeat = Heartbeat()
        self.depend_map = []
        self.kv_map = []
        self.heartbeat_list = []
        self.inservice_list = []

    def load(self, d):
        self.service_id = d['service_id']
        self.service_name = d['service_name']
        self.heartbeat.load(d['heartbeat'])
        for n in d['depend_map']:
            depend = Depend()
            depend.load(n)
            self.depend_map.append(depend)
        for n in d['kv_map']:
            kv = KV()
            kv.load(n)
            self.kv_map.append(kv)
        for n in d['heartbeat_list']:
            ip_info = IPInfo()
            ip_info.load(n)
            self.heartbeat_list.append(ip_info)
        for n in d['inservice_list']:
            ip_info = IPInfo()
            ip_info.load(n)
            self.inservice_list.append(ip_info)

        service = Service()
        if type(service.service_id) != type(self.service_id):
            raise Exception('type failed')
        if type(service.service_name) != type(self.service_name):
            raise Exception('type failed')
        if type(service.heartbeat) != type(self.heartbeat):
            raise Exception('type failed')
        if type(service.depend_map) != type(self.depend_map):
            raise Exception('type failed')
        if type(service.kv_map) != type(self.kv_map):
            raise Exception('type failed')
        if type(service.heartbeat_list) != type(self.heartbeat_list):
            raise Exception('type failed')
        if type(service.inservice_list) != type(self.inservice_list):
            raise Exception('type failed')


class ServiceConfig:
    def __init__(self):
        self.service_map = {}

    def json_to_map(self, str):
        d = json.loads(str)
        try:
            for n in d['service_map']:
                service = Service()
                service.load(n)
                self.service_map[service.service_id] = service
        except:
            return False
        return True


str = '{"service_map":[{"service_id":10100,"service_name":"gate","heartbeat":{"heartbeat_enable":true,"heartbeat_gap":5,"lose_time":3,"recover_time":5},"depend_map":[{"depend_service_id":10200}],"kv_map":[{"key":"timeout","val":"30"},{"key":"env","val":"test"}],"heartbeat_list":[{"proc_id":100,"proc_des":"gate_1_0","in_ip":"121.1.1.1","out_ip":"11.1.1.1","port":10100}],"inservice_list":[{"proc_id":200,"proc_des":"gate_2_0","in_ip":"121.1.1.2","out_ip":"11.1.1.2","port":10100}]},{"service_id":10200,"service_name":"group","heartbeat":{"heartbeat_enable":true,"heartbeat_gap":5,"lose_time":3,"recover_time":5},"depend_map":[{"depend_service_id":10100}],"kv_map":[{"key":"name_max_size","val":"1024"},{"key":"buffer_max_size","val":"1024"}],"heartbeat_list":[{"proc_id":100,"proc_des":"group_1_0","in_ip":"121.1.1.10","out_ip":"11.1.1.10","port":10200}],"inservice_list":[{"proc_id":200,"proc_des":"group_2_0","in_ip":"121.1.1.20","out_ip":"11.1.1.20","port":10200},{"proc_id":201,"proc_des":"group_2_1","in_ip":"121.1.1.21","out_ip":"11.1.1.21","port":10201}]}]}'

sc = ServiceConfig()
sc.json_to_map(str)

print(sc)

