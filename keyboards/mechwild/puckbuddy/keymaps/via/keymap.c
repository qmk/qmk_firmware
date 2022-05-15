/* Copyright 2021 Kyle McCreery
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
 
//void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  //debug_enable=true;
  //debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
//}

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN1,
    _FN2,
    _FN3
};
/*
    k00, k01, k02, k03,      k05,\
    k10,                     k15,\
    k20,                     k25,\
    k30, k31, k32, k33, k34, k35 \
*/
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
    KC_1,    KC_2,    KC_3,    RESET,            KC_5,    
    KC_6,                                       KC_7,    
    KC_8,                                       KC_9,    
    KC_0,    KC_Q,    KC_W,    KC_E,    KC_R,   KC_T
    ),
    [_FN1] = LAYOUT(                                                                                   
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, 
    KC_TRNS,                                     KC_TRNS, 
    KC_TRNS,                                     KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [_FN2] = LAYOUT(                                                                                   
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, 
    KC_TRNS,                                     KC_TRNS, 
    KC_TRNS,                                     KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [_FN3] = LAYOUT(                                                                                   
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, 
    KC_TRNS,                                     KC_TRNS, 
    KC_TRNS,                                     KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
};
