/* Copyright 2020 customMK
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

#include "v2.h"

keyevent_t encoder_left_ccw = {
    .key = (keypos_t){.row = 5, .col = 0},
    .pressed = false
};

keyevent_t encoder_left_cw = {
    .key = (keypos_t){.row = 5, .col = 1},
    .pressed = false
};

keyevent_t encoder_right_ccw = {
    .key = (keypos_t){.row = 5, .col = 2},
    .pressed = false
};

keyevent_t encoder_right_cw = {
    .key = (keypos_t){.row = 5, .col = 3},
    .pressed = false
};

void matrix_scan_kb(void) {
    if (IS_PRESSED(encoder_left_ccw)) {
        encoder_left_ccw.pressed = false;
        encoder_left_ccw.time = (timer_read() | 1);
        action_exec(encoder_left_ccw);
    }

    if (IS_PRESSED(encoder_left_cw)) {
        encoder_left_cw.pressed = false;
        encoder_left_cw.time = (timer_read() | 1);
        action_exec(encoder_left_cw);
    }

    if (IS_PRESSED(encoder_right_ccw)) {
        encoder_right_ccw.pressed = false;
        encoder_right_ccw.time = (timer_read() | 1);
        action_exec(encoder_right_ccw);
    }

    if (IS_PRESSED(encoder_right_cw)) {
        encoder_right_cw.pressed = false;
        encoder_right_cw.time = (timer_read() | 1);
        action_exec(encoder_right_cw);
    }

	matrix_scan_user();
}


void encoder_update_kb(int8_t index, bool clockwise) {
	if (index == 0) {
		if (clockwise) {
			encoder_left_cw.pressed = true;
			encoder_left_cw.time = (timer_read() | 1);
			action_exec(encoder_left_cw);
		} else {
			encoder_left_ccw.pressed = true;
			encoder_left_ccw.time = (timer_read() | 1);
			action_exec(encoder_left_ccw);
		}
	} else {
		if (clockwise) {
			encoder_right_cw.pressed = true;
			encoder_right_cw.time = (timer_read() | 1);
			action_exec(encoder_right_cw);
		} else {
			encoder_right_ccw.pressed = true;
			encoder_right_ccw.time = (timer_read() | 1);
			action_exec(encoder_right_ccw);
		}
	}
	
	encoder_update_user(index, clockwise);
}


/*
__attribute__((weak)) void encoder_update_user(uint8_t index, bool clockwise) {
	// top left encoder 
	if (index == 0) {
		if (clockwise) {
			tap_code(KC_VOLU);
		} else {
			tap_code(KC_VOLD);
		}
	}
	//top right encoder
	else if (index == 1) {
		if (clockwise) {
			tap_code(KC_VOLU);
		} else {
			tap_code(KC_VOLD);
		}
	}    
}
*/