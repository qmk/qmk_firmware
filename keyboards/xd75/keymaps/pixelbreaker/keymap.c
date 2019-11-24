/* Copyright 2017 Wunder
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

// Layer shorthand
#define _QWERTY 0
#define _SYMB 1
#define _NAV 2
#define _FN 3
#define _TOGGLE 4
#define _GAMING 5
#define _LOCK 6
#define _UNLOCK 7
#define _RESET 8

// Nicer keycode alias for keymap readability
#define x KC_NO // No action
#define ___ KC_TRNS // Pass through
#define L_SYMB LT(_SYMB,KC_CAPSLOCK)
#define L_NAV LT(_NAV,KC_TAB)
#define L_TOGGLE LT(_TOGGLE,KC_HOME)
#define L_GAMING TG(_GAMING)
#define L_LOCK TO(_LOCK)
#define L_UNLOCK TO(_QWERTY)
#define HYP_MINS ALL_T(KC_MINS)
#define MEH_PLUS MEH_T(KC_PPLS)
#define CUT LGUI(KC_X)
#define COPY LGUI(KC_C)
#define PASTE LGUI(KC_V)
#define UNDO LGUI(KC_Z)
#define REDO LSFT(LGUI(KC_Z))

// VSCODE keys
#define CONSOLE LCTL(KC_C)
#define DEL_LINE MEH(KC_K)
#define LINE_DOWN LALT(KC_DOWN)
#define LINE_UP LALT(KC_UP)
#define PANE_1 LGUI(KC_1)
#define PANE_2 LGUI(KC_2)
#define PANE_3 LGUI(KC_3)
#define SORT_LINES KC_F5

// Gaming
#define SCRSHT MEH(KC_PSCR)
#define STATS MEH(KC_8)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_ortho_5x15(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS, KC_GRV,  KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    L_NAV,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC, KC_BSLS, KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_GRV,
    L_SYMB, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_PGDN, KC_DEL,  KC_PGUP, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    L_TOGGLE,  KC_UP,   KC_END, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
    KC_LCTL, KC_LALT, KC_LGUI, MO(_FN), KC_SPC,  KC_SPC,  KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC,  KC_BSPC,  L_NAV, KC_MEH, KC_HYPR, KC_RCTL
  ),

  [_SYMB] = LAYOUT_ortho_5x15(
    ___,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,    ___,    ___,    ___,    KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    ___,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    KC_EXLM, KC_LPRN, KC_RPRN, KC_DLR,  KC_PERC, KC_F12,
    ___,    ___,    PANE_1,  PANE_2,  PANE_3,    ___,    ___,    ___,    ___, KC_PIPE, KC_LCBR, KC_RCBR, KC_EQL,  KC_COLN, KC_DQUO,
    ___,    ___,    CUT,    COPY,   PASTE,    ___,    ___,    ___,    ___,    KC_AMPR,KC_LT,   KC_GT,   KC_MINS, KC_SLSH, KC_GRV,
    ___,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    DEL_LINE,    DEL_LINE,    ___,    ___,    ___,    ___
  ),

  [_FN] = LAYOUT_ortho_5x15(
    RGB_TOG,    RGB_RMOD,    RGB_MOD,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    KC_MRWD, KC_MPLY, KC_MFFD, KC__MUTE,KC_VOLU,
    ___,    ___,    ___,    KC_WH_U,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    KC_UP,  ___,      ___,       KC_VOLD,
    ___,    ___,    KC_WH_L, KC_WH_D, KC_WH_R,    ___,    ___,    ___,    ___,    ___,    KC_LEFT, KC_DOWN, KC_RGHT, ___,       KC_MPLY,
    ___,    ___,    ___,    ___,    ___,    ___,    KC_BTN1,    KC_MS_U,    KC_BTN2,    ___,    LALT(KC_LEFT),___,    LALT(KC_RGHT),    ___,    ___,
    ___,    ___,    ___,    ___,    ___,    ___,    KC_MS_L, KC_MS_D, KC_MS_R,    KC_DEL,    KC_DEL,    ___,    ___,    ___,    ___
  ),

  [_TOGGLE] = LAYOUT_ortho_5x15(
    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    L_LOCK,
    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,
    x,    x,    x,    x,    x,    L_GAMING,    x,    x,    x,    x,    x,    x,    x,    x,    x,
    x,    x,    x,    x,    x,    x,    ___,    x,    MO(_RESET),    x,    x,    x,    x,    x,    x,
    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x
  ),

  [_GAMING] = LAYOUT_ortho_5x15(
    ___,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    STATS,    SCRSHT,    KC_VOLU,
    KC_TAB,    ___,    ___,    ___,    ___,    ___,    KC_Y,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    KC_VOLD,
    KC_CAPS,    ___,    ___,    ___,    ___,    ___,    KC_H,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    ___,
    KC_LSFT,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    KC_ENT,
    ___,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    ___
  ),

  [_LOCK] = LAYOUT_ortho_5x15(
    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,
    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,
    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,
    x,    x,    x,    x,    x,    x,    MO(_UNLOCK),    x,    x,    x,    x,    x,    x,    x,    x,
    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x
  ),

  [_UNLOCK] = LAYOUT_ortho_5x15(
    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    L_UNLOCK,
    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,
    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,
    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,
    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x
  ),

  [_RESET] = LAYOUT_ortho_5x15(
    RESET,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,
    DEBUG,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,
    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,
    x,    x,    x,    x,    x,    x,    ___,    x,    ___,    x,    x,    x,    x,    x,    x,
    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x,    x
  ),

  [_NAV] = LAYOUT_ortho_5x15(
    ___,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    KC_MRWD, KC_MPLY, KC_MFFD, KC__MUTE,KC_VOLU,
    ___,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    KC_UP,   ___,       ___,       KC_VOLD,
    ___,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    KC_LEFT, KC_DOWN, KC_RGHT, ___,       KC_MPLY,
    ___,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    LALT(KC_LEFT),___,    LALT(KC_RGHT),___,   ___,
    ___,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    ___,    ___
  )
};

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//   switch (keycode) {
//     case QMKBEST:
//       if (record->event.pressed) {
//         // when keycode QMKBEST is pressed
//         SEND_STRING("QMK is the best thing ever!");
//       } else {
//         // when keycode QMKBEST is released
//       }
//       break;
//     case QMKURL:
//       if (record->event.pressed) {
//         // when keycode QMKURL is pressed
//         SEND_STRING("https://qmk.fm/" SS_TAP(X_ENTER));
//       } else {
//         // when keycode QMKURL is released
//       }
//       break;
//   }
//   return true;
// }

// void matrix_init_user(void) {

// }

// void matrix_scan_user(void) {

// }

// void led_set_user(uint8_t usb_led) {

// }
