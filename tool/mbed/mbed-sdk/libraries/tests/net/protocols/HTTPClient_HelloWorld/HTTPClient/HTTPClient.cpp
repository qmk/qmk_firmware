/* HTTPClient.cpp */
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

//Debug is disabled by default
#if 1
//Enable debug
#include <cstdio>
//#define DBG(x, ...) std::printf("[HTTPClient : DBG]"x"\r\n", ##__VA_ARGS__);
#define DBG(x, ...)
#define WARN(x, ...) std::printf("[HTTPClient : WARN]"x"\r\n", ##__VA_ARGS__);
#define ERR(x, ...) std::printf("[HTTPClient : ERR]"x"\r\n", ##__VA_ARGS__);

#else
//Disable debug
#define DBG(x, ...)
#define WARN(x, ...)
#define ERR(x, ...)

#endif

#define HTTP_PORT 80

#define OK 0

#define MIN(x,y) (((x)<(y))?(x):(y))
#define MAX(x,y) (((x)>(y))?(x):(y))

#define CHUNK_SIZE 256

#include <cstring>

#include "HTTPClient.h"

HTTPClient::HTTPClient() :
m_sock(), m_basicAuthUser(NULL), m_basicAuthPassword(NULL), m_httpResponseCode(0)
{

}

HTTPClient::~HTTPClient()
{

}

#if 0
void HTTPClient::basicAuth(const char* user, const char* password) //Basic Authentification
{
  m_basicAuthUser = user;
  m_basicAuthPassword = password;
}
#endif

HTTPResult HTTPClient::get(const char* url, IHTTPDataIn* pDataIn, int timeout /*= HTTP_CLIENT_DEFAULT_TIMEOUT*/) //Blocking
{
  return connect(url, HTTP_GET, NULL, pDataIn, timeout);
}

HTTPResult HTTPClient::get(const char* url, char* result, size_t maxResultLen, int timeout /*= HTTP_CLIENT_DEFAULT_TIMEOUT*/) //Blocking
{
  HTTPText str(result, maxResultLen);
  return get(url, &str, timeout);
}

HTTPResult HTTPClient::post(const char* url, const IHTTPDataOut& dataOut, IHTTPDataIn* pDataIn, int timeout /*= HTTP_CLIENT_DEFAULT_TIMEOUT*/) //Blocking
{
  return connect(url, HTTP_POST, (IHTTPDataOut*)&dataOut, pDataIn, timeout);
}

int HTTPClient::getHTTPResponseCode()
{
  return m_httpResponseCode;
}

#define CHECK_CONN_ERR(ret) \
  do{ \
    if(ret) { \
      m_sock.close(); \
      ERR("Connection error (%d)", ret); \
      return HTTP_CONN; \
    } \
  } while(0)

#define PRTCL_ERR() \
  do{ \
    m_sock.close(); \
    ERR("Protocol error"); \
    return HTTP_PRTCL; \
  } while(0)

HTTPResult HTTPClient::connect(const char* url, HTTP_METH method, IHTTPDataOut* pDataOut, IHTTPDataIn* pDataIn, int timeout) //Execute request
{
  m_httpResponseCode = 0; //Invalidate code
  m_timeout = timeout;

  char scheme[8];
  uint16_t port;
  char host[32];
  char path[64];
  //First we need to parse the url (http[s]://host[:port][/[path]]) -- HTTPS not supported (yet?)
  HTTPResult res = parseURL(url, scheme, sizeof(scheme), host, sizeof(host), &port, path, sizeof(path));
  if(res != HTTP_OK)
  {
    ERR("parseURL returned %d", res);
    return res;
  }

  if(port == 0) //TODO do handle HTTPS->443
  {
    port = 80;
  }

  DBG("Scheme: %s", scheme);
  DBG("Host: %s", host);
  DBG("Port: %d", port);
  DBG("Path: %s", path);

  //Connect
  DBG("Connecting socket to server");
  int ret = m_sock.connect(host, port);
  if (ret < 0)
  {
    m_sock.close();
    ERR("Could not connect");
    return HTTP_CONN;
  }

  //Send request
  DBG("Sending request");
  char buf[CHUNK_SIZE];
  const char* meth = (method==HTTP_GET)?"GET":(method==HTTP_POST)?"POST":"";
  snprintf(buf, sizeof(buf), "%s %s HTTP/1.1\r\nHost: %s\r\n", meth, path, host); //Write request
  ret = send(buf);
  if(ret)
  {
    m_sock.close();
    ERR("Could not write request");
    return HTTP_CONN;
  }

  //Send all headers

  //Send default headers
  DBG("Sending headers");
  if( (method == HTTP_POST) && (pDataOut != NULL) )
  {
    if( pDataOut->getIsChunked() )
    {
      ret = send("Transfer-Encoding: chunked\r\n");
      CHECK_CONN_ERR(ret);
    }
    else
    {
      snprintf(buf, sizeof(buf), "Content-Length: %d\r\n", pDataOut->getDataLen());
      ret = send(buf);
      CHECK_CONN_ERR(ret);
    }
    char type[48];
    if( pDataOut->getDataType(type, 48) == HTTP_OK )
    {
      snprintf(buf, sizeof(buf), "Content-Type: %s\r\n", type);
      ret = send(buf);
      CHECK_CONN_ERR(ret);
    }
  }

  //Close headers
  DBG("Headers sent");
  ret = send("\r\n");
  CHECK_CONN_ERR(ret);

  size_t trfLen;

  //Send data (if POST)
  if( (method == HTTP_POST) && (pDataOut != NULL) )
  {
    DBG("Sending data");
    while(true)
    {
      size_t writtenLen = 0;
      pDataOut->read(buf, CHUNK_SIZE, &trfLen);
      if( pDataOut->getIsChunked() )
      {
        //Write chunk header
        char chunkHeader[16];
        snprintf(chunkHeader, sizeof(chunkHeader), "%X\r\n", trfLen); //In hex encoding
        ret = send(chunkHeader);
        CHECK_CONN_ERR(ret);
      }
      else if( trfLen == 0 )
      {
        break;
      }
      if( trfLen != 0 )
      {
        ret = send(buf, trfLen);
        CHECK_CONN_ERR(ret);
      }

      if( pDataOut->getIsChunked()  )
      {
        ret = send("\r\n"); //Chunk-terminating CRLF
        CHECK_CONN_ERR(ret);
      }
      else
      {
        writtenLen += trfLen;
        if( writtenLen >= pDataOut->getDataLen() )
        {
          break;
        }
      }

      if( trfLen == 0 )
      {
        break;
      }
    }

  }

  //Receive response
  DBG("Receiving response");
  ret = recv(buf, CHUNK_SIZE - 1, CHUNK_SIZE - 1, &trfLen); //Read n bytes
  CHECK_CONN_ERR(ret);

  buf[trfLen] = '\0';

  char* crlfPtr = strstr(buf, "\r\n");
  if(crlfPtr == NULL)
  {
    PRTCL_ERR();
  }

  int crlfPos = crlfPtr - buf;
  buf[crlfPos] = '\0';

  //Parse HTTP response
  if( sscanf(buf, "HTTP/%*d.%*d %d %*[^\r\n]", &m_httpResponseCode) != 1 )
  {
    //Cannot match string, error
    ERR("Not a correct HTTP answer : %s\n", buf);
    PRTCL_ERR();
  }

  if(m_httpResponseCode != 200)
  {
    //Cannot match string, error
    WARN("Response code %d", m_httpResponseCode);
    PRTCL_ERR();
  }

  DBG("Reading headers");

  memmove(buf, &buf[crlfPos+2], trfLen - (crlfPos + 2) + 1); //Be sure to move NULL-terminating char as well
  trfLen -= (crlfPos + 2);

  size_t recvContentLength = 0;
  bool recvChunked = false;
  //Now get headers
  while( true )
  {
    crlfPtr = strstr(buf, "\r\n");
    if(crlfPtr == NULL)
    {
      if( trfLen < CHUNK_SIZE - 1 )
      {
        size_t newTrfLen;
        ret = recv(buf + trfLen, 1, CHUNK_SIZE - trfLen - 1, &newTrfLen);
        trfLen += newTrfLen;
        buf[trfLen] = '\0';
        DBG("Read %d chars; In buf: [%s]", newTrfLen, buf);
        CHECK_CONN_ERR(ret);
        continue;
      }
      else
      {
        PRTCL_ERR();
      }
    }

    crlfPos = crlfPtr - buf;

    if(crlfPos == 0) //End of headers
    {
      DBG("Headers read");
      memmove(buf, &buf[2], trfLen - 2 + 1); //Be sure to move NULL-terminating char as well
      trfLen -= 2;
      break;
    }

    buf[crlfPos] = '\0';

    char key[64] = {0};
    char value[32] = {0};

    int n = sscanf(buf, "%63[^:]: %31[^\r\n]", key, value);

    if ( n == 2 )
    {
      DBG("Read header : %s: %s\n", key, value);
      if( !strcmp(key, "Content-Length") )
      {
        sscanf(value, "%d", &recvContentLength);
        pDataIn->setDataLen(recvContentLength);
      }
      else if( !strcmp(key, "Transfer-Encoding") )
      {
        if( !strcmp(value, "Chunked") || !strcmp(value, "chunked") )
        {
          recvChunked = true;
          pDataIn->setIsChunked(true);
        }
      }
      else if( !strcmp(key, "Content-Type") )
      {
        pDataIn->setDataType(value);
      }

      memmove(buf, &buf[crlfPos+2], trfLen - (crlfPos + 2) + 1); //Be sure to move NULL-terminating char as well
      trfLen -= (crlfPos + 2);

    }
    else
    {
      ERR("Could not parse header");
      PRTCL_ERR();
    }

  }

  //Receive data
  DBG("Receiving data");
  while(true)
  {
    size_t readLen = 0;

    if( recvChunked )
    {
      //Read chunk header
      crlfPos=0;
      for(crlfPos++; crlfPos < trfLen - 2; crlfPos++)
      {
        if( buf[crlfPos] == '\r' && buf[crlfPos + 1] == '\n' )
        {
          break;
        }
      }
      if(crlfPos >= trfLen - 2) //Try to read more
      {
        if( trfLen < CHUNK_SIZE )
        {
          size_t newTrfLen;
          ret = recv(buf + trfLen, 0, CHUNK_SIZE - trfLen - 1, &newTrfLen);
          trfLen += newTrfLen;
          CHECK_CONN_ERR(ret);
          continue;
        }
        else
        {
          PRTCL_ERR();
        }
      }
      buf[crlfPos] = '\0';
      int n = sscanf(buf, "%x", &readLen);
      if(n!=1)
      {
        ERR("Could not read chunk length");
        PRTCL_ERR();
      }

      memmove(buf, &buf[crlfPos+2], trfLen - (crlfPos + 2)); //Not need to move NULL-terminating char any more
      trfLen -= (crlfPos + 2);

      if( readLen == 0 )
      {
        //Last chunk
        break;
      }
    }
    else
    {
      readLen = recvContentLength;
    }

    DBG("Retrieving %d bytes", readLen);

    do
    {
      pDataIn->write(buf, MIN(trfLen, readLen));
      if( trfLen > readLen )
      {
        memmove(buf, &buf[readLen], trfLen - readLen);
        trfLen -= readLen;
        readLen = 0;
      }
      else
      {
        readLen -= trfLen;
      }

      if(readLen)
      {
        ret = recv(buf, 1, CHUNK_SIZE - trfLen - 1, &trfLen);
        CHECK_CONN_ERR(ret);
      }
    } while(readLen);

    if( recvChunked )
    {
      if(trfLen < 2)
      {
        size_t newTrfLen;
        //Read missing chars to find end of chunk
        ret = recv(buf, 2 - trfLen, CHUNK_SIZE, &newTrfLen);
        CHECK_CONN_ERR(ret);
        trfLen += newTrfLen;
      }
      if( (buf[0] != '\r') || (buf[1] != '\n') )
      {
        ERR("Format error");
        PRTCL_ERR();
      }
      memmove(buf, &buf[2], trfLen - 2);
      trfLen -= 2;
    }
    else
    {
      break;
    }

  }

  m_sock.close();
  DBG("Completed HTTP transaction");

  return HTTP_OK;
}

HTTPResult HTTPClient::recv(char* buf, size_t minLen, size_t maxLen, size_t* pReadLen) //0 on success, err code on failure
{
  DBG("Trying to read between %d and %d bytes", minLen, maxLen);
  size_t readLen = 0;

  if(!m_sock.is_connected())
  {
    WARN("Connection was closed by server");
    return HTTP_CLOSED; //Connection was closed by server
  }

  int ret;
  while(readLen < maxLen)
  {
    if(readLen < minLen)
    {
      DBG("Trying to read at most %d bytes [Blocking]", minLen - readLen);
      m_sock.set_blocking(false, m_timeout);
      ret = m_sock.receive_all(buf + readLen, minLen - readLen);
    }
    else
    {
      DBG("Trying to read at most %d bytes [Not blocking]", maxLen - readLen);
      m_sock.set_blocking(false, 0);
      ret = m_sock.receive(buf + readLen, maxLen - readLen);
    }

    if( ret > 0)
    {
      readLen += ret;
    }
    else if( ret == 0 )
    {
      break;
    }
    else
    {
      if(!m_sock.is_connected())
      {
        ERR("Connection error (recv returned %d)", ret);
        *pReadLen = readLen;
        return HTTP_CONN;
      }
      else
      {
        break;
      }
    }

    if(!m_sock.is_connected())
    {
      break;
    }
  }
  DBG("Read %d bytes", readLen);
  *pReadLen = readLen;
  return HTTP_OK;
}

HTTPResult HTTPClient::send(char* buf, size_t len) //0 on success, err code on failure
{
  if(len == 0)
  {
    len = strlen(buf);
  }
  DBG("Trying to write %d bytes", len);
  size_t writtenLen = 0;

  if(!m_sock.is_connected())
  {
    WARN("Connection was closed by server");
    return HTTP_CLOSED; //Connection was closed by server
  }

  m_sock.set_blocking(false, m_timeout);
  int ret = m_sock.send_all(buf, len);
  if(ret > 0)
  {
    writtenLen += ret;
  }
  else if( ret == 0 )
  {
    WARN("Connection was closed by server");
    return HTTP_CLOSED; //Connection was closed by server
  }
  else
  {
    ERR("Connection error (send returned %d)", ret);
    return HTTP_CONN;
  }

  DBG("Written %d bytes", writtenLen);
  return HTTP_OK;
}

HTTPResult HTTPClient::parseURL(const char* url, char* scheme, size_t maxSchemeLen, char* host, size_t maxHostLen, uint16_t* port, char* path, size_t maxPathLen) //Parse URL
{
  char* schemePtr = (char*) url;
  char* hostPtr = (char*) strstr(url, "://");
  if(hostPtr == NULL)
  {
    WARN("Could not find host");
    return HTTP_PARSE; //URL is invalid
  }

  if( maxSchemeLen < hostPtr - schemePtr + 1 ) //including NULL-terminating char
  {
    WARN("Scheme str is too small (%d >= %d)", maxSchemeLen, hostPtr - schemePtr + 1);
    return HTTP_PARSE;
  }
  memcpy(scheme, schemePtr, hostPtr - schemePtr);
  scheme[hostPtr - schemePtr] = '\0';

  hostPtr+=3;

  size_t hostLen = 0;

  char* portPtr = strchr(hostPtr, ':');
  if( portPtr != NULL )
  {
    hostLen = portPtr - hostPtr;
    portPtr++;
    if( sscanf(portPtr, "%hu", port) != 1)
    {
      WARN("Could not find port");
      return HTTP_PARSE;
    }
  }
  else
  {
    *port=0;
  }
  char* pathPtr = strchr(hostPtr, '/');
  if( hostLen == 0 )
  {
    hostLen = pathPtr - hostPtr;
  }

  if( maxHostLen < hostLen + 1 ) //including NULL-terminating char
  {
    WARN("Host str is too small (%d >= %d)", maxHostLen, hostLen + 1);
    return HTTP_PARSE;
  }
  memcpy(host, hostPtr, hostLen);
  host[hostLen] = '\0';

  size_t pathLen;
  char* fragmentPtr = strchr(hostPtr, '#');
  if(fragmentPtr != NULL)
  {
    pathLen = fragmentPtr - pathPtr;
  }
  else
  {
    pathLen = strlen(pathPtr);
  }

  if( maxPathLen < pathLen + 1 ) //including NULL-terminating char
  {
    WARN("Path str is too small (%d >= %d)", maxPathLen, pathLen + 1);
    return HTTP_PARSE;
  }
  memcpy(path, pathPtr, pathLen);
  path[pathLen] = '\0';

  return HTTP_OK;
}
