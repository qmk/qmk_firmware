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
#include <stddef.h>
#include "us_ticker_api.h"
#include "PeripheralNames.h"

//New, using MRT instead of SCT, needed to free up SCT for PWM
//Ported from LPC824 libs
static int us_ticker_inited = 0;
unsigned int ticker_fullcount_us;
unsigned long int ticker_expired_count_us = 0;
int MRT_Clock_MHz;

#define US_TICKER_TIMER_IRQn     MRT_IRQn

void us_ticker_init(void) {
    
    if (us_ticker_inited)
        return;

    us_ticker_inited = 1;
    
    // Calculate MRT clock value (MRT has no prescaler)
    MRT_Clock_MHz = (SystemCoreClock / 1000000);
    // Calculate fullcounter value in us (MRT has 31 bits and clock is 30 MHz) 
    ticker_fullcount_us = 0x80000000UL/MRT_Clock_MHz;

    // Enable the MRT clock
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 10);

    // Clear peripheral reset the MRT
    LPC_SYSCON->PRESETCTRL |= (1 << 7);

    // Force load interval value (Bit 0-30 is interval value, Bit 31 is Force Load bit)     
    LPC_MRT->INTVAL0 = 0xFFFFFFFFUL;
    // Enable Ch0 interrupt, Mode 0 is Repeat Interrupt
    LPC_MRT->CTRL0 = (0x0 << 1) | (0x1 << 0);

    // Force load interval value (Bit 0-30 is interval value, Bit 31 is Force Load bit)     
    LPC_MRT->INTVAL1 = 0x80000000UL;
    // Disable ch1 interrupt, Mode 0 is Repeat Interrupt
    LPC_MRT->CTRL1 = (0x0 << 1) | (0x0 << 0);
    
    // Set MRT interrupt vector
    NVIC_SetVector(US_TICKER_TIMER_IRQn, (uint32_t)us_ticker_irq_handler);
    NVIC_EnableIRQ(US_TICKER_TIMER_IRQn);
}

//TIMER0 is used for us ticker and timers (Timer, wait(), wait_us() etc)
uint32_t us_ticker_read() {
    
    if (!us_ticker_inited)
        us_ticker_init();

    // Generate ticker value
    // MRT source clock is SystemCoreClock (30MHz) and MRT is a 31-bit countdown timer
    // Calculate expected value using current count and number of expired times to mimic a 32bit timer @ 1 MHz 
    //
    // ticker_expired_count_us
    // The variable ticker_expired_count_us keeps track of the number of 31bits overflows (counted by TIMER0) and
    // corrects that back to us counts.
    //
    // (0x7FFFFFFFUL - LPC_MRT->TIMER0)/MRT_Clock_MHz
    // The counter is a 31bit downcounter from 7FFFFFFF so correct to actual count-up value and correct
    // for 30 counts per us.
    //
    // Added up these 2 parts result in current us time returned as 32 bits.
    return (0x7FFFFFFFUL - LPC_MRT->TIMER0)/MRT_Clock_MHz + ticker_expired_count_us;            
}

//TIMER1 is used for Timestamped interrupts (Ticker(), Timeout())
void us_ticker_set_interrupt(timestamp_t timestamp) {
    
    // MRT source clock is SystemCoreClock (30MHz) and MRT is a 31-bit countdown timer    
    // Force load interval value (Bit 0-30 is interval value, Bit 31 is Force Load bit)
    // Note: The MRT has less counter headroom available than the typical mbed 32bit timer @ 1 MHz.
    //       The calculated counter interval until the next timestamp will be truncated and an
    //       'early' interrupt will be generated in case the max required count interval exceeds
    //       the available 31 bits space. However, the mbed us_ticker interrupt handler will 
    //       check current time against the next scheduled timestamp and simply re-issue the
    //       same interrupt again when needed. The calculated counter interval will now be smaller.
    LPC_MRT->INTVAL1 = (((timestamp - us_ticker_read()) * MRT_Clock_MHz) | 0x80000000UL);
    
    // Enable interrupt 
    LPC_MRT->CTRL1 |= 1;
}

//Disable Timestamped interrupts triggered by TIMER1
void us_ticker_disable_interrupt() {
    //Timer1 for Timestamped interrupts (31 bits downcounter @ SystemCoreClock)    
    LPC_MRT->CTRL1 &= ~1;
}

void us_ticker_clear_interrupt() {
    
    //Timer1 for Timestamped interrupts (31 bits downcounter @ SystemCoreClock)
    if (LPC_MRT->STAT1 & 1)
        LPC_MRT->STAT1 = 1;
    
    //Timer0 for us counter (31 bits downcounter @ SystemCoreClock)
    if (LPC_MRT->STAT0 & 1) {
        LPC_MRT->STAT0 = 1;
        // ticker_expired_count_us = (ticker_expired * 0x80000000UL) / MRT_Clock_MHz
        // The variable ticker_expired_count_us keeps track of the number of 31bits overflows (counted by TIMER0) and
        // the multiplication/division corrects that back to us counts.
        ticker_expired_count_us += ticker_fullcount_us;
    }
}
