# -*- coding: utf-8 -*-

from src.core import kv

class InserviceList:

    def __init__(self, service_id, il):
        self.depend_service_id = service_id
        self.count = 0
        self.inservice_list = il
        self.inservice_map = {}
        for ip_info in self.inservice_list:
            self.inservice_map[ip_info.proc_id] = ip_info


class InserviceService:

    def __init__(self):
        self.is_ok = False
        self.map = {}
        self.kv = kv.Kv()

    def load_ip_info(self, service_id, sc):
        service = sc.get_service(service_id)
        if not service:
            self.is_ok = False
            return self.is_ok

        for depend in service.depend_map:
            depend_service = sc.get_service(depend.depend_service_id)
            if depend_service is None or len(depend_service.inservice_list) == 0:
                self.is_ok = False
                return self.is_ok

            il = InserviceList(depend.depend_service_id, 
                               depend_service.inservice_list)
            self.map[depend.depend_service_id] = il

        self.is_ok = self.kv.load_kv(service.kv_map)
        return self.is_ok

    def get_ip_info(self, depend_service_id, proc_id=0):
        il = self.map.get(depend_service_id)
        if il is not None:
            if proc_id == 0:
                size = len(il.inservice_list)
                if size > 0:
                    il.count += 1
                    index = il.count % size
                    return il.inservice_list[index]
            else:
                return il.inservice_map.get(proc_id)

        return None

    def get_inservice_list(self, depend_service_id):
        return self.map.get(depend_service_id)





