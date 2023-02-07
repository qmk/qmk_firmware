/*
Copyright 2020 <me@homedrop.org>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

enum layers {
    _LAYER0,
    _LAYER1,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_LAYER0] = LAYOUT_ortho_6x4(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,
        KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
        KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_P4,   KC_P5,   KC_P6,   KC_TRNS,
        KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        KC_P0,   KC_PDOT, KC_PDOT, MO(1)
    ),

    [_LAYER1] = LAYOUT_ortho_6x4(
        QK_BOOT, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_HOME, KC_UP,   KC_PGUP, KC_TRNS,
        KC_LEFT, KC_TRNS, KC_RGHT, KC_TRNS,
        KC_END,  KC_DOWN, KC_PGDN, KC_TRNS,
        KC_INS,  KC_TRNS, KC_DEL,  KC_TRNS
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_LAYER0] =  { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [_LAYER1] =  { ENCODER_CCW_CW(KC_TRNS, KC_TRNS),           ENCODER_CCW_CW(KC_TRNS, KC_TRNS)  }
};
#endif