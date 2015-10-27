/* mbed Microcontroller Library
 * Copyright (c) 2006-2015 ARM Limited
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

static void init(void) {
    // enable PORTC clock
    SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;

    // enable RTC clock
    SIM->SCGC6 |= SIM_SCGC6_RTC_MASK;

    // OSC32 as source
    SIM->SOPT1 &= ~SIM_SOPT1_OSC32KSEL_MASK;
    SIM->SOPT1 |= SIM_SOPT1_OSC32KSEL(0);
}

void rtc_init(void) {
    init();
    
    // Enable the oscillator
#if defined (TARGET_K20D50M)
    RTC->CR |= RTC_CR_OSCE_MASK;
#else
    // Teensy3.1 requires 20pF MCU loading capacitors for 32KHz RTC oscillator
    /* RTC->CR: SC2P=0,SC4P=1,SC8P=0,SC16P=1,CLKO=0,OSCE=1,UM=0,SUP=0,SPE=0,SWR=0 */
    RTC->CR |= RTC_CR_OSCE_MASK |RTC_CR_SC16P_MASK | RTC_CR_SC4P_MASK; 
#endif

    //Configure the TSR. default value: 1
    RTC->TSR = 1;

    // enable counter
    RTC->SR |= RTC_SR_TCE_MASK;
}

void rtc_free(void) {
    // [TODO]
}

/*
 * Little check routine to see if the RTC has been enabled
 * 0 = Disabled, 1 = Enabled
 */
int rtc_isenabled(void) {
    // even if the RTC module is enabled,
    // as we use RTC_CLKIN and an external clock,
    // we need to reconfigure the pins. That is why we
    // call init() if the rtc is enabled

    // if RTC not enabled return 0
    SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
    SIM->SCGC6 |= SIM_SCGC6_RTC_MASK;
    if ((RTC->SR & RTC_SR_TCE_MASK) == 0)
        return 0;

    init();
    return 1;
}

time_t rtc_read(void) {
    return RTC->TSR;
}

void rtc_write(time_t t) {
    // disable counter
    RTC->SR &= ~RTC_SR_TCE_MASK;

    // we do not write 0 into TSR
    // to avoid invalid time
    if (t == 0)
        t = 1;

    // write seconds
    RTC->TSR = t;

    // re-enable counter
    RTC->SR |= RTC_SR_TCE_MASK;
}
