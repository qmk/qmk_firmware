/* Copyright 2023 Logan Butler*/
/* SPDX-License-Identifier: GPL-2.0-or-later */

#include QMK_KEYBOARD_H

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT_reverse(
        KC_BSPC, KC_EQL,  LSFT(KC_9),LSFT(KC_0),
        KC_PMNS, KC_PAST, KC_PSLS, TG(1),
        KC_PPLS, KC_P7,   KC_P8,   KC_P9,
                 KC_P4,   KC_P5,   KC_P6,
        KC_PENT, KC_P1,   KC_P2,   KC_P3,
                 KC_PDOT,          KC_P0
    ),

    [1] = LAYOUT_reverse(
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, KC_PGUP, KC_UP,   KC_HOME,
                 KC_LEFT, _______, KC_RGHT,
        _______, KC_PGDN, KC_DOWN, KC_END,
                 KC_DEL,           KC_INS
    ),
};