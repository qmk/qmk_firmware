/* Copyright 2025 Matrice Technologies
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
#define ENCODER_MAP_LAYERS 1

#include "quantum.h"
#include QMK_KEYBOARD_H

// ─── KEYMAP ────────────────────────────────────────────────────────────────────
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_3x4(
        KC_F13, KC_F14, KC_F15, KC_F16,
        KC_F17, KC_F18, KC_F19, KC_F20,
        KC_F21, KC_F22, KC_F23, KC_F24
    ),
};

// ─── ENCODER MAP ────────────────────────────────────────────────────────────────
// Must be uint16_t and use NUM_DIRECTIONS:

// ─── ENCODER MAP ────────────────────────────────────────────────────────────────
// Note the explicit `[ENCODER_MAP_LAYERS]` instead of `[]`
const uint16_t PROGMEM encoder_map[ENCODER_MAP_LAYERS][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { { KC_VOLD, KC_VOLU } },
};

// ─── HOOKS & MATRIX SCAN ───────────────────────────────────────────────────────

void keyboard_pre_init_kb(void) {
    gpio_set_pin_input_high(F6);
    keyboard_pre_init_user();
}

bool shutdown_kb(bool jump_to_bootloader) {
    return shutdown_user(jump_to_bootloader);
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    return layer_state_set_user(state);
}

void matrix_init_kb(void) {
    matrix_init_user();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true;
}

void matrix_scan_user(void) {
    static bool last = false;
    bool now = !readPin(F6);
    if (now && !last) {
        tap_code(KC_MUTE);
    }
    last = now;
}
