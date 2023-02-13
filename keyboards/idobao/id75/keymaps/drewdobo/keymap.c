/* Copyright 2020 Drew Smathers
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

// Keyboard Layers
enum layer_names {
    _QW,
    _QW_MAC,
    _FN,
    _MOUSE,
};

// Some short-cut aliases
#define Z_LALT LALT_T(KC_ESC)
#define Z_MAC DF(_QW_MAC)
#define Z_PC DF(_QW)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 [_QW] = LAYOUT_ortho_5x15( /* QWERTY */
    KC_ESC,  KC_1,     KC_2,    KC_3,       KC_4,    KC_5,    XXXXXXX, XXXXXXX, XXXXXXX, KC_6,   KC_7,     KC_8,     KC_9,    KC_0,    KC_BSLS, \
    KC_TAB,  KC_Q,     KC_W,    KC_E,       KC_R,    KC_T,    XXXXXXX, XXXXXXX, XXXXXXX, KC_Y,   KC_U,     KC_I,     KC_O,    KC_P,    KC_QUOT, \
    Z_LALT,  KC_A,     KC_S,    KC_D,       KC_F,    KC_G,    XXXXXXX, XXXXXXX, XXXXXXX, KC_H,   KC_J,     KC_K,     KC_L,    KC_SCLN, KC_RALT,  \
    KC_LSFT, KC_Z,     KC_X,    KC_C,       KC_V,    KC_B,    KC_LCTL, XXXXXXX, KC_RCTL, KC_N,   KC_M,     KC_COMM,  KC_DOT,  KC_SLSH, KC_RSFT, \
    TT(_FN), XXXXXXX,  XXXXXXX, TT(_MOUSE), KC_EQL,  KC_BSPC, KC_DEL,  XXXXXXX, KC_ENT,  KC_SPC, KC_MINUS, KC_GRAVE, KC_LBRC, KC_RBRC, XXXXXXX \
 ),
 
 [_QW_MAC] = LAYOUT_ortho_5x15( /* QWERTY MAC */
    KC_ESC,  KC_1,     KC_2,    KC_3,       KC_4,    KC_5,    KC_BRMU, KC_MUTE, KC_VOLU,     KC_6,   KC_7,     KC_8,     KC_9,    KC_0,    KC_BSLS, \
    KC_TAB,  KC_Q,     KC_W,    KC_E,       KC_R,    KC_T,    KC_BRMD, XXXXXXX, KC_VOLD,     KC_Y,   KC_U,     KC_I,     KC_O,    KC_P,    KC_QUOT, \
    Z_LALT,  KC_A,     KC_S,    KC_D,       KC_F,    KC_G,    XXXXXXX, XXXXXXX, XXXXXXX,     KC_H,   KC_J,     KC_K,     KC_L,    KC_SCLN, KC_RALT,  \
    KC_LSFT, KC_Z,     KC_X,    KC_C,       KC_V,    KC_B,    KC_LCMD, XXXXXXX, KC_RCMD,     KC_N,   KC_M,     KC_COMM,  KC_DOT,  KC_SLSH, KC_RSFT, \
    TT(_FN), KC_LCTL,  XXXXXXX, TT(_MOUSE), KC_EQL,  KC_BSPC, KC_DEL,  XXXXXXX, KC_ENT,      KC_SPC, KC_MINUS, KC_GRAVE, KC_LBRC, KC_RBRC, KC_RCTL  \
 ),

 [_FN] = LAYOUT_ortho_5x15( /* FUNCTION */
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   XXXXXXX, QK_BOOT, XXXXXXX, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGDN, KC_PGUP, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, Z_MAC,   _______, XXXXXXX, KC_HOME, KC_END,  XXXXXXX, XXXXXXX, XXXXXXX, \
    TT(_FN), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, Z_PC,    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX  \
 ),

 [_MOUSE] = LAYOUT_ortho_5x15( /* MOUSE */
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN3, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    TT(_FN), XXXXXXX, XXXXXXX, TT(_MOUSE), XXXXXXX, KC_ACL1, KC_ACL2, XXXXXXX, KC_BTN2, KC_BTN1, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX  \
 )
};
