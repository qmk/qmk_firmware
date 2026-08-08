/* Copyright 2026 Ryan McLean
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
#include QMK_KEYBOARD_H

/*
 * Physical layout:
 *
 *         Col 0        Col 1        Col 2
 *  Enc  KC_A / B2     —         KC_B / A6
 *  r0   KC_C / B19  KC_D / B21  KC_E / A15
 *  r1   KC_F / B20  KC_G / A12  KC_H / A3
 *  r2   KC_I / B22  KC_J / A13  KC_K / A2
 *  r3   KC_L / B15  KC_M / A14  KC_N / A1
 *
 * Layer 1 (hold ENC1 button):
 *   ENC2 button = QK_BOOT (reset/reflash)
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        MO(1),
        KC_C,  KC_D,
        KC_F,
        KC_I,
        KC_N,
        KC_K,
        KC_L,
        KC_J,  KC_M,
        KC_B,
        KC_G,
        KC_E,  KC_H
    ),
    [1] = LAYOUT(
        _______,
        _______, _______,
        _______,
        _______,
        _______,
        _______,
        _______,
        _______, _______,
        QK_BOOT,
        _______,
        _______, _______
    )
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______) },
};
