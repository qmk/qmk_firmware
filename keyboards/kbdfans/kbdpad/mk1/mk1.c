/* Copyright 2019 MechMerlin
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

#include "mk1.h"

#define NUMLOCK_PIN D0

void matrix_init_kb(void) {
    setPinOutput(NUMLOCK_PIN);
    matrix_init_user();
}

void led_set_kb(uint8_t usb_led) {
    writePin(NUMLOCK_PIN, IS_LED_ON(usb_led, USB_LED_NUM_LOCK));
    led_set_user(usb_led);
}
