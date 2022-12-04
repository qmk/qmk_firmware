/* Copyright 2022 Kyle McCreery
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

#define FN1_BSPC    LT(1, KC_BSPC)
#define FN2_SPC     LT(2, KC_SPC)
#define FN3_B       LT(3, KC_B)
#define CTL_Z       CTL_T(KC_Z)
#define ALT_X       ALT_T(KC_X)
#define ALT_N       ALGR_T(KC_N)
#define CTL_M       RCTL_T(KC_M)
#define SFT_ENT     RSFT_T(KC_ENT)
#define WIN_C       LGUI_T(KC_C)

enum layer_names {
  _BASE,
  _FN1,
  _FN2,
  _FN3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,     KC_Y,    KC_U,     KC_I,    KC_O,    KC_P,    KC_P7,   KC_P8,   KC_P9,   KC_MUTE,
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,     KC_H,    KC_J,     KC_K,    KC_L,    KC_ESC,  KC_P4,   KC_P5,   KC_P6,   KC_P0,
    CTL_Z,   ALT_X,   WIN_C,   KC_V,    FN1_BSPC, FN2_SPC, FN3_B,    ALT_N,   CTL_M,   SFT_ENT, KC_P1,   KC_P2,   KC_P3,   KC_MINS
  ),
  [_FN1] = LAYOUT(
    _______, _______, _______, QK_BOOT, _______,  _______,  KC_PSCR, KC_LBRC, KC_RBRC, KC_BSLS, KC_7,    KC_8,    KC_9,    KC_NLCK,
    _______, _______, _______, _______, _______,  _______,  _______, KC_GRV,  KC_SCLN, KC_QUOT, KC_4,    KC_5,    KC_6,    KC_0,
    _______, _______, _______, _______, _______,  KC_TAB,   KC_LGUI, KC_COMM, KC_DOT,  KC_SLSH, KC_1,    KC_2,    KC_3,    KC_EQL
  ),
  [_FN2] = LAYOUT(
    _______, _______, _______, _______, _______,  _______,  _______, KC_LCBR, KC_RCBR, KC_PIPE, KC_AMPR, KC_ASTR, KC_LPRN, KC_CLCK,
    _______, _______, _______, _______, _______,  _______,  _______, KC_TILD, KC_COLN, KC_DQUO, KC_DLR,  KC_PERC, KC_CIRC, KC_RPRN,
    _______, _______, _______, _______, KC_DEL,   _______,  _______, KC_LABK, KC_RABK, KC_QUES, KC_EXLM, KC_AT,   KC_HASH, KC_PLUS
  ),
  [_FN3] = LAYOUT(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,    KC_F6,    KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, RGB_TOG,
    _______, _______, _______, _______, _______,  _______,  _______, _______, _______, _______, RGB_HUI, RGB_SAI, RGB_VAI, RGB_MOD,
    _______, _______, _______, _______, _______,  _______,  _______, _______, _______, _______, RGB_HUD, RGB_SAD, RGB_VAD, RGB_RMOD
  )

};

#ifdef ENCODER_MAP_ENABLE
    const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
        [_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
        [_FN1]  = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
        [_FN2]  = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
        [_FN3]  = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    };
#endif
