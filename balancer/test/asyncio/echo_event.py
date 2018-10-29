import asyncio

import time
import concurrent.futures
import threading

pool = concurrent.futures.ThreadPoolExecutor(100)

g_lock = threading.Lock()
g_e = None
g_rsp = []
g_count = 0

async def event_loop():
    while True:
        print('on wait')
        await g_e.wait()
        with g_lock:
            print('on awake ' + str(g_rsp))
            for index in g_rsp:
                print('index: ' + str(index))
            g_rsp.clear()
        g_e.clear()

def timer():
#    print("time: " + str(loop.time()))
    loop.call_later(1, timer)
#    print(len(pool._threads))


def Sleeping(index):
    print('begin ' + str(index))
 #   time.sleep(1)
    print('end ' + str(index))

    with g_lock:
        g_rsp.append(index)

    if not g_e.is_set():
        print('event set: ' + str(index))
        g_e.set()
    else:
        print('event not set: ' + str(index))

@asyncio.coroutine
def handle_echo(reader, writer):
    print("on connect create")
    while True:
        data = yield from reader.read(100)
        if data is b'':
            print("on connect close")
            writer.close()
            break

        addr = writer.get_extra_info('peername')
        print("Received %r from %r" % (data, addr))

        # global g_count
        # g_count += 1
        # loop.run_in_executor(pool, Sleeping, g_count % 4)
        for index in range(0, 10000):
            loop.run_in_executor(pool, Sleeping, index)

        print("Send: %r" % data)
        writer.write(data)
        yield from writer.drain()

loop = asyncio.get_event_loop()
coro = asyncio.start_server(handle_echo, '0.0.0.0', 8888, loop=loop)
loop.call_later(0, timer)
server = loop.run_until_complete(coro)

g_e = asyncio.Event(loop=loop)
asyncio.ensure_future(event_loop(), loop=loop)

# Serve requests until Ctrl+C is pressed
print('Serving on {}'.format(server.sockets[0].getsockname()))
try:
    loop.run_forever()
except KeyboardInterrupt:
    pass

# Close the server
server.close()
loop.run_until_complete(server.wait_closed())
loop.close()


'''
数据库连接池 无锁获取
1.主线程一开始建立好线程数相同的连接数，加入有锁的list
2.1每当线程获取连接时，先看自己连接是否为None，如果None去从连接池获取永不归还，否则连接已获取(函数上下文有状态)
2.2每当线程获取连接时，加锁获取，用完，加锁归还(函数上下文无状态)

'''