/* Copyright 2020 DmNosachev
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
#include "debug.h"
#include "version.h"

enum custom_keycodes {
  VRSN = SAFE_RANGE,
  MC1
};

enum unicode_names {
  USCT,
  ULSB,
  URSB,
  USCO,
  UAPO,
  UCOM,
  UDOT,
  USLS,
  ULCB,
  URCB,
  UCLN,
  UQOT,
  ULTH,
  UGTH,
  UQUE,
  UGRV,
  UTLD,
  UAT,
  UHSH,
  UDLR,
  UPCT,
  UCFX,
  UAMP,
  UAST
};

const uint32_t unicode_map[] PROGMEM = {
  [USCT]  = 0x00A7, // §
  [ULSB]  = 0x005B, // [
  [URSB]  = 0x005D, // ]
  [USCO]  = 0x003B, // ;
  [UAPO]  = 0x0027, // '
  [UCOM]  = 0x002C, // ,
  [UDOT]  = 0x002E, // .
  [USLS]  = 0x002F, // slash
  [ULCB]  = 0x007B, // {
  [URCB]  = 0x007D, // }
  [UCLN]  = 0x003A, // :
  [UQOT]  = 0x0022, // "
  [ULTH]  = 0x003C, // <
  [UGTH]  = 0x003E, // >
  [UQUE]  = 0x003F, // ?
  [UGRV]  = 0x0060, // `
  [UTLD]  = 0x007E, // ~
  [UAT]   = 0x0040, // at
  [UHSH]  = 0x0023, // hash
  [UDLR]  = 0x0024, // dollar
  [UPCT]  = 0x0025, // percent
  [UCFX]  = 0x005E, // ^
  [UAMP]  = 0x0026, // &
  [UAST]  = 0x002A, // asterisk
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * ,-------------------------------------------------------------------------------------------------------------------------------------.
 * | gui |     |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 | Vol-| Vol+| Mute|Pause|                         |
 * |-------------------------------------------------------------------------------------------------------------------------------------|
 * | esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |  ~  |backspc|  | PgUp| Home|  |NumLk|  /  |  *  |  -  |
 * |-------------------------------------------------------------------------------------------------------------------------------------|
 * |  tab  |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |   enter      | PgDn|  End|  |  7  |  8  |  9  | +=  |
 * |--------------------------------------------------------------------------------              |--------------------------------------|
 * |  ctrl  |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;: |  '" |  |\ |             | Del |NumLk|  |  4  |  5  |  6  |  +  |
 * |-------------------------------------------------------------------------------------------------------------------------------------|
 * |   shift   |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /? |  [] |     shift      |  up | down|  |  1  |  2  |  3  |enter|
 * |-------------------------------------------------------------------------------------------------------------------------------|     |
 * |         | caps |  alt  |                    Space                      |  Fn |                | left|right|  |     0     |  .  |     |
 * `-------------------------------------------------------------------------------------------------------------------------------------'
*/
    [0] = LAYOUT(
    KC_LGUI,          KC_F1,  KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, KC_F12, KC_VOLD,   KC_VOLU, KC_MUTE,  KC_PSCR,
    KC_ESC,  KC_1,    KC_2,   KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL, KC_GRV, KC_BSPC,   KC_PGUP, KC_HOME,  KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
    KC_TAB,  KC_Q,    KC_W,   KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,        KC_ENT,    KC_PGDN, KC_END,   KC_P7,   KC_P8,   KC_P9,   KC_EQL,
    KC_LCTL, KC_A,   KC_S,   KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_BSLS,                   KC_DEL,  KC_NUM,   KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
    KC_LSFT,          KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, MC1,            KC_RSFT,   KC_UP,   KC_DOWN,  KC_P1,   KC_P2,   KC_P3,   KC_PENT,
                   KC_CAPS, KC_LALT,                                KC_SPC,                                    MO(1),                   KC_LEFT, KC_RGHT,     KC_P0,   KC_PDOT
    ),
/*
 * ,-------------------------------------------------------------------------------------------------------------------------------------.
 * | VRSN|     |Sleep|     |Umode|     |     |     |     |     |     |     |     |     |     |     |     |     |                         |
 * |-------------------------------------------------------------------------------------------------------------------------------------|
 * |     |     | @   | #   |  $  |  §  |  ^  |  &  | *   |     |     |     |     |     |       |  |     |     |  |Calc |     |     |     |
 * |-------------------------------------------------------------------------------------------------------------------------------------|
 * |       | mb1 | m↑  | mb2 | mb3 |     |     |     |SysRq|ScrLk|Pause|     |     |              |     |     |  |     |     |     |     |
 * |--------------------------------------------------------------------------------              |--------------------------------------|
 * |        | m←  | m↓  | m→  | mb5 |     |     |     |     |     |     |     |     |             |     |     |  |     |     |     |     |
 * |-------------------------------------------------------------------------------------------------------------------------------------|
 * |           |     |     | mb4 |     |     |     |     |     |     |     |     |                |     |     |  |     |     |     |     |
 * |-------------------------------------------------------------------------------------------------------------------------------|     |
 * |         |     |       |                                               |     |                |     |     |  |           |     |     |
 * `-------------------------------------------------------------------------------------------------------------------------------------'
*/    
    [1] = LAYOUT(
    VRSN,             KC_SLEP, _______, UC_NEXT, _______, _______, _______, _______, _______, _______,        _______,        _______, _______, _______, _______, _______, _______,
    _______, _______, UM(UAT),  UM(UHSH), UM(UDLR), UM(USCT), UM(UCFX), UM(UAMP), UM(UAST), _______, _______,        _______,               _______, _______, _______, _______, _______, KC_CALC, _______, _______, _______,
    _______, KC_BTN1, KC_MS_U, KC_BTN2, KC_BTN3, _______, _______, _______, KC_SYRQ, KC_SCRL, KC_PAUS,        UP(ULSB, ULCB), UP(URSB, URCB),        _______,   _______, _______, _______, _______, _______, _______,
    _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN5, _______, _______, _______, _______, _______, UP(USCO, UCLN), UP(UAPO, UQOT),        _______,                          _______, _______, _______, _______, _______, _______,
    _______,          _______, _______, KC_BTN4, _______, _______, _______, _______, UP(UCOM, ULTH), UP(UDOT, UGTH), UP(USLS, UQUE),        KC_APP,               _______,    _______, _______, _______, _______, _______, _______,
                   _______, _______,                               _______,                                   _______,                                   _______, _______,    _______,   _______
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
	  
   case MC1:
      if (record->event.pressed) {
        send_unicode_string("[]");
      }
      return false;
      break;
  }
  return true;
}
