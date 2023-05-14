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

/** \ingroup Group_Common Common Files
 *  \defgroup Group_TimeoutTimer timeout timer
 *  @{ */

#ifndef _TUSB_TIMEOUT_H_
#define _TUSB_TIMEOUT_H_

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  uint32_t start;
  uint32_t interval;
}tu_timeout_t;

#if 0

extern uint32_t tusb_hal_millis(void);

static inline void tu_timeout_set(tu_timeout_t* tt, uint32_t msec)
{
  tt->interval = msec;
  tt->start    = tusb_hal_millis();
}

static inline bool tu_timeout_expired(tu_timeout_t* tt)
{
  return ( tusb_hal_millis() - tt->start ) >= tt->interval;
}

// For used with periodic event to prevent drift
static inline void tu_timeout_reset(tu_timeout_t* tt)
{
  tt->start += tt->interval;
}

static inline void tu_timeout_restart(tu_timeout_t* tt)
{
  tt->start = tusb_hal_millis();
}

#endif

#ifdef __cplusplus
 }
#endif

#endif /* _TUSB_TIMEOUT_H_ */

/** @} */
