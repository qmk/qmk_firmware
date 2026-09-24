/* Copyright 2021 Yang Hu
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
#include "layers.h"

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define ADJUST MO(_ADJUST)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_split_3x6_4(
    KC_TAB,         KC_Q, KC_W, KC_E, KC_R, KC_T,    KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_BSPC,
    LCTL_T(KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G,    KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, KC_QUOT,
    KC_LSFT,        KC_Z, KC_X, KC_C, KC_V, KC_B,    KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, RSFT_T(KC_ENT),
                 KC_LCTL, KC_LALT, LOWER, KC_ENT,    KC_BSPC, KC_SPC, RAISE, KC_RGUI
  ),

  [_LOWER] = LAYOUT_split_3x6_4(
    _______,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,    KC_PERC,            KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_DEL,
    _______,  KC_UNDS,  KC_PLUS,  KC_LCBR,  KC_RCBR,   KC_PIPE,            KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_GRV,   KC_TILD,
    _______,  KC_ESC,   KC_LGUI,  KC_LALT,  KC_CAPS,   KC_DQUO,            KC_HOME,  KC_END,   KC_PGUP,  KC_PGDN,  KC_PSCR,  RSFT_T(KC_SPC),
             _______,  _______,   _______,   _______,  _______,   _______,   _______,  _______
  ),

  [_RAISE] = LAYOUT_split_3x6_4(
    _______,  KC_1,     KC_2,     KC_3,     KC_4,      KC_5,               KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_DEL,
    _______,  KC_MINS,  KC_EQL,   KC_LBRC,  KC_RBRC,   KC_BSLS,            KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,
    _______,  KC_ESC,   KC_RGUI,  KC_RALT,  KC_CAPS,   KC_QUOT,            KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,
             _______,  _______,   _______,   _______,  _______,   _______,   _______,  _______
  ),

  [_ADJUST] = LAYOUT_split_3x6_4(
    UG_VALU,   UG_SATU, UG_HUEU,  UG_NEXT,  XXXXXXX,   UG_TOGG,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    UG_VALD,   UG_SATD, UG_HUED,  UG_PREV,  XXXXXXX,   XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,   XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,            QK_BOOT,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
             _______,  _______,   _______,   _______,  _______,   _______,   _______,  _______
  ),
};
// clang-format on
layer_state_t layer_state_set_user(layer_state_t state) { return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST); }

// Left encoder scrolls the mousewheel. Right encoder adjusts underglow hue.
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
#ifdef MOUSEKEY_ENABLE
            tap_code(MS_WHLD);
#else
            tap_code(KC_PGDN);
#endif
        } else {
#ifdef MOUSEKEY_ENABLE
            tap_code(MS_WHLU);
#else
            tap_code(KC_PGUP);
#endif
        }
    } else {  // index = 1: right encoder
        if (clockwise) {
#ifdef RGB_MATRIX_ENABLE
            rgb_matrix_step();
#else
            rgblight_increase_hue_noeeprom();
#endif
        } else {
#ifdef RGB_MATRIX_ENABLE
            rgb_matrix_step_reverse();
#else
            rgblight_decrease_hue_noeeprom();
#endif
        }
    }
    return false;
}

// Set underglow color to blue.
void keyboard_post_init_user(void) { rgblight_sethsv_noeeprom(RGBLIGHT_DEFAULT_COLOR); }
