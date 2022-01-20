/* Copyright 2017 Benjamin Kesselring
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

#include "xd75.h"

#define XD75_CAPSLOCK_LED B2
#define XD75_GP103_LED F4
#define XD75_GP100_LED F7

void matrix_init_kb(void) {
    capslock_led_init();
    gp100_led_init();
    gp103_led_init();

    matrix_init_user();
}

void capslock_led_init(void) {
    setPinOutput(XD75_CAPSLOCK_LED);
    capslock_led_off();
}

void capslock_led_off(void) {
    writePinHigh(XD75_CAPSLOCK_LED);
}

void capslock_led_on(void) {
    writePinLow(XD75_CAPSLOCK_LED);
}

void gp100_led_init(void) {
    setPinOutput(XD75_GP100_LED);
    gp100_led_off();
}

void gp100_led_off(void) {
    writePinHigh(XD75_GP100_LED);
}

void gp100_led_on(void) {
    writePinLow(XD75_GP100_LED);
}

void gp103_led_init(void) {
    setPinOutput(XD75_GP103_LED);
    gp103_led_off();
}

void gp103_led_off(void) {
    writePinLow(XD75_GP103_LED);
}

void gp103_led_on(void) {
    writePinHigh(XD75_GP103_LED);
}
