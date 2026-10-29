// Copyright 2025 Jack Sachinidhs (@jacksaxi)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"

void keyboard_post_init_kb(void) {
    // Initialize LED pins
    gpio_set_pin_output(LED_PIN_LAYER_0);
    gpio_write_pin_low(LED_PIN_LAYER_0);
    gpio_set_pin_output(LED_PIN_LAYER_1);
    gpio_write_pin_low(LED_PIN_LAYER_1);
    gpio_set_pin_output(LED_PIN_LAYER_2);
    gpio_write_pin_low(LED_PIN_LAYER_2);
    gpio_set_pin_output(LED_PIN_LAYER_3);
    gpio_write_pin_low(LED_PIN_LAYER_3);

    keyboard_post_init_user();
}

// Update LEDs based on the current layer
void housekeeping_task_kb(void) {
    gpio_write_pin(LED_PIN_LAYER_0, (get_highest_layer(layer_state) == 0));
    gpio_write_pin(LED_PIN_LAYER_1, (get_highest_layer(layer_state) == 1));
    gpio_write_pin(LED_PIN_LAYER_2, (get_highest_layer(layer_state) == 2));
    gpio_write_pin(LED_PIN_LAYER_3, (get_highest_layer(layer_state) == 3));
}
