/* Copyright 2020 Neil Brian Ramirez
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


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    /* ENC1_CCW, ENC1_P,  ENC1_CW,   ENC2_CCW, ENC2_P, ENC2_CW,
		         MACRO1,  MACRO2,    MACRO3,   MACRO4,
			     MACRO5,  MACRO6,    MACRO7,   MACRO8
	*/
	[0] = LAYOUT(
		KC_VOLD, KC_ESC,   KC_VOLU,  KC_BRID, RESET,  KC_BRIU,
		         KC_Q,     KC_W,     KC_E,     KC_R,
			     KC_A,     KC_S,     KC_D,     KC_F
		
    ),
	[1] = LAYOUT(
		KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,
		         KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,
			     KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS
		
    ),
	[2] = LAYOUT(
		KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,
		         KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,
			     KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS
		
    ),
	[3] = LAYOUT(
		KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,
		         KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,
			     KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS
		
    ),
};

/* E01A is row 2 col 2 (see LAYOUT) */
keyevent_t encoder_cw  = {
    .key = (keypos_t){.row = 2, .col = 2},
    .pressed = false
};
/* E01B is row 2 col 3 (see LAYOUT) */
keyevent_t encoder_ccw  = {
    .key = (keypos_t){.row = 2, .col = 3},
    .pressed = false
};
/* E00A is row 2 col 0 (see LAYOUT) */
keyevent_t encoder2_cw  = {
    .key = (keypos_t){.row = 2, .col = 0},
    .pressed = false
};
/* E00B is row 2 col 1 (see LAYOUT) */
keyevent_t encoder2_ccw  = {
    .key = (keypos_t){.row = 2, .col = 1},
    .pressed = false
};

void matrix_scan_user(void) {
    if (IS_PRESSED(encoder_cw)) { /* release enconder CW */
        encoder_cw.pressed = false;
        encoder_cw.time = (timer_read() | 1);
        action_exec(encoder_cw);
    }

    if (IS_PRESSED(encoder_ccw)) { /* release enconder CCW */
        encoder_ccw.pressed = false;
        encoder_ccw.time = (timer_read() | 1);
        action_exec(encoder_ccw);
    }

    if (IS_PRESSED(encoder2_cw)) { /* release enconder CW */
        encoder2_cw.pressed = false;
        encoder2_cw.time = (timer_read() | 1);
        action_exec(encoder2_cw);
    }

    if (IS_PRESSED(encoder2_ccw)) { /* release enconder CCW */
        encoder2_ccw.pressed = false;
        encoder2_ccw.time = (timer_read() | 1);
        action_exec(encoder2_ccw);
    }
};

void encoder_update_user(uint8_t index, bool clockwise) {
    // uint8_t layer = get_highest_layer(layer_state);

    if (index == 0) { /* First encoder */
        if (clockwise) {
            encoder_ccw.pressed = true;
            encoder_ccw.time = (timer_read() | 1); /* time should not be 0 */
            action_exec(encoder_ccw);
        } else {
            encoder_cw.pressed = true;
            encoder_cw.time = (timer_read() | 1); /* time should not be 0 */
            action_exec(encoder_cw);
        }
    } else if (index == 1) { /* second encoder */
        if (clockwise) {
            encoder2_ccw.pressed = true;
            encoder2_ccw.time = (timer_read() | 1); /* time should not be 0 */
            action_exec(encoder2_ccw);
        } else {
            encoder2_cw.pressed = true;
            encoder2_cw.time = (timer_read() | 1); /* time should not be 0 */
            action_exec(encoder2_cw);
        }
  }
};
