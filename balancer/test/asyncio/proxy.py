import pymysql
import pymongo
import redis

import time
import json

def test_mysql():
    client = pymysql.connect(host='111.230.141.42',
                             port=3306,
                             user='tps',
                             passwd='TPS$1tps',
                             db='im_backend_test',
                             autocommit=True,
                             charset='utf8')
    pass


def test_redis():
    client = redis.StrictRedis(host='10.1.1.81',
                               port=6379,
                               password='tps#test')
    begin = time.time()
    s = client.scan(0)
    while s[0] != 0:
        print(s)
        s = client.scan(s[0])
    print(s)
    end = time.time()
    print(end - begin)
    pass


def test_mongo():
    client = pymongo.MongoClient(host='10.1.1.80',
                                 port=27017,
                                 username='im_test',
                                 password='tpstest',
                                 authSource='im_test')
    post = {
        "author": "Mike",
        "text": "My first blog post!",
        "tags": ["0000", "1111", "2222"]
    }

    im_test = client['im_test']
    test_collect = im_test['test_collect']
    post_id = test_collect.insert_one(post).inserted_id
    print('post_id: ' + str(post_id))

    l = test_collect.find()
    for n in l:
        print(n)
    print(l.count())

    pass


if __name__ == '__main__':
    test_mongo()