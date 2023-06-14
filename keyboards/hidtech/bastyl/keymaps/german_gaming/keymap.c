/*
 * Copyright 2021 Joschua Gandert
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
#include "keymap_german.h"


enum layer_names {
    _BASE,
    _GAME, /* WASD shifted right once  */
    _LOWER,
    _RAISE,
    _ADJUST /* when both LOWER and RAISE pressed */
};

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_ESC , KC_1  ,  KC_2  ,  KC_3  , KC_4  , KC_5  ,              KC_6  , KC_7  , KC_8   , KC_9  , KC_0   , DE_SS  ,
    KC_TAB , KC_Q  ,  KC_W  ,  KC_E  , KC_R  , KC_T  ,              DE_Z  , KC_U  , KC_I   , KC_O  , KC_P   , DE_UDIA,
    KC_LSFT, KC_A  ,  KC_S  ,  KC_D  , KC_F  , KC_G  ,              KC_H  , KC_J  , KC_K   , KC_L  , DE_ODIA, DE_ADIA,
    KC_LCTL, DE_Y  ,  KC_X  ,  KC_C  , KC_V  , KC_B  ,              KC_N  , KC_M  , KC_COMM, KC_DOT, DE_MINS, DE_PLUS,

                                  RAISE,  KC_SPC,   KC_LCTL,    KC_RALT,  KC_BSPC,  LOWER,
                                          KC_ENT,   KC_LALT,    KC_LGUI,  KC_RSFT
  ),

  [_GAME] = LAYOUT(
    _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______,
    KC_T   , KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   ,           _______, _______, KC_UP,   _______, _______, _______,
    KC_G   , KC_LSFT, KC_A   , KC_S   , KC_D   , KC_F   ,           _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
    KC_B   , KC_LCTL, DE_Y   , KC_X   , KC_C   , KC_V   ,           _______, _______, _______, _______, _______, _______,

                                  _______, _______, _______,    _______, _______, _______,
                                           _______, _______,    _______, _______
  ),

  [_LOWER] = LAYOUT(
    KC_TILD, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC,           KC_CIRC, KC_AMPR, KC_PSLS, KC_PAST, KC_PMNS, KC_DEL     ,
    _______, DE_HASH, DE_CIRC, KC_PGUP, DE_LABK, _______,           _______, KC_P7  , KC_P8  , KC_P9  , KC_PPLS, KC_BSPC    ,
    _______, DE_ACUT, KC_HOME, KC_PGDN, KC_END , KC_LPRN,           KC_RPRN, KC_P4  , KC_P5  , KC_P6  , KC_PDOT, _______    ,
    _______, KC_PLUS, KC_PIPE, KC_UNDS, _______, _______,           KC_P0  , KC_P1  , KC_P2  , KC_P3  , KC_PENT, KC_KP_EQUAL,

                                  _______, KC_RGHT, _______,    _______, _______, _______,
                                           KC_LEFT, _______,    QK_BOOT, _______
  ),

  [_RAISE] = LAYOUT(
    KC_F12 , KC_F1  ,  KC_F2 ,   KC_F3 ,  KC_F4 ,  KC_F5 ,          KC_F6  , KC_F7   , KC_F8   ,  KC_F9  , KC_F10    , KC_F11 ,
    _______, _______, _______,  KC_UP  , _______, _______,          KC_LALT, KC_INS  , KC_NUM  ,  KC_CALC, KC_PSCR   , KC_MUTE,
    _______, _______, KC_LEFT,  KC_DOWN, KC_RGHT, KC_ENT ,          KC_MSEL, KC_MPRV , KC_MPLY ,  KC_MNXT, _______   , KC_VOLU,
    _______, _______, _______,  _______, _______, _______,          DE_HASH, KC_MYCM , _______ ,  _______, KC_SCRL   , KC_VOLD,

                                  _______, _______, _______,    _______, KC_UP  , _______,
                                           _______, _______,    _______, KC_DOWN
  ),

  [_ADJUST] = LAYOUT(
    _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, QK_BOOT, _______,           _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, DF(_GAME),         _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, DF(_BASE),         _______, _______, _______, _______, _______, _______,

                                   _______, _______, _______,    _______, _______, _______,
                                            _______, _______,    _______, _______
  ),
};


layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
