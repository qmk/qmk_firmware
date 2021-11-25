/* Copyright 2021 Chonkerkeys
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
#include "virtser.h"
#include "../protocol.c"

#define LAYER_COUNT 2

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
    QMKURL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        QMKBEST,    QMKURL,    KC_D, KC_A,
        QMKBEST,  QMKURL, MO(_FN), KC_B,
        QMKBEST, QMKURL, MO(_FN), KC_C
    ),
    [_FN] = LAYOUT(
        QMKBEST, QMKURL,  _______, KC_G,
            KC_H,    XXXXXXX, KC_A, KC_B,
            KC_C, KC_D, KC_E, KC_F
    )
};

void switch_layer(void) {
    uint16_t current_layer = _BASE;
    for (uint16_t i = _BASE; i < LAYER_COUNT; ++i) {
        if (IS_LAYER_ON(i)) {
            current_layer = i;
            break;
        }
    }
    layer_clear();
    uint16_t next_layer = current_layer + 1;
    if (next_layer >= LAYER_COUNT) {
        next_layer = 0;
    }
    layer_on(next_layer);
}

void virtser_recv(uint8_t c) {
    // Echo back whatever is sent.
    char str[] = {(char)c};
    send_string(str);
    process_protocol(c);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static bool is_either_pressed = false;
    // For some reason, virtser_send isn't working.
    virtser_send('.');
    virtser_send('\n');
    switch (keycode) {
        case KC_A:
            if (record->event.pressed && is_either_pressed) {
                switch_layer();
            }
            is_either_pressed = record->event.pressed;
            break;
        case KC_B:
            if (record->event.pressed && is_either_pressed) {
                switch_layer();
            }
            is_either_pressed = record->event.pressed;
            break;
        case QMKBEST:
            if (record->event.pressed) {
                // when keycode QMKBEST is pressed
                SEND_STRING("QMK is the best thing ever!");
            } else {
                // when keycode QMKBEST is released
            }
            break;
        case QMKURL:
            if (record->event.pressed) {
                // when keycode QMKURL is pressed
                SEND_STRING("https://qmk.fm/\n");
            } else {
                // when keycode QMKURL is released
            }
            break;
    }
    return true;
}
