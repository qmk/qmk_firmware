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
from SocketServer import BaseRequestHandler, UDPServer

class UDPEchoClient_Handler(BaseRequestHandler):
    def handle(self):
        """ One handle per connection
        """
        data, socket = self.request
        socket.sendto(data, self.client_address)
        if '{{end}}' in data:
            print
            print data
        else:
            sys.stdout.write('.')
        stdout.flush()

class UDPEchoClientTest():

    def send_server_ip_port(self, selftest, ip_address, port_no):
        c = selftest.mbed.serial_readline() # 'UDPCllient waiting for server IP and port...'
        if c is None:
            selftest.print_result(selftest.RESULT_IO_SERIAL)
            return
        selftest.notify(c.strip())

        selftest.notify("HOST: Sending server IP Address to target...")
        connection_str = ip_address + ":" + str(port_no) + "\n"
        selftest.mbed.serial_write(connection_str)

        c = selftest.mbed.serial_readline() # 'UDPCllient waiting for server IP and port...'
        if c is None:
            self.print_result(selftest.RESULT_IO_SERIAL)
            return
        selftest.notify(c.strip())
        return selftest.RESULT_PASSIVE

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
        server = UDPServer((SERVER_IP, SERVER_PORT), UDPEchoClient_Handler)
        print "HOST: Listening for UDP connections..."
        self.send_server_ip_port(selftest, SERVER_IP, SERVER_PORT)
        server.serve_forever()
