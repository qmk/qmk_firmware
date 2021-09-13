/* Copyright 2020 NeohertzParts
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
/*const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

        KEYMAP(
                KC_A, KC_B, KC_C, KC_D,
                KC_E, KC_F, KC_G, KC_H,
                KC_I, KC_J, KC_K, KC_L,
 		KC_1, KC_2, KC_3, KC_4,
 		KC_5, KC_6, KC_7, KC_8,
 		KC_9, KC_X, KC_Y, KC_Z)
};*/

#define _QWERTY 0
#define _RAISE 1
#define _LOWER 2
#define _DVORAK 3

// Fillers to make layering more clear

#define ____ KC_TRNS

#define SFT_ESC  SFT_T(KC_ESC)
#define CTL_BSPC CTL_T(KC_BSPC)
#define ALT_SPC  ALT_T(KC_SPC)
#define SFT_ENT  SFT_T(KC_ENT)

#define KC_ML KC_MS_LEFT
#define KC_MR KC_MS_RIGHT
#define KC_MU KC_MS_UP
#define KC_MD KC_MS_DOWN
#define KC_MB1 KC_MS_BTN1
#define KC_MB2 KC_MS_BTN1

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 /*
 Base (qwerty)
 * +-----------------------------------------+                             +-----------------------------------------+
 * | ESC  |   q  |   w  |   e  |   r  |   t  |                             |   y  |   u  |   i  |   o  |   p  |      |
 * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
 * | TAB  |   a  |   s  |   d  |   f  |   g  |                             |   h  |   j  |   k  |   l  |   ;  |      |
 * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
 * | SHFT |   z  |   x  |   c  |   v  |   b  |                             |   n  |   m  |   ,  |   .  |   /  |      |
 * +------+------+------+------+-------------+                             +-------------+------+------+------+------+
 *               |  [   |   ]  |                                                         |      |      |
 *               +-------------+-------------+                             +-------------+-------------+
 *                             |      |      |                             |      |      |
 *                             |------+------|                             |------+------|
 *                             |      |      |                             |      |      |
 *                             +-------------+                             +-------------+
 *                                           +-------------+ +-------------+
 *                                           |      |      | |      |      |
 *                                           |------+------| |------+------|
 *                                           |      |      | |      |      |
 *                                           +-------------+ +-------------+
 */


[_DVORAK] = LAYOUT( \

    _______, KC_QUOT,  KC_COMM, KC_DOT, KC_P, KC_Y,         KC_F,   KC_G,   KC_C,   KC_R,   KC_L, _______, \
    _______, KC_A,     KC_O,    KC_E,   KC_U, KC_I,         KC_D,   KC_H,   KC_T,   KC_N,   KC_S, _______, \
    _______, KC_SCLN,  KC_Q,    KC_J,   KC_K, KC_X,         KC_B,   KC_M,   KC_W,   KC_V,   KC_Z, _______, \
          KC_GRV, KC_MINUS,                                         KC_LPRN,KC_RPRN,                    \
                          KC_LCTL,  KC_LSHIFT,    KC_SPC, KC_ENT,                                     \
                          KC_TAB, TG(LOWER),      KC_BSPC, KC_DEL,                                    \
                          KC_ESC, KC_LGUI,        KC_LALT, TG(RAISE)                                    \
),                                                    													     \

[_QWERTY] = LAYOUT( \

    KC_TAB,    KC_Q,  KC_W,   KC_E,   KC_R,   KC_T,         KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,    KC_BSPC, \
    KC_ESC,    KC_A,  KC_S,   KC_D,   KC_F,   KC_G,         KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN, KC_ENT, \
    KC_LSHIFT, KC_Z,  KC_X,   KC_C,   KC_V,   KC_B,         KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH, KC_BSLASH, \
                      KC_GRV, KC_QUOT,                                      KC_PLUS,KC_EQL,                    \
                          KC_LCTL, KC_SPC,                          KC_SPC, KC_ENT,                                     \
                          RAISE,   LOWER,                           KC_BSPC,KC_DEL,                                    \
                          KC_LALT, KC_LGUI,                         KC_LALT,RAISE                                    \
),                                                    													     \



[_LOWER] = LAYOUT(
    _______, _______,_______,_______,_______, KC_LPRN,            KC_RPRN, KC_7,   KC_8,   KC_9,   KC_BSPC, _______,          \
    _______, KC_HOME,KC_PGUP,KC_PGDN,KC_END , _______,            KC_MS_L, KC_MS_D,KC_MS_U,KC_MS_R,KC_MINS, _______,        \
    KC_LSHIFT,_______,_______,_______,_______,KC_LBRC,            KC_RBRC, KC_1,   KC_2,   KC_3,   KC_EQL,  _______,        \
                           _______, _______,                           KC_0, _______,                                          \
                           KC_LCTL, KC_PSCR,                         KC_BTN1,KC_BTN2,                                         \
                           _______,_______,                          KC_WH_U,KC_WH_D,                                         \
                           _______,_______,                            _______,_______                                          \
),


[_RAISE] = LAYOUT(
    _______,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,            KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS,		\
    RESET,     KC_LEFT,KC_UP  ,KC_DOWN,KC_RGHT,KC_LPRN,         KC_LEFT,KC_DOWN,KC_UP,  KC_RIGHT,KC_LPRN, KC_RPRN,		\
    KC_F1,     KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,           KC_F7,  KC_F8,  KC_F9,  KC_F10,  KC_F11,  KC_F12,	\
                              _______,_______,       	KC_EQL, _______,                                   				\
                              _______,_______,       	_______,_______,                                   				\
                              _______,_______,       	_______,_______,                                   				\
                              _______,_______,       	_______,_______                                    				\
)
};


void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

layer_state_t layer_state_set_user(layer_state_t state) {
  // The pins used for the LEDs are:
  // - Red:
  // - Green:
  // - Blue:
  switch (get_highest_layer(state)) {
    case _DVORAK:
        break;
    case _RAISE:
        break;
    case _LOWER:
        break;
    case _QWERTY:
        break;
    default: //  for any other layers, or the default layer
        break;
    }
  return state;
}
