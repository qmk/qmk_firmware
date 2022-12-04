/* Copyright 2021 Pierre-Emmanuel Ott
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        [0] = LAYOUT(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSLS, KC_GRV, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSPC, KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_LSPO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSPC, LT(2,KC_HOME), LCTL_T(KC_MPRV), LGUI_T(KC_MPLY), LALT_T(KC_MNXT), LT(1,KC_SPC), RALT_T(KC_DEL), KC_APP, RCTL_T(KC_END)),
        [1] = LAYOUT(KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LBRC, KC_UP, KC_RBRC, KC_HOME, KC_PGUP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_END, KC_PGDN, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_CALC, KC_MYCM, KC_PSCR, KC_ENT, KC_BSPC, KC_TRNS, KC_WREF, KC_WBAK, KC_WFWD, KC_WHOM, KC_TRNS, KC_PGUP, KC_TRNS, KC_TRNS, KC_VOLD, KC_TRNS, KC_VOLU, KC_TRNS, KC_PGDN),
        [2] = LAYOUT(RGB_TOG, KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, KC_TRNS, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, KC_TRNS, KC_TRNS, KC_TRNS, QK_BOOT, KC_TRNS, KC_P7, KC_P8, KC_P9, KC_PPLS, KC_TRNS, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, KC_UP, KC_TRNS, KC_TRNS, KC_CAPS, KC_P4, KC_P5, KC_P6, KC_PCMM, KC_TRNS, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_LEFT, KC_RGHT, KC_TRNS, KC_TRNS, KC_P1, KC_P2, KC_P3, KC_PEQL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DOWN, KC_TRNS, KC_TRNS, KC_TRNS, KC_P0, KC_PDOT, KC_PENT, KC_TRNS, KC_TRNS, KC_TRNS)
};
