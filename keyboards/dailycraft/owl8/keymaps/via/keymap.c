/* Copyright 2021 yfuku
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN1,
    _FN2,
    _FN3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_NO,   KC_NO,   KC_NO,  KC_NO, // for encoders
        KC_NO,   KC_NO,   KC_NO,  KC_NO, // for ext keys
        MO(1),   KC_BSPC, KC_SPC, KC_ENT,
        KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT
    ),
    [_FN1] = LAYOUT(
        KC_NO,   KC_NO,   KC_NO,  KC_NO,
        KC_NO,   KC_NO,   KC_NO,  KC_NO,
        KC_1,    KC_2,    KC_3,   KC_4,
        KC_5,    KC_6,    KC_7,   KC_8
    ),
    [_FN2] = LAYOUT(
        KC_NO,   KC_NO,   KC_NO,  KC_NO,
        KC_NO,   KC_NO,   KC_NO,  KC_NO,
        KC_1,    KC_2,    KC_3,   KC_4,
        KC_5,    KC_6,    KC_7,   KC_8
    ),
    [_FN3] = LAYOUT(
        KC_NO,   KC_NO,   KC_NO,  KC_NO,
        KC_NO,   KC_NO,   KC_NO,  KC_NO,
        KC_1,    KC_2,    KC_3,   KC_4,
        KC_5,    KC_6,    KC_7,   KC_8
    )
};

keyevent_t encoder1_ccw = {
    .key = (keypos_t){.row = 0, .col = 12},
    .pressed = false
};

keyevent_t encoder1_cw = {
    .key = (keypos_t){.row = 0, .col = 13},
    .pressed = false
};

keyevent_t encoder2_ccw = {
    .key = (keypos_t){.row = 0, .col = 14},
    .pressed = false
};

keyevent_t encoder2_cw = {
    .key = (keypos_t){.row = 0, .col = 15},
    .pressed = false
};

void matrix_scan_user(void) {
    if (IS_PRESSED(encoder1_ccw)) {
        encoder1_ccw.pressed = false;
        encoder1_ccw.time = (timer_read() | 1);
        action_exec(encoder1_ccw);
    }

    if (IS_PRESSED(encoder1_cw)) {
        encoder1_cw.pressed = false;
        encoder1_cw.time = (timer_read() | 1);
        action_exec(encoder1_cw);
    }

    if (IS_PRESSED(encoder2_ccw)) {
        encoder2_ccw.pressed = false;
        encoder2_ccw.time = (timer_read() | 1);
        action_exec(encoder2_ccw);
    }

    if (IS_PRESSED(encoder2_cw)) {
        encoder2_cw.pressed = false;
        encoder2_cw.time = (timer_read() | 1);
        action_exec(encoder2_cw);
    }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            encoder1_cw.pressed = true;
            encoder1_cw.time = (timer_read() | 1);
            action_exec(encoder1_cw);
        } else {
            encoder1_ccw.pressed = true;
            encoder1_ccw.time = (timer_read() | 1);
            action_exec(encoder1_ccw);
        }
    } else if (index == 1) {
        if (clockwise) {
            encoder2_cw.pressed = true;
            encoder2_cw.time = (timer_read() | 1);
            action_exec(encoder2_cw);
        } else {
            encoder2_ccw.pressed = true;
            encoder2_ccw.time = (timer_read() | 1);
            action_exec(encoder2_ccw);
        }
    }

    return true;
}
