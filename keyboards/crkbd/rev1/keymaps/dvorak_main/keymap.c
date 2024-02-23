/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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

#include <stdint.h>
#include QMK_KEYBOARD_H

#include "oneshot.h"

#define MG(k) LGUI_T(k)
#define MS(k) LSFT_T(k)
#define MA(k) LALT_T(k)
#define MC(k) LCTL_T(k)


/**
 * DVORAK
 **/


#ifdef TAPPING_TERM_PER_KEY
uint16_t get_tapping_term(uint16_t kc, keyrecord_t *r)
{
    switch(kc){
        case MS(KC_E):
        case MS(KC_H):
            return TAPPING_TERM - 50;
        default:
            return TAPPING_TERM;
    }
}
#endif

enum keycodes {
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_CMD,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, KC_QUOTE, KC_COMMA, KC_DOT, KC_P,  KC_Y,                           KC_F,     KC_G,    KC_C,    KC_R,    KC_L, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,  KC_A ,   KC_O ,   KC_E ,   KC_U , KC_I,                           KC_D,     KC_H ,    KC_T ,     KC_N ,  KC_S,   XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
   XXXXXXX, KC_SEMICOLON,  KC_Q,  KC_J,    KC_K, KC_X,                           KC_B,    KC_M,    KC_W,    KC_V,     KC_Z,  XXXXXXX,
 //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
					XXXXXXX, MO(1), MC(KC_SPC),    MS(KC_TAB), MO(2), XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

    [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX, KC_GRV, KC_LBRC, KC_LCBR, KC_LPRN, KC_PLUS,                     KC_MINUS, KC_RPRN, KC_RCBR, KC_RBRC, KC_ESC,    XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX,  OS_CMD,  OS_ALT,  OS_SHFT,  OS_CTRL, KC_ENT,                    KC_BSPC, KC_DLR, KC_HASH,  KC_EQL, KC_PERC,  XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, KC_TILD,  KC_AT,  KC_BACKSLASH, KC_EXLM,  KC_SLASH,              KC_CIRC, KC_AMPR, KC_ASTR, KC_UNDS, KC_QUES,  XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
					XXXXXXX, _______, MC(KC_SPC),  MS(KC_TAB), MO(3), XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),
    
    [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
    XXXXXXX,  KC_1,    KC_2,     KC_3,    KC_4,    KC_5,                       LSFT(KC_QUOTE), C(KC_A), C(KC_C), A(KC_X), KC_ESC, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,  KC_6,    KC_7,     KC_8,    KC_9,    KC_0,                      KC_SLASH,  OS_CTRL , OS_SHFT, OS_ALT, OS_CMD, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_TILD,  KC_AT,  KC_BACKSLASH, KC_EXLM,  KC_SLASH,              KC_CIRC, KC_AMPR, KC_ASTR, KC_UNDS, KC_QUES,  XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
					XXXXXXX, MO(3), MC(KC_SPC),  MS(KC_TAB), _______, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

    [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     XXXXXXX, KC_F1,   KC_F2,   KC_F3,    KC_F4,    KC_F5,                      KC_F11,   KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX, 
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     XXXXXXX, OS_CMD,   OS_ALT, OS_SHFT, OS_CTRL, KC_PSCR,                      KC_F12,  KC_LEFT,  KC_DOWN,  KC_UP, KC_RIGHT, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,                      KC_MPLY, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, _______ ,XXXXXXX,   XXXXXXX, _______, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  )
};


bool is_oneshot_cancel_key(uint16_t keycode){
    switch (keycode) {
        case MO(1):
        case MO(2):
            return true;
        default:
            return false;
    }
}


bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case MO(1):
    case MO(2):
    case KC_LSFT:
    case OS_SHFT:
    case OS_CTRL:
    case OS_ALT:
    case OS_CMD:
        return true;
    default:
        return false;
    }
}

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record){
    update_oneshot(
            &os_shft_state, KC_LSFT, OS_SHFT,
            keycode, record
            );
    update_oneshot(
            &os_ctrl_state, KC_LCTL, OS_CTRL,
            keycode, record
            );
    update_oneshot(
            &os_alt_state, KC_LALT, OS_ALT,
            keycode, record
            );
    update_oneshot(
            &os_cmd_state, KC_LCMD, OS_CMD,
            keycode, record
            );
    return true;
}
