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
#include "rtc_api.h"

#include <time.h>
#include "rtc_time.h"
#include "us_ticker_api.h"

#if DEVICE_RTC
static void (*_rtc_init)(void) = rtc_init;
static int (*_rtc_isenabled)(void) = rtc_isenabled;
static time_t (*_rtc_read)(void) = rtc_read;
static void (*_rtc_write)(time_t t) = rtc_write;
#else
static void (*_rtc_init)(void) = NULL;
static int (*_rtc_isenabled)(void) = NULL;
static time_t (*_rtc_read)(void) = NULL;
static void (*_rtc_write)(time_t t) = NULL;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#if defined (__ICCARM__)
time_t __time32(time_t *timer)
#else
time_t time(time_t *timer)
#endif

{
    if (_rtc_isenabled != NULL) {
        if (!(_rtc_isenabled())) {
            set_time(0);
        }
    }
    
    time_t t = 0;
    if (_rtc_read != NULL) {
        t = _rtc_read();
    }

    if (timer != NULL) {
        *timer = t;
    }
    return t;
}

void set_time(time_t t) {
    if (_rtc_init != NULL) {
        _rtc_init();
    }
    if (_rtc_write != NULL) {
        _rtc_write(t);
    }
}

clock_t clock() {
    clock_t t = us_ticker_read();
    t /= 1000000 / CLOCKS_PER_SEC; // convert to processor time
    return t;
}

void attach_rtc(time_t (*read_rtc)(void), void (*write_rtc)(time_t), void (*init_rtc)(void), int (*isenabled_rtc)(void)) {
    __disable_irq();
    _rtc_read = read_rtc;
    _rtc_write = write_rtc;
    _rtc_init = init_rtc;
    _rtc_isenabled = isenabled_rtc;
    __enable_irq();
}



#ifdef __cplusplus
}
#endif
