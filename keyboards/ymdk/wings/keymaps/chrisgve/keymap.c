/* Copyright 2021 alittlepeace
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


enum wings_layers {
    _QWERTY,
    _FN,
    _DIR,
    _FULL_DIR
};


#define CPS_CTL         LCTL_T(KC_CAPS)
#define D_DIR           LT(_DIR, KC_D)
#define FN              MO(_FN)
#define F_DIR           MO(_FULL_DIR)
#define F_WORD          A(KC_RIGHT)
#define B_WORD          A(KC_LEFT)
// #define L_MOD           LGUI_T(KC_SPC)
#define R_MOD           RCTL_T(KC_SPC)
#define L_MOD           LT(_FN, KC_SPC)
// #define R_MOD           LT(_FN, KC_SPC)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_all(
    KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, _______, KC_PGUP,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGDN,
    CPS_CTL, KC_A,    KC_S,    D_DIR,   KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,                    FN,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                   KC_UP,
    KC_LCTL,          KC_LGUI, L_MOD,   KC_LALT,          R_MOD,   KC_RGUI,                                              KC_LEFT, KC_DOWN, KC_RGHT
  ),

  [_DIR] = LAYOUT_all(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, F_WORD,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
    _______, _______, _______, _______, F_DIR,   _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, _______,                   _______,
    _______, _______, _______, _______, _______, B_WORD,  _______, _______, _______, _______, _______, _______,          _______,
    _______,          _______, _______, _______,          _______, _______,                                     _______, _______, _______
  ),

  [_FULL_DIR] = LAYOUT_all(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
    _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______, _______,                   _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
    _______,          _______, _______, _______,          _______, _______,                                     _______, _______, _______
  ),

  [_FN] = LAYOUT_all(
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  _______, KC_HOME,
    RESET,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, RGB_SPI, RGB_SPD, _______, _______, _______,          KC_END,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
    _______, _______, _______, _______, _______, _______, _______, KC_MUTE, _______, _______, _______, _______,          KC_VOLU,
    _______,          _______, KC_MPLY, _______,          KC_MPLY, _______,                                     KC_MPRV, KC_VOLD, KC_MNXT
  ),
};
