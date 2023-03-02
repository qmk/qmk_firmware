/*pteron56
*Copyright (C) 2023 @kraken-jokes
*
*This program is free software: you can redistribute it and/or modify
*it under the terms of the GNU General Public License as published by
*the Free Software Foundation, either version 3 of the License, or
*(at your option) any later version.
*
*This program is distributed in the hope that it will be useful,
*but WITHOUT ANY WARRANTY; without even the implied warranty of
*IMERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*GNU General Public License for more details.
*
*You should have received a copy of the GNU General Public License
*along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "pteron56.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, 
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_EQL, 
        KC_BSPC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, 
        KC_SPC, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_ENT, 
        LT(1,KC_LGUI), KC_LCTL, KC_LSFT, LT(2,KC_LALT), LT(1,KC_DEL), KC_SPC, LT(2,KC_APP), KC_TAB),

    [1] = LAYOUT(
        KC_GRV, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, 
        KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, 
        KC_VOLU, KC_HOME, KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_U, KC_PGUP, KC_UP, KC_PGDN, KC_MENU, KC_RBRC, KC_TRNS, 
        KC_VOLD, KC_END,  KC_MS_L, KC_MS_D,  KC_MS_R, KC_WH_D, KC_LEFT, KC_DOWN, KC_RGHT, KC_LBRC, KC_BSLS, KC_TRNS, 
        KC_TRNS, KC_LCTL, KC_LSFT, KC_LALT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS ),

    [2] = LAYOUT(
        RESET, KC_SLEP, KC_WAKE, KC_TRNS, KC_PWR, KC_TRNS, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC, 
        KC_DEL, RGB_HUI, RGB_SAI, RGB_VAI, RGB_MOD, KC_TRNS, KC_TRNS, KC_TRNS, KC_MSEL, KC_MYCM, KC_PSLS, KC_PAST, 
        RGB_TOG, RGB_HUD, RGB_SAD, RGB_VAD, RGB_RMOD, RGB_M_P, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_LSFT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PDOT),

};

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}
