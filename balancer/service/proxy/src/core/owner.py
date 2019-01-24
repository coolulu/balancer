# -*- coding: utf-8 -*-

from src.tool import util
from src.protocol.protobuf.proto_py import center_pb2


class Owner:

    EN_CHANGE_HEARTBEAT = 10
    EN_CHANGE_INSERVICE = 20

    def __init__(self):
        self.level = center_pb2.INIT_LEVEL
        self.proc_id = 0
        self.state = center_pb2.STATE_BEGIN
        self.owner_hb_time = util.now_s()
        self.expire_second = 0
        self.conf_update_time = 0
        self.msg_seq_id = 0

    def update_owner_hb_time(self, now, level, state):
        ret = 0

        self.expire_second = now - self.owner_hb_time
        if level == self.level:
            if self.state == center_pb2.HEARTBEAT and state == center_pb2.INSERVICE:
                ret = Owner.EN_CHANGE_INSERVICE
            elif self.state == center_pb2.INSERVICE and state == center_pb2.HEARTBEAT:
                ret = Owner.EN_CHANGE_HEARTBEAT

            self.owner_hb_time = now
            self.state = state

        return ret

    def update_owner(self, level, proc_id, conf_update_time, msg_seq_id):
        self.level = level
        self.proc_id = proc_id
        self.conf_update_time = conf_update_time
        self.msg_seq_id = msg_seq_id

    def is_inservice(self):
        return  self.state == Owner.EN_CHANGE_INSERVICE

    def is_not_inservice(self):
        return self.state != Owner.EN_CHANGE_INSERVICE
