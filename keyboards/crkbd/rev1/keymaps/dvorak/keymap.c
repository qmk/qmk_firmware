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
 * DVORAK with HomeRows
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
      KC_TAB, KC_QUOTE, KC_COMMA, KC_DOT, KC_P,  KC_Y,                       KC_F,    KC_G,    KC_C,    KC_R,   KC_L,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_EQL, MG(KC_A),  MA(KC_O),    MS(KC_E), MC(KC_U), KC_I,                   KC_D,    MC(KC_H),    MS(KC_T),    MA(KC_N), MG(KC_S),KC_SLASH,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
   KC_TILD, KC_SEMICOLON,  KC_Q,  KC_J,    KC_K,  KC_X,                           KC_B,    KC_M,    KC_W,    KC_V,     KC_Z, KC_BSLS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_BSPC,   MO(1),  KC_SPC,    KC_ENT,   MO(2), KC_SLASH
                                      //`--------------------------'  `--------------------------'
  ),

    [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_ESC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_EQL, MG(KC_GRV), MA(KC_LBRC), MS(KC_LCBR), MC(KC_LPRN), S(KC_EQL),    KC_MINUS, MC(KC_RPRN), MS(KC_RCBR), MA(KC_RBRC), MG(KC_QUOTE),  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TILD, KC_EXLM,  KC_AT,  KC_HASH, KC_DLR,  KC_PERC,                     KC_CIRC, KC_AMPR, KC_ASTR, KC_UNDS, KC_QUES,  KC_BSLS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, _______,  KC_SPC,     KC_ENT,   MO(3), KC_PIPE
                                      //`--------------------------'  `--------------------------'
  ),


    [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, KC_HOME,   KC_PGDN, KC_PGUP,  KC_END, KC_PERC,                    KC_CIRC, C(KC_A), C(KC_C), A(KC_X), KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, OS_CMD, OS_ALT, OS_SHFT, OS_CTRL, KC_MS_WH_DOWN,                  KC_MS_WH_UP,  KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT,  XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_MSTP, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_MPLY,                      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, MO(3),  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),
    [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    KC_MS_ACCEL0, KC_MS_BTN1, KC_MS_WH_DOWN, KC_MS_WH_UP, KC_MS_BTN2, KC_PSCR,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, OS_CMD, OS_ALT, OS_SHFT, OS_CTRL, XXXXXXX,                     XXXXXXX, KC_MS_LEFT, KC_MS_DOWN, KC_MS_UP, KC_MS_RIGHT, KC_VOLU,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     KC_MS_ACCEL2, XXXXXXX, KC_MPLY, KC_MSTP, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_EQL, MO(3),  KC_SPC,     KC_ENT, _______, XXXXXXX
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
    switch (keycode){
        case MA(KC_LBRC):
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_LBRC);
                return false;
            }
            break;
        case MS(KC_LCBR):
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_LCBR);
                return false;
            }
            break;
        case MC(KC_LPRN):
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_LPRN);
                return false;
            }
            break;
        case MC(KC_RPRN):
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_RPRN);
                return false;
            }
            break;
        case MS(KC_RCBR):
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_RCBR);
                return false;
            }
            break;
        case MA(KC_RBRC):
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_RBRC);
                return false;
            }
            break;
    }
    return true;
}
