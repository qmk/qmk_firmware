// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

/* Keymap for 3x4 Macropad
 *
 * Layer 0 (Base Layer) - Numpad layout with mute button and layer toggle:
 * ,----------------------,
 * |   7   |   8   |   9   |  MUTE  |
 * |-------+-------+-------+--------|
 * |   4   |   5   |   6   | Layer1 |
 * |-------+-------+-------+--------|
 * |   1   |   2   |   3   |   0   |
 * `-----------------------^--------'
 *
 * Layer 1 (Function Layer) - Accessed by holding MO(1):
 * ,----------------------,
 * | BKSP  |   /   |   -   |  ----  |
 * |-------+-------+-------+--------|
 * |   =   |   *   |   +   |  ----  |
 * |-------+-------+-------+--------|
 * | ENTER |  ---- |  ---- |   .    |
 * `-----------------------^--------'
 *
 * The base layer (0) provides standard numpad functionality with:
 * - Numbers 0-9 in traditional numpad layout
 * - Mute button in top right
 * - Layer 1 momentary toggle (MO1) in middle right
 *
 * The function layer (1) adds:
 * - Basic mathematical operators (+, -, *, /)
 * - Backspace, Enter, and decimal point
 * - Equal sign for calculations
 * - Empty slots marked as ---- (KC_NO)
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT_ortho_3x4(
        KC_KP_7,    KC_KP_8,    KC_KP_9,    KC_MUTE,
        KC_KP_4,    KC_KP_5,    KC_KP_6,    MO(1),
        KC_KP_1,    KC_KP_2,    KC_KP_3,    KC_KP_0
    ),

    [1] = LAYOUT_ortho_3x4(
        KC_BACKSPACE, KC_KP_SLASH,    KC_KP_MINUS, _______,
        KC_EQUAL,     KC_KP_ASTERISK, KC_KP_PLUS,  _______,
        KC_ENTER,     _______,          _______,       KC_KP_DOT
    )
};


/*
 * Handle layer state changes by updating RGB matrix colors
 *
 * Sets RGB matrix colors based on active layer:
 * - Layer 0: Light green (#88FB7A)
 * - Layer 1: Red
 * - Other layers: Red (fallback)
 */
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case 0:
        rgb_matrix_sethsv(85, 255, 251); // #88FB7A for layer 0
        break;
    case 1:
        rgb_matrix_sethsv(0, 255, 255); // Red for layer 1
        break;
    default:
        rgb_matrix_sethsv(0, 255, 255); // Red for any other layer
        break;
    }
    return state;
}
