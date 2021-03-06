# -*- coding: utf-8 -*-

import json
from src.tool import util


class Heartbeat:
    def __init__(self):
        self.heartbeat_enable = False
        self.heartbeat_gap = 0
        self.lose_time = 0
        self.recover_time = 0

    def load(self, jo):
        self.heartbeat_enable = jo.heartbeat_enable
        self.heartbeat_gap = jo.heartbeat_gap
        self.lose_time = jo.lose_time
        self.recover_time = jo.recover_time

        heartbeat = Heartbeat()
        if type(heartbeat.heartbeat_enable) != type(self.heartbeat_enable):
            raise Exception('type failed')
        if type(heartbeat.heartbeat_gap) != type(self.heartbeat_gap) or \
                heartbeat.heartbeat_gap == self.heartbeat_gap:
            raise Exception('type failed')
        if type(heartbeat.lose_time) != type(self.lose_time) or \
                heartbeat.lose_time == self.lose_time:
            raise Exception('type failed')
        if type(heartbeat.recover_time) != type(self.recover_time) or \
                heartbeat.recover_time == self.recover_time:
            raise Exception('type failed')


class Depend:
    def __init__(self):
        self.depend_service_id = 0

    def load(self, jo):
        self.depend_service_id = jo.depend_service_id

        depend = Depend()
        if type(depend.depend_service_id) != type(self.depend_service_id) or \
                depend.depend_service_id == self.depend_service_id:
            raise Exception('type failed')


class KV:
    def __init__(self):
        self.key = ''
        self.val = ''

    def load(self, jo):
        self.key = jo.key
        self.val = jo.val

        kv = KV()
        if type(kv.key) != type(self.key) or kv.key == self.key:
            raise Exception('type failed')
        if type(kv.val) != type(self.val) or kv.val == self.val:
            raise Exception('type failed')


class IPInfo:
    def __init__(self):
        self.proc_id = 0
        self.proc_des = ''
        self.in_ip = ''
        self.in_port = 0
        self.out_ip = ''
        self.out_port = 0

    def load(self, jo):
        self.proc_id = jo.proc_id
        self.proc_des = jo.proc_des
        self.in_ip = jo.in_ip
        self.in_port = jo.in_port
        self.out_ip = jo.out_ip
        self.out_port = jo.out_port

        ip_info = IPInfo()
        if type(ip_info.proc_id) != type(self.proc_id) or ip_info.proc_id == self.proc_id:
            raise Exception('type failed')
        if type(ip_info.proc_des) != type(self.proc_des) or ip_info.proc_des == self.proc_des:
            raise Exception('type failed')
        if type(ip_info.in_ip) != type(self.in_ip) or ip_info.in_ip == self.in_ip:
            raise Exception('type failed')
        if type(ip_info.in_port) != type(self.in_port) or ip_info.in_port == self.in_port:
            raise Exception('type failed')
        if type(ip_info.out_ip) != type(self.out_ip) or ip_info.out_ip == self.out_ip:
            raise Exception('type failed')
        if type(ip_info.out_port) != type(self.out_port) or ip_info.out_port == self.out_port:
            raise Exception('type failed')


class Service:
    def __init__(self):
        self.service_id = 0
        self.service_name = ''
        self.heartbeat = Heartbeat()
        self.depend_map = {}
        self.kv_map = {}
        self.heartbeat_list = []
        self.inservice_list = []

    def load(self, jo):
        self.service_id = jo.service_id
        self.service_name = jo.service_name
        self.heartbeat.load(jo.heartbeat)
        for n in jo.depend_map:
            depend = Depend()
            depend.load(n)
            self.depend_map[depend.depend_service_id] = depend
        for n in jo.kv_map:
            kv = KV()
            kv.load(n)
            self.kv_map[kv.key] = kv
        for n in jo.heartbeat_list:
            ip_info = IPInfo()
            ip_info.load(n)
            self.heartbeat_list.append(ip_info)
        for n in jo.inservice_list:
            ip_info = IPInfo()
            ip_info.load(n)
            self.inservice_list.append(ip_info)

        service = Service()
        if type(service.service_id) != type(self.service_id) or service.service_id == self.service_id:
            raise Exception('type failed')
        if type(service.service_name) != type(self.service_name) or service.service_name == self.service_name:
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
        self.json = ''

    def __str__(self):
        return self.json

    def json_to_map(self, str):
        jo = json.loads(str, object_hook=util.JsonObject)
        try:
            for n in jo.service_map:
                service = Service()
                service.load(n)
                self.service_map[service.service_id] = service
        except Exception as e:
            print(e)
            return False

        self.json = str
        return True

    def get_service(self, service_id):
        if service_id != 0:
            return self.service_map.get(service_id)

        return None


str = '{ "service_map": [ { "service_id": 10100, "service_name": "gate", "heartbeat": { "heartbeat_enable": false, "heartbeat_gap": 5, "lose_time": 3, "recover_time": 5 }, "depend_map": [ { "depend_service_id": 10200 } ], "kv_map": [ { "key": "timeout", "val": "30" }, { "key": "env", "val": "test" } ], "heartbeat_list": [ { "proc_id": 100, "proc_des": "gate_1_0", "in_ip": "121.1.1.1", "in_port": 10100, "out_ip": "11.1.1.1", "out_port": 30000 } ], "inservice_list": [ { "proc_id": 200, "proc_des": "gate_2_0", "in_ip": "121.1.1.2", "in_port": 10100, "out_ip": "11.1.1.2", "out_port": 30000 } ] }, { "service_id": 10200, "service_name": "group", "heartbeat": { "heartbeat_enable": true, "heartbeat_gap": 5, "lose_time": 3, "recover_time": 5 }, "depend_map": [ { "depend_service_id": 10100 } ], "kv_map": [ { "key": "name_max_size", "val": "1024" }, { "key": "buffer_max_size", "val": "1024" }, {  "key": "navigate_key",  "val": "qsdjkajwojfdowjowj"  },  {  "key": "navigate_key_timeout_us",  "val": "60000000"  },  { "key": "map_gate_service_id",  "val": "10300" } ], "heartbeat_list": [ { "proc_id": 100, "proc_des": "group_1_0", "in_ip": "121.1.1.10", "in_port": 10200, "out_ip": "11.1.1.10", "out_port": 10200 } ], "inservice_list": [ { "proc_id": 200, "proc_des": "group_2_0", "in_ip": "121.1.1.20", "in_port": 10200, "out_ip": "11.1.1.20", "out_port": 10200 }, { "proc_id": 201, "proc_des": "group_2_1", "in_ip": "121.1.1.21", "in_port": 10201, "out_ip": "11.1.1.21", "out_port": 10201 } ] } ] } '

sc = ServiceConfig()
sc.json_to_map(str)

print(sc)





