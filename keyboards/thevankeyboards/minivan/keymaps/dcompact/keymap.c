/* Copyright 2020 Dan Herrera
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
#include "keymap_steno.h"

// Custom Keycodes and Combinations Used
#define DEL_SHF SFT_T(KC_DEL)
#define SPC_ALT LALT_T(KC_SPC)
#define QUAKE LCTL(KC_GRV)

#define WKSP_L LALT(LCTL(KC_LEFT))
#define WKSP_D LALT(LCTL(KC_DOWN))
#define WKSP_U LALT(LCTL(KC_UP))
#define WKSP_R LALT(LCTL(KC_RGHT))

#define AM_CYC A(S(KC_SPC))
#define AM_SHR A(S(KC_COMM))
#define AM_GRW A(S(KC_DOT))
#define AM_REL A(S(KC_Z))
#define AM_LFT A(S(KC_H))
#define AM_RGH A(S(KC_L))
#define AM_CW A(S(KC_K))
#define AM_CCW A(S(KC_J))
#define AM_TLL A(S(KC_1))
#define AM_TLW A(S(KC_2))
#define AM_BSP A(S(KC_3))
#define AM_FUL A(S(KC_4))



enum layers {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT(
    KC_TAB, KC_QUOT, KC_COMM,  KC_DOT,    KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L, KC_SLSH,
    KC_ESC,    KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S, KC_MINS,
   DEL_SHF, KC_SCLN,    KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z, KC_BSPC,
   KC_LCTL, KC_LGUI,   LOWER,                   KC_LSFT, SPC_ALT,                     RAISE, KC_RGUI, KC_ENT
),

[_LOWER] = LAYOUT(
   XXXXXXX,  AM_CYC,  AM_SHR,  AM_GRW,  AM_REL, XXXXXXX, XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, XXXXXXX,
   XXXXXXX,  AM_LFT,  AM_CCW,   AM_CW,  AM_RGH, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX,
   XXXXXXX,  AM_TLL,  AM_TLW,  AM_BSP,  AM_FUL, XXXXXXX, XXXXXXX,  WKSP_L,  WKSP_D,  WKSP_U,  WKSP_R, XXXXXXX,
   _______, XXXXXXX, _______,                   _______, XXXXXXX,                   _______, _______, XXXXXXX
),

[_RAISE] = LAYOUT(
     QUAKE,  KC_GRV, KC_TILD, KC_BSLS, KC_PIPE, KC_LPRN, KC_RPRN,    KC_7,    KC_8,    KC_9, KC_SLSH,  KC_EQL,
   XXXXXXX, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_LCBR, KC_RCBR,    KC_4,    KC_5,    KC_6, KC_ASTR, KC_PLUS,
   XXXXXXX, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LBRC, KC_RBRC,    KC_1,    KC_2,    KC_3, KC_MINS, KC_BSPC,
   _______, XXXXXXX, _______,                   KC_LABK, KC_RABK,                   _______,    KC_0, XXXXXXX
),

[_ADJUST] = LAYOUT(
     QK_BOOT, KC_SLEP, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX,   KC_F9,  KC_F10,  KC_F11,  KC_F12, XXXXXXX,
   XXXXXXX, KC_WAKE, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX, XXXXXXX,   KC_F5,   KC_F6,   KC_F7,   KC_F8, XXXXXXX,
   XXXXXXX,  KC_PWR, KC_MRWD, KC_MPLY, KC_MFFD, XXXXXXX, XXXXXXX,   KC_F1,   KC_F2,   KC_F3,   KC_F4, XXXXXXX,
   _______, _______, _______,                   XXXXXXX, XXXXXXX,                   _______, _______, XXXXXXX
),
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
