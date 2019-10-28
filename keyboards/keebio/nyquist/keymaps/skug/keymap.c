/* Copyright 2019 Christoffer Holmberg
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
#include "keymap_swedish.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define BASE 0
#define GAME 1
#define SYMB 2
#define MDIA 3
#define ARRW 4
#define _ADJUST 16

#define CT_APOS CTL_T(SE_APOS)
#define CT_TILD CTL_T(SE_TILD)
#define MD_OSLH LT(MDIA, SE_OSLH)
#define SM_AE   LT(SYMB, SE_AE)
#define SE_LT   SE_LESS
#define SE_GT   LSFT(SE_LESS)

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE,
  ADJUST,
  DVORAK,
  COLEMAK,
  QWERTY
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Base layer
 * ,-----------------------------------------.   .-----------------------------------------.
 * |  Esc |   1  |   2  |   3  |   4  |   5  |   |   6  |   7  |   8  |   9  |   0  |   +  |
 * |------+------+------+------+------+------+   +------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   |   Y  |   U  |   I  |   O  |   P  |   Å  |
 * |------+------+------+------+------+------|   |------+------+------+------+------+------|
 * | ARRW |   A  |   S  |   D  |   F  |   G  |   |   H  |   J  |   K  |   L  |   Ö  |   Ä  |
 * |------+------+------+------+------+------|   |------+------+------+------+------+------|
 * |Shift(|   Z  |   X  |   C  |   V  |   B  |   |   N  |   M  |   ,  |   .  |   -  |)Shift|
 * |------+------+------+------+------+------+   +------+------+------+------+------+------|
 * |'/Ctrl|  ´   | Alt  |  Bsp |Space |  Win |   | Entr | Space| Bsb  | AlGr |   *  |Ctrl/¨|
 * `-----------------------------------------'   '-----------------------------------------'
 */
[BASE] = LAYOUT( \
                //       LEFT HAND                                               RIGHT HAND
  KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    SE_PLUS, \
  KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    SE_AA,   \
  MO(ARRW), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L,    MD_OSLH, SM_AE,   \
  KC_LSPO,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M,    KC_COMM, KC_DOT,  SE_MINS, KC_RSPC, \
  CT_APOS,  SE_ACUT, KC_LALT, KC_BSPC, KC_SPC,  KC_LGUI,     KC_ENT,  KC_SPC,  KC_BSPC, KC_ALGR, SE_ASTR, CT_TILD  \
),

/* Gaming layer
 * ,-----------------------------------------.   .-----------------------------------------.
 * |  Esc |   1  |   2  |   3  |   4  |   5  |   |   6  |   7  |   8  |   9  |   0  |   +  |
 * |------+------+------+------+------+------+   +------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   |   Y  |   U  |   I  |   O  |   P  |   Å  |
 * |------+------+------+------+------+------|   |------+------+------+------+------+------|
 * | ARRW |   A  |   S  |   D  |   F  |   G  |   |   H  |   J  |   K  |   L  |   Ö  |   Ä  |
 * |------+------+------+------+------+------|   |------+------+------+------+------+------|
 * |Shift |   Z  |   X  |   C  |   V  |   B  |   |   N  |   M  |   ,  |   .  |   -  | Shift|
 * |------+------+------+------+------+------+   +------+------+------+------+------+------|
 * | Ctrl |  ´   | Alt  |  Bsp |Space |  Win |   | Entr | Space| Bsb  | AlGr |   *  | Ctrl |
 * `-----------------------------------------'   '-----------------------------------------'
 */
[GAME] = LAYOUT( \
                //       LEFT HAND                                               RIGHT HAND
  KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    SE_PLUS, \
  KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    SE_AA,   \
  MO(ARRW), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L,    MD_OSLH, SM_AE,   \
  KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M,    KC_COMM, KC_DOT,  SE_MINS, KC_RSFT, \
  KC_LCTL,  SE_ACUT, KC_LALT, KC_BSPC, KC_SPC,  KC_LGUI,     KC_ENT,  KC_SPC,  KC_BSPC, KC_ALGR, SE_ASTR, KC_RCTL  \
),

/* Symbols layer
 * ,-----------------------------------------.   .-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |   |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------+   +------+------+------+------+------+------|
 * |      |   !  |   @  |   {  |   }  |   |  |   |  Up  |   7  |   8  |   9  |   *  | F12  |
 * |------+------+------+------+------+------|   |------+------+------+------+------+------|
 * |      |   #  |   $  |   (  |  )   |   `  |   | Down |   4  |   5  |   6  |   +  |      |
 * |------+------+------+------+------+------|   |------+------+------+------+------+------|
 * |      |   %  |   ^  |   [  |  ]   |   ~  |   |   &  |   1  |   2  |   3  |   -  |      |
 * |------+------+------+------+------+------+   +------+------+------+------+------+------|
 * |      |      |      |   <  |  >   |      |   |      |      |   .  |   0  |   =  |      |
 * `-----------------------------------------'   '-----------------------------------------'
 */
[SYMB] = LAYOUT( \
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  \
  _______, KC_EXLM, SE_AT,   SE_LCBR, SE_RCBR, SE_PIPE,     KC_UP,   KC_7,    KC_8,    KC_9,    SE_ASTR, KC_F12,  \
  _______, KC_HASH, SE_DLR,  SE_LPRN, SE_RPRN, SE_GRV,      KC_DOWN, KC_4,    KC_5,    KC_6,    SE_PLUS, _______, \
  _______, KC_PERC, SE_CIRC, SE_LBRC, SE_RBRC, SE_TILD,     SE_AMPR, KC_1,    KC_2,    KC_3,    SE_MINS, _______, \
  _______, _______, _______, SE_LT,   SE_GT,   _______,     _______, _______, KC_DOT,  KC_0,    SE_EQL,  _______  \
),

/* Media layer
 * ,-----------------------------------------.   .-----------------------------------------.
 * |      |      |      |      |      |      |   |      |      |      |      |      |      |
 * |------+------+------+------+------+------+   +------+------+------+------+------+------|
 * |      |      |      |      |      |      |   |      |      |      |      |      |      |
 * |------+------+------+------+------+------|   |------+------+------+------+------+------|
 * |      |      |      |      |      |      |   |      |      |      |      |      |      |
 * |------+------+------+------+------+------|   |------+------+------+------+------+------|
 * |      |      |      |      |      |      |   |      |      |      |      |      |      |
 * |------+------+------+------+------+------+   +------+------+------+------+------+------|
 * |      |      |      |      |      |      |   |      |      |      |      |      |      |
 * `-----------------------------------------'   '-----------------------------------------'
 */
[MDIA] = LAYOUT( \
  _______,  _______,  _______,  _______,  _______,  _______,     _______,  _______,  _______,  _______,  _______,  _______, \
  _______,  _______,  _______,  _______,  _______,  _______,     _______,  _______,  _______,  _______,  _______,  _______, \
  _______,  _______,  _______,  _______,  _______,  _______,     _______,  _______,  _______,  _______,  _______,  _______, \
  _______,  _______,  _______,  _______,  _______,  _______,     _______,  _______,  _______,  _______,  _______,  _______, \
  _______,  _______,  _______,  _______,  _______,  _______,     _______,  _______,  _______,  _______,  _______,  _______  \
),

/* Arrow layer
 * ,-----------------------------------------.   .-----------------------------------------.
 * |  §/½ |      |      |      |      |      |   |      |      |      | Ins  | Home | PgUp |
 * |------+------+------+------+------+------+   +------+------+------+------+------+------|
 * |      |      |  Up  |      |      |      |   |      |      |      | Del  | End  | PgDn |
 * |------+------+------+------+------+------|   |------+------+------+------+------+------|
 * |      | Left | Down | Right|      | Back |   |  Fwd |      |      |      |      |      |
 * |------+------+------+------+------+------|   |------+------+------+------+------+------|
 * |      |      |      |      |      |      |   |      |      |      |      |      |      |
 * |------+------+------+------+------+------+   +------+------+------+------+------+------|
 * |      |      |      |  Del |      |      |   |      |      |      |      |      |      |
 * `-----------------------------------------'   '-----------------------------------------'
 */
[ARRW] = LAYOUT( \
  SE_HALF,  _______,  _______,  _______ ,  _______,  _______,     _______,  _______,  _______,  KC_INS ,  KC_HOME,  KC_PGUP, \
  _______,  _______,  KC_UP  ,  _______ ,  _______,  _______,     _______,  _______,  _______,  KC_DEL ,  KC_END ,  KC_PGDN, \
  _______,  KC_LEFT,  KC_DOWN,  KC_RIGHT,  _______,  KC_WBAK,     KC_WFWD,  _______,  _______,  _______,  _______,  _______, \
  _______,  _______,  _______,  _______ ,  _______,  _______,     _______,  _______,  _______,  _______,  _______,  _______, \
  _______,  _______,  _______,  KC_DEL  ,  _______,  _______,     _______,  _______,  _______,  _______,  _______,  _______  \
),

/* Adjust ()
 * ,-----------------------------------------.   .-----------------------------------------.
 * |      |      |      |      |      |      |   |      |      |      |      |      |      |
 * |------+------+------+------+------+------+   +------+------+------+------+------+------|
 * |      | Reset|RGB Tg|RGB Md|Hue Up|Hue Dn|   |Sat Up|Sat Dn|Val Up|Val Dn|      |      |
 * |------+------+------+------+------+------+   +------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|   |AGswap|Qwerty|Colemk|Dvorak|      |      |
 * |------+------+------+------+------+------|   |------+------+------+------+------+------|
 * |      |      |      |      |      |      |   |      |      |      |      |      |      |
 * |------+------+------+------+------+------+   +------+------+------+------+------+------|
 * |      |      |      |      |      |      |   |      |      |      |      |      |      |
 * `-----------------------------------------'   '-----------------------------------------'
 */
[_ADJUST] =  LAYOUT( \
  _______,  _______,  _______,  _______,  _______,  _______,     _______,  _______,  _______,  _______,  _______,  _______, \
  _______,  RESET  ,  RGB_TOG,  RGB_MOD,  RGB_HUD,  RGB_HUI,     RGB_SAD,  RGB_SAI,  RGB_VAD,  RGB_VAI,  _______,  _______, \
  _______,  _______,  _______,  AU_ON,    AU_OFF,   AG_NORM,     AG_SWAP,  QWERTY,   COLEMAK,  DVORAK,   _______,  _______, \
  _______,  _______,  _______,  _______,  _______,  _______,     _______,  _______,  _______,  _______,  _______,  _______, \
  _______,  _______,  _______,  _______,  _______,  _______,     _______,  _______,  _______,  _______,  _______,  _______  \
)

};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}
