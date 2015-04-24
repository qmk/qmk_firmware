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
#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <stdint.h>
#include "cmsis_os.h"

namespace rtos {

/** The Semaphore class is used to manage and protect access to a set of shared resources. */
class Semaphore {
public:
    /** Create and Initialize a Semaphore object used for managing resources.
      @param number of available resources; maximum index value is (count-1).
    */
    Semaphore(int32_t count);

    /** Wait until a Semaphore resource becomes available.
      @param   millisec  timeout value or 0 in case of no time-out. (default: osWaitForever).
      @return  number of available tokens, or -1 in case of incorrect parameters
    */
    int32_t wait(uint32_t millisec=osWaitForever);

    /** Release a Semaphore resource that was obtain with Semaphore::wait.
      @return  status code that indicates the execution status of the function.
    */
    osStatus release(void);

    ~Semaphore();

private:
    osSemaphoreId _osSemaphoreId;
    osSemaphoreDef_t _osSemaphoreDef;
#ifdef CMSIS_OS_RTX
    uint32_t _semaphore_data[2];
#endif
};

}
#endif
