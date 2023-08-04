/* Copyright 2023 meletrix
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

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = {  ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [1] = {  ENCODER_CCW_CW(KC_MNXT, KC_MPRV)  },
};
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_pad(
        KC_ESC,  KC_TAB,  MO(1),   KC_MUTE,
        KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
        KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_P4,   KC_P5,   KC_P6,
        KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        KC_P0,            KC_PDOT
    ),
    [1] = LAYOUT_pad(
        QK_BOOT, _______, _______, KC_MPLY,
        _______, _______, _______, _______,
        KC_HOME, KC_UP,   KC_PGUP, _______,
        KC_LEFT, XXXXXXX, KC_RGHT,
        KC_END,  KC_DOWN, KC_PGDN, _______,
        KC_INS,           KC_DEL
    ),
};
