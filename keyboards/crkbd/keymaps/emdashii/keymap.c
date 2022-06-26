/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>
Copyright 2022 Elliott Claus <@emdashii>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include <stdio.h>
#include "keycodes.h"


#ifdef OLED_ENABLE
#include "oled.h"
#endif


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// QWERTY
//  ,-----------------------------------------------------.                    ,-----------------------------------------------------.
//  |   Tab  |   Q    |   W    |   E    |   R    |   T    |                    |   Y    |   U    |   I    |   O    |   P    | Bksp   |
//  |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//  |   Nav  |  A/GUI | S/ALT  | D/SHIFT| F/CTRL |   G    |                    |   H    | J/CTRL | K/SHIFT| L/ALT  | ;/GUI  |   '    |
//  |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//  | Shift  |   Z    |   X    |   C    |   V    |   B    |                    |   N    |   M    |   ,    |   .    |   /    | Escape |
//  `--------+--------+--------+--------+--------+--------+--------.  .--------+--------+--------+--------+--------+--------+--------'
//                                      | Del/Sym| Spc/Num|Function|  | C+S+Nav| Spc/Nav| Enter  |
//                                      `--------------------------'  `--------------------------'
  [_QWERTY] = LAYOUT_split_3x6_3(
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
         LNAV,  HOME_A,  HOME_S,  HOME_D,  HOME_F,    KC_G,                         KC_H,  HOME_J,  HOME_K,  HOME_L,HOME_SCLN, KC_QUOT,
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
                                          LSYMDEL, LNUMSPC, LOSLFUN,     LNAVCSX, LNAVSPC, LNAVENT

  ),

//  Navigation
//  ,-----------------------------------------------------.                    ,-----------------------------------------------------.
//  |Tab/LGui| Pg Up  |  Home  |   Up   |  End   |Rt Click|                    |  Acl0  | Wh up  | Ms up  | Wh dn  |        |  Bksp  |
//  |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//  | QWERTY | Pg Dn  |  Left  |  Down  | Right  |MidlClik|                    |  Acl1  | Ms lft | Ms dn  | Ms rgt |        | Delete |
//  |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//  | Shift  | Insert |        |Tab Back|Tab Fwd |LeftClic|                    |  Acl2  | Wh lft |        | Wh rgt |        | Escape |
//  `--------+--------+--------+--------+--------+--------+--------.  .--------+--------+--------+--------+--------+--------+--------'
//                                      |   Alt  |Spc/Ctrl|Ctrl+Shft| | QWERTY |Spc/Ctrl| Adjust |
//                                      `--------------------------'  `--------------------------'
  [_NAVIGATION] = LAYOUT_split_3x6_3(
      TABLGUI, KC_PGUP,  KC_HOME,  KC_UP,  KC_END, KC_BTN1,                      KC_ACL0, KC_WH_U, KC_MS_U, KC_WH_D, XXXXXXX, KC_BSPC,
      LQWERTY, KC_PGDN,  KC_LEFT,KC_DOWN, KC_RGHT, KC_BTN3,                      KC_ACL1, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX,  KC_DEL,
      KC_LSFT,  KC_INS, XXXXXXX, TABBKWD, TABFWRD, KC_BTN2,                      KC_ACL2, KC_WH_L, XXXXXXX, KC_WH_R, XXXXXXX,  KC_ESC,
                                          KC_LALT, CTRLSPC, CTRLSFT,    LQWERTY, CTRLSPC, LADJUST

  ),

// Number
//  ,-----------------------------------------------------.                    ,-----------------------------------------------------.
//  |   `    |   1    |   2    |   3    |   4    |   5    |                    |   6    |   7    |   8    |   9    |   0    |  Bksp  |
//  |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//  |        |        |        |        |        |        |                    |   =    |   4    |   5    |   6    |   -    |   /    |
//  |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//  |        |        |        |        |        |        |                    |   :    |   1    |   2    |   3    |   +    |   *    |
//  `--------+--------+--------+--------+--------+--------+--------.  .--------+--------+--------+--------+--------+--------+--------'
//                                      |   Del  |Spc/Ctrl|        |  | QWERTY |   0    |   .    |
//                                      `--------------------------'  `--------------------------'
  [_NUMBER] = LAYOUT_split_3x6_3(
       KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       KC_EQL,    KC_4,    KC_5,    KC_6, KC_MINS, KC_SLSH,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                        COLON,    KC_1,    KC_2,    KC_3, KC_PLUS, KC_ASTR,
                                           KC_DEL, CTRLSPC, XXXXXXX,   LQWERTY,     KC_0,  KC_DOT

  ),

// Symbol
//  ,-----------------------------------------------------.                    ,-----------------------------------------------------.
//  |   ~    |   !    |   @    |   #    |   $    |   %    |                    |   ^    |   &    |   *    |   (    |   )    |  Del   |
//  |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//  |        |        |        |   {    |   }    |        |                    |   =    |   -    |   +    |        |   ;    |   ' "  |
//  |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//  |        |        |    |   |   [    |   ]    |        |                    |   :    |   _    |  , <   |   . >  |   / ?  |   \    |
//  `--------+--------+--------+--------+--------+--------+--------.  .--------+--------+--------+--------+--------+--------+--------'
//                                      |        |        |        |  | QWERTY |        |        |
//                                      `--------------------------'  `--------------------------'
  [_SYMBOL] = LAYOUT_split_3x6_3(
      KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,  KC_DEL,
      XXXXXXX, XXXXXXX, XXXXXXX, KC_LCBR, KC_RCBR, XXXXXXX,                       KC_EQL, KC_MINS, KC_PLUS, XXXXXXX, KC_SCLN, KC_QUOT,
      XXXXXXX, XXXXXXX, KC_PIPE, KC_LBRC, KC_RBRC, XXXXXXX,                        COLON, KC_UNDS, KC_COMM,  KC_DOT, KC_SLSH, KC_BSLS,
                                          XXXXXXX, XXXXXXX, XXXXXXX,   LQWERTY,  XXXXXXX, XXXXXXX

  ),

// Fuction
//  ,-----------------------------------------------------.                    ,-----------------------------------------------------.
//  |        |   F1   |   F2   |   F3   |   F4   |   F5   |                    |   F6   |   F7   |   F8   |   F9   |   F10  |        |
//  |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//  |        |        |        |        |        |        |                    |        |   F4   |   F5   |   F6   |   F11  |        |
//  |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//  |        |        |        |        |        |        |                    |        |   F1   |   F2   |   F3   |   F12  |        |
//  `--------+--------+--------+--------+--------+--------+--------.  .--------+--------+--------+--------+--------+--------+--------'
//                                      |        |        |        |  | QWERTY |        |        |
//                                      `--------------------------'  `--------------------------'
  [_FUNCTION] = LAYOUT_split_3x6_3(
       KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_DEL,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                          XXXXXXX, XXXXXXX, XXXXXXX,   LQWERTY,  XXXXXXX, XXXXXXX

  ),

// Adjust
//  ,-----------------------------------------------------.                    ,-----------------------------------------------------.
//  |  Reset |        |        |        |        | Print  |                    | NumLock|CapsLock| Scroll |        | Bright+|  Vol+  |
//  |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//  | On/Off | Hue ↑  | Sat ↑  | Brght ↑|        |        |                    | Gaming |        |        |        | Bright-|  Vol-  |
//  |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//  | Cycle  | Hue ↓  | Sat ↓  | Brght ↓|        |        |                    |SetQWERTY|       |        |        |        |  Mute  |
//  `--------+--------+--------+--------+--------+--------+--------.  .--------+--------+--------+--------+--------+--------+--------'
//                                      |        |        |        |  | QWERTY |        |        |
//                                      `--------------------------'  `--------------------------'
  [_ADJUST] = LAYOUT_split_3x6_3(
        RESET, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR,                       KC_NUM, KC_CAPS, KC_SCRL, XXXXXXX, KC_BRIU, KC_VOLU,
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      LGAMING, XXXXXXX, XXXXXXX, XXXXXXX, KC_BRID, KC_VOLD,
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      SQWERTY, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE,
                                          XXXXXXX, XXXXXXX, XXXXXXX,    LQWERTY, XXXXXXX, XXXXXXX
  ),

// Gaming
//  ,-----------------------------------------------------.                    ,-----------------------------------------------------.
//  | Tab    |   Q    |   W    |   E    |   R    |   T    |                    |   Y    |   U    |   I    |   O    |   P    | Bksp   |
//  |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//  | Shift  |   A    |   S    |   D    |   F    |   G    |                    |   H    |   J    |   K    |   L    |   ;    |   '    |
//  |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//  | Ctrl   |   Z    |   X    |   C    |   V    |   B    |                    |   N    |   M    |   ,    |   .    |   /    |  Esc   |
//  `--------+--------+--------+--------+--------+--------+--------.  .--------+--------+--------+--------+--------+--------+--------'
//                                      |   F3   | Space  |Fun/Num |  | QWERTY | Spc/Num| Enter  |
//                                      `--------------------------'  `--------------------------'
  [_GAMING] = LAYOUT_split_3x6_3(
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
      KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
      KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
                                            KC_F3,  KC_SPC, LNUMFUN,     LQWERTY, LNUMSPC,  KC_ENT

  )
};



layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _SYMBOL, _NUMBER, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

#ifdef OLED_ENABLE
    if (record->event.pressed) {
        set_keylog(keycode, record);
    }
#endif // OLED_ENABLE

    switch (keycode) {
        case FUN:
            if  (!host_keyboard_led_state().num_lock) {
                tap_code(KC_NUMLOCK);
            }
        return true;
        break;
    }
    return true;
}

void keyboard_post_init_user(void) {
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(HSV_OFF);
#endif
}


// Template from @toinux

// TEMPLATE
//  ,-----------------------------------------------------.                    ,-----------------------------------------------------.
//  |        |        |        |        |        |        |                    |        |        |        |        |        |        |
//  |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//  |        |        |        |        |        |        |                    |        |        |        |        |        |        |
//  |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//  |        |        |        |        |        |        |                    |        |        |        |        |        |        |
//  `--------+--------+--------+--------+--------+--------+--------.  .--------+--------+--------+--------+--------+--------+--------'
//                                      |        |        |        |  |        |        |        |
//                                      `--------------------------'  `--------------------------'
