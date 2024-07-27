/* Copyright 2023 9R
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

#include "leds.h"
#include <stdbool.h>
#include "gpio.h"

//////////// Status LEDs //////////////
void init_leds(void) {
    // Both LEDs off, they have inverted logic
    gpio_set_pin_output(STATUS_LED_A_PIN);
    gpio_set_pin_output(STATUS_LED_B_PIN);
    gpio_write_pin_high(STATUS_LED_A_PIN);
    gpio_write_pin_high(STATUS_LED_B_PIN);
}

void set_leds(uint8_t highest_active_layer) {
    // any layer other than 0-3, quit and LEDs off
    if (highest_active_layer > 3) {
        gpio_write_pin_high(STATUS_LED_A_PIN);
        gpio_write_pin_high(STATUS_LED_B_PIN);
        return;
    }

    // use bitwise operations to display active layer in binary
    bool bit1 = !(highest_active_layer & 1);
    bool bit2 = !(highest_active_layer & 2);
    gpio_write_pin(STATUS_LED_A_PIN, bit1);
    gpio_write_pin(STATUS_LED_B_PIN, bit2);
}
