/* fsl_os_mbed_abstraction.h */
/* Copyright (C) 2012 mbed.org, MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef FSL_OS_ABSTRACTION_MBED_H_
#define FSL_OS_ABSTRACTION_MBED_H_

// This is not really an "abstraction", but rather a set of quick&dirty
// defines to allow the KSDK to compile. Currently, this is relevant only
// in the context of the ENET driver (fsl_enet_driver.c)

typedef int event_object_t;
typedef int lock_object_t;
typedef void sync_object_t;
typedef unsigned int event_group_t;
typedef int task_t;
typedef void task_stack_t;
typedef int task_handler_t;
typedef int msg_queue_handler_t;
typedef void msg_queue_t;
typedef int msg_queue_item_t;

#endif // #ifdef FSL_OS_ABSTRACTION_MBED_H_
