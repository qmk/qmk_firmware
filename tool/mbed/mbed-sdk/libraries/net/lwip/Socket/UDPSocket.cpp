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

#include "Socket/UDPSocket.h"

#include <cstring>

using std::memset;

UDPSocket::UDPSocket() {
}

int UDPSocket::init(void) {
    return init_socket(SOCK_DGRAM);
}

// Server initialization
int UDPSocket::bind(int port) {
    if (init_socket(SOCK_DGRAM) < 0)
        return -1;
    
    struct sockaddr_in localHost;
    std::memset(&localHost, 0, sizeof(localHost));
    
    localHost.sin_family = AF_INET;
    localHost.sin_port = htons(port);
    localHost.sin_addr.s_addr = INADDR_ANY;
    
    if (lwip_bind(_sock_fd, (const struct sockaddr *) &localHost, sizeof(localHost)) < 0) {
        close();
        return -1;
    }
    
    return 0;
}

int UDPSocket::join_multicast_group(const char* address) {
    struct ip_mreq mreq;
    
    // Set up group address 
    mreq.imr_multiaddr.s_addr = inet_addr(address);
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    
    return set_option(IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));
}

int UDPSocket::set_broadcasting(bool broadcast) {
    int option = (broadcast) ? (1) : (0);
    return set_option(SOL_SOCKET, SO_BROADCAST, &option, sizeof(option));
}

// -1 if unsuccessful, else number of bytes written
int UDPSocket::sendTo(Endpoint &remote, char *packet, int length) {
    if (_sock_fd < 0)
        return -1;
    
    if (!_blocking) {
        TimeInterval timeout(_timeout);
        if (wait_writable(timeout) != 0)
            return 0;
    }
    
    return lwip_sendto(_sock_fd, packet, length, 0, (const struct sockaddr *) &remote._remoteHost, sizeof(remote._remoteHost));
}

// -1 if unsuccessful, else number of bytes received
int UDPSocket::receiveFrom(Endpoint &remote, char *buffer, int length) {
    if (_sock_fd < 0)
        return -1;
    
    if (!_blocking) {
        TimeInterval timeout(_timeout);
        if (wait_readable(timeout) != 0)
            return 0;
    }
    remote.reset_address();
    socklen_t remoteHostLen = sizeof(remote._remoteHost);
    return lwip_recvfrom(_sock_fd, buffer, length, 0, (struct sockaddr*) &remote._remoteHost, &remoteHostLen);
}
