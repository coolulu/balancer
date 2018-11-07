# -*- coding: utf-8 -*-

from protocol.protobuf.proto_py import center_pb2


class CenterStack:

    @staticmethod
    def HeartbeatRsp(body,
                     code, info,
                     level, service_id, proc_id, conf_update_time, expire_second):
        msg = center_pb2.CenterMsg()

        msg.HeartbeatRsp.level = level
        msg.HeartbeatRsp.service_id = service_id
        msg.HeartbeatRsp.proc_id = proc_id
        msg.HeartbeatRsp.conf_update_time = conf_update_time
        msg.HeartbeatRsp.expire_second = expire_second

        body.msg_rsp.code = code
        body.msg_rsp.code = info

        body.service_msg.Pack(msg)
