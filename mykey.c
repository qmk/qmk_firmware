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
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "usb_device.h"
#include "print.h"
#include "matrix.h"
#include "keymap.h"
#include "jump_bootloader.h"

#define LED_CONFIG    (DDRD |= (1<<6))
#define LED_ON        (PORTD &= ~(1<<6))
#define LED_OFF        (PORTD |= (1<<6))
#define CPU_PRESCALE(n)    (CLKPR = 0x80, CLKPR = (n))

static void print_matrix(void);


uint16_t idle_count=0;



int main(void)
{
    bool modified = false;
    bool has_ghost = false;
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

    print("firmware 0.2 for t.m.k.\n");

    int loop_count = 0;
    while (1) {
        int layer = 0;

        matrix_scan();
        layer = get_layer();

        modified = matrix_is_modified();
        has_ghost = matrix_has_ghost();

        // doesnt send keys during ghost occurs
        if (modified && !has_ghost) {
            key_index = 0;
            keyboard_modifier_keys = 0;
            for (int i = 0; i < 6; i++) keyboard_keys[i] = KB_NO;

            for (int row = 0; row < MATRIX_ROWS; row++) {
                for (int col = 0; col < MATRIX_COLS; col++) {
                    if (matrix[row] & 1<<col) continue;

                    uint8_t code = get_keycode(layer, row, col);
                    if (code == KB_NO) {
                        continue;
                    } else if (KB_LCTRL <= code && code <= KB_RGUI) {
                        // modifier keycode: 0xE0-0xE7
                        keyboard_modifier_keys |= 1<<(code & 0x07);
                    } else {
                        if (key_index < 6)
                            keyboard_keys[key_index] = code;
                        key_index++;
                    }
                }
            }

            // run bootloader when 4 left modifier keys down
            if (keyboard_modifier_keys == (MOD_LCTRL | MOD_LSHIFT | MOD_LALT | MOD_LGUI)) {
                // cancel all keys
                keyboard_modifier_keys = 0;
                for (int i = 0; i < 6; i++) keyboard_keys[i] = KB_NO;
                usb_keyboard_send();

                print("jump to bootloader...\n");
                _delay_ms(1000);
                jump_bootloader();
            }

            if (key_index > 6) {
                //Rollover
            }

            usb_keyboard_send();


            // variables shared with interrupt routines must be
            // accessed carefully so the interrupt routine doesn't
            // try to use the variable in the middle of our access
            cli();
            //idle_count = 0;
            sei();
        }

        // print matrix state for debug
        if (modified) {
            print_matrix();

            // LED flush
            DDRD |= 1<<PD6;
            PORTD |= 1<<PD6;
        }

/*
        // print counts for debug
        if ((loop_count % 0x1000) == 0) {
            //print(".");
            print("idle_count: "); phex((idle_count & 0xFF00) >> 8); phex(idle_count & 0xFF); print("\n");
            print("loop_count: "); phex((loop_count & 0xFF00) >> 8); phex(loop_count & 0xFF); print("\n");
            print_matrix();
        }

        // teensy LED flush for debug
        if ((loop_count & 0x100) == 0) {
            DDRD |= 1<<PD6;
            PORTD |= 1<<PD6;
        }
*/

        // now the current pins will be the previous, and
        // wait a short delay so we're not highly sensitive
        // to mechanical "bounce".
        _delay_ms(2);
        loop_count++;
    }
}

static void print_matrix(void) {
            print("\nr/c 01234567\n");
            for (int row = 0; row < MATRIX_ROWS; row++) {
                phex(row); print(": ");
                pbin_reverse(matrix[row]);
                if (matrix_has_ghost_in_row(row)) {
                    print(" <ghost");
                }
                print("\n");
            }
            print("keys: ");
            for (int i = 0; i < 6; i++) { phex(keyboard_keys[i]); print(" "); }
            print("\n");
            print("mod: "); phex(keyboard_modifier_keys); print("\n");
}

// This interrupt routine is run approx 61 times per second.
// A very simple inactivity timeout is implemented, where we
// will send a space character and print a message to the
// hid_listen debug message window.
ISR(TIMER0_OVF_vect)
{
    idle_count++;
}
