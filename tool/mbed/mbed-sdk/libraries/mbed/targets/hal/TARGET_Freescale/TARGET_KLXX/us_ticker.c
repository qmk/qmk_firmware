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
#include "clk_freqs.h"

static void pit_init(void);
static void lptmr_init(void);

static int us_ticker_inited = 0;

void us_ticker_init(void) {
    if (us_ticker_inited) return;
    us_ticker_inited = 1;
    
    pit_init();
    lptmr_init();
}

/******************************************************************************
 * Timer for us timing.
 ******************************************************************************/
static void pit_init(void) {
    SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;   // Clock PIT
    PIT->MCR = 0;                       // Enable PIT
    
    // Channel 1
    PIT->CHANNEL[1].LDVAL = 0xFFFFFFFF;
    PIT->CHANNEL[1].TCTRL = PIT_TCTRL_CHN_MASK;    // Chain to timer 0, disable Interrupts
    PIT->CHANNEL[1].TCTRL |= PIT_TCTRL_TEN_MASK;   // Start timer 1
    
    // Use channel 0 as a prescaler for channel 1
    PIT->CHANNEL[0].LDVAL = (bus_frequency() + 500000) / 1000000 - 1;
    PIT->CHANNEL[0].TCTRL = PIT_TCTRL_TEN_MASK;    // Start timer 0, disable interrupts
}

uint32_t us_ticker_read() {
    if (!us_ticker_inited)
        us_ticker_init();
    
    // The PIT is a countdown timer
    return ~(PIT->CHANNEL[1].CVAL);
}

/******************************************************************************
 * Timer Event
 * 
 * It schedules interrupts at given (32bit)us interval of time.
 * It is implemented used the 16bit Low Power Timer that remains powered in all
 * power modes.
 ******************************************************************************/
static void lptmr_isr(void);

static void lptmr_init(void) {
	uint32_t extosc;

    /* Clock the timer */
    SIM->SCGC5 |= SIM_SCGC5_LPTMR_MASK;
    
    /* Reset */
    LPTMR0->CSR = 0;

#if defined(TARGET_KL43Z)
    /* Set interrupt handler */
    NVIC_SetVector(LPTMR0_IRQn, (uint32_t)lptmr_isr);
    NVIC_EnableIRQ(LPTMR0_IRQn);


    MCG->C1 |= MCG_C1_IRCLKEN_MASK;
    extosc = mcgirc_frequency();
#else
    /* Set interrupt handler */
    NVIC_SetVector(LPTimer_IRQn, (uint32_t)lptmr_isr);
    NVIC_EnableIRQ(LPTimer_IRQn);

    /* Clock at (1)MHz -> (1)tick/us */
    /* Check if the external oscillator can be divided to 1MHz */
    extosc = extosc_frequency();
#endif
    if (extosc != 0) {                      //If external oscillator found
        if (extosc % 1000000u == 0) {       //If it is a multiple if 1MHz
            extosc /= 1000000;
            if (extosc == 1)    {           //1MHz, set timerprescaler in bypass mode
                LPTMR0->PSR = LPTMR_PSR_PCS(3) | LPTMR_PSR_PBYP_MASK;
                return;
            } else {                        //See if we can divide it to 1MHz
                uint32_t divider = 0;
                extosc >>= 1;
                while (1) {
                    if (extosc == 1) {
                        LPTMR0->PSR = LPTMR_PSR_PCS(3) | LPTMR_PSR_PRESCALE(divider);
                        return;
                    }
                    if (extosc % 2 != 0)    //If we can't divide by two anymore
                        break;
                    divider++;
                    extosc >>= 1;
                }
            }
        }
    }
#if defined(TARGET_KL43Z)
    //No suitable actual IRC oscillator clock -> Set it to (8MHz / divider) 
    MCG->SC &= ~MCG_SC_FCRDIV_MASK;
    MCG->MC &= ~MCG->MC & MCG_MC_LIRC_DIV2_MASK;
    LPTMR0->PSR = LPTMR_PSR_PCS(0) | LPTMR_PSR_PRESCALE(2);
#else
    //No suitable external oscillator clock -> Use fast internal oscillator (4MHz / divider)
    MCG->C1 |= MCG_C1_IRCLKEN_MASK;
    MCG->C2 |= MCG_C2_IRCS_MASK;
    LPTMR0->PSR =  LPTMR_PSR_PCS(0);
    switch (MCG->SC & MCG_SC_FCRDIV_MASK) {
        case MCG_SC_FCRDIV(0):                  //4MHz
            LPTMR0->PSR |= LPTMR_PSR_PRESCALE(1);
            break;
        case MCG_SC_FCRDIV(1):                  //2MHz
            LPTMR0->PSR |= LPTMR_PSR_PRESCALE(0);
            break;
        default:                                //1MHz or anything else, in which case we put it on 1MHz
            MCG->SC &= ~MCG_SC_FCRDIV_MASK;
            MCG->SC |= MCG_SC_FCRDIV(2);
            LPTMR0->PSR |= LPTMR_PSR_PBYP_MASK;
    }
#endif    
}

void us_ticker_disable_interrupt(void) {
    LPTMR0->CSR &= ~LPTMR_CSR_TIE_MASK;
}

void us_ticker_clear_interrupt(void) {
    // we already clear interrupt in lptmr_isr
}

static uint32_t us_ticker_int_counter = 0;
static uint16_t us_ticker_int_remainder = 0;

static void lptmr_set(unsigned short count) {
    /* Reset */
    LPTMR0->CSR = 0;
    
    /* Set the compare register */
    LPTMR0->CMR = count;
    
    /* Enable interrupt */
    LPTMR0->CSR |= LPTMR_CSR_TIE_MASK;
    
    /* Start the timer */
    LPTMR0->CSR |= LPTMR_CSR_TEN_MASK;
}

static void lptmr_isr(void) {
    // write 1 to TCF to clear the LPT timer compare flag
    LPTMR0->CSR |= LPTMR_CSR_TCF_MASK;
    
    if (us_ticker_int_counter > 0) {
        lptmr_set(0xFFFF);
        us_ticker_int_counter--;
    
    } else {
        if (us_ticker_int_remainder > 0) {
            lptmr_set(us_ticker_int_remainder);
            us_ticker_int_remainder = 0;
        
        } else {
            // This function is going to disable the interrupts if there are
            // no other events in the queue
            us_ticker_irq_handler();
        }
    }
}

void us_ticker_set_interrupt(timestamp_t timestamp) {
    int delta = (int)((uint32_t)timestamp - us_ticker_read());
    if (delta <= 0) {
        // This event was in the past:
        us_ticker_irq_handler();
        return;
    }
    
    us_ticker_int_counter   = (uint32_t)(delta >> 16);
    us_ticker_int_remainder = (uint16_t)(0xFFFF & delta);
    if (us_ticker_int_counter > 0) {
        lptmr_set(0xFFFF);
        us_ticker_int_counter--;
    } else {
        lptmr_set(us_ticker_int_remainder);
        us_ticker_int_remainder = 0;
    }
}
