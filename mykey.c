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

#include "usb.h"
#include "usb_keyboard.h"
#include "usb_mouse.h"
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
    // set for 16 MHz clock
    CPU_PRESCALE(0);

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


    matrix_init();
    print("firmware 0.3 for t.m.k.\n");

    bool modified = false;
    bool has_ghost = false;
    int layer = 0;
    int key_index = 0;
    uint8_t mouse_x = 0;
    uint8_t mouse_y = 0;
    uint8_t mouse_btn = 0;
    int8_t mouse_wheel = 0;
    int8_t mouse_hwheel = 0;
    while (1) {
        matrix_scan();
        modified = matrix_is_modified();
        has_ghost = matrix_has_ghost();
        layer = get_layer();

        // print matrix state for debug
        if (modified) {
            print_matrix();

            // LED flush
            DDRD |= 1<<PD6;
            PORTD |= 1<<PD6;
        }

        keyboard_modifier_keys = 0;
        for (int i = 0; i < 6; i++) keyboard_keys[i] = KB_NO;
        key_index = 0;
        mouse_x = 0;
        mouse_y = 0;
        mouse_btn = 0;
        mouse_wheel = 0;
        mouse_hwheel = 0;

        // convert matrix state to HID report
        for (int row = 0; row < MATRIX_ROWS; row++) {
            for (int col = 0; col < MATRIX_COLS; col++) {
                if (matrix[row] & 1<<col) continue;

                uint8_t code = get_keycode(layer, row, col);
                if (code == KB_NO) {
                    continue;
                } else if (KB_LCTRL <= code && code <= KB_RGUI) {
                    // modifier keycode: 0xE0-0xE7
                    keyboard_modifier_keys |= 1<<(code & 0x07);
                } else if (code >= MS_UP) {
                    // mouse
                    if (code == MS_UP)    mouse_y -= 15;
                    if (code == MS_DOWN)  mouse_y += 15;
                    if (code == MS_LEFT)  mouse_x -= 15;
                    if (code == MS_RIGHT) mouse_x += 15;
                    if (code == MS_BTN1)  mouse_btn |= 1<<0;
                    if (code == MS_BTN2)  mouse_btn |= 1<<1;
                    if (code == MS_BTN3)  mouse_btn |= 1<<2;
                    if (code == MS_BTN4)  mouse_btn |= 1<<3;
                    if (code == MS_BTN5)  mouse_btn |= 1<<4;
                    if (code == MS_WH_UP)  mouse_wheel -= 1;
                    if (code == MS_WH_DOWN)  mouse_wheel += 1;
                    if (code == MS_WH_LEFT)  mouse_hwheel -= 1;
                    if (code == MS_WH_RIGHT) mouse_hwheel += 1;
                } else {
                    if (key_index < 6)
                        keyboard_keys[key_index] = code;
                    key_index++;
                }
            }
        }

        if (!has_ghost)  {
            // when 4 left modifier keys down
            if (keyboard_modifier_keys == (MOD_LCTRL | MOD_LSHIFT | MOD_LALT | MOD_LGUI)) {
                // cancel all keys
                keyboard_modifier_keys = 0;
                for (int i = 0; i < 6; i++) keyboard_keys[i] = KB_NO;
                usb_keyboard_send();

                print("jump to bootloader...\n");
                _delay_ms(1000);
                jump_bootloader(); // not return
            }

            if (mouse_x || mouse_y || mouse_wheel || mouse_hwheel || mouse_btn != mouse_buttons) {
                mouse_buttons = mouse_btn;
                print("mouse_buttons: 0b"); pbin(mouse_buttons); print("\n");
                print("mouse_wheel: 0x"); phex(mouse_wheel); print("\n");
                usb_mouse_move(mouse_x, mouse_y, mouse_wheel, mouse_hwheel);
                _delay_ms(100);
            }


            // send keys to host
            if (modified) {
                if (key_index > 6) {
                    //Rollover
                }
                usb_keyboard_send();
            }
        }
        _delay_ms(2);
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
