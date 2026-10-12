/* Copyright 2021 Obosob <obosob@riseup.net>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#define HM_A    LSFT_T(KC_A)
#define HM_S    LT(5,KC_S)
#define HM_D    LT(1,KC_D)
#define HM_F    LT(3,KC_F)

#define HM_J    LT(4,KC_J)
#define HM_K    LT(2,KC_K)
#define HM_L    LT(6,KC_L)
#define HM_SCLN LSFT_T(KC_SCLN)

#define MT_X    LCTL_T(KC_X)
#define MT_C    LALT_T(KC_C)
#define MT_SPC  LT(7,KC_SPC)
#define MT_COMM LALT_T(KC_COMM)
#define MT_DOT  LCTL_T(KC_DOT)

#define CTL_ALT LCTL(KC_LALT)
#define CT_AL_S LCA(KC_LSFT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_split_3x5_2(
KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, 
HM_A,    HM_S,    HM_D,    HM_F,    KC_G,    KC_H,    HM_J,    HM_K,    HM_L,    HM_SCLN, 
KC_Z,    MT_X,    MT_C,    KC_V,    KC_B,    KC_N,    KC_M,    MT_COMM, MT_DOT,  KC_SLSH, 
                           KC_P0,   KC_BSPC, MT_SPC,  KC_P1
                        ),
	[1] = LAYOUT_split_3x5_2(
_______, _______, _______, _______, _______, _______, MS_BTN1, MS_WHLU, MS_BTN2, _______, 
_______, MS_BTN2, XXXXXXX, MS_BTN1, _______, _______, MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT, 
_______, _______, _______, _______, _______, _______, MS_WHLL, MS_WHLD, MS_WHLR, _______, 
                           _______, _______, _______, _______
                        ),
	[2] = LAYOUT_split_3x5_2(
_______, _______, KC_PGUP, _______, _______, _______, _______, _______, _______, _______, 
KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT, _______, _______, KC_LGUI, XXXXXXX, CTL_ALT, CT_AL_S, 
_______, KC_HOME, KC_PGDN, KC_END,  _______, _______, _______, _______, _______, _______, 
                           _______, _______, _______, _______
                        ),
	[3] = LAYOUT_split_3x5_2(
_______, _______, _______, _______, _______, _______, KC_UNDS, KC_PIPE, KC_QUOT, _______, 
KC_CIRC, KC_ASTR, KC_AMPR, XXXXXXX, _______, KC_HASH, KC_TILD, KC_SLSH, KC_DQUO, KC_DLR, 
_______, _______, _______, _______, _______, _______, KC_MINS, KC_BSLS, KC_GRV,  _______, 
                           _______, _______, _______, _______
                    ),
	[4] = LAYOUT_split_3x5_2(
_______, KC_COLN, KC_LT,   KC_GT,   KC_SCLN, _______, _______, _______, _______, _______, 
KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, KC_AT,   _______, XXXXXXX, KC_EQL,  KC_PLUS, KC_PERC, 
_______, KC_EXLM, KC_LBRC, KC_RBRC, _______, _______, _______, _______, _______, _______, 
                           KC_VOLD, _______, _______, KC_VOLU
                        ),
	[5] = LAYOUT_split_3x5_2(
_______, _______, _______, _______, _______, _______, KC_F7,   KC_F8,   KC_F9,   KC_F10, 
_______, XXXXXXX, CTL_ALT, _______, _______, _______, KC_F4,   KC_F5,   KC_F6,   KC_F11, 
_______, _______, _______, _______, _______, _______, KC_F1,   KC_F2,   KC_F3,   KC_F12, 
                           _______, _______, _______, _______
                        ),
	[6] = LAYOUT_split_3x5_2(
KC_PSLS, KC_7,    KC_8,    KC_9,    KC_PPLS, _______, _______, _______, _______, _______, 
KC_0,    KC_1,    KC_2,    KC_3,    KC_PMNS, _______, _______, _______, XXXXXXX, _______, 
KC_PAST, KC_4,    KC_5,    KC_6,    KC_PEQL, _______, _______, _______, _______, _______, 
                           _______, _______, _______, _______
                        ),
#undef  MT_COMM
#define MT_COMM RALT_T(KC_COMM)
#undef  MT_DOT
#define MT_DOT  RCTL_T(KC_DOT)
	[7] = LAYOUT_split_3x5_2(
_______, _______, KC_COLN, KC_ESC,  _______, _______, _______, _______, _______, KC_DEL, 
_______, KC_PERC, KC_SLSH, KC_ENT,  _______, DF(1),   KC_LGUI, _______, _______, _______, 
_______, _______, _______, KC_EXLM, _______, DF(0),   _______, MT_COMM, MT_DOT,  QK_BOOT, 
                           _______, KC_TAB,  XXXXXXX, _______
                    )
};

