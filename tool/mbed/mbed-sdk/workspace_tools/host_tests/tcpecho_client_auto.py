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

import sys
import socket
from sys import stdout
from SocketServer import BaseRequestHandler, TCPServer

class TCPEchoClient_Handler(BaseRequestHandler):
    def handle(self):
        """ One handle per connection
        """
        print "HOST: Connection received...",
        count = 1;
        while True:
            data = self.request.recv(1024)
            if not data: break
            self.request.sendall(data)
            if '{{end}}' in str(data):
                print
                print str(data)
            else:
                if not count % 10:
                    sys.stdout.write('.')
                count += 1
            stdout.flush()

class TCPEchoClientTest():
    def send_server_ip_port(self, selftest, ip_address, port_no):
        """ Set up network host. Reset target and and send server IP via serial to Mbed
        """
        c = selftest.mbed.serial_readline() # 'TCPCllient waiting for server IP and port...'
        if c is None:
            self.print_result(selftest.RESULT_IO_SERIAL)
            return

        selftest.notify(c.strip())
        selftest.notify("HOST: Sending server IP Address to target...")

        connection_str = ip_address + ":" + str(port_no) + "\n"
        selftest.mbed.serial_write(connection_str)
        selftest.notify(connection_str)

        # Two more strings about connection should be sent by MBED
        for i in range(0, 2):
            c = selftest.mbed.serial_readline()
            if c is None:
                selftest.print_result(self.RESULT_IO_SERIAL)
                return
            selftest.notify(c.strip())

    def test(self, selftest):
        # We need to discover SERVEP_IP and set up SERVER_PORT
        # Note: Port 7 is Echo Protocol:
        #
        # Port number rationale:
        #
        # The Echo Protocol is a service in the Internet Protocol Suite defined
        # in RFC 862. It was originally proposed for testing and measurement
        # of round-trip times[citation needed] in IP networks.
        #
        # A host may connect to a server that supports the Echo Protocol using
        # the Transmission Control Protocol (TCP) or the User Datagram Protocol
        # (UDP) on the well-known port number 7. The server sends back an
        # identical copy of the data it received.
        SERVER_IP = str(socket.gethostbyname(socket.getfqdn()))
        SERVER_PORT = 7

        # Returning none will suppress host test from printing success code
        server = TCPServer((SERVER_IP, SERVER_PORT), TCPEchoClient_Handler)
        print "HOST: Listening for TCP connections: " + SERVER_IP + ":" + str(SERVER_PORT)
        self.send_server_ip_port(selftest, SERVER_IP, SERVER_PORT)
        server.serve_forever()
