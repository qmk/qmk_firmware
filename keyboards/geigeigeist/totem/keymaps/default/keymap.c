/* Copyright 2025 Jose M Zelezarof (git@zelezarof.ca)
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

enum totem_layers { ALP, NUM, FUN, NAV };

#define ToT_A MT(MOD_LGUI, KC_A)
#define ToT_S MT(MOD_LALT, KC_S)
#define ToT_D MT(MOD_LCTL, KC_D)
#define ToT_F MT(MOD_LSFT, KC_F)

#define ToT_J MT(MOD_RSFT, KC_J)
#define ToT_K MT(MOD_RCTL, KC_K)
#define ToT_L MT(MOD_RALT, KC_L)
#define ToT_SCLN MT(MOD_RGUI, KC_SCLN)

#define _KC_SPC LT(NAV, KC_SPC)
#define _KC_BSPC LT(NUM, KC_BSPC)
#define _KC_DEL LT(FUN, KC_DEL)

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = LAYOUT(
                   'L',       'L',       'L',       'L',       'L',                   'R',       'R',       'R',       'R',       'R',
                   'L',       'L',       'L',       'L',       'L',                   'R',       'R',       'R',       'R',       'R',
        'L',       'L',       'L',       'L',       'L',       'L',                   'R',       'R',       'R',       'R',       'R',       'R',
                                         '*',       '*',       '*',                   '*',       '*',       '*'
);


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [ALP] = LAYOUT(
                   KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,                  KC_Y,      KC_U,      KC_I,      KC_O,      KC_P,
                   ToT_A,     ToT_S,     ToT_D,     ToT_F,     KC_G,                  KC_H,      ToT_J,     ToT_K,     ToT_L,     ToT_SCLN,
        KC_Q,      KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,                  KC_N,      KC_M,      KC_COMM,   KC_DOT,    KC_SLSH,   KC_QUOT,
                                         KC_ESC,    _KC_SPC,   KC_TAB,                KC_ENT,    _KC_BSPC,  _KC_DEL
    ),
    [NUM] = LAYOUT(
                   KC_LBRC,   KC_7,      KC_8,      KC_9,      KC_RBRC,               XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,
                   KC_SCLN,   KC_4,      KC_5,      KC_6,      KC_EQL,                XXXXXXX,   KC_RSFT,   KC_RCTL,   KC_RALT,   KC_RGUI,
        KC_LBRC,   KC_GRV,    KC_1,      KC_2,      KC_3,      KC_BSLS,               XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   KC_RGUI,
                                         KC_DOT,    KC_0,      KC_MINS,               _______,   _______,   _______
    ),
    [FUN] = LAYOUT(
                   KC_F12,    KC_F7,     KC_F8,     KC_F9,     KC_PSCR,               XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,
                   KC_F11,    KC_F4,     KC_F5,     KC_F6,     KC_SCRL,               XXXXXXX,   KC_RSFT,   KC_RCTL,   KC_RALT,   KC_RGUI,
        KC_F12,    KC_F10,    KC_F1,     KC_F2,     KC_F3,     KC_PAUS,               XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   KC_RGUI,
                                         _______,   _______,   _______,               _______,   _______,   _______
    ),
    [NAV] = LAYOUT(
                   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,               XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,
                   KC_LGUI,   KC_LALT,   KC_LCTL,   KC_LSFT,   XXXXXXX,               KC_LEFT,   KC_DOWN,   KC_UP,     KC_RGHT,   CW_TOGG,
        KC_LGUI,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,               KC_HOME,   KC_PGDN,   KC_PGUP,   KC_END,    KC_INS,    CW_TOGG,
                                         _______,   _______,   _______,               _______,   _______,   _______
    )
};
