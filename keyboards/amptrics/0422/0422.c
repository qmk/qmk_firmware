/* Copyright 2024 Vinod Chowl (@vchowl)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2.0 of the License, or
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

#include QMK_KEYBOARD_H

#define LED_LAYER_0 B3
#define LED_LAYER_1 B4
#define LED_LAYER_2 B5
#define LED_LAYER_3 B6

#define LED_PINS_COUNT 4

pin_t pins[LED_PINS_COUNT] = {LED_LAYER_0, LED_LAYER_1, LED_LAYER_2, LED_LAYER_3};


// Function to turn on all LEDs
void turn_on_all_leds(void) {
    for (int i = 0; i < LED_PINS_COUNT; i++) {
        gpio_write_pin_high(pins[i]); // Turn on LED
    }
}

// Function to turn off all LEDs
void turn_off_all_leds(void) {
    for (int i = 0; i < LED_PINS_COUNT; i++) {
        gpio_write_pin_low(pins[i]); // Turn off LED
    }
}

void update_leds_for_layer(uint8_t layer) {
    turn_off_all_leds();
    gpio_write_pin_high(pins[layer]);
}

void keyboard_post_init_kb(void) {
    for (int i = 0; i < LED_PINS_COUNT; i++) {
        gpio_set_pin_output(pins[i]);
        gpio_write_pin_low(pins[i]);
    }

    // Blink all LEDs
    turn_on_all_leds();
    wait_ms(500); // Keep LEDs on for 500ms
    turn_off_all_leds();

    update_leds_for_layer(0); // Update LEDs to indicate the default layer
    keyboard_post_init_user();
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    uint8_t layer = get_highest_layer(state);
    update_leds_for_layer(layer);
    return layer_state_set_user(state);
}
