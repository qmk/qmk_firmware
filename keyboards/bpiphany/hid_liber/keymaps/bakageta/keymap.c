/* Copyright 2017 Mathias Andersson <wraul@dbox.se>: Phantom Layout
 * Copyright 2018 bakageta <amo@bakageta.com>: HID Liberation layouts
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
#include "hid_liber.h"

// Helpful defines
#define FN_CAPS LT(_FL, KC_CAPS)

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

#define _BL 0 // Base Layer
#define _GL 1 // Gaming Layer
#define _FL 2 // Function Layer

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BL] = LAYOUT( \
        KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,       KC_PSCR, KC_SCRL, KC_BRK,  \
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,      KC_INS,  KC_HOME, KC_PGUP, \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,      KC_DEL,  KC_END,  KC_PGDN, \
        FN_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,                                  \
        KC_LSFT, KC_NO,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,               KC_UP,            \
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, KC_RGUI, TT(_FL), KC_RCTL,      KC_LEFT, KC_DOWN, KC_RGHT  \
    ),
    [_GL] = LAYOUT( \
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      _______, _______, _______, \
        KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,                                 \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,               _______,          \
        _______, KC_NO,   _______,                            _______,                            _______, _______, _______, _______,      _______, _______, _______  \
    ),
    [_FL] = LAYOUT( \
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      _______, _______, _______, \
        _______, TO(_BL), TO(_GL), _______, _______, _______, _______, KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS, _______, _______, _______,      KC_VOLD, KC_MSTP, KC_VOLU, \
        _______, _______, _______, _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   KC_PPLS, _______, _______, _______,      KC_MNXT, KC_MPLY, KC_MNXT, \
        _______, _______, _______, _______, _______, _______, _______, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, _______,          _______,                                 \
        _______, _______, _______, _______, _______, _______, _______, _______, KC_P1,   KC_P2,   KC_P3,   KC_PENT,          _______,               _______,          \
        _______, _______, _______,                            KC_P0,                              KC_PDOT, KC_PENT, _______, _______,      _______, _______, _______  \
    ),
};
