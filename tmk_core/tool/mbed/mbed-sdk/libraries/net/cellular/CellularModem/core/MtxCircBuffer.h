/* MtxCircBuf.h */
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

#ifndef MTXCIRCBUFFER_H
#define MTXCIRCBUFFER_H

#include "rtos.h"

//Mutex protected circualr buffer
template<typename T, int size>
class MtxCircBuffer
{
public:
  MtxCircBuffer() //:
      //mtx()
  {
    write = 0;
    read = 0;
  }

  bool isFull()
  {
    mtx.lock();
    bool r = (((write + 1) % size) == read);
    mtx.unlock();
    return r;
  }

  bool isEmpty()
  {
    mtx.lock();
    bool r = (read == write);
    mtx.unlock();
    return r;
  }

  void queue(T k)
  {
    mtx.lock();
    buf[write++] = k;
    write %= size;
    if (isFull())
    {
        read++;
        read %= size;
    }
    mtx.unlock();
  }

  uint16_t available()
  {
    mtx.lock();
    uint16_t a = (write >= read) ? (write - read) : (size - read + write);
    mtx.unlock();
    return a;
  }

  bool dequeue(T * c)
  {
    mtx.lock();
    bool empty = (read == write);
    if (!empty)
    {
      *c = buf[read++];
      read %= size;
    }
    mtx.unlock();
    return (!empty);
  }

private:
  volatile uint16_t write;
  volatile uint16_t read;
  volatile T buf[size];
  Mutex mtx;
};

#endif

