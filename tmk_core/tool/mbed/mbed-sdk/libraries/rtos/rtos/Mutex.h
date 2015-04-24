/* mbed Microcontroller Library
 * Copyright (c) 2006-2012 ARM Limited
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef MUTEX_H
#define MUTEX_H

#include <stdint.h>
#include "cmsis_os.h"

namespace rtos {

/** The Mutex class is used to synchronise the execution of threads.
 This is for example used to protect access to a shared resource.
*/
class Mutex {
public:
    /** Create and Initialize a Mutex object */
    Mutex();

    /** Wait until a Mutex becomes available.
      @param   millisec  timeout value or 0 in case of no time-out. (default: osWaitForever)
      @return  status code that indicates the execution status of the function.
     */
    osStatus lock(uint32_t millisec=osWaitForever);

    /** Try to lock the mutex, and return immediately
      @return  true if the mutex was acquired, false otherwise.
     */
    bool trylock();

    /** Unlock the mutex that has previously been locked by the same thread
      @return  status code that indicates the execution status of the function.
     */
    osStatus unlock();

    ~Mutex();

private:
    osMutexId _osMutexId;
    osMutexDef_t _osMutexDef;
#ifdef CMSIS_OS_RTX
    int32_t _mutex_data[3];
#endif
};

}
#endif
