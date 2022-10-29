/* Copyright 2022 DmNosachev
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
#include "version.h"

enum layer_names {
    _BASE, // default layer
    _NM,  // numpad onright, mouse on left
    _MC   // macros
};

#define MC1 COMP_FR_QUOTES
#define MC2 COMP_NBSP_EM_DASH
#define MC3 COMP_NBSP

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  VRSN,
  COMP_FR_QUOTES,		// Compose: french quotes
  COMP_NBSP_EM_DASH,	// Compose: nbsp followed by em dash
  COMP_NBSP,			// Compose: nbsp
  PWD1,
  PWD2,
  PWD3,
  PWD4,
  EMAIL1				// Gmail address
};

/*
*
*
* ,--------------------------------------------                           --------------------------------------------.
* |  Esc   |  F2  |  F3  |  F4  |  F5  |  F6  |                           |  F7  |  F8  |  F9  |  F10 | PrSc |  RAlt  |
* |--------+------+------+------+------+------+                           +------+------+------+------+------+--------|
* | +=/Alt |   1  |   2  |   3  |   4  |   5  |                           |   6  |   7  |   8  |   9  |   0  |   -    |
* |--------+------+------+------+------+------|                           +------+------+------+------+------+--------|
* |  Tab   |   Q  |   W  |   E  |   R  |   T  |                           |   Y  |   U  |   I  |   O  |   P  | \|     |
* |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
* |`~/Ctrl |   A  |   S  |   D  |   F  |   G  |                           |   H  |   J  |   K  |   L  |  ;:  | '"/NM  |
* |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
* | Shift  |Z/Ctrl|   X  |   C  |   V  |   B  |                           |   N  |   M  |  ,.  |  .>  |  /?  | Shift  |
* `-+------+------+------+------+------+------|                           |------+------+------+------+------+------+-'
*   | Play |  MC  |C+Shft|   [  |   ]  |      |                           |      | Left | Down |  Up  | Right|      |
*   `-----------------------------------------'                           `-----------------------------------------'
*                                        ,-------------.         ,-------------.
*                                        |  NM  |Enter |         | Gui  | Ctrl |
*                                 ,------|------|------|         |------+------+------.
*                                 |      |      | Home |         | PgUp |      |      |
*                                 |Space |Backsp|------|         |------|  Del | Enter|
*                                 |      |      | End  |         | PgDn |      |      |
*                                 `--------------------'         `--------------------'
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT_all(
    KC_ESC,           KC_F2,  KC_F3,         KC_F4,   KC_F5,   KC_F6,     KC_F7,  KC_F8,  KC_F9,   KC_F10, KC_PSCR, KC_RALT,
    LALT_T(KC_EQL),   KC_1,   KC_2,          KC_3,    KC_4,    KC_5,      KC_6,   KC_7,   KC_8,    KC_9,   KC_0,    KC_MINS,
    KC_TAB,           KC_Q,   KC_W,          KC_E,    KC_R,    KC_T,      KC_Y,   KC_U,   KC_I,    KC_O,   KC_P,    KC_BSLS,
    LCTL_T(KC_GRV),   KC_A,   KC_S,          KC_D,    KC_F,    KC_G,      KC_H,   KC_J,   KC_K,    KC_L,   KC_SCLN, LT(_NM, KC_QUOT),
    KC_LSPO,    LCTL_T(KC_Z), KC_X,          KC_C,    KC_V,    KC_B,      KC_N,   KC_M,   KC_COMM, KC_DOT, KC_SLSH, KC_RSPC,
    KC_MPLY,         MO(_MC), LCTL(KC_LSFT), KC_LBRC, KC_RBRC, KC_NO,     KC_NO,  KC_LEFT,KC_DOWN, KC_UP,  KC_RGHT,KC_NO,
			                                        MO(_NM),  KC_ENTER,            KC_RGUI,KC_RCTRL,
                                                        KC_HOME,             KC_PGUP,
                                       KC_SPC, KC_BSPC, KC_END,              KC_PGDN,KC_DEL, KC_ENTER
    ),
/*
*
*
* ,--------------------------------------------                           --------------------------------------------.
* |   F1   |au on |au off|      |      |      |                           |ck tg |ck up |ck dn |ck rst| F11  |  F12   |
* |--------+------+------+------+------+------+                           +------+------+------+------+------+--------|
* |        |      |      |      |      |      |                           |ScrLk |Numlck|  =   |  /   |  *   |        |
* |--------+------+------+------+------+------|                           +------+------+------+------+------+--------|
* |        |      |  MbL |  MUp |  MbR | Ins  |                           |CapsLk|  7   |  8   |  9   |  -   |        |
* |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
* |        |      |  ML  |  MDn |  MR  |      |                           |      |  4   |  5   |  6   |  +   |  L1    |
* |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
* |        |      |      |      |      |      |                           |  .   |  1   |  2   |  3   |Enter |        |
* `-+------+------+------+------+------+------|                           |------+------+------+------+------+------+-'
*   |      |      |      |      |      |      |                           |      |      |      |      |      |      |
*   `-----------------------------------------'                           `-----------------------------------------'
*                                        ,-------------.         ,-------------.
*                                        |      |      |         |      |      |
*                                 ,------|------|------|         |------+------+------.
*                                 |      |      |MWhUp |         |      |      |      |
*                                 |      |      |------|         |------|      |  0   |
*                                 |      |      |MWhDn |         |      |      |      |
*                                 `--------------------'         `--------------------'
*/
[_NM] = LAYOUT_all(
    KC_F1,   AU_ON,   AU_OFF,  _______, _______, _______,   CK_TOGG, CK_UP,   CK_DOWN, CK_RST,  KC_F11,  KC_F12,
    _______, _______, _______, _______, _______, _______,   KC_SLCK, KC_NLCK, KC_PEQL, KC_PSLS, KC_PAST, _______,
    _______, _______, KC_BTN1, KC_MS_U, KC_BTN2, KC_INS,    KC_CAPS, KC_P7,   KC_P8,   KC_P9,   KC_PMNS, _______,
    _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______,   _______, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, _______,
    _______, _______, _______, _______, _______, _______,   KC_PDOT, KC_P1,   KC_P2,   KC_P3,   KC_PENT, _______,
    _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______,
			                                  _______, _______,   _______, _______,
                                                 KC_WH_U,   _______,
                               _______, _______, KC_WH_D,   _______, _______, KC_P0
    ),
/*
*
*
* ,--------------------------------------------                           --------------------------------------------.
* |        |      |      |      |      |      |                           |email |      | PWD4 | PWD3 | PWD2 |  PWD1  |
* |--------+------+------+------+------+------+                           +------+------+------+------+------+--------|
* |        |      |      |      |      |      |                           |      |      |      |      |      |   MC2  |
* |--------+------+------+------+------+------|                           +------+------+------+------+------+--------|
* |        |      |      |      |reset |      |                           |      |      |      |      |      |        |
* |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
* |        |      |      |      |      |      |                           |      |      |      |      |      |        |
* |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
* |        |      |      |      |      |      |                           |      |      |  MC1 |      |      |        |
* `-+------+------+------+------+------+------|                           |------+------+------+------+------+------+-'
*   |      |      |      |      |      |      |                           |      |      |      |      |      |      |
*   `-----------------------------------------'                           `-----------------------------------------'
*                                        ,-------------.         ,-------------.
*                                        |      |      |         |      |      |
*                                 ,------|------|------|         |------+------+------.
*                                 |      |      |      |         |      |      |      |
*                                 |  MC3 |      |------|         |------|      |      |
*                                 |      |      |      |         |      |      |      |
*                                 `--------------------'         `--------------------'
*/
[_MC] = LAYOUT_all(
    VRSN,    _______, _______, _______, _______, _______,   EMAIL1,  _______, PWD4,    PWD3,    PWD2,    PWD1,
    _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, MC2,
    _______, _______, _______, _______, QK_BOOT, _______,   _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,   _______, _______, MC1,     _______, _______, _______,
    _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______,
			                                  _______, _______,   _______, _______,
                                                 _______,   _______,
                               MC3,     _______, _______,   _______, _______, _______
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
	  case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
	  
	  case COMP_FR_QUOTES:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_RALT)"<<"SS_TAP(X_RALT)">>"SS_TAP(X_LEFT));
      }
      return false;
      break;
	  
	  case COMP_NBSP_EM_DASH:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_RALT)"  "SS_TAP(X_RALT)"--- ");
      }
      return false;
      break;
	  
	  case COMP_NBSP:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_RALT)"  ");
      }
      return false;
      break;
	  
    case PWD1:
      if (record->event.pressed) {
        SEND_STRING("NakedLunch1991"SS_TAP(X_ENTER));
      }
      return false;
      break;
	  
	  case PWD2:
      if (record->event.pressed) {
        SEND_STRING("O94nx4sUWHc4akud"SS_TAP(X_ENTER));
      }
      return false;
      break;
	  
	  case PWD3:
      if (record->event.pressed) {
        SEND_STRING("Q123qQ123q"SS_TAP(X_ENTER));
      }
      return false;
      break;
      
    case PWD4:
      if (record->event.pressed) {
        SEND_STRING("EraserHead1976"SS_TAP(X_ENTER));
      }
      return false;
      break;  
	  
	  case EMAIL1:
      if (record->event.pressed) {
        SEND_STRING("quartz64@gmail.com");
      }
      return false;
      break;
  }
  return true;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return false;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    writePin(LED4_PIN, !layer_state_cmp(state, _MC));
  return state;
}
