// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H


/* Coordinate keymap - designed to send a string in the format [a-r][0-5] corresponding to the matrix position, where a0 is the top left and r5 is bottom right */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT(
        KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,
        KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,
        KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,
        KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,
        KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,
        KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0
    ),
};


/* String generation */

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (record->event.pressed) {
        char col = record->event.key.col + 'a';
        char row = record->event.key.row + '0';
        char result[2] = {col, row};
        send_string(result);
    }

    return false;
}
