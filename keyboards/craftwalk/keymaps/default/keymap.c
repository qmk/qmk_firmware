/* Copyright 2020 sotoba
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
    _NUM,
    _ADJUST
};

#define MO_NUM MO(_NUM)
#define MO_ADJ MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
                 KC_Q,    KC_W,    KC_E,
        KC_LCTL, KC_A,    KC_S,    KC_D,
        KC_LSFT, MO_ADJ,  MS_WHLU, MS_WHLD, KC_F,    MO_NUM,  KC_SPC
    ),
    /* Number */
    [_NUM] = LAYOUT(
                 KC_7,    KC_8,    KC_9,
        KC_ESC,  KC_4,    KC_5,    KC_6,
        KC_TRNS, KC_1,    KC_2,    KC_3,    KC_F3,   KC_TRNS, KC_TRNS
    ),
    /* Adjust */
    [_ADJUST] = LAYOUT(
                 UG_HUEU, UG_SATU, UG_VALU,
        QK_BOOT, UG_HUED, UG_SATD, UG_VALD,
        RGB_M_T, KC_TRNS, UG_NEXT, UG_PREV, UG_TOGG, KC_TRNS, KC_TRNS
    )
};
