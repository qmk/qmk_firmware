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
#include "Semaphore.h"

#include <string.h>

namespace rtos {

Semaphore::Semaphore(int32_t count) {
#ifdef CMSIS_OS_RTX
    memset(_semaphore_data, 0, sizeof(_semaphore_data));
    _osSemaphoreDef.semaphore = _semaphore_data;
#endif
    _osSemaphoreId = osSemaphoreCreate(&_osSemaphoreDef, count);
}

int32_t Semaphore::wait(uint32_t millisec) {
    return osSemaphoreWait(_osSemaphoreId, millisec);
}

osStatus Semaphore::release(void) {
    return osSemaphoreRelease(_osSemaphoreId);
}

Semaphore::~Semaphore() {
    osSemaphoreDelete(_osSemaphoreId);
}

}
