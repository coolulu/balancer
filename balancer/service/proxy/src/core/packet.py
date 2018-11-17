

from proto_py import data_pb2


class Packet:

    k_header = 0x00000000

    def __init__(self):
        self.header = 0
        self.len = 0
        self.version = 0
        self.from_service_id = 0
        self.to_service_id = 0
        self.to_proc_id = 0
        self.app_id = 0
        self.app_version = 0
        self.conn_seq_id = 0
        self.msg_seq_id = 0
        self.data_format = 0
        self.reserve_field_0 = 0
        self.reserve_field_1 = 0
        self.reserve_field_2 = 0
        self.reserve_field_3 = 0
        self.data = b''
        self.check_sum = 0

        self._body = data_pb2.Body()


