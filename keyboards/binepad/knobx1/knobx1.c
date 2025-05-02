// (c) 2025 Binepad (@binpad)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "knobx1.h"

#ifdef DYNAMIC_KEYMAP_LAYER_COUNT
#    define X1_KEYMAP_LAYER_COUNT DYNAMIC_KEYMAP_LAYER_COUNT
#else
#    define X1_KEYMAP_LAYER_COUNT 4
#endif

void keyboard_pre_init_kb(void) {
    setPinOutput(IND1_LED); // Set Indicators as output
    writePinLow(IND1_LED);  // Set initial indicator low / OFF
    setPinOutput(IND2_LED);
    writePinLow(IND2_LED);
    setPinOutput(IND3_LED);
    writePinLow(IND3_LED);
    setPinOutput(IND4_LED);
    writePinLow(IND4_LED);

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
    setPinOutput(ROW0_PIN); // Set Col0 as an output
    writePinLow(ROW0_PIN);  // Set Col0 to low / ground

    matrix_init_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    switch (keycode) {
        case X1_LAYER_SELECTOR:
            if (record->event.pressed) {
                uint8_t current_layer = get_highest_layer(layer_state);
                uint8_t next_layer    = (current_layer + 1) % X1_KEYMAP_LAYER_COUNT; // Cycle through layers
                layer_move(next_layer);
                x1_layer_led(next_layer); // Update LED indicators
            }
            return false;

        default:
            return true;
    }
}
