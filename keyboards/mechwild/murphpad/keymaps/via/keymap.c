/* Copyright 2021 Kyle McCreery
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

// Defines names for use in layer keycodes and the keymap

enum layer_names {
    _BASE,
    _FN1,
    _FN2,
    _FN3
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
                  KC_F1,   KC_F2,   KC_F3,   KC_F4,
                  KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
                  KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_MUTE,  KC_P4,   KC_P5,   KC_P6,   _______,
        MO(_FN1), KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        KC_BSPC,  KC_P0,   _______, KC_PDOT, _______,

                  KC_F5,   KC_F6,   KC_F7

    ),
    [_FN1] = LAYOUT(
                 _______,  _______, _______, _______,
                 _______,  _______, _______, _______,
                 RGB_HUD,  RGB_SPI, RGB_HUI, _______,
        _______, RGB_RMOD, RGB_TOG, RGB_MOD, _______,
        _______, RGB_VAD,  RGB_SPD, RGB_VAI, _______,
        _______, RGB_SAD,  _______, RGB_SAI, _______,

                 _______,  _______, _______

    ),
    [_FN2] = LAYOUT(
                  _______, _______, _______, _______,
                  _______, _______, _______, _______,
                  _______, _______, _______, _______,
        _______,  _______, _______, _______, _______,
        _______,  _______, _______, _______, _______,
        _______,  _______, _______, _______, _______,

                  _______, _______, _______

    ),
    [_FN3] = LAYOUT(
                  _______, _______, _______, _______,
                  _______, _______, _______, _______,
                  _______, _______, _______, _______,
        _______,  _______, _______, _______, _______,
        _______,  _______, _______, _______, _______,
        _______,  _______, _______, _______, _______,

                  _______, _______, _______

    )
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_BRID, KC_BRIU) },
    [_FN1]  = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_FN2]  = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_FN3]  = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
};
#endif
