/* Copyright 2022 Jose Pablo Ramirez <jp.ramangulo@gmail.com>
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

#include "quantum.h"

static pin_t pins[MATRIX_ROWS][MATRIX_COLS] = DIRECT_PINS;
static pin_t led_pins[LED_PINS] = LED_PINS_HW;
static bool led_state[MATRIX_COLS] = {0};
static uint8_t led_cycle_counter = 0;

void keyboard_post_init_kb(void) {
    for(uint8_t row = 0; row < MATRIX_ROWS; row++)
    {
        for(uint8_t col = 0; col < MATRIX_COLS; col++)
        {
            gpio_write_pin_low(pins[row][col]); //Disable internal pull-up resistors
        }
    }

    keyboard_post_init_user();
}

void cycle_leds(void) {
    for(uint8_t i = 0; i < 3; i++) {
        gpio_set_pin_input(led_pins[i]);
        gpio_write_pin_low(led_pins[i]);
    }

    led_cycle_counter++;
    led_cycle_counter %= 6;

    switch (led_cycle_counter) {
        case 0:
            if (led_state[0]) { // Up Arrow
                gpio_set_pin_input(led_pins[0]);
                gpio_write_pin_low(led_pins[0]);
                gpio_set_pin_output(led_pins[1]);
                gpio_write_pin_high(led_pins[1]);
                gpio_set_pin_output(led_pins[2]);
                gpio_write_pin_low(led_pins[2]);
            }
            break;
        case 1:
            if (led_state[1]) { // Down Arrow
                gpio_set_pin_output(led_pins[0]);
                gpio_write_pin_high(led_pins[0]);
                gpio_set_pin_output(led_pins[1]);
                gpio_write_pin_low(led_pins[1]);
                gpio_set_pin_input(led_pins[2]);
                gpio_write_pin_low(led_pins[2]);
            }
            break;
        case 2:
            if (led_state[2]) { // Left Arrow
                gpio_set_pin_output(led_pins[0]);
                gpio_write_pin_low(led_pins[0]);
                gpio_set_pin_output(led_pins[1]);
                gpio_write_pin_high(led_pins[1]);
                gpio_set_pin_input(led_pins[2]);
                gpio_write_pin_low(led_pins[2]);
            }
            break;
        case 3:
            if (led_state[3]) { // Right Arrow
                gpio_set_pin_input(led_pins[0]);
                gpio_write_pin_low(led_pins[0]);
                gpio_set_pin_output(led_pins[1]);
                gpio_write_pin_low(led_pins[1]);
                gpio_set_pin_output(led_pins[2]);
                gpio_write_pin_high(led_pins[2]);
            }
            break;
        case 4:
            if (led_state[4]) { // Space
                gpio_set_pin_output(led_pins[0]);
                gpio_write_pin_low(led_pins[0]);
                gpio_set_pin_input(led_pins[1]);
                gpio_write_pin_low(led_pins[1]);
                gpio_set_pin_output(led_pins[2]);
                gpio_write_pin_high(led_pins[2]);
              }
            break;
         case 5:
            if (led_state[5]) { // Right Click
                gpio_set_pin_output(led_pins[0]);
                gpio_write_pin_high(led_pins[0]);
                gpio_set_pin_input(led_pins[1]);
                gpio_write_pin_low(led_pins[1]);
                gpio_set_pin_output(led_pins[2]);
                gpio_write_pin_low(led_pins[2]);
            }
            break;
        default:
            break;
    }
}

void matrix_scan_kb(void) {
    cycle_leds();
    matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {

    uint8_t row = record->event.key.row;
    uint8_t col = record->event.key.col;

    if(row == 0 && col >= 0 && col < MATRIX_COLS) {
        led_state[col] = record->event.pressed;
    }

    return process_record_user(keycode, record);
}
