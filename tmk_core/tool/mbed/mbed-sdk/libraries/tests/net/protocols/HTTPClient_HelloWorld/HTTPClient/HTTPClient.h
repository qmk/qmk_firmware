/* HTTPClient.h */
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

/** \file
HTTP Client header file
*/

#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include "TCPSocketConnection.h"

#define HTTP_CLIENT_DEFAULT_TIMEOUT 15000

class HTTPData;

#include "IHTTPData.h"
#include "mbed.h"

///HTTP client results
enum HTTPResult
{
  HTTP_PROCESSING, ///<Processing
  HTTP_PARSE, ///<url Parse error
  HTTP_DNS, ///<Could not resolve name
  HTTP_PRTCL, ///<Protocol error
  HTTP_NOTFOUND, ///<HTTP 404 Error
  HTTP_REFUSED, ///<HTTP 403 Error
  HTTP_ERROR, ///<HTTP xxx error
  HTTP_TIMEOUT, ///<Connection timeout
  HTTP_CONN, ///<Connection error
  HTTP_CLOSED, ///<Connection was closed by remote host
  HTTP_OK = 0, ///<Success
};

/**A simple HTTP Client
The HTTPClient is composed of:
- The actual client (HTTPClient)
- Classes that act as a data repository, each of which deriving from the HTTPData class (HTTPText for short text content, HTTPFile for file I/O, HTTPMap for key/value pairs, and HTTPStream for streaming purposes)
*/
class HTTPClient
{
public:
  ///Instantiate the HTTP client
  HTTPClient();
  ~HTTPClient();

#if 0 //TODO add header handlers
  /**
  Provides a basic authentification feature (Base64 encoded username and password)
  Pass two NULL pointers to switch back to no authentication
  @param user username to use for authentication, must remain valid durlng the whole HTTP session
  @param user password to use for authentication, must remain valid durlng the whole HTTP session
  */
  void basicAuth(const char* user, const char* password); //Basic Authentification
#endif

  //High Level setup functions
  /** Execute a GET request on the url
  Blocks until completion
  @param url : url on which to execute the request
  @param pDataIn : pointer to an IHTTPDataIn instance that will collect the data returned by the request, can be NULL
  @param timeout waiting timeout in ms (osWaitForever for blocking function, not recommended)
  @return 0 on success, HTTP error (<0) on failure
  */
  HTTPResult get(const char* url, IHTTPDataIn* pDataIn, int timeout = HTTP_CLIENT_DEFAULT_TIMEOUT); //Blocking

  /** Execute a GET request on the url
  Blocks until completion
  This is a helper to directly get a piece of text from a HTTP result
  @param url : url on which to execute the request
  @param result : pointer to a char array in which the result will be stored
  @param maxResultLen : length of the char array (including space for the NULL-terminating char)
  @param timeout waiting timeout in ms (osWaitForever for blocking function, not recommended)
  @return 0 on success, HTTP error (<0) on failure
  */
  HTTPResult get(const char* url, char* result, size_t maxResultLen, int timeout = HTTP_CLIENT_DEFAULT_TIMEOUT); //Blocking

  /** Execute a POST request on the url
  Blocks until completion
  @param url : url on which to execute the request
  @param dataOut : a IHTTPDataOut instance that contains the data that will be posted
  @param pDataIn : pointer to an IHTTPDataIn instance that will collect the data returned by the request, can be NULL
  @param timeout waiting timeout in ms (osWaitForever for blocking function, not recommended)
  @return 0 on success, HTTP error (<0) on failure
  */
  HTTPResult post(const char* url, const IHTTPDataOut& dataOut, IHTTPDataIn* pDataIn, int timeout = HTTP_CLIENT_DEFAULT_TIMEOUT); //Blocking

  /** Get last request's HTTP response code
  @return The HTTP response code of the last request
  */
  int getHTTPResponseCode();

private:
  enum HTTP_METH
  {
    HTTP_GET,
    HTTP_POST,
    HTTP_HEAD
  };

  HTTPResult connect(const char* url, HTTP_METH method, IHTTPDataOut* pDataOut, IHTTPDataIn* pDataIn, int timeout); //Execute request
  HTTPResult recv(char* buf, size_t minLen, size_t maxLen, size_t* pReadLen); //0 on success, err code on failure
  HTTPResult send(char* buf, size_t len = 0); //0 on success, err code on failure
  HTTPResult parseURL(const char* url, char* scheme, size_t maxSchemeLen, char* host, size_t maxHostLen, uint16_t* port, char* path, size_t maxPathLen); //Parse URL

  //Parameters
  TCPSocketConnection m_sock;

  int m_timeout;

  const char* m_basicAuthUser;
  const char* m_basicAuthPassword;
  int m_httpResponseCode;

};

//Including data containers here for more convenience
#include "data/HTTPText.h"
#include "data/HTTPMap.h"

#endif
