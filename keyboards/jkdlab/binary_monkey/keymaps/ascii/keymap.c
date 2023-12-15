/*
 * Copyright 2021 JKDLAB. <jkdlab.co@gmail.com>
 * Copyright 2021 Jaehee <ljh34210329@gmail.com>
 * 
 * This program is free software: you can redistribute it and/or modify 
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License,
 * or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see https://www.gnu.org/licenses/.
 */
 
#include QMK_KEYBOARD_H

char ascii = 0;

enum custom_keycodes {
    BIN_0 = SAFE_RANGE,
    BIN_1,
    BIN_RETURN
};

enum layers {
    _BASE = 0
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        BIN_0,   BIN_1,
          BIN_RETURN
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case BIN_0:
            if (record->event.pressed) {   
                ascii = ascii << 1;
            }

            return true;
        case BIN_1:
            if (record->event.pressed) {
                    ascii = ascii << 1;
                    ++ascii;
                }

            return true;
        case BIN_RETURN:
            if (record->event.pressed) {
                char str[2] = { ascii & 127, '\0' };

                send_string(str);

                ascii = 0;
            }

            return true;
        default:
            return true;
    }

    return true;
}
