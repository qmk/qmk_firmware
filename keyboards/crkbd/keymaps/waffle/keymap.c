/* Copyright 2020 Jack Sangdahl
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
#include "keycodes.h"
#ifdef UNICODEMAP_ENABLE
#     include "unicodes.h"
#endif
#include "macros.h"
#ifdef COMBO_ENABLE
#    include "combos.h"
#endif
#ifdef OLED_DRIVER_ENABLE
#   include "oled.c"
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
    //|------------------------------------------------------------|        |-----------------------------------------------------------|
       GPSCR,     KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,     KC_O,     KC_P,      UNIT3,
    //|--------+--------+--------+--------+--------+--------------|         |--------+--------+--------+--------+--------+--------------|
        ALT_TAB,  SFA,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,     KC_L,    SFCLN,     UNIT4,
    //---------+--------+--------+--------+--------+-------------|          |--------+--------+--------+--------+--------+--------------|
       CP_PSTE,   CTLTZ,  KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M,    KC_COMM,  KC_DOT,  CTLSLH,    CTLS,
    //---------+--------+--------+--------+--------+--------+---------|  |--------+--------+--------+--------+--------+--------+--------|
                                           KC_LGUI, MO(1), KC_SPC,          KC_BSPC, MO(2), KC_RALT
                                      //|----------------------------|  |------------------------|
  ),

  [_LOWER] = LAYOUT(
    //|-------------------------------------------------------------|            |------------------------------------------------------------------|
       _______, KC_1,    KC_2,    KC_3,     KC_4,     KC_5,                       KC_6,     KC_7,     KC_8,     KC_9,      KC_0,      UNIT,
    //|--------+--------+--------+--------+--------+----------------|            |--------+--------+--------+--------+--------+---------------------|
       _______, SFEXM,    KC_AT,   KC_HASH,  KC_DLR,   KC_PERC,                    KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  SFPRN,     UNIT2,
    //|--------+--------+--------+--------+--------+----------------|            |--------+--------+--------+--------+--------+---------------------|
       _______, CTLESC,   KC_TAB,  KC_CAPS,  KC_TILD,  KC_GRV,                     KC_QUOT,  KC_PSCR,  KC_MPRV,  KC_MPLY,  CTLNXT,    _______,
    //|--------+--------+--------+--------+--------+--------+------------|  |--------+--------+--------+--------+--------+--------+-----------------|
                                          KC_PGUP, KC_TRNS, KC_SPC,             KC_ENT, KC_TRNS, KC_PGDN
                                   //|----------------------------------|  |---------------------------------|
  ),

  [_RAISE] = LAYOUT(
    //|-----------------------------------------------------|                    |-----------------------------------------------------|
       RGB_TOG, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,                      _______,  _______, _______, _______,  _______, UC_M_WC,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       RGB_VAI, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,                      KC_LEFT,  KC_DOWN, KC_UP,  KC_DOWN,   _______, UC_M_MA,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       RGB_VAD, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        _______, _______,  _______, _______, _______,  UC_M_LN,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                       KC_VOLD, KC_TRNS, KC_SPC,             KC_ENT, KC_TRNS, KC_VOLU
                                      //|---------------------------|  |---------------------------------------|
  )
};
