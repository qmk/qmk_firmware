/* Copyright 2021 Klesh Wong
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {[0] = LAYOUT_plack_2x2u(LGUI_T(KC_TAB), KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, RGUI_T(KC_BSPC), LCTL_T(KC_GRV), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, RCTL_T(KC_ENT), LSFT_T(KC_LBRC), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, RSFT_T(KC_RBRC), LCTL_T(KC_LEFT), LGUI_T(KC_DOWN), LALT_T(KC_BSLS), LT(1, KC_MINS), LT(3, KC_ESC), KC_SPC, LT(2, KC_EQL), RALT_T(KC_QUOT), RGUI_T(KC_UP), RCTL_T(KC_RGHT)),
                                                              [1] = LAYOUT_plack_2x2u(KC_TRNS, KC_PIPE, KC_LT, KC_GT, KC_LCBR, KC_RCBR, KC_DOT, KC_7, KC_8, KC_9, KC_TRNS, KC_TRNS, KC_TRNS, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PMNS, KC_4, KC_5, KC_6, KC_PPLS, KC_TRNS, KC_TRNS, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_PAST, KC_1, KC_2, KC_3, KC_PSLS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_0, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
                                                              [2] = LAYOUT_plack_2x2u(KC_TRNS, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, BL_TOGG, BL_STEP, BL_BRTG, BL_DEC, BL_INC, KC_TRNS, KC_TRNS, KC_F5, KC_F6, KC_F7, KC_F8, KC_TRNS, RGB_TOG, RGB_RMOD, RGB_MOD, RGB_VAD, RGB_VAI, KC_TRNS, KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
                                                              [3] = LAYOUT_plack_2x2u(KC_TRNS, LALT(KC_F4), KC_TRNS, KC_END, KC_TRNS, KC_TRNS, KC_WBAK, LCTL(KC_PGUP), LCTL(KC_PGDN), KC_WFWD, KC_MPRV, KC_TRNS, KC_TRNS, KC_HOME, KC_TRNS, KC_DEL, KC_RGHT, KC_TRNS, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPLY, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_CAPS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)};
