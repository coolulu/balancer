
import struct
import zlib

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


def stream_encode(pkt):
    stream_head = struct.pack('!I', pkt.header)
    stream_middle = struct.pack('!IHHHIIIQQBBIII' + str(len(pkt.data)) + 's',
                                pkt.len,
                                pkt.version,
                                pkt.from_service_id,
                                pkt.to_service_id,
                                pkt.to_proc_id,
                                pkt.app_id,
                                pkt.app_version,
                                pkt.conn_seq_id,
                                pkt.msg_seq_id,
                                pkt.data_format,
                                pkt.reserve_field_0,
                                pkt.reserve_field_1,
                                pkt.reserve_field_2,
                                pkt.reserve_field_3,
                                pkt.data)
    stream_check_sum = zlib.adler32(stream_middle, 0)
    stream_end = struct.pack('!I', stream_check_sum)
    stream = stream_head + stream_check_sum + stream_end
    return stream
