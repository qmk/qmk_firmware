/*
Bluefruit Protocol for TMK firmware
Author: Benjamin Gould, 2013
Based on code Copyright 2011 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include "../serial.h"
#include "keyboard.h"
#include "host.h"
#include "timer.h"
#include "print.h"
#include "debug.h"
#include "sendchar.h"
#include "suspend.h"
#include "bluefruit.h"

#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))

int main(void) {
    CPU_PRESCALE(0);

    // DDRD  = _BV(PD5);
    // DDRB  = _BV(PB0);

    // PORTD = _BV(PD5);
    // PORTB = _BV(PB0);

    print_set_sendchar(sendchar);

    keyboard_setup();

    dprintf("Initializing keyboard...\n");
    keyboard_init();

    dprintf("Setting host driver to bluefruit...\n");
    host_set_driver(bluefruit_driver());

    dprintf("Initializing serial...\n");
    serial_init();

    // char swpa[] = "+++\r\n";
    // for (int i = 0; i < 5; i++) {
    //     serial_send(swpa[i]);
    // }

    // char ble_enable[] = "AT+BLEKEYBOARDEN=1\r\n";
    // for (int i = 0; i < 20; i++) {
    //     serial_send(ble_enable[i]);
    // }

    // char reset[] = "ATZ\r\n";
    // for (int i = 0; i < 5; i++) {
    //     serial_send(reset[i]);
    // }

    // for (int i = 0; i < 5; i++) {
    //     serial_send(swpa[i]);
    // }

    // wait an extra second for the PC's operating system
    // to load drivers and do whatever it does to actually
    // be ready for input
    _delay_ms(1000);
    // PORTD = ~_BV(PD5);
    dprintf("Starting main loop");
    while (1) {
        keyboard_task();
    }
}
