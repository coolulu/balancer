# -*- coding: utf-8 -*-

from tool import util
from protocol.protobuf.proto_py import center_pb2


class Owner:

    EN_CHANGE_HEARTBEAT = 10
    EN_CHANGE_INSERVICE = 20

    def __init__(self):
        self._level = center_pb2.INIT_LEVEL
        self._proc_id = 0
        self._state = center_pb2.STATE_BEGIN
        self._owner_hb_time = util.now_s()
        self._expire_second = 0
        self._conf_update_time = 0
        self._msg_seq_id = 0

    def update_owner_hb_time(self, now, level, state):
        ret = 0

        self._expire_second = now - self._owner_hb_time
        if level == self._level:
            if self._state == center_pb2.HEARTBEAT and state == center_pb2.INSERVICE:
                ret = Owner.EN_CHANGE_INSERVICE
            elif self._state == center_pb2.INSERVICE and state == center_pb2.HEARTBEAT:
                ret = Owner.EN_CHANGE_HEARTBEAT

            self._owner_hb_time = now
            self._state = state

        return ret

    def update_owner(self, level, proc_id, conf_update_time, msg_seq_id):
        self._level = level
        self._proc_id = proc_id
        self._conf_update_time = conf_update_time
        self._msg_seq_id = msg_seq_id

    def is_inservice(self):
        return  self._state == Owner.EN_CHANGE_INSERVICE

    def is_not_inservice(self):
        return self._state != Owner.EN_CHANGE_INSERVICE
