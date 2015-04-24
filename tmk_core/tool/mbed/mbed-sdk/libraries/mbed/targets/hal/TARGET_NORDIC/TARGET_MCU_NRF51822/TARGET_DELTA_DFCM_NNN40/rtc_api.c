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

 
#define LFCLK_FREQUENCY         (32768UL)
#define RTC0_COUNTER_PRESCALER  ((LFCLK_FREQUENCY/8) - 1)
#define COMPARE_COUNTERTIME       (691200UL) //86400 x 8


time_t	initTime;

void rtc_init(void) {

    NVIC_EnableIRQ(RTC0_IRQn);                                      // Enable Interrupt for the RTC in the core.
    //NRF_RTC0->TASKS_STOP =1;
    NRF_RTC0->PRESCALER     = RTC0_COUNTER_PRESCALER;               // Set prescaler to a TICK of RTC_FREQUENCY.
    NRF_RTC0->CC[0]         = COMPARE_COUNTERTIME;                 // Compare0 after approx COMPARE_COUNTERTIME seconds.

    // Enable COMPARE0 event and COMPARE0 interrupt:
    NRF_RTC0->EVTENSET      = RTC_EVTENSET_COMPARE0_Msk;
    NRF_RTC0->INTENSET      = RTC_INTENSET_COMPARE0_Msk;
    NRF_RTC0->TASKS_START = 1;
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
    // [TODO] return(((NRF_RTC0->TASKS_START) & 0x01) != 0);
}

time_t rtc_read(void) {

    time_t t = initTime;
    t += (86400*NRF_RTC0->EVENTS_COMPARE[0]);
    t += (int)((NRF_RTC0->COUNTER)/8);
    return(t);
}

void rtc_write(time_t t) {
    // Convert the time in to a tm

    // Pause clock, and clear counter register (clears us count)
    NRF_RTC0->TASKS_STOP = 1;

    initTime = t;
    // Restart clock
    NRF_RTC0->TASKS_START = 1;
}
