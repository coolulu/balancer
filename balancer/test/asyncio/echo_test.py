import asyncio
import concurrent.futures
import time
import signal
import os


pool = concurrent.futures.ThreadPoolExecutor(4)
g_count = 0
g_conn_map = {}


class Conn:
    def __init__(self, conn_id, writer):
        self.conn_id = conn_id
        self.writer = writer
        self.peername = writer.get_extra_info('peername')
        self.socket = writer.get_extra_info('socket')
        self.is_close = False
        self.create_time = time.time()
        self.update_time = self.create_time

    def update(self):
        self.update_time = time.time()

    def write(self, data):
        self.writer.write(data)
        self.update_time = time.time()

    def close(self):
        if not self.is_close:
            self.is_close = True
            self.writer.close()
            self.update_time = time.time()
            return True
        else:
            return False


def timer():
    now = time.time()

    timeout_list = []
    for k, v in g_conn_map.items():
        if now - v.update_time >= 120:
            if v.close():
                timeout_list.append(k)

    for l in timeout_list:
        g_conn_map.pop(l)

    loop.call_later(1, timer)


class Task:
    def __init__(self, conn_id, data, time):
        self.conn_id = conn_id
        self.data = data
        self.create_time = time


def done(task):
    end = time.time()
    print('time end: ' + str(end) + ', diff: ' + str(end - task.create_time))
    conn = g_conn_map.get(task.conn_id)
    if conn is not None:
        print("Send: %r" % task.data)
        conn.write(task.data)
    else:
        print("conn_id is None: %d" % task.conn_id)


def doing(task):
    loop.call_soon_threadsafe(done, task)


async def handle_echo(reader, writer):
    print("on connect create")
    global g_count
    g_count += 1
    conn = Conn(g_count, writer)
    g_conn_map[conn.conn_id] = conn

    while True:
        data = await reader.read(1024)
        conn.update()
        if data is b'':
            print("on connect close")
            if conn.close():
                g_conn_map.pop(conn.conn_id)
            break
        else:
            print("Received %r from %r %r" % (data, conn.peername, conn.update_time))
            loop.run_in_executor(pool, doing, Task(conn.conn_id, data, conn.update_time))

loop = asyncio.get_event_loop()
coro = asyncio.start_server(handle_echo, '0.0.0.0', 8888, loop=loop)
loop.call_later(0, timer)


class A:
    def __init__(self):
        self.stop = False
        self.reload = False

a = A()

def stop(sig, frame):
    print(sig)
    a.stop = True

def reload(sig, frame):
    print(sig)
    a.reload = True

def test(sig, frame):
    print(sig)
    a.stop = True


if hasattr(signal, 'SIGUSR1'):
    signal.signal(getattr(signal, 'SIGUSR1'), stop)

if hasattr(signal, 'SIGUSR2'):
    signal.signal(getattr(signal, 'SIGUSR2'), stop)

if hasattr(signal, 'SIGTERM'):
    signal.signal(getattr(signal, 'SIGTERM'), test)

print(os.getpid())
server = loop.run_until_complete(coro)

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