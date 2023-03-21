/* Copyright 2021 knaruo
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
#include "keymap_japanese.h"

/* keymap layers */
enum _layers {
  _BASE = 0,
  _NUM,
  _FN,
  _RESERVED,  // reserved for VIA
  _END,       // end of supported layers
};

/* Keycode alias */
#define KC_CTBS     RCTL_T(KC_BSPC)     // Backspace + Ctrl
#define KC_XWIN     LWIN_T(KC_X)
#define KC_SPF1     LT(_NUM, KC_SPC)    // Space + NUM layer
#define KC_DLF2     LT(_FN, KC_DEL)     // Del + FN key layer
#define KC_SFEN     RSFT_T(KC_ENT)      // Enter + Shift
#define KC_CAD      LALT(LCTL(KC_DEL))  // ctrl + alt + delete

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Base QWERTY key map */
  [_BASE] = LAYOUT_ortho_3x11(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    /*_____*/ KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    /*_____*/ KC_H,    KC_J,    KC_K,    KC_L,    KC_CTBS,
    KC_LSFT, KC_Z,    KC_XWIN, KC_C,    KC_V,    KC_SPF1, /*_____*/ KC_DLF2, KC_B,    KC_N,    KC_M,    KC_SFEN
  ),

  [_NUM] = LAYOUT_ortho_3x11(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    /*_____*/ KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    _______, KC_TAB,  JP_MINS, JP_CIRC, JP_YEN,  JP_AT,   /*_____*/ JP_SCLN, JP_COLN, JP_LBRC, JP_RBRC, _______,
    _______, _______, JP_ZKHK, KC_LALT, JP_COMM, _______, /*_____*/ _______, JP_DOT,  JP_SLSH, JP_BSLS, _______
  ),

  [_FN] = LAYOUT_ortho_3x11(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   /*_____*/ KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
    _______, KC_F11,  KC_F12,  _______, _______, _______, /*_____*/ KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_CAD,
    _______, _______, _______, _______, _______, _______, /*_____*/ _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
  ),

  [_RESERVED] = LAYOUT_ortho_3x11(
    _______, _______, _______, _______, _______, _______, /*_____*/ _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, /*_____*/ _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, /*_____*/ _______, _______, _______, _______, _______
  ),
};
