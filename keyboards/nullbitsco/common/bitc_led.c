/* Copyright 2021 Jay Greco
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
#include "bitc_led.h"

void set_bitc_LED(uint8_t mode) {
    switch(mode) {
        case LED_ON:
            gpio_set_pin_output(PIN_LED);
            gpio_write_pin(PIN_LED, GPIO_STATE_HIGH);
        break;

        case LED_DIM:
            gpio_set_pin_input(PIN_LED);
        break;

        case LED_OFF:
            gpio_set_pin_output(PIN_LED);
            gpio_write_pin(PIN_LED, GPIO_STATE_LOW);
        break;

        default:
        break;
    }
}