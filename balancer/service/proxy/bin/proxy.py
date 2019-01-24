# -*- coding: utf-8 -*-

import sys
sys.path.append('.')    #不加上，windows上命令行上运行不了(找不到src)
sys.path.append('./src/protocol/protobuf/proto_py')

from src.main import main

if __name__ == '__main__':
    main(sys.argv[1:])
