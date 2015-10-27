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
#include "Mutex.h"

#include <string.h>
#include "mbed_error.h"

namespace rtos {

Mutex::Mutex() {
#ifdef CMSIS_OS_RTX
    memset(_mutex_data, 0, sizeof(_mutex_data));
    _osMutexDef.mutex = _mutex_data;
#endif
    _osMutexId = osMutexCreate(&_osMutexDef);
    if (_osMutexId == NULL) {
        error("Error initializing the mutex object\n");
    }
}

osStatus Mutex::lock(uint32_t millisec) {
    return osMutexWait(_osMutexId, millisec);
}

bool Mutex::trylock() {
    return (osMutexWait(_osMutexId, 0) == osOK);
}

osStatus Mutex::unlock() {
    return osMutexRelease(_osMutexId);
}

Mutex::~Mutex() {
    osMutexDelete(_osMutexId);
}

}
