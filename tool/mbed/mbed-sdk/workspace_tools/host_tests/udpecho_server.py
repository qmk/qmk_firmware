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
from SocketServer import BaseRequestHandler, UDPServer
from private_settings import SERVER_ADDRESS

class UDP_EchoHandler(BaseRequestHandler):
    def handle(self):
        data, socket = self.request
        print "client:", self.client_address
        print "data:", data
        socket.sendto(data, self.client_address)

server = UDPServer((SERVER_ADDRESS, 7195), UDP_EchoHandler)
print "listening for connections"
server.serve_forever()
