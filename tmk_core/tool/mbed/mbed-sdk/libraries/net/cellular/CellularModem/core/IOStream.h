/* IOStream.h */
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

#ifndef IOSTREAM_H_
#define IOSTREAM_H_

#include "rtos.h"

class IStream
{
public:
  //IStream();
  //virtual ~IStream();

    //0 for non-blocking (returns immediately), osWaitForever for infinite blocking
    virtual int read(uint8_t* buf, size_t* pLength, size_t maxLength, uint32_t timeout=osWaitForever) = 0;
    virtual size_t available() = 0;
    virtual int waitAvailable(uint32_t timeout=osWaitForever) = 0; //Wait for data to be available
    virtual int abortRead() = 0; //Abort current reading (or waiting) operation
};

class OStream
{
public:
  //OStream();
  //virtual ~OStream();

    //0 for non-blocking (returns immediately), osWaitForever for infinite blocking
    virtual int write(uint8_t* buf, size_t length, uint32_t timeout=osWaitForever) = 0;
    virtual size_t space() = 0;
    virtual int waitSpace(uint32_t timeout=osWaitForever) = 0; //Wait for space to be available
    virtual int abortWrite() = 0; //Abort current writing (or waiting) operation
};

class IOStream : public IStream, public OStream
{
public:
  //IOStream();
  //virtual ~IOStream();
};


#endif /* IOSTREAM_H_ */
