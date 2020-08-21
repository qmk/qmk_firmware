/*
 * Copyright (C) 2019-2020  Maxr1998 <max.rumpf1998@gmail.com>
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

enum layers {
    DEFAULT
};

const uint16_t PROGMEM led_adjust_combo[] = {KC_LEFT, KC_RGHT, COMBO_END};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEFAULT] = {
        { KC_END,  KC_UP,   KC_MUTE },
        { KC_LEFT, KC_DOWN, KC_RGHT }
    }
};

void matrix_init_user(void) {
}

// Override if necessary
/*
void encoder_one_update(bool clockwise) {
}

void encoder_two_update(bool clockwise) {
}
//*/
