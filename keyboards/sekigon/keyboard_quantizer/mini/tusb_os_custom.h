/* 
 * The MIT License (MIT)
 *
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 * Copyright (c) 2023 sekigon-gonnoc
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
#pragma once

#ifdef __cplusplus
 extern "C" {
#endif

 typedef struct {
     struct {
         void *prev;
             void *next;
     } queue_t;
     void* owner;
     void* next;
     uint32_t cnt;
 } chtemp_mutex_t;

typedef chtemp_mutex_t osal_mutex_def_t, *osal_mutex_t;
void osal_task_delay(uint32_t msec);
osal_mutex_t osal_mutex_create(osal_mutex_def_t* mdef);
bool osal_mutex_lock (osal_mutex_t mutex_hdl, uint32_t msec);
bool osal_mutex_unlock(osal_mutex_t mutex_hdl);

//--------------------------------------------------------------------+
// QUEUE API
//--------------------------------------------------------------------+

#include "common/tusb_fifo.h"

typedef struct
{
    tu_fifo_t ff;
    chtemp_mutex_t mutex;
} osal_queue_def_t;

typedef osal_queue_def_t* osal_queue_t;

static inline void _osal_q_lock(osal_queue_t qhdl) {
    osal_mutex_lock(&qhdl->mutex,0);
}
static inline void _osal_q_unlock(osal_queue_t qhdl){
    osal_mutex_unlock(&qhdl->mutex);
}

// role device/host is used by OS NONE for mutex (disable usb isr) only
#define OSAL_QUEUE_DEF(_int_set, _name, _depth, _type)       \
  uint8_t _name##_buf[_depth*sizeof(_type)];              \
  osal_queue_def_t _name = {                              \
    .ff = TU_FIFO_INIT(_name##_buf, _depth, _type, false) \
  }

TU_ATTR_ALWAYS_INLINE static inline osal_queue_t osal_queue_create(osal_queue_def_t* qdef)
{
  tu_fifo_clear(&qdef->ff);
  osal_mutex_create(&qdef->mutex);
  return (osal_queue_t) qdef;
}

TU_ATTR_ALWAYS_INLINE static inline bool osal_queue_receive(osal_queue_t qhdl, void* data, uint32_t msec)
{
  (void) msec; // not used, always behave as msec = 0

  // TODO: revisit... docs say that mutexes are never used from IRQ context,
  //  however osal_queue_recieve may be. therefore my assumption is that
  //  the fifo mutex is not populated for queues used from an IRQ context
  //assert(!qhdl->ff.mutex);

  _osal_q_lock(qhdl);
  bool success = tu_fifo_read(&qhdl->ff, data);
  _osal_q_unlock(qhdl);

  return success;
}

TU_ATTR_ALWAYS_INLINE static inline bool osal_queue_send(osal_queue_t qhdl, void const * data, bool in_isr)
{
  // TODO: revisit... docs say that mutexes are never used from IRQ context,
  //  however osal_queue_recieve may be. therefore my assumption is that
  //  the fifo mutex is not populated for queues used from an IRQ context
  //assert(!qhdl->ff.mutex);
  (void) in_isr;

  _osal_q_lock(qhdl);
  bool success = tu_fifo_write(&qhdl->ff, data);
  _osal_q_unlock(qhdl);

  TU_ASSERT(success);

  return success;
}

TU_ATTR_ALWAYS_INLINE static inline bool osal_queue_empty(osal_queue_t qhdl)
{
  // TODO: revisit; whether this is true or not currently, tu_fifo_empty is a single
  //  volatile read.

  // Skip queue lock/unlock since this function is primarily called
  // with interrupt disabled before going into low power mode
  return tu_fifo_empty(&qhdl->ff);
}
#ifdef __cplusplus
 }
#endif