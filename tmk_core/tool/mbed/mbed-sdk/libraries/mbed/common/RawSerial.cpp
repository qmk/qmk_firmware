/* mbed Microcontroller Library
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
#include "RawSerial.h"
#include "wait_api.h"
#include <cstdarg>

#if DEVICE_SERIAL

#define STRING_STACK_LIMIT    120

namespace mbed {

RawSerial::RawSerial(PinName tx, PinName rx) : SerialBase(tx, rx) {
}

int RawSerial::getc() {
    return _base_getc();
}

int RawSerial::putc(int c) {
    return _base_putc(c);
}

int RawSerial::puts(const char *str) {
    while (*str)
        putc(*str ++);
    return 0;
}

// Experimental support for printf in RawSerial. No Stream inheritance
// means we can't call printf() directly, so we use sprintf() instead.
// We only call malloc() for the sprintf() buffer if the buffer
// length is above a certain threshold, otherwise we use just the stack.
int RawSerial::printf(const char *format, ...) {
    std::va_list arg;
    va_start(arg, format);
    int len = vsnprintf(NULL, 0, format, arg);
    if (len < STRING_STACK_LIMIT) {
        char temp[STRING_STACK_LIMIT];
        vsprintf(temp, format, arg);
        puts(temp);
    } else {
        char *temp = new char[len + 1];
        vsprintf(temp, format, arg);
        puts(temp);
        delete[] temp;
    }
    va_end(arg);
    return len;
}

} // namespace mbed

#endif
