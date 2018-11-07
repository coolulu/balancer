# -*- coding: utf-8 -*-

from protocol.protobuf.proto_py import proxy_pb2


class ProxyStack:

    @staticmethod
    def GetUserInfoRsp(body,
                       code, info):
        msg = proxy_pb2.ProxyMsg()

        body.msg_rsp.code = code
        body.msg_rsp.code = info

        body.service_msg.Pack(msg)

    @staticmethod
    def CheckPasswdRsp(body,
                       code, info):
        msg = proxy_pb2.ProxyMsg()

        body.msg_rsp.code = code
        body.msg_rsp.code = info

        body.service_msg.Pack(msg)
