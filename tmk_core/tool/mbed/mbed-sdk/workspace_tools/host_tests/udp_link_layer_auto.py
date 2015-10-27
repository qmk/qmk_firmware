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

"""
How to use:
make.py -m LPC1768 -t ARM -d E:\ -n NET_14
udp_link_layer_auto.py -p COM20 -d E:\ -t 10
"""

import re
import uuid
import socket
import thread
from sys import stdout
from time import time, sleep
from host_test import DefaultTest
from SocketServer import BaseRequestHandler, UDPServer


# Received datagrams (with time)
dict_udp_recv_datagrams = dict()

# Sent datagrams (with time)
dict_udp_sent_datagrams = dict()


class UDPEchoClient_Handler(BaseRequestHandler):
    def handle(self):
        """ One handle per connection
        """
        _data, _socket = self.request
        # Process received datagram
        data_str = repr(_data)[1:-1]
        dict_udp_recv_datagrams[data_str] = time()


def udp_packet_recv(threadName, server_ip, server_port):
    """ This function will receive packet stream from mbed device
    """
    server = UDPServer((server_ip, server_port), UDPEchoClient_Handler)
    print "[UDP_COUNTER] Listening for connections... %s:%d"% (server_ip, server_port)
    server.serve_forever()


class UDPEchoServerTest(DefaultTest):
    ECHO_SERVER_ADDRESS = ""       # UDP IP of datagram bursts
    ECHO_PORT = 0                  # UDP port for datagram bursts
    CONTROL_PORT = 23              # TCP port used to get stats from mbed device, e.g. counters
    s = None                       # Socket

    TEST_PACKET_COUNT = 1000       # how many packets should be send
    TEST_STRESS_FACTOR = 0.001     # stress factor: 10 ms
    PACKET_SATURATION_RATIO = 29.9 # Acceptable packet transmission in %

    PATTERN_SERVER_IP = "Server IP Address is (\d+).(\d+).(\d+).(\d+):(\d+)"
    re_detect_server_ip = re.compile(PATTERN_SERVER_IP)

    def get_control_data(self, command="stat\n"):
        BUFFER_SIZE = 256
        try:
            s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            s.connect((self.ECHO_SERVER_ADDRESS, self.CONTROL_PORT))
        except Exception, e:
            data = None
        s.send(command)
        data = s.recv(BUFFER_SIZE)
        s.close()
        return data

    def test(self):
        serial_ip_msg = self.mbed.serial_readline()
        if serial_ip_msg is None:
            return self.RESULT_IO_SERIAL
        stdout.write(serial_ip_msg)
        stdout.flush()
        # Searching for IP address and port prompted by server
        m = self.re_detect_server_ip.search(serial_ip_msg)
        if m and len(m.groups()):
            self.ECHO_SERVER_ADDRESS = ".".join(m.groups()[:4])
            self.ECHO_PORT = int(m.groups()[4]) # must be integer for socket.connect method
            self.notify("HOST: UDP Server found at: " + self.ECHO_SERVER_ADDRESS + ":" + str(self.ECHO_PORT))

        # Open client socket to burst datagrams to UDP server in mbed
        try:
            self.s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        except Exception, e:
            self.s = None
            self.notify("HOST: Error: %s"% e)
            return self.RESULT_ERROR

        # UDP replied receiver works in background to get echoed datagrams
        SERVER_IP = str(socket.gethostbyname(socket.getfqdn()))
        SERVER_PORT = self.ECHO_PORT + 1
        thread.start_new_thread(udp_packet_recv, ("Thread-udp-recv", SERVER_IP, SERVER_PORT))
        sleep(0.5)

        # Burst part
        for no in range(self.TEST_PACKET_COUNT):
            TEST_STRING = str(uuid.uuid4())
            payload = str(no) + "__" + TEST_STRING
            self.s.sendto(payload, (self.ECHO_SERVER_ADDRESS, self.ECHO_PORT))
            dict_udp_sent_datagrams[payload] = time()
            sleep(self.TEST_STRESS_FACTOR)

        if self.s is not None:
            self.s.close()

        # Wait 5 seconds for packets to come
        result = True
        self.notify("HOST: Test Summary:")
        for d in range(5):
            sleep(1.0)
            summary_datagram_success = (float(len(dict_udp_recv_datagrams)) / float(self.TEST_PACKET_COUNT)) * 100.0
            self.notify("HOST: Datagrams received after +%d sec: %.3f%% (%d / %d), stress=%.3f ms"% (d,
                                                                                                     summary_datagram_success,
                                                                                                     len(dict_udp_recv_datagrams),
                                                                                                     self.TEST_PACKET_COUNT,
                                                                                                     self.TEST_STRESS_FACTOR))
            result = result and (summary_datagram_success >= self.PACKET_SATURATION_RATIO)
            stdout.flush()

        # Getting control data from test
        self.notify("...")
        self.notify("HOST: Mbed Summary:")
        mbed_stats = self.get_control_data()
        self.notify(mbed_stats)
        return self.RESULT_SUCCESS if result else self.RESULT_FAILURE


if __name__ == '__main__':
    UDPEchoServerTest().run()
