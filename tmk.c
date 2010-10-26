/* 2010/08/23 noname
 * keyboard firmware based on PJRC USB keyboard example
 */
/* Keyboard example with debug channel, for Teensy USB Development Board
 * http://www.pjrc.com/teensy/usb_keyboard.html
 * Copyright (c) 2008 PJRC.COM, LLC
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
 */

#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "usb.h"
#include "matrix_skel.h"
#include "key_process.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "controller.h"


#define CPU_PRESCALE(n)    (CLKPR = 0x80, CLKPR = (n))

bool debug_enable = false;
bool debug_matrix = false;
bool debug_keyboard = false;
bool debug_mouse = false;

uint16_t idle_count=0;


int main(void)
{
    // set for 16 MHz clock
    CPU_PRESCALE(0);

    // Initialize the USB, and then wait for the host to set configuration.
    // If the Teensy is powered without a PC connected to the USB port,
    // this will wait forever.
    usb_init();
    while (!usb_configured()) /* wait */ ;

    // Configure timer 0 to generate a timer overflow interrupt every
    // 256*1024 clock cycles, or approx 61 Hz when using 16 MHz clock
    // This demonstrates how to use interrupts to implement a simple
    // inactivity timeout.
    TCCR0A = 0x00;
    TCCR0B = 0x05;
    TIMSK0 = (1<<TOIE0);


    matrix_init();
    matrix_scan();
    // debug on by pressing down any 4 keys during boot time.
    if (matrix_key_count() == 4) print_enable = true;

    /* wait for debug pipe ready */
    if (print_enable) {
#ifdef DEBUG_LED
        for (int i = 0; i < 6; i++) {
            DEBUG_LED_CONFIG;
            DEBUG_LED_ON;
            _delay_ms(500);
            DEBUG_LED_OFF;
            _delay_ms(500);
        }
#else
            _delay_ms(6000);
#endif
    }
    // print description
    print(XSTR(DESCRIPTION));

    while (1) {
       proc_matrix(); 
        _delay_ms(2);
    }
}


// This interrupt routine is run approx 61 times per second.
// A very simple inactivity timeout is implemented, where we
// will send a space character and print a message to the
// hid_listen debug message window.
ISR(TIMER0_OVF_vect)
{
    idle_count++;
}
