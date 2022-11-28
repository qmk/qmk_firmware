/*
Copyright 2022 Tibo Loete, aka Mister Eel <mistermister1111@hotmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "mreel.h"

#define LAYOUT_wrapped(...) LAYOUT_80_with_macro(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_DF_MAC] = LAYOUT_wrapped(
    KC_MPLY,          KC_ESC,  _________________FROW_1TO5_________________, KC_F6,            _________________FROW_7TO10_______, KC_F11,  KC_F12,  KC_DEL,  TG(_WIN),
    KC_P1,   KC_P2,   KC_GRV,  ________________NUMBER_1TO5________________, KC_6,    ________________NUMBER_7TO0_______, KC_MINS, KC_EQL,  XXXXXXX, KC_BSPC, CK_HOME,
    KC_P3,   KC_P4,   KC_TAB,  _______________QWERTY_Q_TO_T_______________,          _______________QWERTY_Y_TO_P_______________, KC_LBRC, KC_RBRC, KC_BSLS, CK_END,
    KC_P5,   KC_P6,   CK_BWRD, _______________QWERTY_A_TO_G_______________,          _______________QWERTY_H_TO_SCLN____________, KC_QUOT,          KC_ENT,  KC_PGUP,
    KC_P7,   KC_P8,   KC_RSFT, _______________QWERTY_Z_TO_B_______________,          _______________QWERTY_N_TO_SLSH____________, KC_LSFT,      KC_UP,   KC_PGDN,
    KC_P9,   KC_P0,   KC_HYPR, KC_LCTL, KC_LOPT, KC_LCMD, XXXXXXX,  KC_SPC,            MO(_NAV_FN1), _______, KC_RCMD, MO(_KEYB), XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT
  ),
  [_WIN] = LAYOUT_wrapped(
    _______,          _______, ___________________BLANK5__________________, _______,          ______________BLANK4______________, _______, _______, _______, _______,
    _____BLANK2_____, _______, ___________________BLANK5__________________, _______, ___________________BLANK5__________________, _______, XXXXXXX, _______, _______,
    _____BLANK2_____, _______, ___________________BLANK5__________________,          ___________________BLANK5__________________, _______, _______, _______, _______,
    _____BLANK2_____, _______, ___________________BLANK5__________________,          ___________________BLANK5__________________, _______,          _______, _______,
    _____BLANK2_____, _______, ___________________BLANK5__________________,          ___________________BLANK5__________________, _______,          _______, _______,
    _____BLANK2_____, _______, KC_LGUI, KC_LALT, KC_LCTL, XXXXXXX, _______,            _______,  _______,    KC_RCTL, _______, XXXXXXX,    _______, _______, _______
  ),
  [_NAV_FN1] = LAYOUT_wrapped(
    _______,          _______, ___________________BLANK5__________________, _______,          ______________BLANK4______________, _______, _______, _______, _______,
    UC_SMLE, _______, UC_SP23, ___________________BLANK5__________________, _______, ___________________BLANK5__________________, _______, XXXXXXX, _______, _______,
    _____BLANK2_____, _______, _______, _______, UC_TRME, UC_AAGE, _______,          _______, UC_TRMU, UC_TRMI, UC_TRMO, _______, _______, _______, _______, _______,
    _____BLANK2_____, CK_LWRD, ___________________BLANK5__________________,          KC_LEFT, KC_DOWN,  KC_UP, KC_RGHT,  UC_COL,  _______, CK_RWRD,          _______,
    _____BLANK2_____, _______, ___________________BLANK5__________________,          ___________________BLANK5__________________, _______,          _______, _______,
    _____BLANK2_____, _______, _______, _______, _______, XXXXXXX, UC_UCIS,            _______,  _______,    _______, _______, XXXXXXX,    _______, _______, _______
  ),
  [_KEYB] = LAYOUT_wrapped(
    _______,          RGB_TOG, ___________________BLANK5__________________, _______,          ______________BLANK4______________, _______, _______, _______, _______,
    _____BLANK2_____, _______, ___________________BLANK5__________________, _______, ___________________BLANK5__________________, _______, XXXXXXX, _______, _______,
    _____BLANK2_____, _______, ___________________BLANK5__________________,          ___________________BLANK5__________________, _______, _______, _______, _______,
    _____BLANK2_____, _______, ___________________BLANK5__________________,          ___________________BLANK5__________________, _______,          _______, _______,
    CK_COMP, CK_FLSH, _______, ___________________BLANK5__________________,          ___________________BLANK5__________________, _______,          _______, _______,
    RESET,   _______, _______, _______, _______, _______, XXXXXXX, _______,            _______,  _______,    _______, _______, XXXXXXX,    _______, _______, _______
  ),
  /*
  [_EMPTY] = LAYOUT_wrapped(
    _______,          _______, ___________________BLANK5__________________, _______,          ______________BLANK4______________, _______, _______, _______, _______,
    _____BLANK2_____, _______, ___________________BLANK5__________________, _______, ___________________BLANK5__________________, _______, XXXXXXX, _______, _______,
    _____BLANK2_____, _______, ___________________BLANK5__________________,          ___________________BLANK5__________________, _______, _______, _______, _______,
    _____BLANK2_____, _______, ___________________BLANK5__________________,          ___________________BLANK5__________________, _______,          _______, _______,
    _____BLANK2_____, _______, ___________________BLANK5__________________,          ___________________BLANK5__________________, _______,          _______, _______,
    _____BLANK2_____, _______, _______, _______, _______, XXXXXXX, _______,            _______,  _______,    _______, _______, XXXXXXX,    _______, _______, _______
  ),
  */
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_DF_MAC]=   { ENCODER_CCW_CW(CK_VOLD, CK_VOLU), ENCODER_CCW_CW(CK_DLFT, CK_DRHT)  },
    [_WIN]=   { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)  },
    [_NAV_FN1]=   { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)  },
    [_KEYB]=   { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)  },
};
