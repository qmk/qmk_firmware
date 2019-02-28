/* Copyright 2018 Daisuke Kobayashi
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
#include "keymap_jp.h"

enum {
  _WIN,
  _MACOS,
  _LOWER,
  _RAISE,
  _FUNC
};

#define KC_KNA  KC_LANG1
#define KC_EISU KC_LANG2
#define LOWER   MO(_LOWER)
#define RAISE   MO(_RAISE)
#define FN      MO(_FUNC)
#define WIN     DF(_WIN)
#define MACOS   DF(_MACOS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* WIN
   * ,------------------------------------------------.   ,------------------------------------------------.
   * | Esc  | Del  |   Q  |   W  |   E  |   R  |   T  |   |   Y  |   U  |   I  |   O  |   P  |  @ ` | Bksp |
   * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
   * | Tab  | Ctrl |   A  |   S  |   D  |   F  |   G  |   |   H  |   J  |   K  |   L  |  ; + |  ; * |Enter |
   * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
   * | H/Z  |Shift |   Z  |   X  |   C  |   V  |   B  |   |   N  |   M  |  , < |  . > |  / ? |  Up  |Shift |
   * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
   * |  Fn  | Ctrl | Win  | Alt  | Mhen |LOWER |Space |   |Space |RAISE | Henk | Menu | Left | Down |Right |
   * `------------------------------------------------'   `------------------------------------------------'
   */
  [_WIN] = LAYOUT( \
    KC_ESC,  KC_DELT, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    JP_AT,   KC_BSPC, \
    KC_TAB,  KC_RCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, JP_COLN, KC_ENT,  \
    KC_ZKHK, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,     KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_UP,   KC_RSFT, \
    FN,      KC_LCTL, KC_LGUI, KC_LALT, KC_MHEN, LOWER,   KC_SPC,   KC_SPC,  RAISE,   KC_HENK, KC_APP,  KC_LEFT, KC_DOWN, KC_RGHT  \
  ),

  /* MACOS
   * ,------------------------------------------------.   ,------------------------------------------------.
   * | Esc  | Del  |   Q  |   W  |   E  |   R  |   T  |   |   Y  |   U  |   I  |   O  |   P  |  @ ` | Bksp |
   * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
   * | Tab  | Ctrl |   A  |   S  |   D  |   F  |   G  |   |   H  |   J  |   K  |   L  |  ; + |  ; * |Enter |
   * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
   * | Caps |Shift |   Z  |   X  |   C  |   V  |   B  |   |   N  |   M  |  , < |  . > |  / ? |  Up  |Shift |
   * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
   * |  Fn  | Ctrl | Opt  | Cmd  | Eisu |LOWER |Space |   |Space |RAISE | Kana | Cmd  | Left | Down |Right |
   * `------------------------------------------------'   `------------------------------------------------'
   */
  [_MACOS] = LAYOUT( \
    KC_ESC,  KC_DELT, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    JP_AT,   KC_BSPC, \
    KC_TAB,  KC_RCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, JP_COLN, KC_ENT,  \
    KC_CAPS, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,     KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_UP,   KC_RSFT, \
    FN,      KC_LCTL, KC_LALT, KC_LGUI, KC_EISU, LOWER,   KC_SPC,   KC_SPC,  RAISE,   KC_KNA,  KC_RGUI, KC_LEFT, KC_DOWN, KC_RGHT  \
  ),

  /* LOWER
   * ,------------------------------------------------.   ,------------------------------------------------.
   * |      |      |   !  |   "  |   #  |   $  |   %  |   |   &  |   '  |   (  |   )  |      |   =  |      |
   * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
   * |      |      | XXXX | XXXX | XXXX |   {  |   (  |   |   )  |   }  | XXXX |   ~  |   |  |   _  |      |
   * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
   * |      |      | XXXX | XXXX | XXXX | XXXX | XXXX |   | XXXX | XXXX | XXXX | XXXX | XXXX | PgUp |      |
   * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |   |      |      |      |      | Home | PgDn | End  |
   * `------------------------------------------------'   `------------------------------------------------'
   */
  [_LOWER] = LAYOUT( \
    _______, _______, S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5),  S(KC_6), S(KC_7), S(KC_8), S(KC_9), S(KC_0), JP_EQL,  _______, \
    _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, JP_LCBR, JP_LPRN,  JP_RPRN, JP_RCBR, XXXXXXX, JP_TILD, JP_PIPE, JP_UNDS, _______, \
    _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, _______, \
    _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_END   \
  ),

  /* RAISE
   * ,------------------------------------------------.   ,------------------------------------------------.
   * |      |      |   1  |   2  |   3  |   4  |   5  |   |   6  |   7  |   8  |   9  |   0  |   -  |      |
   * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
   * |      |      | F11  | F12  | XXXX |   [  |   (  |   |   )  |   ]  | XXXX |   ^  |   \  |   \  |      |
   * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
   * |      |      |  F1  |  F2  |  F3  |  F4  |  F5  |   |  F6  |  F7  |  F8  |  F9  | F10  |      |      |
   * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |   |      |      |      |      |      |      |      |
   * `------------------------------------------------'   `------------------------------------------------'
   */
  [_RAISE] = LAYOUT( \
    _______, _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, _______, \
    _______, _______, KC_F11,  KC_F12,  XXXXXXX, JP_LBRC, JP_LPRN,  JP_RPRN, JP_RBRC, XXXXXXX, JP_CIRC, KC_JYEN, KC_RO,   _______, \
    _______, _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,    KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______, _______, \
    _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______  \
  ),

  /* FUNC
   * ,------------------------------------------------.   ,------------------------------------------------.
   * |Reset | Ins  | XXXX | XXXX | XXXX | XXXX | XXXX |   | XXXX | XXXX |PrtSc |SrcLk |Pause | XXXX |      |
   * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
   * |      |      | XXXX | XXXX | XXXX | XXXX | >Win |   |   *  |   /  | Home | PgUp | XXXX | XXXX |      |
   * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
   * | Caps |      | XXXX | XXXX | XXXX | XXXX | >Mac |   |   +  |   -  | End  | PgDn | XXXX | Vol+ |      |
   * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |   |      |      |      |      | Mute | Vol- | Play |
   * `------------------------------------------------'   `------------------------------------------------'
   */
  [_FUNC] = LAYOUT( \
    RESET,   KC_INS,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, KC_PSCR, KC_SLCK, KC_PAUS, XXXXXXX, _______, \
    _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, WIN,      JP_ASTR, KC_SLSH, KC_HOME, KC_PGUP, XXXXXXX, XXXXXXX, _______, \
    KC_CAPS, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MACOS,    JP_PLUS, KC_MINS, KC_END,  KC_PGDN, XXXXXXX, KC_VOLU, _______, \
    _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, KC_MUTE, KC_VOLD, KC_MPLY  \
  )
};

