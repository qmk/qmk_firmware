/* mbed USBHost Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MTXCIRCBUFFER_H
#define MTXCIRCBUFFER_H

#include "stdint.h"
#include "rtos.h"

//Mutex protected circular buffer
template<typename T, int size>
class MtxCircBuffer {
public:

    MtxCircBuffer() {
        write = 0;
        read = 0;
    }

    bool isFull() {
        mtx.lock();
        bool r = (((write + 1) % size) == read);
        mtx.unlock();
        return r;
    }

    bool isEmpty() {
        mtx.lock();
        bool r = (read == write);
        mtx.unlock();
        return r;
    }

    void flush() {
        write = 0;
        read = 0;
    }

    void queue(T k) {
        mtx.lock();
        while (((write + 1) % size) == read) {
            mtx.unlock();
            Thread::wait(10);
            mtx.lock();
        }
        buf[write++] = k;
        write %= size;
        mtx.unlock();
    }

    uint16_t available() {
        mtx.lock();
        uint16_t a = (write >= read) ? (write - read) : (size - read + write);
        mtx.unlock();
        return a;
    }

    bool dequeue(T * c) {
        mtx.lock();
        bool empty = (read == write);
        if (!empty) {
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
