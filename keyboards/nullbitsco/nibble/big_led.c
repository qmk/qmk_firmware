/* Copyright 2020 Jay Greco
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

void set_big_LED_r(uint8_t mode) {
    switch(mode) {
        case LED_ON:
            setPinOutput(BIG_LED_R_PIN);
            writePin(BIG_LED_R_PIN, GPIO_STATE_HIGH);
        break;

        case LED_OFF:
            setPinOutput(BIG_LED_R_PIN);
            writePin(BIG_LED_R_PIN, GPIO_STATE_LOW);
        break;

        default:
        break;
    }
}

void set_big_LED_g(uint8_t mode) {
    switch(mode) {
        case LED_ON:
            setPinOutput(BIG_LED_G_PIN);
            writePin(BIG_LED_G_PIN, GPIO_STATE_HIGH);
        break;

        case LED_OFF:
            setPinOutput(BIG_LED_G_PIN);
            writePin(BIG_LED_G_PIN, GPIO_STATE_LOW);
        break;

        default:
        break;
    }
}

void set_big_LED_b(uint8_t mode) {
    switch(mode) {
        case LED_ON:
            setPinOutput(BIG_LED_B_PIN);
            writePin(BIG_LED_B_PIN, GPIO_STATE_HIGH);
        break;

        case LED_OFF:
            setPinOutput(BIG_LED_B_PIN);
            writePin(BIG_LED_B_PIN, GPIO_STATE_LOW);
        break;

        default:
        break;
    }
}