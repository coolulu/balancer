
import struct
import packet


def test():

    p = packet.Packet()

    p._data = b'1234567810'
    print(len(p._data))

    stream = struct.pack('!IIHHHIIIQQBBIII' + str(len(p._data)) + 'sI',
                         p._header,
                         p._len,
                         p._version,
                         p._from_service_id,
                         p._to_service_id,
                         p._to_proc_id,
                         p._app_id,
                         p._app_version,
                         p._conn_seq_id,
                         p._msg_seq_id,
                         p._data_format,
                         p._reserve_field_0,
                         p._reserve_field_1,
                         p._reserve_field_2,
                         p._reserve_field_3,
                         p._data,
                         p._check_sum)
    print(len(stream))
    print(stream)

    ss = struct.pack('!' + str(len(p._data)) + 's', p._data)
    print(len(ss))
    print(ss)

    head = struct.unpack('!IIHHHIIIQQBBIII' + str(len(p._data)) + 'sI', stream)
    print(head)
    pass


test()

