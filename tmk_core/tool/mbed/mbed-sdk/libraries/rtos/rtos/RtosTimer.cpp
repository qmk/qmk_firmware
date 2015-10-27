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
#include "RtosTimer.h"

#include <string.h>

#include "cmsis_os.h"
#include "mbed_error.h"

namespace rtos {

RtosTimer::RtosTimer(void (*periodic_task)(void const *argument), os_timer_type type, void *argument) {
#ifdef CMSIS_OS_RTX
    _timer.ptimer = periodic_task;

    memset(_timer_data, 0, sizeof(_timer_data));
    _timer.timer = _timer_data;
#endif
    _timer_id = osTimerCreate(&_timer, type, argument);
}

osStatus RtosTimer::start(uint32_t millisec) {
    return osTimerStart(_timer_id, millisec);
}

osStatus RtosTimer::stop(void) {
    return osTimerStop(_timer_id);
}

RtosTimer::~RtosTimer() {
    osTimerDelete(_timer_id);
}

}
