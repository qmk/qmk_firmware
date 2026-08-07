/* Copyright 2022 Leo Deng (@myst729)
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

#define LCTL_Z      LCTL_T(KC_Z)
#define LGUI_X      LGUI_T(KC_X)
#define LALT_C      LALT_T(KC_C)
#define FN1_V       LT(1, KC_V)
#define FN2_B       LT(2, KC_B)
#define FN3_N       LT(3, KC_N)
#define FN4_M       LT(4, KC_M)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT_ortho_3x10(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_RSFT,
        LCTL_Z,  LGUI_X,  LALT_C,  FN1_V,   FN2_B,   FN3_N,   FN4_M,   KC_SPC,  KC_BSPC, KC_ENT),

    [1] = LAYOUT_ortho_3x10(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_TAB,  _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, KC_SCLN, KC_QUOT, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),

    [2] = LAYOUT_ortho_3x10(
        KC_ESC,  KC_GRV,  _______, _______, KC_PSCR, KC_SCRL, KC_PAUS, _______, KC_UP,   _______,
        KC_CAPS, _______, KC_COMM, KC_DOT,  KC_SLSH, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),

    [3] = LAYOUT_ortho_3x10(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   _______, KC_INS,  KC_HOME, KC_PGUP,
        KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_DEL,  KC_END,  KC_PGDN,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),

    [4] = LAYOUT_ortho_3x10(
        QK_BOOT, KC_BRID, KC_BRIU, _______, RM_TOGG, RM_HUEU, RM_SATU, RM_VALU, RM_SPDU, RM_NEXT,
        KC_MUTE, KC_VOLD, KC_VOLU, _______, RGB_M_B, RM_HUED, RM_SATD, RM_VALD, RM_SPDD, RM_PREV,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______)
};
