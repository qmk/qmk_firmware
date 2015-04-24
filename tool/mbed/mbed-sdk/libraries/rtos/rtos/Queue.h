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
#ifndef QUEUE_H
#define QUEUE_H

#include <stdint.h>
#include <string.h>

#include "cmsis_os.h"
#include "mbed_error.h"

namespace rtos {

/** The Queue class allow to control, send, receive, or wait for messages.
 A message can be a integer or pointer value  to a certain type T that is send
 to a thread or interrupt service routine.
  @tparam  T         data type of a single message element.
  @tparam  queue_sz  maximum number of messages in queue.
*/
template<typename T, uint32_t queue_sz>
class Queue {
public:
    /** Create and initialise a message Queue. */
    Queue() {
    #ifdef CMSIS_OS_RTX
        memset(_queue_q, 0, sizeof(_queue_q));
        _queue_def.pool = _queue_q;
        _queue_def.queue_sz = queue_sz;
    #endif
        _queue_id = osMessageCreate(&_queue_def, NULL);
        if (_queue_id == NULL) {
            error("Error initialising the queue object\n");
        }
    }

    /** Put a message in a Queue.
      @param   data      message pointer.
      @param   millisec  timeout value or 0 in case of no time-out. (default: 0)
      @return  status code that indicates the execution status of the function.
    */
    osStatus put(T* data, uint32_t millisec=0) {
        return osMessagePut(_queue_id, (uint32_t)data, millisec);
    }

    /** Get a message or Wait for a message from a Queue.
      @param   millisec  timeout value or 0 in case of no time-out. (default: osWaitForever).
      @return  event information that includes the message and the status code.
    */
    osEvent get(uint32_t millisec=osWaitForever) {
        return osMessageGet(_queue_id, millisec);
    }

private:
    osMessageQId    _queue_id;
    osMessageQDef_t _queue_def;
#ifdef CMSIS_OS_RTX
    uint32_t        _queue_q[4+(queue_sz)];
#endif
};

}
#endif
