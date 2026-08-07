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
#include "big_led.h"

void set_big_LED_rgb(uint8_t r_mode, uint8_t g_mode, uint8_t b_mode) {
    set_big_LED_r(r_mode);
    set_big_LED_g(g_mode);
    set_big_LED_b(b_mode);
}

void set_big_LED_r(uint8_t mode) {
    switch(mode) {
        case LED_ON:
            gpio_set_pin_output(BIG_LED_R_PIN);
            gpio_write_pin(BIG_LED_R_PIN, GPIO_STATE_HIGH);
        break;

        case LED_OFF:
            gpio_set_pin_output(BIG_LED_R_PIN);
            gpio_write_pin(BIG_LED_R_PIN, GPIO_STATE_LOW);
        break;

        default:
        break;
    }
}

void set_big_LED_g(uint8_t mode) {
    switch(mode) {
        case LED_ON:
            gpio_set_pin_output(BIG_LED_G_PIN);
            gpio_write_pin(BIG_LED_G_PIN, GPIO_STATE_HIGH);
        break;

        case LED_OFF:
            gpio_set_pin_output(BIG_LED_G_PIN);
            gpio_write_pin(BIG_LED_G_PIN, GPIO_STATE_LOW);
        break;

        default:
        break;
    }
}

void set_big_LED_b(uint8_t mode) {
    switch(mode) {
        case LED_ON:
            gpio_set_pin_output(BIG_LED_B_PIN);
            gpio_write_pin(BIG_LED_B_PIN, GPIO_STATE_HIGH);
        break;

        case LED_OFF:
            gpio_set_pin_output(BIG_LED_B_PIN);
            gpio_write_pin(BIG_LED_B_PIN, GPIO_STATE_LOW);
        break;

        default:
        break;
    }
}
