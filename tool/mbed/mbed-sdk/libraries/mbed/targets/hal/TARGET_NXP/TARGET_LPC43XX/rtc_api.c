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
 *
 * Ported to NXP LPC43XX by Micromint USA <support@micromint.com>
 */
#include "rtc_api.h"

// ensure rtc is running (unchanged if already running)

/* Setup the RTC based on a time structure, ensuring RTC is enabled
 *
 * Can be clocked by a 32.768KHz oscillator or prescale divider based on the APB clock
 * - We want to use the 32khz clock, allowing for sleep mode
 *
 * Most registers are not changed by a Reset
 * - We must initialize these registers between power-on and setting the RTC into operation

 * Clock Control Register
 *  RTC_CCR[0] : Enable - 0 = Disabled, 1 = Enabled
 *  RTC_CCR[1] : Reset - 0 = Normal, 1 = Reset
 *  RTC_CCR[4] : Clock Source - 0 = Prescaler, 1 = 32k Xtal
 *
 * The RTC may already be running, so we should set it up
 * without impacting if it is the case
 */

void rtc_init(void) {
    // Return, if already enabled
    if (LPC_RTC->CCR & 1)
        return;

    // Enable 1kHz output of 32kHz oscillator
    LPC_CREG->CREG0 &= ~((1 << 3) | (1 << 2));
    LPC_CREG->CREG0 |= (0x03 << 6) | (1 << 1) | (1 << 0);

    // Enable RTC
    do {
        LPC_RTC->CCR |= 1 << 0;
    } while ((LPC_RTC->CCR & 1) == 0);
}

void rtc_free(void) {
    // [TODO]
}

/*
 * Little check routine to see if the RTC has been enabled
 *
 * Clock Control Register
 *  RTC_CCR[0] : 0 = Disabled, 1 = Enabled
 *
 */
int rtc_isenabled(void) {
    return(((LPC_RTC->CCR) & 0x01) != 0);
}

/*
 * RTC Registers
 *  RTC_SEC        Seconds 0-59
 *  RTC_MIN        Minutes 0-59
 *  RTC_HOUR    Hour 0-23
 *  RTC_DOM        Day of Month 1-28..31
 *  RTC_DOW        Day of Week 0-6
 *  RTC_DOY        Day of Year 1-365
 *  RTC_MONTH    Month 1-12
 *  RTC_YEAR    Year 0-4095
 *
 * struct tm
 *  tm_sec        seconds after the minute 0-61
 *  tm_min        minutes after the hour 0-59
 *  tm_hour        hours since midnight 0-23
 *  tm_mday        day of the month 1-31
 *  tm_mon        months since January 0-11
 *  tm_year        years since 1900
 *  tm_wday        days since Sunday 0-6
 *  tm_yday        days since January 1 0-365
 *  tm_isdst    Daylight Saving Time flag
 */
time_t rtc_read(void) {
    // Setup a tm structure based on the RTC
    struct tm timeinfo;
    timeinfo.tm_sec = LPC_RTC->TIME[RTC_TIMETYPE_SECOND];
    timeinfo.tm_min = LPC_RTC->TIME[RTC_TIMETYPE_MINUTE];
    timeinfo.tm_hour = LPC_RTC->TIME[RTC_TIMETYPE_HOUR];
    timeinfo.tm_mday = LPC_RTC->TIME[RTC_TIMETYPE_DAYOFMONTH];
    timeinfo.tm_wday = LPC_RTC->TIME[RTC_TIMETYPE_DAYOFWEEK];
    timeinfo.tm_yday = LPC_RTC->TIME[RTC_TIMETYPE_DAYOFYEAR];
    timeinfo.tm_mon = LPC_RTC->TIME[RTC_TIMETYPE_MONTH] - 1;
    timeinfo.tm_year = LPC_RTC->TIME[RTC_TIMETYPE_YEAR] - 1900;
    
    // Convert to timestamp
    time_t t = mktime(&timeinfo);
    
    return t;
}

void rtc_write(time_t t) {
    // Convert the time in to a tm
    struct tm *timeinfo = localtime(&t);
    
    // Pause clock, and clear counter register (clears us count)
    LPC_RTC->CCR |= 2;
    
    // Set the RTC
    LPC_RTC->TIME[RTC_TIMETYPE_SECOND] = timeinfo->tm_sec;
    LPC_RTC->TIME[RTC_TIMETYPE_MINUTE] = timeinfo->tm_min;
    LPC_RTC->TIME[RTC_TIMETYPE_HOUR] = timeinfo->tm_hour;
    LPC_RTC->TIME[RTC_TIMETYPE_DAYOFMONTH] = timeinfo->tm_mday;
    LPC_RTC->TIME[RTC_TIMETYPE_DAYOFWEEK] = timeinfo->tm_wday;
    LPC_RTC->TIME[RTC_TIMETYPE_DAYOFYEAR] = timeinfo->tm_yday;
    LPC_RTC->TIME[RTC_TIMETYPE_MONTH] = timeinfo->tm_mon + 1;
    LPC_RTC->TIME[RTC_TIMETYPE_YEAR] = timeinfo->tm_year + 1900;
    
    // Restart clock
    LPC_RTC->CCR &= ~((uint32_t)2);
}
