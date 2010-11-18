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
#include "timer.h"
#include "jump_bootloader.h"


#define CPU_PRESCALE(n)    (CLKPR = 0x80, CLKPR = (n))


bool debug_enable = false;
bool debug_matrix = false;
bool debug_keyboard = false;
bool debug_mouse = false;


int main(void)
{
    DEBUG_LED_CONFIG;
    DEBUG_LED_OFF;

    // set for 16 MHz clock
    CPU_PRESCALE(0);

    // Initialize the USB, and then wait for the host to set configuration.
    // If the Teensy is powered without a PC connected to the USB port,
    // this will wait forever.
    usb_init();
    while (!usb_configured()) /* wait */ ;

    timer_init();

    matrix_init();
    matrix_scan();
    // bootloader comes up when any 4 or more keys are pressed at startup
    if (matrix_key_count() >= 4) {
#ifdef DEBUG_LED
        for (int i = 0; i < 6; i++) {
            DEBUG_LED_CONFIG;
            DEBUG_LED_ON;
            _delay_ms(500);
            DEBUG_LED_OFF;
            _delay_ms(500);
        }
#else
        _delay_ms(5000);
#endif
        print_enable = true;
        print("jump to bootloader...\n");
        _delay_ms(1000);
        jump_bootloader(); // not return
    }

    while (1) {
       proc_matrix(); 
        _delay_ms(2);
    }
}
