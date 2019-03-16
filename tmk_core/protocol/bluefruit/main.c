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
#include "usb.h"
#include "host.h"
#include "timer.h"
#include "print.h"
#include "debug.h"
#include "sendchar.h"
#include "suspend.h"
#include "bluefruit.h"
#include "pjrc.h"

#define CPU_PRESCALE(n)    (CLKPR = 0x80, CLKPR = (n))

#define HOST_DRIVER_NOT_SET     0
#define BLUEFRUIT_HOST_DRIVER   1
#define PJRC_HOST_DRIVER        2


int main(void)
{

    CPU_PRESCALE(0);

    // DDRD  = _BV(PD5);
    // DDRB  = _BV(PB0);

    // PORTD = _BV(PD5);
    // PORTB = _BV(PB0);

    print_set_sendchar(sendchar);

    // usb_init();
    // _delay_ms(2000);
    // while (!usb_configured()) /* wait */


    keyboard_setup();

    dprintf("Initializing keyboard...\n");
    keyboard_init();

    // This implementation is pretty simplistic... if the USB connection
    // is not configured, choose the Bluefruit, otherwise use USB
    // Definitely would prefer to have this driven by an input pin and make
    // it switch dynamically - BCG
    // if (!usb_configured()) {

    //     // Send power to Bluefruit... Adafruit says it takes 27 mA, I think
    //     // the pins should provide 40 mA, but just in case I switch the
    //     // Bluefruit using a transistor - BCG
    //     DDRB   = _BV(PB6);
    //     PORTB |= _BV(PB6);

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

//     } else {

//         // I'm not smart enough to get this done with LUFA - BCG
//         dprintf("Setting host driver to PJRC...\n");
//         host_set_driver(pjrc_driver());
// #ifdef SLEEP_LED_ENABLE
//     sleep_led_init();
// #endif
//         // wait an extra second for the PC's operating system
//         // to load drivers and do whatever it does to actually
//         // be ready for input
//         _delay_ms(1000);
//         PORTB = ~_BV(PB0);
//         dprintf("Starting main loop");
//         while (1) {
//             while (suspend) {
//                 suspend_power_down();
//                 if (remote_wakeup && suspend_wakeup_condition()) {
//                     usb_remote_wakeup();
//                 }
//             }
//             keyboard_task();
//         }
//     }

}
