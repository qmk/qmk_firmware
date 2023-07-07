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
        KC_A,    KC_B,    KC_C,   KC_D,
        KC_NO,   KC_NO,   KC_NO,  KC_NO // for encoders
    ),
    [_FN1] = LAYOUT(
        KC_NO,   KC_NO,   KC_NO,  KC_NO,
        KC_NO,   KC_NO,   KC_NO,  KC_NO
    ),
    [_FN2] = LAYOUT(
        KC_NO,   KC_NO,   KC_NO,  KC_NO,
        KC_NO,   KC_NO,   KC_NO,  KC_NO
    ),
    [_FN3] = LAYOUT(
        KC_NO,   KC_NO,   KC_NO,  KC_NO,
        KC_NO,   KC_NO,   KC_NO,  KC_NO
    )
};

keyevent_t encoder1_ccw = {
    .key = (keypos_t){.row = 0, .col = 4},
    .pressed = false,
    .type = KEY_EVENT
};

keyevent_t encoder1_cw = {
    .key = (keypos_t){.row = 0, .col = 5},
    .pressed = false,
    .type = KEY_EVENT
};

keyevent_t encoder2_ccw = {
    .key = (keypos_t){.row = 0, .col = 6},
    .pressed = false,
    .type = KEY_EVENT
};

keyevent_t encoder2_cw = {
    .key = (keypos_t){.row = 0, .col = 7},
    .pressed = false,
    .type = KEY_EVENT
};

void matrix_scan_user(void) {
    if (encoder1_ccw.pressed) {
        encoder1_ccw.pressed = false;
        encoder1_ccw.time = timer_read();
        action_exec(encoder1_ccw);
    }

    if (encoder1_cw.pressed) {
        encoder1_cw.pressed = false;
        encoder1_cw.time = timer_read();
        action_exec(encoder1_cw);
    }

    if (encoder2_ccw.pressed) {
        encoder2_ccw.pressed = false;
        encoder2_ccw.time = timer_read();
        action_exec(encoder2_ccw);
    }

    if (encoder2_cw.pressed) {
        encoder2_cw.pressed = false;
        encoder2_cw.time = timer_read();
        action_exec(encoder2_cw);
    }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            encoder1_cw.pressed = true;
            encoder1_cw.time = timer_read();
            action_exec(encoder1_cw);
        } else {
            encoder1_ccw.pressed = true;
            encoder1_ccw.time = timer_read();
            action_exec(encoder1_ccw);
        }
    } else if (index == 1) {
        if (clockwise) {
            encoder2_cw.pressed = true;
            encoder2_cw.time = timer_read();
            action_exec(encoder2_cw);
        } else {
            encoder2_ccw.pressed = true;
            encoder2_ccw.time = timer_read();
            action_exec(encoder2_ccw);
        }
    }

    return true;
}
