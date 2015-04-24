/* IHTTPData.h */
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

#ifndef IHTTPDATA_H
#define IHTTPDATA_H

#include <cstring>

using std::size_t;

///This is a simple interface for HTTP data storage (impl examples are Key/Value Pairs, File, etc...)
class IHTTPDataOut
{
protected:
  friend class HTTPClient;

  /** Read a piece of data to be transmitted
   * @param buf Pointer to the buffer on which to copy the data
   * @param len Length of the buffer
   * @param pReadLen Pointer to the variable on which the actual copied data length will be stored
   */
  virtual int read(char* buf, size_t len, size_t* pReadLen) = 0;

  /** Get MIME type
   * @param type Internet media type from Content-Type header
   */
  virtual int getDataType(char* type, size_t maxTypeLen) = 0; //Internet media type for Content-Type header

  /** Determine whether the HTTP client should chunk the data
   *  Used for Transfer-Encoding header
   */
  virtual bool getIsChunked() = 0;

  /** If the data is not chunked, get its size
   *  Used for Content-Length header
   */
  virtual size_t getDataLen() = 0;

};

///This is a simple interface for HTTP data storage (impl examples are Key/Value Pairs, File, etc...)
class IHTTPDataIn
{
protected:
  friend class HTTPClient;

  /** Write a piece of data transmitted by the server
   * @param buf Pointer to the buffer from which to copy the data
   * @param len Length of the buffer
   */
  virtual int write(const char* buf, size_t len) = 0;

  /** Set MIME type
   * @param type Internet media type from Content-Type header
   */
  virtual void setDataType(const char* type) = 0;

  /** Determine whether the data is chunked
   *  Recovered from Transfer-Encoding header
   */
  virtual void setIsChunked(bool chunked) = 0;

  /** If the data is not chunked, set its size
   * From Content-Length header
   */
  virtual void setDataLen(size_t len) = 0;

};

#endif
