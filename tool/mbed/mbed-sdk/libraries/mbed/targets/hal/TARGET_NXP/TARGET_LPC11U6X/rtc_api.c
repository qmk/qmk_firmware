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

void rtc_init(void)
{
    // Enables clock for RTC
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 30);

    // Software reset
    LPC_RTC->CTRL |= 1;

    LPC_RTC->COUNT = 0;

    // Enabled RTC
    LPC_RTC->CTRL |= (1 << 7);
    // clear reset
    LPC_RTC->CTRL &= ~1;
}

void rtc_free(void)
{
    LPC_SYSCON->SYSAHBCLKCTRL &= ~(1 << 30);
    LPC_RTC->CTRL &= ~(1 << 7);
}

int rtc_isenabled(void)
{
    return (((LPC_RTC->CTRL) & 0x80) != 0);
}

time_t rtc_read(void)
{
    return (time_t)LPC_RTC->COUNT;
}

void rtc_write(time_t t)
{
    // Disabled RTC
    LPC_RTC->CTRL &= ~(1 << 7);

    // Set count
    LPC_RTC->COUNT = t;

    //Enabled RTC
    LPC_RTC->CTRL |= (1 << 7);
}

#endif
