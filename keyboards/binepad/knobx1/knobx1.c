// (c) 2025 Binepad (@binpad)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "knobx1.h"

#ifdef DYNAMIC_KEYMAP_LAYER_COUNT
#    define X1_KEYMAP_LAYER_COUNT DYNAMIC_KEYMAP_LAYER_COUNT
#else
#    define X1_KEYMAP_LAYER_COUNT 4
#endif

__attribute__((weak)) void x1_layer_led(uint8_t lyr) {
    gpio_write_pin(IND1_LED, lyr >= 0);
    gpio_write_pin(IND2_LED, lyr >= 1);
    gpio_write_pin(IND3_LED, lyr >= 2);
    gpio_write_pin(IND4_LED, lyr >= 3);
}

void keyboard_pre_init_kb(void) {
    const pin_t indicator_leds[4] = {IND1_LED, IND2_LED, IND3_LED, IND4_LED};
    for (int i = 0; i < 4; i++) {
        gpio_set_pin_output(indicator_leds[i]); // Set Indicators as output
        gpio_write_pin_low(indicator_leds[i]);  // Set initial indicator low / OFF
    }

    // Call the user pre-init function if needed
    // Do it after ._kb incase the user wants to change pin stuff
    keyboard_pre_init_user();
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    state         = layer_state_set_user(state);
    uint8_t layer = get_highest_layer(state);
    x1_layer_led(layer);
    return state;
}

void matrix_init_kb(void) {
    // Direct PINS use; gpio -> switch -> ground.
    // Setting Row 0 to ground makes it work like a direct pin
    gpio_set_pin_output(ROW0_PIN); // Set Col0 as an output
    gpio_write_pin_low(ROW0_PIN);  // Set Col0 to low / ground

    matrix_init_user();
}

bool process_x1_layer_up(keyrecord_t *record) {
    if (record->event.pressed) {
        uint8_t current_layer = get_highest_layer(layer_state);
        // Cycle through layers
        uint8_t next_layer    = (current_layer + 1) % X1_KEYMAP_LAYER_COUNT;
        layer_move(next_layer);
        x1_layer_led(next_layer); // Update LED indicators
    }
    return false;
}

bool process_x1_layer_down(keyrecord_t *record) {
    if (record->event.pressed) {
        uint8_t current_layer = get_highest_layer(layer_state);
        // Reverse through layers
        uint8_t prev_layer = (current_layer == 0) ? (X1_KEYMAP_LAYER_COUNT - 1) : (current_layer - 1);
        layer_move(prev_layer);
        x1_layer_led(prev_layer);
    }
    return false;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    switch (keycode) {
        case X1_LAYER_SELECTOR_UP:
            return process_x1_layer_up(record);

        case X1_LAYER_SELECTOR_DOWN:
            return process_x1_layer_down(record);

        default:
            return true;
    }
}
