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
#include <cstring>

using std::memset;

Socket::Socket() : _sock_fd(-1), _blocking(true), _timeout(1500) {
    
}

void Socket::set_blocking(bool blocking, unsigned int timeout) {
    _blocking = blocking;
    _timeout = timeout;
}

int Socket::init_socket(int type) {
    if (_sock_fd != -1)
        return -1;
    
    int fd = lwip_socket(AF_INET, type, 0);
    if (fd < 0)
        return -1;
    
    _sock_fd = fd;
    return 0;
}

int Socket::set_option(int level, int optname, const void *optval, socklen_t optlen) {
    return lwip_setsockopt(_sock_fd, level, optname, optval, optlen);
}

int Socket::get_option(int level, int optname, void *optval, socklen_t *optlen) {
    return lwip_getsockopt(_sock_fd, level, optname, optval, optlen);
}

int Socket::select(struct timeval *timeout, bool read, bool write) {
    fd_set fdSet;
    FD_ZERO(&fdSet);
    FD_SET(_sock_fd, &fdSet);
    
    fd_set* readset  = (read ) ? (&fdSet) : (NULL);
    fd_set* writeset = (write) ? (&fdSet) : (NULL);
    
    int ret = lwip_select(FD_SETSIZE, readset, writeset, NULL, timeout);
    return (ret <= 0 || !FD_ISSET(_sock_fd, &fdSet)) ? (-1) : (0);
}

int Socket::wait_readable(TimeInterval& timeout) {
    return select(&timeout._time, true, false);
}

int Socket::wait_writable(TimeInterval& timeout) {
    return select(&timeout._time, false, true);
}

int Socket::close(bool shutdown) {
    if (_sock_fd < 0)
        return -1;
    
    if (shutdown)
        lwip_shutdown(_sock_fd, SHUT_RDWR);
    lwip_close(_sock_fd);
    _sock_fd = -1;
    
    return 0;
}

Socket::~Socket() {
    close(); //Don't want to leak
}

TimeInterval::TimeInterval(unsigned int ms) {
    _time.tv_sec = ms / 1000;
    _time.tv_usec = (ms - (_time.tv_sec * 1000)) * 1000;
}
