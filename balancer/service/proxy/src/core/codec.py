
import struct
from core import packet



def test():

    p = packet.Packet()

    p.data = b'1234567810'
    print(len(p.data))

    stream = struct.pack('!IIHHHIIIQQBBIII' + str(len(p.data)) + 'sI',
                         p.header,
                         p.len,
                         p.version,
                         p.from_service_id,
                         p.to_service_id,
                         p.to_proc_id,
                         p.app_id,
                         p.app_version,
                         p.conn_seq_id,
                         p.msg_seq_id,
                         p.data_format,
                         p.reserve_field_0,
                         p.reserve_field_1,
                         p.reserve_field_2,
                         p.reserve_field_3,
                         p.data,
                         p.check_sum)
    print(len(stream))
    print(stream)

    ss = struct.pack('!' + str(len(p.data)) + 's', p.data)
    print(len(ss))
    print(ss)


test()

