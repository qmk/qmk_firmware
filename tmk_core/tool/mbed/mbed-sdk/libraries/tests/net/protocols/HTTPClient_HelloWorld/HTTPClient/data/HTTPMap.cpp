/* HTTPMap.cpp */
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

#include "HTTPMap.h"

#include <cstring>

#include <cctype>

#define OK 0

using std::strncpy;

HTTPMap::HTTPMap() : m_pos(0), m_count(0)
{

}

void HTTPMap::put(const char* key, const char* value)
{
  if(m_count >= HTTPMAP_TABLE_SIZE)
  {
    return;
  }
  m_keys[m_count] = key;
  m_values[m_count] = value;
  m_count++;
}

void HTTPMap::clear()
{
  m_count = 0;
  m_pos = 0;
}


/*virtual*/ int HTTPMap::read(char* buf, size_t len, size_t* pReadLen)
{
  if(m_pos >= m_count)
  {
    *pReadLen = 0;
    m_pos = 0;
    return OK;
  }

  //URL encode
  char* out = buf;
  const char* in = m_keys[m_pos];
  if( (m_pos != 0) && (out - buf < len - 1) )
  {
    *out='&';
    out++;
  }

  while( (*in != '\0') && (out - buf < len - 3) )
  {
    if (std::isalnum(*in) || *in == '-' || *in == '_' || *in == '.' || *in == '~')
    {
      *out = *in;
      out++;
    }
    else if( *in == ' ' )
    {
      *out='+';
      out++;
    }
    else
    {
      char hex[] = "0123456789abcdef";
      *out='%';
      out++;
      *out=hex[(*in>>4)&0xf];
      out++;
      *out=hex[(*in)&0xf];
      out++;
    }
    in++;
  }

  if( out - buf < len - 1 )
  {
    *out='=';
    out++;
  }

  in = m_values[m_pos];
  while( (*in != '\0') && (out - buf < len - 3) )
  {
    if (std::isalnum(*in) || *in == '-' || *in == '_' || *in == '.' || *in == '~')
    {
      *out = *in;
      out++;
    }
    else if( *in == ' ' )
    {
      *out='+';
      out++;
    }
    else
    {
      char hex[] = "0123456789abcdef";
      *out='%';
      out++;
      *out=hex[(*in>>4)&0xf];
      out++;
      *out=hex[(*in)&0xf];
      out++;
    }
    in++;
  }

  *pReadLen = out - buf;

  m_pos++;
  return OK;
}

/*virtual*/ int HTTPMap::getDataType(char* type, size_t maxTypeLen) //Internet media type for Content-Type header
{
  strncpy(type, "application/x-www-form-urlencoded", maxTypeLen-1);
  type[maxTypeLen-1] = '\0';
  return OK;
}

/*virtual*/ bool HTTPMap::getIsChunked() //For Transfer-Encoding header
{
  return false; ////Data is computed one key/value pair at a time
}

/*virtual*/ size_t HTTPMap::getDataLen() //For Content-Length header
{
  size_t count = 0;
  for(size_t i = 0; i< m_count; i++)
  {
    //URL encode
    const char* in = m_keys[i];
    if( i != 0 )
    {
      count++;
    }

    while( (*in != '\0') )
    {
      if (std::isalnum(*in) || *in == '-' || *in == '_' || *in == '.' || *in == '~')
      {
        count++;
      }
      else if( *in == ' ' )
      {
        count++;
      }
      else
      {
        count+=3;
      }
      in++;
    }

    count ++;

    in = m_values[i];
    while( (*in != '\0') )
    {
      if (std::isalnum(*in) || *in == '-' || *in == '_' || *in == '.' || *in == '~')
      {
        count++;
      }
      else if( *in == ' ' )
      {
        count++;
      }
      else
      {
        count+=3;
      }
      in++;
    }
  }
  return count;
}
