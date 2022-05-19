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
    KC_MUTE,  MO(_FN3), MO(_FN2), MO(_FN1),       LGUI(KC_D),    
    KC_HOME,                                      KC_PGUP,    
    KC_END,                                       KC_PGDN,    
    KC_BTN3,  KC_BTN1, KC_BTN2, KC_BTN2, KC_BTN1, DPI_FINE
    ),
    [_FN1] = LAYOUT(                                                                                   
    RGB_TOG, KC_TRNS, KC_TRNS, KC_TRNS,          RESET, 
    KC_TRNS,                                     DPI_UP, 
    KC_TRNS,                                     DPI_DN, 
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
