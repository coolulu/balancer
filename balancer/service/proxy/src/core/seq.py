# -*- coding: utf-8 -*-

from src.tool import util


class Seq:

    EN_SEQ_NULL = 0

    def __init__(self):
        self.count = 0

    def make_seq(self):
        self.count += 1
        if False:
            return util.uiui2ull(util.now_s(), self.count)
        else:
            return self.count


