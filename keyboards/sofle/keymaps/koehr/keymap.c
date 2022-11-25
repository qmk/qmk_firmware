 /* Copyright 2020 Josef Adamcik
  * Modification for VIA support and RGB underglow by Jens Bonk-Wiltfang
  * "who-needs-capslock" and further modifications by Norman Köhring
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC/~|   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  [   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | LS/( |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * | LC/( |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  | RS/( |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |LOWER |LCtrl | LAlt |Space | / LGUI  /       \ Enter\  |BckSpc| RAlt |RCtrl | RAISE|
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[0] = LAYOUT(
  QK_GESC,  KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_MINS,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_LBRC,
  KC_LSPO,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,  KC_QUOT,
  KC_LCPO,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE,   KC_HOME, KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSPC,
                   TT(1), KC_LCTL, KC_LALT,  KC_SPC, KC_LGUI,    KC_ENT, KC_BSPC, KC_RALT, KC_RCTL, TT(2)
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC/~|  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  |  =   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  | F11  | F12  | F13  | F14  | F15  |                    | F16  | F17  | F18  | F19  | F20  |   ]  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | LS/( | F21  | F22  | F23  | F24  |      |-------.    ,-------| HOME | PGUP |  UP  | PDWN |   '  |   \  |
 * |------+------+------+------+------+------|  PLAY |    |  END  |------+------+------+------+------+------|
 * | LC/( |      |      |      |      |      |-------|    |-------|  END | LEFT | DOWN | RGHT |   [  |  ]   |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |LOWER |LCtrl | LAlt |Space | / LGUI  /       \ Enter\  |BckSpc| RAlt |RCtrl | RAISE|
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[1] = LAYOUT(
  KC_TRNS,  KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_EQL,
  KC_TRNS,KC_F11, KC_F12,  KC_F13,  KC_F14,  KC_F15,                   KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_RBRC,
  KC_TRNS,KC_F21, KC_F22,  KC_F23,  KC_F24,   KC_NO,                  KC_HOME, KC_PGUP,   KC_UP, KC_PGDN, KC_SCLN,  KC_BSLS,
  KC_TRNS, KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_MPLY,   KC_END,KC_END, KC_LEFT, KC_DOWN, KC_RGHT, KC_LBRC,  KC_RBRC,
                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,  KC_DEL, KC_TRNS, KC_TRNS, KC_NO
),
/* RAISE
 * ,----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |MWLEFT| MUP  |MWRGHT| MWUP |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------| DEBUG |    | RESET |------+------+------+------+------+------|
 * |      |      |MLEFT | MDOWN| MRGHT| MWDWN|-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | / MBTN1 /       \ MBTN2\ |      |      |      | RAISE|
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[2] = LAYOUT(
  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,                  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,                  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
  KC_NO,  KC_NO,KC_WH_L,KC_MS_U,KC_WH_R,KC_WH_U,                  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
  KC_NO,  KC_NO,KC_MS_L,KC_MS_D,KC_MS_R,KC_WH_D, DB_TOGG,QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO,
                  KC_NO,  KC_NO,  KC_NO,  KC_NO,KC_BTN1, KC_BTN2, KC_NO, KC_NO, KC_NO, KC_TRNS
)
};
