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
#ifndef ENDPOINT_H
#define ENDPOINT_H

class UDPSocket;

/**
IP Endpoint (address, port)
*/
class Endpoint {
    friend class UDPSocket;

public:
    /** IP Endpoint (address, port)
     */
    Endpoint(void);
    
    ~Endpoint(void);
    
    /** Reset the address of this endpoint
     */
    void reset_address(void);
    
    /** Set the address of this endpoint
    \param host The endpoint address (it can either be an IP Address or a hostname that will be resolved with DNS).
    \param port The endpoint port
    \return 0 on success, -1 on failure (when an hostname cannot be resolved by DNS).
     */
    int  set_address(const char* host, const int port);
    
    /** Get the IP address of this endpoint
    \return The IP address of this endpoint.
     */
    char* get_address(void);
    
    /** Get the port of this endpoint
    \return The port of this endpoint
     */
    int get_port(void);

protected:
    char _ipAddress[17];
    struct sockaddr_in _remoteHost;

};

#endif
