# -*- coding: utf-8 -*-

from src.protocol.protobuf.proto_py import service_pb2


class Define:

    BUFFER_SIZE = 1024 * 1024

    service_version = service_pb2.PROXY
    service_name = 'proxy'

    conf_file_postfix = '.conf'