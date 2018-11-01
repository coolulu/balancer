# -*- coding: utf-8 -*-

import sys
sys.path.append('./proto_py')


from proto_py import common_pb2
from proto_py import proxy_pb2
from proto_py import data_pb2

from pake import aa

def main():

    # t = common_pb2.TestReq()
    # t.service_id = 10
    # data = t.SerializeToString()
    #
    # t2 = common_pb2.TestReq()
    # t2.ParseFromString(data)
    # print(data)

    msg = proxy_pb2.ProxyMsg()
    msg.check_passwd_req.user_id = 1111
    msg.check_passwd_req.passwd = b'passwd'
    buff = msg.SerializeToString()


    body = data_pb2.Body()
    body.service_msg.Pack(msg)
    buffer = body.SerializeToString()


    rsp = data_pb2.Body()
    rsp.ParseFromString(buffer)
    print(rsp.service_msg.TypeName())
    print(rsp.service_msg.Is(proxy_pb2.ProxyMsg().DESCRIPTOR))

    rsp_msg = proxy_pb2.ProxyMsg()
    print(rsp.service_msg.Unpack(rsp_msg))
    print(rsp_msg.HasField('check_passwd_req'))
    print(rsp_msg.WhichOneof("choice"))
    print(rsp_msg.check_passwd_req.user_id)
    print(rsp_msg.check_passwd_req.passwd)

    pass


if __name__ == '__main__':
    main()
