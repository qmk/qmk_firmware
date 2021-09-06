/* Copyright 2020 foostan
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

// Left-hand home row mods
#define HM_A LALT_T(KC_A)
#define HM_R LCTL_T(KC_R)
#define HM_S LSFT_T(KC_S)
#define HM_T LGUI_T(KC_T)

// Right-hand home row mods
#define HM_N RGUI_T(KC_N)
#define HM_E RSFT_T(KC_E)
#define HM_I RCTL_T(KC_I)
#define HM_O LALT_T(KC_O)

// Genshin layer specialties
#define GSH_TAB MT(KC_TAB, KC_V)
#define GSH_X LALT_T(KC_X)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT(
      KC_TAB, KC_Q,    KC_W,    KC_F,      KC_P,   KC_B,    KC_J,     KC_L,   KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
      KC_ESC, HM_A,    HM_R,    HM_S,      HM_T,   KC_G,    KC_M,     HM_N,   HM_E,    HM_I,    HM_O,    KC_QUOT,
     KC_LSFT, KC_Z,    KC_X,    KC_C,      KC_D,   KC_V,    KC_K,     KC_H,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
     XXXXXXX, KC_LCTL, KC_LGUI, KC_LALT,   MO(1),  KC_SPC,  KC_ENT,   MO(2),  KC_RALT, KC_RGUI, KC_RCTL,   TG(4)
  ),

[1] = LAYOUT(
     _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, XXXXXXX, XXXXXXX,
     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
     _______, _______, _______, _______,   MO(1), _______, _______,   MO(3), _______, _______, _______, _______
  ),

[2] = LAYOUT(
     _______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MINS,  KC_EQL, KC_LCBR, KC_RCBR, KC_PIPE,  KC_GRV,
     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_UNDS, KC_PLUS, KC_LBRC, KC_RBRC, KC_BSLS, KC_TILD,
     _______, _______, _______, _______,   MO(3), _______, _______,   MO(2), _______, _______, _______, _______
  ),

[3] = LAYOUT(
     _______,   RESET, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
     _______, _______, _______, _______,   MO(3), _______, _______,   MO(3), _______, _______, _______, _______
  ),

[4] = LAYOUT(
      KC_TAB, KC_ESC,  KC_Q,    KC_W,      KC_E,   KC_R,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      KC_T,   GSH_TAB, KC_A,    KC_S,      KC_D,   KC_F,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
     KC_LSFT, KC_1,    KC_2,    KC_3,      KC_4,   KC_5,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
     XXXXXXX, KC_LCTL, KC_Z,    KC_Z,      GSH_X,  KC_SPC, _______,   MO(3), _______, _______, _______, _______
  ),
};
