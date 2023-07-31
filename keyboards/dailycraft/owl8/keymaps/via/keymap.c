/* Copyright 2021 yfuku
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
    [_BASE] = LAYOUT(
        KC_NO,   KC_NO,   KC_NO,  KC_NO, // for ext keys
        MO(1),   KC_BSPC, KC_SPC, KC_ENT,
        KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT
    ),
    [_FN1] = LAYOUT(
        KC_NO,   KC_NO,   KC_NO,  KC_NO,
        KC_1,    KC_2,    KC_3,   KC_4,
        KC_5,    KC_6,    KC_7,   KC_8
    ),
    [_FN2] = LAYOUT(
        KC_NO,   KC_NO,   KC_NO,  KC_NO,
        KC_1,    KC_2,    KC_3,   KC_4,
        KC_5,    KC_6,    KC_7,   KC_8
    ),
    [_FN3] = LAYOUT(
        KC_NO,   KC_NO,   KC_NO,  KC_NO,
        KC_1,    KC_2,    KC_3,   KC_4,
        KC_5,    KC_6,    KC_7,   KC_8
    )
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =   { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)  },
    [1] =   { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)  },
    [2] =   { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)  },
    [3] =   { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)  }
};
#endif
