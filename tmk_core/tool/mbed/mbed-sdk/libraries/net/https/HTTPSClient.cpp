#include "HTTPSClient.h"
#include "HTTPHeader.h"
#include <string>
#include <cstring>
#include "mbed.h"
#include <stdlib.h>
#include <stdio.h>

using std::memset;
using std::memcpy;    
using std::string;

const static int HTTPS_PORT = 443;
char buf[256];

HTTPSClient::HTTPSClient() :
        _is_connected(false),
        _ssl_ctx(),
        _ssl(),
        _host() {
}

HTTPSClient::~HTTPSClient() {
    close();
}

int HTTPSClient::connect(const char* host) {
    if (init_socket(SOCK_STREAM) < 0)
        return -1;
    
    if (set_address(host, HTTPS_PORT) != 0)
        return -1;
    
    if (lwip_connect(_sock_fd, (const struct sockaddr *) &_remoteHost, sizeof(_remoteHost)) < 0) {
        close();
        return -1;
    }

    if(ssl_ctx_new(&_ssl_ctx, SSL_SERVER_VERIFY_LATER, SSL_DEFAULT_CLNT_SESS) != &_ssl_ctx)
        return -1;

    _ssl.ssl_ctx = &_ssl_ctx;
    
    if(ssl_client_new(&_ssl, _sock_fd, NULL, 0) == NULL)
    {
        close();
        return -1;
    }
    if(_ssl.hs_status != SSL_OK)
    {
        close();
        return -1;
    }
    
    _is_connected = true;
    _host = host;
    return 0;
}

bool HTTPSClient::is_connected(void) {
    return _is_connected;
}

int HTTPSClient::send(char* data, int length) {
    if ((_sock_fd < 0) || !_is_connected)
        return -1;
            
    return ssl_write(&_ssl, (uint8_t*)data, length);
}



HTTPHeader HTTPSClient::get(char *request)
{
    if((_sock_fd < 0) || !_is_connected)
        return HTTPHeader();
        
    sprintf(buf, "GET %s HTTP/1.1\r\nHost: %s\r\n\r\n", request, _host.c_str());
    printf("buf=%s\n", buf);
    if(send(buf, strlen(buf)) != strlen(buf))
        return HTTPHeader();
    printf("Finished sending request\n");
    return read_header();
}


HTTPHeader HTTPSClient::read_header()
{
    _ssl.bm_read_index = 0;
    _ssl.bm_index = 0;
    HTTPHeader hdr;
    if(read_line())
        return hdr;
    
    int status;
    
    if(sscanf(buf, "HTTP/%*d.%*d %d %*s", &status) == -1)
        return hdr;
    
    if(status == 200)
        hdr._status = HTTP_OK;
   if(read_line())
        return hdr;
    do
    {
        string tmp(buf);
        std::size_t sep = tmp.find(':');
        string name = tmp.substr(0, sep);
        string value = tmp.substr(sep+2, tmp.size());
        hdr._fields[name] = value;
        if(read_line())
            return hdr;
    }while(strlen(buf));
    
    return hdr;
}

uint8_t HTTPSClient::read_line()
{
    int index = 0;
    do
    {
        if(ssl_read(&_ssl, (uint8_t*)(&buf[index]), 1) != 1)
        {
            return 1;
        }
        index++;
    }while(buf[index-1] != '\r' && index < 256);
    ssl_read(&_ssl, (uint8_t*)(&buf[index-1]), 1);  // skip '\n'
    buf[index-1] = '\0';
    
    return 0;
}

// -1:error
// otherwise return nb of characters read. Cannot be > than len
int HTTPSClient::read(char *data, int len)
{
    return ssl_read(&_ssl, (uint8_t*)data, len);
}
/*
    0    : must close connection
    -1   : error
    else : get data

int HTTPSClient::receive(char* data, int length) {
    if ((_sock_fd < 0) || !_is_connected)
        return -1;
  
    if(read_record(&_ssl) < 0)
        return -1;
    return process_data(&_ssl, (uint8_t*)data, length);
}
*/
void HTTPSClient::close()
{
    if(!_is_connected)
        return;
    ssl_ctx_free(_ssl.ssl_ctx);
    Socket::close();
    _is_connected = false;
    _host.clear();
}
