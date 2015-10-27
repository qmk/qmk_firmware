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
#ifndef RTOS_TIMER_H
#define RTOS_TIMER_H

#include <stdint.h>
#include "cmsis_os.h"

namespace rtos {

/** The RtosTimer class allow creating and and controlling of timer functions in the system.
 A timer function is called when a time period expires whereby both on-shot and
 periodic timers are possible. A timer can be started, restarted, or stopped.

 Timers are handled in the thread osTimerThread.
 Callback functions run under control of this thread and may use CMSIS-RTOS API calls.
*/
class RtosTimer {
public:
    /** Create and Start timer.
      @param   task      name of the timer call back function.
      @param   type      osTimerOnce for one-shot or osTimerPeriodic for periodic behaviour. (default: osTimerPeriodic)
      @param   argument  argument to the timer call back function. (default: NULL)
    */
    RtosTimer(void (*task)(void const *argument),
          os_timer_type type=osTimerPeriodic,
          void *argument=NULL);

    /** Stop the timer.
      @return  status code that indicates the execution status of the function.
    */
    osStatus stop(void);

    /** start a timer.
      @param   millisec  time delay value of the timer.
      @return  status code that indicates the execution status of the function.
    */
    osStatus start(uint32_t millisec);

    ~RtosTimer();

private:
    osTimerId _timer_id;
    osTimerDef_t _timer;
#ifdef CMSIS_OS_RTX
    uint32_t _timer_data[5];
#endif
};

}

#endif
