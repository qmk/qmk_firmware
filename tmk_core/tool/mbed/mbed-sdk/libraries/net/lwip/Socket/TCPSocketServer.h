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
#ifndef TCPSOCKETSERVER_H
#define TCPSOCKETSERVER_H

#include "Socket/Socket.h"
#include "TCPSocketConnection.h"

/** TCP Server.
  */
class TCPSocketServer : public Socket {
  public:
    /** Instantiate a TCP Server.
    */
    TCPSocketServer();
    
    /** Bind a socket to a specific port.
    \param port The port to listen for incoming connections on.
    \return 0 on success, -1 on failure.
    */
    int bind(int port);
    
    /** Start listening for incoming connections.
    \param backlog number of pending connections that can be queued up at any
                   one time [Default: 1].
    \return 0 on success, -1 on failure.
    */
    int listen(int backlog=1);
    
    /** Accept a new connection.
    \param connection A TCPSocketConnection instance that will handle the incoming connection.
    \return 0 on success, -1 on failure.
    */
    int accept(TCPSocketConnection& connection);
};

#endif
