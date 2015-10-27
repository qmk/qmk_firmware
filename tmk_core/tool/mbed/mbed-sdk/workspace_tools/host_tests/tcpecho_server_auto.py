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

import re
import sys
import uuid
import socket
from sys import stdout

class TCPEchoServerTest():
    ECHO_SERVER_ADDRESS = ""
    ECHO_PORT = 0
    ECHO_LOOPs = 100
    s = None # Socket

    PATTERN_SERVER_IP = "Server IP Address is (\d+).(\d+).(\d+).(\d+):(\d+)"
    re_detect_server_ip = re.compile(PATTERN_SERVER_IP)

    def test(self, selftest):
        result = False
        c = selftest.mbed.serial_readline()
        if c is None:
            return selftest.RESULT_IO_SERIAL
        selftest.notify(c)

        m = self.re_detect_server_ip.search(c)
        if m and len(m.groups()):
            self.ECHO_SERVER_ADDRESS = ".".join(m.groups()[:4])
            self.ECHO_PORT = int(m.groups()[4]) # must be integer for socket.connect method
            selftest.notify("HOST: TCP Server found at: " + self.ECHO_SERVER_ADDRESS + ":" + str(self.ECHO_PORT))

            # We assume this test fails so can't send 'error' message to server
            try:
                self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                self.s.connect((self.ECHO_SERVER_ADDRESS, self.ECHO_PORT))
            except Exception, e:
                self.s = None
                selftest.notify("HOST: Socket error: %s"% e)
                return selftest.RESULT_ERROR

            print 'HOST: Sending %d echo strings...'% self.ECHO_LOOPs,
            for i in range(0, self.ECHO_LOOPs):
                TEST_STRING = str(uuid.uuid4())
                try:
                    self.s.sendall(TEST_STRING)
                    data = self.s.recv(128)
                except Exception, e:
                    self.s = None
                    selftest.notify("HOST: Socket error: %s"% e)
                    return selftest.RESULT_ERROR

                received_str = repr(data)[1:-1]
                if TEST_STRING == received_str: # We need to cut not needed single quotes from the string
                    sys.stdout.write('.')
                    stdout.flush()
                    result = True
                else:
                    print "Expected: "
                    print "'%s'"% TEST_STRING
                    print "received: "
                    print "'%s'"% received_str
                    result = False
                    break

            if self.s is not None:
                self.s.close()
        else:
            selftest.notify("HOST: TCP Server not found")
            result = False
        return selftest.RESULT_SUCCESS if result else selftest.RESULT_FAILURE
