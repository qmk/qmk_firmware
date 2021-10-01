/* Copyright 2021 datafx
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "solderable.h"
#include "quantum.h"

#define noLed {255,255}

#define ledSollSP (80+3)
#define ledNumSP (80+7)
#define ledCapSP (80+8)

void backlight_init_ports(void) {
    setPinOutput(Lseg0);
    setPinOutput(Lseg1);
    setPinOutput(Lseg2);
    setPinOutput(Lseg3);
    setPinOutput(Lseg4);
    setPinOutput(Lseg5);
    setPinOutput(Lcom0);
    setPinOutput(Lcom1);
    setPinOutput(Lcom2);
    setPinOutput(Lcom3);
    setPinOutput(Lcom4);
    setPinOutput(Lcom5);
    setPinOutput(Lcom6);
    setPinOutput(Lcom7);
    setPinOutput(Lcom8);
    setPinOutput(Lcom9);
    setPinOutput(Lcom10);
    setPinOutput(Lcom11);
    setPinOutput(Lcom12);
    setPinOutput(Lcom13);
    setPinOutput(Lcom14);
    setPinOutput(Lcom15);
}

void backlight_set(uint8_t level) {
}

void backlight_task(void) {
    // This is a temporary workaround to get the status LEDs working until we can figure out the LED matrix
    led_t host_leds = host_keyboard_led_state();
    if (host_leds.scroll_lock) {
    writePinHigh(Lcom3);
    writePinHigh(Lseg5);
    } else {
    writePinLow(Lcom3);
    }
    if (host_leds.num_lock) {
    writePinHigh(Lcom7);
    writePinHigh(Lseg5);
    } else {
    writePinLow(Lcom7);
    }
    if (host_leds.caps_lock) {
    writePinHigh(Lcom8);
    writePinHigh(Lseg5);
    } else {
    writePinLow(Lcom8);
    }
}

