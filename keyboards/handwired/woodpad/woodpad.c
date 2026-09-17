/* Copyright 2017 WoodKeys
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

#include "woodpad.h"

void keyboard_pre_init_kb(void) {
    gpio_set_pin_output(F7);
    keyboard_pre_init_user();
}

inline void numlock_led_on(void) {
    gpio_write_pin_high(F7);
}

inline void numlock_led_off(void) {
    gpio_write_pin_low(F7);
}
