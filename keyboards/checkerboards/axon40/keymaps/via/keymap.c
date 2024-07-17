/* Copyright 2021 Nathan Spears
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


// Defines for task manager and such
#define CALTDEL LCTL(LALT(KC_DEL))
#define TSKMGR LCTL(LSFT(KC_ESC))


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Ctrl  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc    |  OS   |  Alt  |  Layer  |    Space     |  Alt |  RGB  |   Super  |
 * `-----------------------------------------------------------------------------------'
 */

[0] = LAYOUT(
  KC_TAB,        KC_Q,    KC_W,    KC_F,         KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
  CTL_T(KC_ESC), KC_A,    KC_R,    KC_S,         KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
  KC_LSFT,       KC_Z,    KC_X,    KC_C,         KC_V,    KC_B,    KC_K,    KC_M,     KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
  KC_LGUI,       KC_LALT, TT(1),   LT(2, KC_SPC), KC_RALT, KC_CAPS
),

/* 1
 * ,-----------------------------------------------------------------------------------.
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */

[1] = LAYOUT(
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  KC_SLSH, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PPLS, KC_EQL, _______, _______, _______,
  CALTDEL,  TSKMGR, _______, KC_SPC,  KC_NUBS, KC_GRV
),

/* 2
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  /   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */

[2] = LAYOUT(
  RGB_HUI,  RGB_SAI,  _______,   KC_UP,   _______,  _______,  _______,  KC_UNDS, _______, KC_LBRC, KC_RBRC, RGB_VAI,
  RGB_HUD,  RGB_SAD,   KC_LEFT, KC_DOWN, KC_RGHT,   _______,  _______,  KC_MINS, _______, KC_LCBR, KC_RCBR, RGB_VAD,
  KC_F1,    KC_F2,     KC_F3,   KC_F4,   KC_F5,     KC_F6,    KC_F7,    KC_F8,   KC_F9,   KC_F10,   KC_F11,  KC_F12,
  QK_BOOT,  RGB_TOG,  _______,  _______,  RGB_MOD,  RGB_RMOD
),

/* 2
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  /   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */

[3] = LAYOUT(
  RGB_HUI,  RGB_SAI,  _______,   KC_UP,   _______,  _______,  _______,  KC_UNDS, _______, KC_LBRC, KC_RBRC, RGB_VAI,
  RGB_HUD,  RGB_SAD,   KC_LEFT, KC_DOWN, KC_RGHT,   _______,  _______,  KC_MINS, _______, KC_LCBR, KC_RCBR, RGB_VAD,
  KC_F1,    KC_F2,     KC_F3,   KC_F4,   KC_F5,     KC_F6,    KC_F7,    KC_F8,   KC_F9,   KC_F10,   KC_F11,  KC_F12,
  QK_BOOT,  RGB_TOG,  _______,  _______,  RGB_MOD,  RGB_RMOD
),

};
