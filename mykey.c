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
#include "keymap.h"

#define LED_CONFIG	(DDRD |= (1<<6))
#define LED_ON		(PORTD &= ~(1<<6))
#define LED_OFF		(PORTD |= (1<<6))
#define CPU_PRESCALE(n)	(CLKPR = 0x80, CLKPR = (n))

uint8_t number_keys[10]=
	{KEY_0,KEY_1,KEY_2,KEY_3,KEY_4,KEY_5,KEY_6,KEY_7,KEY_8,KEY_9};

uint16_t idle_count=0;



//
// scan matrix
//
uint8_t MAX_ROW = 9;

// initialize ports for matrix
void port_setup(void)
{
        // Column: input w/pullup
	DDRB = 0x00;
	PORTB = 0xFF;

        // Row: Hi-Z(unselected)
        // PD:0,1,2,3,6,7
        // PC:6,7
        // PF:7
	DDRD = 0x00;
	PORTD = 0x00;
	DDRC = 0x00;
	PORTC = 0x00;
	DDRF = 0x00;
	PORTF = 0x00;
}

// select a row of matrix for read
void select_row(uint8_t row)
{
    switch (row) {
        case 0:
            DDRD  = (1<<0);
            PORTD = 0x00;
            DDRC  = 0x00;
            PORTC = 0x00;
            DDRF  = 0x00;
            PORTF = 0x00;
            break;
        case 1:
            DDRD  = (1<<1);
            PORTD = 0x00;
            DDRC  = 0x00;
            PORTC = 0x00;
            DDRF  = 0x00;
            PORTF = 0x00;
            break;
        case 2:
            DDRD  = (1<<2);
            PORTD = 0x00;
            DDRC  = 0x00;
            PORTC = 0x00;
            DDRF  = 0x00;
            PORTF = 0x00;
            break;
        case 3:
            DDRD  = (1<<3);
            PORTD = 0x00;
            DDRC  = 0x00;
            PORTC = 0x00;
            DDRF  = 0x00;
            PORTF = 0x00;
            break;
        case 4:
            DDRD  = (1<<6);
            PORTD = 0x00;
            DDRC  = 0x00;
            PORTC = 0x00;
            DDRF  = 0x00;
            PORTF = 0x00;
            break;
        case 5:
            DDRD  = (1<<7);
            PORTD = 0x00;
            DDRC  = 0x00;
            PORTC = 0x00;
            DDRF  = 0x00;
            PORTF = 0x00;
            break;
        case 6:
            DDRD  = 0x00;
            PORTD = 0x00;
            DDRC  = (1<<6);
            PORTC = 0x00;
            DDRF  = 0x00;
            PORTF = 0x00;
            break;
        case 7:
            DDRD  = 0x00;
            PORTD = 0x00;
            DDRC  = (1<<7);
            PORTC = 0x00;
            DDRF  = 0x00;
            PORTF = 0x00;
            break;
        case 8:
            DDRD  = 0x00;
            PORTD = 0x00;
            DDRC  = 0x00;
            PORTC = 0x00;
            DDRF  = (1<<7);
            PORTF = 0x00;
            break;
    }
}

uint8_t read_col(void)
{
    return PINB;
}

int main(void)
{
	uint8_t i, reset_idle;
	uint8_t prev_state[MAX_ROW];
        for (int i=0; i < MAX_ROW; i++) prev_state[i] = 0xFF;

	// set for 16 MHz clock
	CPU_PRESCALE(0);

        port_setup();


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

	print("Begin keyboard example program\n");
	print("All Port B or Port D pins are inputs with pullup resistors.\n");
	print("Any connection to ground on Port B or D pins will result in\n");
	print("keystrokes sent to the PC (and debug messages here).\n");

        uint8_t col;
        uint8_t code;
	while (1) {
            reset_idle = 0;

            for (uint8_t r=0; r < MAX_ROW; r++) {
                select_row(r);

                // without this read unstable value.
                _delay_us(30);

                col = read_col();
                if (col != prev_state[r]) {
                    prev_state[r] = col;
                    phex(r);
                    print(": ");
                    pbin(col);
                    print("\n");

                    for (int c = 0; c < 8; c++) {
                        if (col & 1<<c) continue;
                        code = get_keycode(r, c);
                        phex(code);
                        print("\n");
                        usb_keyboard_press(code, 0);
                    }

                    reset_idle = 1;
                }
            }
                


		// if any keypresses were detected, reset the idle counter
		if (reset_idle) {
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
		print("Timer Event :)\n");
		//usb_keyboard_press(KEY_SPACE, 0);
	}
}


