/* HTTPMap.h */
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


#ifndef HTTPMAP_H_
#define HTTPMAP_H_

#include "../IHTTPData.h"

#define HTTPMAP_TABLE_SIZE 32

/** Map of key/value pairs
 * Used to transmit POST data using the application/x-www-form-urlencoded encoding
 */
class HTTPMap: public IHTTPDataOut
{
public:
  /**
   Instantiates HTTPMap
   It supports at most 32 key/values pairs
   */
  HTTPMap();

  /** Put Key/Value pair
   The references to the parameters must remain valid as long as the clear() function is not called
   @param key The key to use
   @param value The corresponding value
   */
  void put(const char* key, const char* value);

  /** Clear table
   */
  void clear();

protected:
  //IHTTPDataIn
  virtual void readReset();

  virtual int read(char* buf, size_t len, size_t* pReadLen);

  virtual int getDataType(char* type, size_t maxTypeLen); //Internet media type for Content-Type header

  virtual bool getIsChunked(); //For Transfer-Encoding header

  virtual size_t getDataLen(); //For Content-Length header

private:
  const char* m_keys[HTTPMAP_TABLE_SIZE];
  const char* m_values[HTTPMAP_TABLE_SIZE];

  size_t m_pos;
  size_t m_count;
};

#endif /* HTTPMAP_H_ */
