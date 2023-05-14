/* 
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
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
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * This file is part of the TinyUSB stack.
 */

#ifndef _TUSB_OSAL_H_
#define _TUSB_OSAL_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "common/tusb_common.h"

typedef void (*osal_task_func_t)( void * );

// Timeout
#define OSAL_TIMEOUT_NOTIMEOUT     (0)          // Return immediately
#define OSAL_TIMEOUT_NORMAL        (10)         // Default timeout
#define OSAL_TIMEOUT_WAIT_FOREVER  (UINT32_MAX) // Wait forever
#define OSAL_TIMEOUT_CONTROL_XFER  OSAL_TIMEOUT_WAIT_FOREVER

// Mutex is required when using a preempted RTOS or MCU has multiple cores
#if (CFG_TUSB_OS == OPT_OS_NONE) && !TUP_MCU_MULTIPLE_CORE
  #define OSAL_MUTEX_REQUIRED   0
  #define OSAL_MUTEX_DEF(_name) uint8_t :0
#else
  #define OSAL_MUTEX_REQUIRED   1
  #define OSAL_MUTEX_DEF(_name) osal_mutex_def_t _name
#endif

// OS thin implementation
#if CFG_TUSB_OS == OPT_OS_NONE
  #include "osal_none.h"
#elif CFG_TUSB_OS == OPT_OS_FREERTOS
  #include "osal_freertos.h"
#elif CFG_TUSB_OS == OPT_OS_MYNEWT
  #include "osal_mynewt.h"
#elif CFG_TUSB_OS == OPT_OS_PICO
  #include "osal_pico.h"
#elif CFG_TUSB_OS == OPT_OS_RTTHREAD
  #include "osal_rtthread.h"
#elif CFG_TUSB_OS == OPT_OS_RTX4
  #include "osal_rtx4.h"
#elif CFG_TUSB_OS == OPT_OS_CUSTOM
  #include "tusb_os_custom.h" // implemented by application
#else
  #error OS is not supported yet
#endif

//--------------------------------------------------------------------+
// OSAL Porting API
// Should be implemented as static inline function in osal_port.h header
/*
   osal_semaphore_t osal_semaphore_create(osal_semaphore_def_t* semdef);
   bool osal_semaphore_post(osal_semaphore_t sem_hdl, bool in_isr);
   bool osal_semaphore_wait(osal_semaphore_t sem_hdl, uint32_t msec);
   void osal_semaphore_reset(osal_semaphore_t sem_hdl); // TODO removed

   osal_mutex_t osal_mutex_create(osal_mutex_def_t* mdef);
   bool osal_mutex_lock (osal_mutex_t sem_hdl, uint32_t msec);
   bool osal_mutex_unlock(osal_mutex_t mutex_hdl);

   osal_queue_t osal_queue_create(osal_queue_def_t* qdef);
   bool osal_queue_receive(osal_queue_t qhdl, void* data, uint32_t msec);
   bool osal_queue_send(osal_queue_t qhdl, void const * data, bool in_isr);
   bool osal_queue_empty(osal_queue_t qhdl);
*/
//--------------------------------------------------------------------+

#ifdef __cplusplus
 }
#endif

#endif /* _TUSB_OSAL_H_ */
