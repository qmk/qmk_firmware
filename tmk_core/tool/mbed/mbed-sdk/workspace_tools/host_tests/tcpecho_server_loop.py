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
# Be sure that the tools directory is in the search path
import sys
from os.path import join, abspath, dirname
ROOT = abspath(join(dirname(__file__), "..", ".."))
sys.path.insert(0, ROOT)

from workspace_tools.private_settings import LOCALHOST
from SocketServer import BaseRequestHandler, TCPServer


class TCP_EchoHandler(BaseRequestHandler):
    def handle(self):
        print "\nHandle connection from:", self.client_address
        while True:
            data = self.request.recv(1024)
            if not data: break
            self.request.sendall(data)
        self.request.close()
        print "socket closed"

if __name__ == '__main__':
    server = TCPServer((LOCALHOST, 7), TCP_EchoHandler)
    print "listening for connections on:", (LOCALHOST, 7)
    server.serve_forever()
