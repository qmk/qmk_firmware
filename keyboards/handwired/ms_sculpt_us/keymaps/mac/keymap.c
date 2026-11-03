/* Copyright 2026 Winston Burbank (@winstonburbank)
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

enum layers {
    _BASE,
    _FKEYS,
    _MOUSE_LOCK,
    _MOUSE
};

// Shared by _MOUSE (held with Tab) and _MOUSE_LOCK (stays on until Esc).
// Only the Q position differs between them.
#define MOUSE_LAYOUT(q_key) LAYOUT( \
    TO(_BASE),           KC_TRNS,    KC_TRNS,    KC_TRNS,  KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
    KC_TRNS,             KC_TRNS,    KC_TRNS,    KC_TRNS,  KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, \
    KC_TRNS,             q_key,      KC_NO,      MS_ACL2,  KC_NO,        KC_NO,   KC_NO,   MS_WHLD, MS_UP,   KC_NO,   KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, \
    KC_TRNS,             KC_NO,      KC_LSFT,    MS_ACL1,  KC_NO,        KC_NO,   MS_WHLL, MS_LEFT, MS_DOWN, MS_RGHT, MS_WHLR, KC_NO,   KC_TRNS,                            KC_TRNS, KC_TRNS, \
    KC_TRNS,             KC_NO,      KC_NO,      MS_ACL0,  KC_NO,        KC_NO,   KC_NO,   MS_WHLU, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                     KC_TRNS, KC_TRNS, \
    KC_TRNS,             KC_TRNS,    KC_TRNS,              MS_BTN2,      MS_BTN1,          MS_BTN3, KC_TRNS, KC_TRNS,                                              KC_TRNS, KC_TRNS, KC_TRNS \
)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(  // Play on Right side
    KC_ESC,               KC_MPLY,   KC_MUTE,    KC_VOLD,  KC_VOLU,      KC_MPRV, KC_MNXT, KC_BRID, KC_BRIU, KC_MPLY, KC_MUTE, KC_VOLD, KC_VOLU, LGUI(LSFT(KC_4)), KC_NO, KC_NO, KC_MCTL,
    LT(_FKEYS, KC_GRV),   KC_1,      KC_2,       KC_3,     KC_4,         KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,                    KC_BSPC,  KC_DEL,  KC_HOME,
    LT(_MOUSE, KC_TAB),   KC_Q,      KC_W,       KC_E,     KC_R,         KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,                             KC_END,
    KC_CAPS,              KC_A,      KC_S,       KC_D,     KC_F,         KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,                               LGUI(KC_SPC), KC_PGUP,
    KC_LSFT,              KC_Z,      KC_X,       KC_C,     KC_V,         KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                                               KC_UP,   KC_PGDN,
    KC_LCTL,              KC_LOPT,   KC_LCMD,              KC_SPC,       KC_SPC,           KC_RCMD, KC_ROPT, KC_RCTL,                                              KC_LEFT,  KC_DOWN, KC_RGHT
  ),
  [_FKEYS] = LAYOUT(
    KC_ESC,              KC_F1,      KC_F2,      KC_F3,    KC_F4,        KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,             KC_F1,      KC_F2,      KC_F3,    KC_F4,        KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_TRNS, KC_TRNS,                   LGUI(KC_LBRC), KC_TRNS, KC_TRNS,
    KC_TRNS,             KC_NO,      KC_NO,      KC_NO,    LSFT(KC_F11), KC_NO,   KC_NO,   MS_WHLD, KC_UP,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS, KC_TRNS,                            KC_TRNS,
    KC_TRNS,             KC_NO,      LGUI(KC_S), KC_F5,    KC_F10,       KC_NO,   MS_WHLL, KC_LEFT, KC_DOWN, KC_RGHT, MS_WHLR, KC_NO,   KC_TRNS,                            KC_TRNS, KC_TRNS,
    KC_TRNS,             KC_NO,      KC_NO,      KC_NO,    KC_F11,       KC_NO,   KC_NO,   MS_WHLU, KC_NO,   KC_NO,   KC_NO,   KC_TRNS,                                     KC_TRNS, KC_TRNS,
    KC_TRNS,             KC_TRNS,    KC_TRNS,              MS_BTN2,      MS_BTN1,          MS_BTN3, KC_TRNS, KC_TRNS,                                              KC_TRNS, KC_TRNS, KC_TRNS
  ),
  // Below _MOUSE so holding Tab while locked still shows _MOUSE on top
  [_MOUSE_LOCK] = MOUSE_LAYOUT(KC_NO),
  [_MOUSE] = MOUSE_LAYOUT(TO(_MOUSE_LOCK))
};
