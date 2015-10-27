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
import socket
import string, random
from time import time

from private_settings import SERVER_ADDRESS

ECHO_PORT = 7

LEN_PACKET = 127
N_PACKETS = 5000
TOT_BITS = float(LEN_PACKET * N_PACKETS * 8) * 2
MEGA = float(1024 * 1024)
UPDATE_STEP = (N_PACKETS/10)

class TCP_EchoClient:
    def __init__(self, host):
        self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.s.connect((host, ECHO_PORT))
        self.packet = ''.join(random.choice(string.ascii_uppercase + string.digits) for _ in range(LEN_PACKET))

    def __packet(self):
        # Comment out the checks when measuring the throughput
        # self.packet = ''.join(random.choice(string.ascii_uppercase + string.digits) for _ in range(LEN_PACKET))
        self.s.send(self.packet)
        data = self.s.recv(LEN_PACKET)
        # assert self.packet == data, "packet error:\n%s\n%s\n" % (self.packet, data)

    def test(self):
        start = time()
        for i in range(N_PACKETS):
            if (i % UPDATE_STEP) == 0: print '%.2f%%' % ((float(i)/float(N_PACKETS)) * 100.)
            self.__packet()
        t = time() - start
        print 'Throughput: (%.2f)Mbits/s' % ((TOT_BITS / t)/MEGA)

    def __del__(self):
        self.s.close()

while True:
    e = TCP_EchoClient(SERVER_ADDRESS)
    e.test()
