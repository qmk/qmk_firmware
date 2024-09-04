/* Copyright 2024 W. Alex Ronke, a.k.a. NoPunIn10Did (w.alex.ronke@gmail.com)
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

#define DB_CONT KC_F5
#define DB_STOP LSFT(KC_F5)
#define DB_DTCH  LCTL(KC_F5)
#define STEP_IN KC_F11
#define STEPOUT LSFT(KC_F11)
#define STEPOVR KC_F10
#define UNXCOPY LCTL(KC_INS)
#define UNXPAST LSFT(KC_INS)
#define LSA_DEL LSA_T(KC_DEL)
#define FN_CALC LT(1,KC_CALC)
#define SCRNSHT SGUI(KC_S)
#define GUI_F16 LGUI_T(KC_F16)
#define ALT_GRV LALT_T(KC_GRV)
#define RALTHOM RALT_T(KC_HOME)
#define RGUIEND RGUI_T(KC_END)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = LAYOUT( 
    DB_STOP, DB_CONT, QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,           KC_BSPC, KC_DEL,
    STEP_IN, DB_DTCH, KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,                   KC_PGUP,
    STEPOUT, UNXCOPY, KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_BSLS,          KC_ENT,  KC_PGDN,
    STEPOVR, UNXPAST, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    LSA_DEL, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   FN_CALC,
    KC_INS,  SCRNSHT, KC_RCTL, GUI_F16, ALT_GRV,                            KC_SPC,                             RALTHOM, RGUIEND,          KC_LEFT, KC_DOWN, KC_RGHT
  ),

[1] = LAYOUT( 
    EE_CLR,  KC_NO,   QK_BOOT, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_TRNS, KC_TRNS,
    KC_NO,   KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_INS,  KC_TRNS, KC_PSCR, KC_TRNS, KC_TRNS,                   KC_TRNS,
    KC_NO,   KC_NO,   KC_CAPS, KC_TRNS, KC_SCRL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_SCRL, KC_TRNS, KC_TRNS, KC_INT3,          KC_TRNS, KC_TRNS,
    KC_NO,   KC_NO,   KC_TRNS, KC_NUBS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PAUS, KC_TRNS, KC_TRNS, KC_APP,  KC_TRNS, KC_TRNS, KC_INT1, KC_TRNS,          KC_TRNS, KC_TRNS,
    KC_NO,   KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                            KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS
  )
};
