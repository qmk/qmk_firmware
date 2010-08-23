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

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "usb_keyboard_debug.h"
#include "print.h"
#include "matrix.h"
#include "keymap.h"

#define LED_CONFIG    (DDRD |= (1<<6))
#define LED_ON        (PORTD &= ~(1<<6))
#define LED_OFF        (PORTD |= (1<<6))
#define CPU_PRESCALE(n)    (CLKPR = 0x80, CLKPR = (n))


uint16_t idle_count=0;



int main(void)
{
    uint8_t modified = 0;
    uint8_t key_index = 0;

    // set for 16 MHz clock
    CPU_PRESCALE(0);

    matrix_init();


    // Initialize the USB, and then wait for the host to set configuration.
    // If the Teensy is powered without a PC connected to the USB port,
    // this will wait forever.
    usb_init();
    while (!usb_configured()) /* wait */ ;

    // Wait an extra second for the PC's operating system to load drivers
    // and do whatever it does to actually be ready for input
    _delay_ms(1000);

    // Configure timer 0 to generate a timer overflow interrupt every
    // 256*1024 clock cycles, or approx 61 Hz when using 16 MHz clock
    // This demonstrates how to use interrupts to implement a simple
    // inactivity timeout.
    TCCR0A = 0x00;
    TCCR0B = 0x05;
    TIMSK0 = (1<<TOIE0);

    print("keyboard firmware 0.1 for t.m.k.\n");

    while (1) {
        uint8_t row, col, code;

        modified = 0;

        matrix_scan();

        keyboard_modifier_keys = 0;
        for (int i = 0; i < 6; i++)
            keyboard_keys[i] = KB_NO;
        key_index = 0;

        for (row = 0; row < MATRIX_ROWS; row++) {
            if (matrix[row] != prev_matrix[row]) {
                modified = 1;
            }

            for (col = 0; col < MATRIX_COLS; col++) {
                if (matrix[row] & 1<<col) continue;
                code = get_keycode(row, col);
                
                // Modifier keycode: 0xE0-0xE7
                if (KB_LCTRL <= code && code <= KB_RGUI) {
                    keyboard_modifier_keys |= 1<<(code&0x07);
                } else {
                    if (key_index < 6) {
                        keyboard_keys[key_index] = code;
                    }
                    key_index++;
                }

            }
        }

        if (key_index > 6) {
            //Rollover
        }
                


        // if any keypresses were detected, reset the idle counter
        if (modified) {
            print("    01234567\n");
            for (row = 0; row < MATRIX_ROWS; row++) {
                phex(row); print(": "); pbin_reverse(matrix[row]); print("\n");
            }
            print("keys: ");
            for (int i = 0; i < 6; i++) { phex(keyboard_keys[i]); print(" "); }
            print("\n");
            print("mod: "); phex(keyboard_modifier_keys); print("\n");
            usb_keyboard_send();

            // variables shared with interrupt routines must be
            // accessed carefully so the interrupt routine doesn't
            // try to use the variable in the middle of our access
            cli();
            idle_count = 0;
            sei();
        }

        // now the current pins will be the previous, and
        // wait a short delay so we're not highly sensitive
        // to mechanical "bounce".
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
    if (idle_count > 61 * 8) {
        idle_count = 0;
        //print("Timer Event :)\n");
        //usb_keyboard_press(KEY_SPACE, 0);
    }
}
