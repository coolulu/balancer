
from pake import bb

def test_aa():
    print("test_aa")

def test_aa_bb():
    print("test_aa_bb")
    bb.test_bb()


from proto_py import proxy_pb2

def test_proxy():
    r = proxy_pb2.CheckPasswdReq()
    pass