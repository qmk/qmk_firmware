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
from sys import stdout
from socket import socket, AF_INET, SOCK_DGRAM

class UDPEchoServerTest():
    ECHO_SERVER_ADDRESS = ""
    ECHO_PORT = 0
    s = None # Socket

    PATTERN_SERVER_IP = "Server IP Address is (\d+).(\d+).(\d+).(\d+):(\d+)"
    re_detect_server_ip = re.compile(PATTERN_SERVER_IP)

    def test(self, selftest):
        result = True
        serial_ip_msg = selftest.mbed.serial_readline()
        if serial_ip_msg is None:
            return selftest.RESULT_IO_SERIAL
        selftest.notify(serial_ip_msg)
        # Searching for IP address and port prompted by server
        m = self.re_detect_server_ip.search(serial_ip_msg)
        if m and len(m.groups()):
            self.ECHO_SERVER_ADDRESS = ".".join(m.groups()[:4])
            self.ECHO_PORT = int(m.groups()[4]) # must be integer for socket.connect method
            selftest.notify("HOST: UDP Server found at: " + self.ECHO_SERVER_ADDRESS + ":" + str(self.ECHO_PORT))

            # We assume this test fails so can't send 'error' message to server
            try:
                self.s = socket(AF_INET, SOCK_DGRAM)
            except Exception, e:
                self.s = None
                selftest.notify("HOST: Socket error: %s"% e)
                return selftest.RESULT_ERROR

            for i in range(0, 100):
                TEST_STRING = str(uuid.uuid4())
                self.s.sendto(TEST_STRING, (self.ECHO_SERVER_ADDRESS, self.ECHO_PORT))
                data = self.s.recv(len(TEST_STRING))
                received_str = repr(data)[1:-1]
                if TEST_STRING != received_str:
                    result = False
                    break
                sys.stdout.write('.')
                stdout.flush()
        else:
            result = False

        if self.s is not None:
            self.s.close()
        return selftest.RESULT_SUCCESS if result else selftest.RESULT_FAILURE
