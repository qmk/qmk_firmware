// Copyright 2025 Jack Sachinidhs (@jacksaxi)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

enum layers {
    _LAYER1,
    _LAYER2,
    _LAYER3,
    _LAYER4
};

// Define the pin for the layer change button
#define LAYER_CHANGE_PIN GP13
#define DEBOUNCE_DELAY 10 // Debounce time in milliseconds

// Update LEDs based on the current layer
void set_layer_indicator(uint8_t layer) {
    writePin(LED_PIN_LAYER1, layer == _LAYER1);
    writePin(LED_PIN_LAYER2, layer == _LAYER2);
    writePin(LED_PIN_LAYER3, layer == _LAYER3);
    writePin(LED_PIN_LAYER4, layer == _LAYER4);
}

// Initialize pins
void keyboard_post_init_user(void) {
    setPinOutput(LED_PIN_LAYER1);
    setPinOutput(LED_PIN_LAYER2);
    setPinOutput(LED_PIN_LAYER3);
    setPinOutput(LED_PIN_LAYER4);

    // Initialize the layer change button pin
    setPinInputHigh(LAYER_CHANGE_PIN);

    set_layer_indicator(_LAYER1);
}

// Cycle through layers based on the layer change button state
void matrix_scan_user(void) {
    static bool last_button_state = false;
    static uint16_t last_debounce_time = 0;

    // Read the current state of the button (active low)
    bool current_button_state = !readPin(LAYER_CHANGE_PIN);

    // Check if the button state has changed and debounce time has passed
    if (current_button_state != last_button_state) {
        if (timer_elapsed(last_debounce_time) > DEBOUNCE_DELAY) {
            last_debounce_time = timer_read(); // Reset debounce timer

            if (current_button_state) {
                // Button was just pressed, move to the next layer
                uint8_t current_layer = get_highest_layer(layer_state);
                uint8_t next_layer = (current_layer + 1) % 4; // Cycle to the next layer
                layer_move(next_layer);
                set_layer_indicator(next_layer);
            }
        }
    }

    // Update the last known button state
    last_button_state = current_button_state;
}

// Define the keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_LAYER1] = LAYOUT(
        KC_1, KC_2, KC_3,
        KC_4, KC_5, KC_6,
        KC_7, KC_8, KC_9
    ),
    [_LAYER2] = LAYOUT(
        KC_Q, KC_W, KC_E,
        KC_R, KC_T, KC_Y,
        KC_U, KC_I, KC_O
    ),
    [_LAYER3] = LAYOUT(
        KC_A, KC_S, KC_D,
        KC_F, KC_G, KC_H,
        KC_J, KC_K, KC_L
    ),
    [_LAYER4] = LAYOUT(
        KC_Z, KC_X, KC_C,
        KC_V, KC_B, KC_N,
        KC_M, KC_COMM, KC_DOT
    ),
};
