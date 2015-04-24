"""
mbed SDK
Copyright (c) 2011-2013 ARM Limited

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
"""
from SocketServer import BaseRequestHandler, TCPServer
from time import time

from private_settings import LOCALHOST

MAX_INDEX = 126
MEGA = float(1024 * 1024)

class TCP_EchoHandler(BaseRequestHandler):
    def handle(self):
        print "\nconnection received"
        start = time()
        bytes = 0
        index = 0
        while True:
            data = self.request.recv(1024)
            if not data: break

            bytes += len(data)
            for n in map(ord, data):
                if n != index:
                    print "data error %d != %d" % (n , index)
                index += 1
                if index > MAX_INDEX:
                    index = 0

            self.request.sendall(data)
        t = time() - start
        b = float(bytes * 8) * 2
        print "Throughput: (%.2f)Mbits/s" % ((b/t)/MEGA)

server = TCPServer((LOCALHOST, 7), TCP_EchoHandler)
print "listening for connections"
server.serve_forever()
