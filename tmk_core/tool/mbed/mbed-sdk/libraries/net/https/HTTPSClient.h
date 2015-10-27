#ifndef HTTPSCLIENT_H
#define HTTPSCLIENT_H

#include "Socket/Socket.h"
#include "Socket/Endpoint.h"
#include "axTLS/ssl/ssl.h"
#include "HTTPHeader.h"

/**
TCP socket connection
*/
class HTTPSClient : public Socket, public Endpoint {
    
public:
    /** TCP socket connection
    */
    HTTPSClient();
    
    
    virtual ~HTTPSClient();
    
    /** Connects this TCP socket to the server
    \param host The host to connect to. It can either be an IP Address or a hostname that will be resolved with DNS.
    \param port The host's port to connect to.
    \return 0 on success, -1 on failure.
    */
    int connect(const char* host);
    
    /** Check if the socket is connected
    \return true if connected, false otherwise.
    */
    bool is_connected(void);
    
    // Returns the size of the body
    HTTPHeader get(char *path);
    
    int read(char *data, int len);


    void close();
    
private:


    int send(char* data, int length);
    
    uint8_t read_line();
    HTTPHeader read_header();

    bool _is_connected;
    SSL_CTX _ssl_ctx;
    SSL _ssl;
    std::string _host;
};

#endif
