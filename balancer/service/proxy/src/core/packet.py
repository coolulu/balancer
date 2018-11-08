

from proto_py import data_pb2


class Packet:

    k_header = 0x00000000

    def __init__(self):
        self._header = 0
        self._len = 0
        self._version = 0
        self._from_service_id = 0
        self._to_service_id = 0
        self._to_proc_id = 0
        self._app_id = 0
        self._app_version = 0
        self._conn_seq_id = 0
        self._msg_seq_id = 0
        self._data_format = 0
        self._reserve_field_0 = 0
        self._reserve_field_1 = 0
        self._reserve_field_2 = 0
        self._reserve_field_3 = 0
        self._data = b''
        self._check_sum = 0

        self._body = data_pb2.Body()


