// Copyright 2022 Kyle McCreery (@kylemccreery)
// SPDX-License-Identifier: GPL-2.0-or-later
 
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
 *   /-------------------\
 *   |ENC| 1 | 2 | 3 |ENC| 
 *   |---+---'---'---+---|
 *   | 4 |           | 5 |
 *   |---|           |---|
 *   | 6 |           | 7 |
 *   |---|           |---|
 *   | 8 |           | 9 |
 *   \-----,---,---,-----/
 *     | A | B | C | D |
 *     \---'---'---'---/
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
