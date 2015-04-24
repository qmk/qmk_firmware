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

#if DEVICE_RTC

#include "pinmap.h"
#include "fsl_rtc_hal.h"
#include "fsl_clock_manager.h"
#include "PeripheralPins.h"

void rtc_init(void) {
    SIM_HAL_EnableRtcClock(SIM_BASE, 0U);

    RTC_HAL_Init(RTC_BASE);
    RTC_HAL_Enable(RTC_BASE);

    RTC_HAL_EnableCounter(RTC_BASE, true);
}

void rtc_free(void) {
    // [TODO]
}

/*
 * Little check routine to see if the RTC has been enabled
 * 0 = Disabled, 1 = Enabled
 */
int rtc_isenabled(void) {
    SIM_HAL_EnableRtcClock(SIM_BASE, 0U);
    return (int)RTC_HAL_IsCounterEnabled(RTC_BASE);
}

time_t rtc_read(void) {
    return (time_t)RTC_HAL_GetSecsReg(RTC_BASE);
}

void rtc_write(time_t t) {
    if (t == 0) {
        t = 1;
    }
    RTC_HAL_EnableCounter(RTC_BASE, false);
    RTC_HAL_SetSecsReg(RTC_BASE, t);
    RTC_HAL_EnableCounter(RTC_BASE, true);
}

#endif
