/* Copyright 2021 JasonRen(biu)
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
    LAYOUT(
    KC_ESC,  KC_1,    KC_2,       KC_3,    KC_4,    KC_5,    KC_6,
    KC_TAB,  KC_Q,    KC_W,       KC_E,    KC_R,    KC_T,    KC_Y,
    KC_CAPS, KC_A,    KC_S,       KC_D,    KC_F,    KC_G,    KC_H,
    RGB_TOG, KC_Z,    KC_X,       KC_C,    KC_V,    MO(1),    KC_RSFT),
    LAYOUT(
    KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,    KC_SPACE,KC_TRNS, KC_TRNS, KC_TRNS)
};


// void keyboard_post_init_user(void) {
//     eeconfig_init();
//     // Customise these values to desired behaviour
//     // debug_enable=true;
//     // debug_matrix=false;
//     // debug_keyboard=true;
//     //debug_mouse=true;
// }

