/* Copyright (C) 2012 mbed.org, MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#include "Socket/Socket.h"
#include "Socket/Endpoint.h"
#include <cstring>
#include <cstdio>

Endpoint::Endpoint()  {
    reset_address();
}
Endpoint::~Endpoint() {}

void Endpoint::reset_address(void) {
    std::memset(&_remoteHost, 0, sizeof(struct sockaddr_in));
    _ipAddress[0] = '\0';
}

#include "stdio.h"

int Endpoint::set_address(const char* host, const int port) {
    reset_address();
    
    // IP Address
    char address[5];
    char *p_address = address;
    
    // Dot-decimal notation
    int result = std::sscanf(host, "%3u.%3u.%3u.%3u",
        (unsigned int*)&address[0], (unsigned int*)&address[1],
        (unsigned int*)&address[2], (unsigned int*)&address[3]);
    
    if (result != 4) {
        // Resolve address with DNS
        struct hostent *host_address = lwip_gethostbyname(host);
        if (host_address == NULL)
            return -1; //Could not resolve address
        p_address = (char*)host_address->h_addr_list[0];
    }
    std::memcpy((char*)&_remoteHost.sin_addr.s_addr, p_address, 4);
    
    // Address family
    _remoteHost.sin_family = AF_INET;
    
    // Set port
    _remoteHost.sin_port = htons(port);
    
    return 0;
}

char* Endpoint::get_address() {
    if ((_ipAddress[0] == '\0') && (_remoteHost.sin_addr.s_addr != 0))
            inet_ntoa_r(_remoteHost.sin_addr, _ipAddress, sizeof(_ipAddress));
    return _ipAddress;
}

int   Endpoint::get_port() {
    return ntohs(_remoteHost.sin_port);
}
