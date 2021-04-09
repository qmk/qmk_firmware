/*
The MIT License (MIT)

Copyright (c) 2016 Fred Sundvik

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include "host_driver.h"
#include <stdbool.h>

void           init_serial_link(void);
void           init_serial_link_hal(void);
bool           is_serial_link_connected(void);
bool           is_serial_link_master(void);
host_driver_t* get_serial_link_driver(void);
void           serial_link_update(void);

#if defined(PROTOCOL_CHIBIOS)
#    include <ch.h>

static inline void serial_link_lock(void) { chSysLock(); }

static inline void serial_link_unlock(void) { chSysUnlock(); }

void signal_data_written(void);

#else

inline void serial_link_lock(void) {}

inline void serial_link_unlock(void) {}

void signal_data_written(void);

#endif
