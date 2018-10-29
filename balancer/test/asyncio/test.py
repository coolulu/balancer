import asyncio
import time

import concurrent.futures


def Sleeping(index):
    print('begin ' + str(index))
    time.sleep(1)
    print('end ' + str(index))
    return index

async def main():
    loop = asyncio.get_event_loop()
    pool = concurrent.futures.ThreadPoolExecutor(4)

    l = []
    for i in range(0, 20):
        f = loop.run_in_executor(pool, Sleeping, i)
        l.append(f)

    for f in l:
        index = await f
        print('ok ' + str(index))
    print('over')



loop = asyncio.get_event_loop()
loop.run_until_complete(main())

