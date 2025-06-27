/* Copyright 2025 maxgpdx
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
    /* 
    **                       | F13 | F14 | F15 | F16 |  | F17 | F18 | F19 | F20 |  | F21 | F22 | F23 | F24 |
    **                       | F1  | F2  | F3  | F4  |  | F5  | F6  | F7  | F8  |  | F9  | F10 | F11 | F12 |
    ** 
    ** |  M1  |  M2  |    | ESC |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |  ~  |  BS  |    | INS | HOM | PGU |    | NML |  /  |  ,  |  -  | 
    ** |  M3  |  M4  |    |  TAB   |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |  ENT    |    | DEL | END | PGD |    |  7  |  8  |  9  |  +  | 
    ** |  M5  |  M6  |    |  CAPS   |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |  \  |        |          | UP  |          |  4  |  5  |  6  |     | 
    ** |  M7  |  M8  |    |  SHIFT    |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |  j  |    SHIFT   |    | LEF | MID | RIG |    |  1  |  2  |  3  | ENT | 
    ** |  M9  |  M10 |    | CTRL   |  |  ALT   |   SPACE   |    BS     |   SPACE   |  ALT   |               |  CTRL  |          | DWN |          |     0     |  .  |     | 
    */
    [0] = LAYOUT(
        
        KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, KC_F21, KC_F22, KC_F23, KC_F24, \
        KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, \
        PB_1, PB_2, PB_3, PB_4, PB_5, PB_6, PB_7, PB_8, PB_9, PB_10, \
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_GRV, KC_BSPC, \
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_ENT, \
        KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_BSLS, \
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_NO, KC_RSFT, \
        KC_LCTL, KC_LALT, KC_SPC, KC_BSPC, KC_SPC, KC_RALT, KC_RCTL, \
        KC_INS, KC_DEL, KC_HOME, KC_END, KC_PGUP, KC_PGDN, \
        KC_UP, KC_LEFT, KC_DOWN, KC_RGHT, KC_DOWN, \
        KC_NUM, KC_PSLS, KC_PCMM, KC_PMNS, KC_PPLS, KC_PENT, KC_PDOT, KC_P0, KC_P1, KC_P2, KC_P3, KC_P4, KC_P5, KC_P6, KC_P7, KC_P8, KC_P9

    )
};
