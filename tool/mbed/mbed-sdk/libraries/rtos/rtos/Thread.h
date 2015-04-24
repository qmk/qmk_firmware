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
#ifndef THREAD_H
#define THREAD_H

#include <stdint.h>
#include "cmsis_os.h"

namespace rtos {

/** The Thread class allow defining, creating, and controlling thread functions in the system. */
class Thread {
public:
    /** Create a new thread, and start it executing the specified function.
      @param   task           function to be executed by this thread.
      @param   argument       pointer that is passed to the thread function as start argument. (default: NULL).
      @param   priority       initial priority of the thread function. (default: osPriorityNormal).
      @param   stack_size      stack size (in bytes) requirements for the thread function. (default: DEFAULT_STACK_SIZE).
      @param   stack_pointer  pointer to the stack area to be used by this thread (default: NULL).
    */
    Thread(void (*task)(void const *argument), void *argument=NULL,
           osPriority priority=osPriorityNormal,
           uint32_t stack_size=DEFAULT_STACK_SIZE,
           unsigned char *stack_pointer=NULL);

    /** Terminate execution of a thread and remove it from Active Threads
      @return  status code that indicates the execution status of the function.
    */
    osStatus terminate();

    /** Set priority of an active thread
      @param   priority  new priority value for the thread function.
      @return  status code that indicates the execution status of the function.
    */
    osStatus set_priority(osPriority priority);

    /** Get priority of an active thread
      @return  current priority value of the thread function.
    */
    osPriority get_priority();

    /** Set the specified Signal Flags of an active thread.
      @param   signals  specifies the signal flags of the thread that should be set.
      @return  previous signal flags of the specified thread or 0x80000000 in case of incorrect parameters.
    */
    int32_t signal_set(int32_t signals);

    /** State of the Thread */
    enum State {
        Inactive,           /**< Not created or terminated */
        Ready,              /**< Ready to run */
        Running,            /**< Running */
        WaitingDelay,       /**< Waiting for a delay to occur */
        WaitingInterval,    /**< Waiting for an interval to occur */
        WaitingOr,          /**< Waiting for one event in a set to occur */
        WaitingAnd,         /**< Waiting for multiple events in a set to occur */
        WaitingSemaphore,   /**< Waiting for a semaphore event to occur */
        WaitingMailbox,     /**< Waiting for a mailbox event to occur */
        WaitingMutex,       /**< Waiting for a mutex event to occur */
    };

    /** State of this Thread
      @return  the State of this Thread
    */
    State get_state();

    /** Wait for one or more Signal Flags to become signaled for the current RUNNING thread.
      @param   signals   wait until all specified signal flags set or 0 for any single signal flag.
      @param   millisec  timeout value or 0 in case of no time-out. (default: osWaitForever).
      @return  event flag information or error code.
    */
    static osEvent signal_wait(int32_t signals, uint32_t millisec=osWaitForever);

    /** Wait for a specified time period in millisec:
      @param   millisec  time delay value
      @return  status code that indicates the execution status of the function.
    */
    static osStatus wait(uint32_t millisec);

    /** Pass control to next thread that is in state READY.
      @return  status code that indicates the execution status of the function.
    */
    static osStatus yield();

    /** Get the thread id of the current running thread.
      @return  thread ID for reference by other functions or NULL in case of error.
    */
    static osThreadId gettid();

    virtual ~Thread();

private:
    osThreadId _tid;
    osThreadDef_t _thread_def;
    bool _dynamic_stack;
};

}
#endif
