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
#ifndef SOCKET_H_
#define SOCKET_H_

#include "lwip/sockets.h"
#include "lwip/netdb.h"

//DNS
inline struct hostent *gethostbyname(const char *name) {
  return lwip_gethostbyname(name);
}

inline int gethostbyname_r(const char *name, struct hostent *ret, char *buf, size_t buflen, struct hostent **result, int *h_errnop) {
  return lwip_gethostbyname_r(name, ret, buf, buflen, result, h_errnop);
}

class TimeInterval;

/** Socket file descriptor and select wrapper
  */
class Socket {
public:
    /** Socket
     */
    Socket();
    
    /** Set blocking or non-blocking mode of the socket and a timeout on
        blocking socket operations
    \param blocking  true for blocking mode, false for non-blocking mode.
    \param timeout   timeout in ms [Default: (1500)ms].
    */
    void set_blocking(bool blocking, unsigned int timeout=1500);
    
    /** Set socket options
    \param level     stack level (see: lwip/sockets.h)
    \param optname   option ID
    \param optval    option value
    \param socklen_t length of the option value
    \return 0 on success, -1 on failure
    */
    int set_option(int level, int optname, const void *optval, socklen_t optlen);
    
    /** Get socket options
        \param level     stack level (see: lwip/sockets.h)
        \param optname   option ID
        \param optval    buffer pointer where to write the option value
        \param socklen_t length of the option value
        \return 0 on success, -1 on failure
        */
    int get_option(int level, int optname, void *optval, socklen_t *optlen);
    
    /** Close the socket
        \param shutdown   free the left-over data in message queues
     */
    int close(bool shutdown=true);
    
    ~Socket();
    
protected:
    int _sock_fd;
    int init_socket(int type);
    
    int wait_readable(TimeInterval& timeout);
    int wait_writable(TimeInterval& timeout);
    
    bool _blocking;
    unsigned int _timeout;
    
private:
    int select(struct timeval *timeout, bool read, bool write);
};

/** Time interval class used to specify timeouts
 */
class TimeInterval {
    friend class Socket;

public:
    /** Time Interval
     \param ms time interval expressed in milliseconds
      */
    TimeInterval(unsigned int ms);
    
private:
    struct timeval _time;
};

#endif /* SOCKET_H_ */
