/* Copyright 2022 Ian Klug
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

#include "joystick.h"
#include "timer.h"

// how long to wait (ms) between pulses before releasing encoder hold in bms/keyboard modes
#define ENC_HOLD_TIME 50

// joystick axes
joystick_config_t joystick_axes[JOYSTICK_AXES_COUNT] = {
    [0] = JOYSTICK_AXIS_VIRTUAL,
    [1] = JOYSTICK_AXIS_VIRTUAL
};

// encoder
int x_axis_val = 0;
int enc_reverse = 0;
uint16_t hold_timer = 0;
uint16_t held_keycode = 0;

// toggle button
bool is_toggled = 0;

// layer state
bool is_player_two = 0;
int mode_swap = 0;
int mode_swap_p2 = 0;
bool mode_swap_standard = 0;
bool mode_swap_inverted = 0;
bool mode_swap_bms = 0;
bool mode_swap_keyboard = 0;
bool mode_swap_ninekey = 0;

//	bemini v1 key layout, player 1 configuration
//      .-----------------------------------------------------------------------------------------.
//      |                                                                                         |
//      |                                    .-------.-------.-------.-------.        .-------.   |
//      |                                    |       |       |       |       |        |       |   |
//      |                                    |       |       |       |       |        |  K12  |   |
//      |                                    |  K02  |  K04  |  K06  |  K08  |        |       |   |
//      |            .-------.               |       |       |       |       |        +-------+   |
//      |            |       |               |       |       |       |       |        |       |   |
//      |            |K13/ENC|           .---+---+---+---+---+---+---+---+---+---.    |  K11  |   |
//      |            |       |           |       |       |       |       |       |    |       |   |
//      |            '-------'           |       |       |       |       |       |    +-------+   |
//      |                                |  K01  |  K03  |  K05  |  K07  |  K09  |    |       |   |
//      |                                |       |       |       |       |       |    |  K10  |   |
//      |                                |       |       |       |       |       |    |       |   |
//      |                                '-------'-------'-------'-------'-------'    '-------'   |
//      |                                                                                         |
//      '-----------------------------------------------------------------------------------------'

// NOTE: QMK joystick buttons are mapped out of order.
// qmk codes for buttons 1-16 are: 7 0 1 2 3 4 5 6 15 8 9 10 11 12 13 14

enum custom_keycodes {
    TOGGLE_BUTTON = SAFE_RANGE,
};

enum layer_names {
    STANDARD_P1,
    INVERTED_P1,
    BMS_P1,
    KEYBOARD_P1,
    NINEKEY_P1,
    STANDARD_P2,
    INVERTED_P2,
    BMS_P2,
    KEYBOARD_P2,
    NINEKEY_P2
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//	K01          K02          K03          K04          K05          K06          K07          K08          K09          K10          K11          K12          K13
    [STANDARD_P1] = LAYOUT(
	JS_BUTTON11, JS_BUTTON12, JS_BUTTON7,  JS_BUTTON0,  JS_BUTTON1,  JS_BUTTON2,  JS_BUTTON3,  JS_BUTTON4,  JS_BUTTON5,  JS_BUTTON9,  JS_BUTTON8,  JS_BUTTON15, TOGGLE_BUTTON
    ),
    [INVERTED_P1] = LAYOUT(
	JS_BUTTON11, JS_BUTTON12, JS_BUTTON7,  JS_BUTTON0,  JS_BUTTON1,  JS_BUTTON2,  JS_BUTTON3,  JS_BUTTON4,  JS_BUTTON5,  JS_BUTTON9,  JS_BUTTON8,  JS_BUTTON15, TOGGLE_BUTTON
    ),
    [BMS_P1] = LAYOUT(
	JS_BUTTON11, JS_BUTTON12, JS_BUTTON7,  JS_BUTTON0,  JS_BUTTON1,  JS_BUTTON2,  JS_BUTTON3,  JS_BUTTON4,  JS_BUTTON5,  JS_BUTTON9,  JS_BUTTON8,  JS_BUTTON15, TOGGLE_BUTTON
    ),
    [KEYBOARD_P1] = LAYOUT(
	KC_A,        KC_S,        KC_D,        KC_F,        KC_G,        KC_H,        KC_J,        KC_K,        KC_L,        KC_T,        KC_R,        KC_E,        TOGGLE_BUTTON
    ),
    [NINEKEY_P1] = LAYOUT(
	JS_BUTTON7,  JS_BUTTON0,  JS_BUTTON1,  JS_BUTTON2,  JS_BUTTON3,  JS_BUTTON4,  JS_BUTTON5,  JS_BUTTON6,  JS_BUTTON15, JS_BUTTON10, JS_BUTTON9,  JS_BUTTON8,  KC_NO
    ),
    [STANDARD_P2] = LAYOUT(
        JS_BUTTON12, JS_BUTTON11, JS_BUTTON5,  JS_BUTTON4,  JS_BUTTON3,  JS_BUTTON2,  JS_BUTTON1,  JS_BUTTON0,  JS_BUTTON7,  JS_BUTTON15, JS_BUTTON8,  JS_BUTTON9,  TOGGLE_BUTTON
    ),
    [INVERTED_P2] = LAYOUT(
        JS_BUTTON12, JS_BUTTON11, JS_BUTTON5,  JS_BUTTON4,  JS_BUTTON3,  JS_BUTTON2,  JS_BUTTON1,  JS_BUTTON0,  JS_BUTTON7,  JS_BUTTON15, JS_BUTTON8,  JS_BUTTON9,  TOGGLE_BUTTON
    ),
    [BMS_P2] = LAYOUT(
        JS_BUTTON12, JS_BUTTON11, JS_BUTTON5,  JS_BUTTON4,  JS_BUTTON3,  JS_BUTTON2,  JS_BUTTON1,  JS_BUTTON0,  JS_BUTTON7,  JS_BUTTON15, JS_BUTTON8,  JS_BUTTON9,  TOGGLE_BUTTON
    ),
    [KEYBOARD_P2] = LAYOUT(
        KC_DOT,      KC_COMM,     KC_M,        KC_N,        KC_B,        KC_V,        KC_C,        KC_X,        KC_Z,        KC_O,        KC_P,        KC_LBRC,     TOGGLE_BUTTON
    ),
    [NINEKEY_P2] = LAYOUT(
        JS_BUTTON15, JS_BUTTON6,  JS_BUTTON5,  JS_BUTTON4,  JS_BUTTON3,  JS_BUTTON2,  JS_BUTTON1,  JS_BUTTON0,  JS_BUTTON7,  JS_BUTTON8,  JS_BUTTON9,  JS_BUTTON10, KC_NO
    )
};

// set player state from eeprom on boot
void matrix_init_user(void) {
    eeconfig_read_default_layer();
    if (biton32(default_layer_state) == STANDARD_P2) {
	is_player_two = 1;
    }
}

// manage encoder hold/release behavior (bms, keyboard modes)
// hold while rotating, release hold when rotation stops
void matrix_scan_user(void) {
    if (hold_timer != 0) {
        if (timer_elapsed(hold_timer) > ENC_HOLD_TIME) {
            if ((layer_state_is(BMS_P1) || layer_state_is(BMS_P2)) && x_axis_val != 0) {
                x_axis_val = 0;
                joystick_status.axes[0] = x_axis_val;
                joystick_status.status |= JS_UPDATED;
            } else if ((layer_state_is(KEYBOARD_P1) || layer_state_is(KEYBOARD_P2)) && held_keycode != 0) {
                unregister_code(held_keycode);
                held_keycode = 0;
           }
           hold_timer = 0;
        }
    }
}

// encoder behavior
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (layer_state_is(STANDARD_P1) || layer_state_is(STANDARD_P2)) {
            if (clockwise) {
                x_axis_val = joystick_status.axes[0] + 1;
                if (x_axis_val > 127) {
  	            x_axis_val = -127;
                }
            } else {
                x_axis_val = joystick_status.axes[0] - 1;
                if (x_axis_val < -127) {
	            x_axis_val = 127;
                }
            }
            joystick_status.axes[0] = x_axis_val;
            joystick_status.status |= JS_UPDATED;
        } else if (layer_state_is(INVERTED_P1) || layer_state_is(INVERTED_P2)) {
            if (clockwise) {
                x_axis_val = joystick_status.axes[0] - 1;
                if (x_axis_val < -127) {
	            x_axis_val = 127;
                }
            } else {
                x_axis_val = joystick_status.axes[0] + 1;
                if (x_axis_val > 127) {
  	            x_axis_val = -127;
                }
            }
            joystick_status.axes[0] = x_axis_val;
            joystick_status.status |= JS_UPDATED;
        } else if (layer_state_is(BMS_P1) || layer_state_is(BMS_P2)) {
            uint16_t x_axis_input = 0;
            if (clockwise) {
	        x_axis_input = 127;
            } else {
	        x_axis_input = -127;
            }

            if (x_axis_val == 0) {
                x_axis_val = x_axis_input;
		joystick_status.axes[0] = x_axis_input;
                joystick_status.status |= JS_UPDATED;

                enc_reverse = 0;
		hold_timer = timer_read();
            } else if (x_axis_val != x_axis_input) {
                enc_reverse++;

		// require two consecutive reverse signals to change direction
        	if (enc_reverse > 1) {
	            x_axis_val = x_axis_input;
	            joystick_status.axes[0] = x_axis_input;
	            joystick_status.status |= JS_UPDATED;

	            enc_reverse = 0;
	            hold_timer = timer_read();
	        }
            } else {
	        enc_reverse = 0;
	        hold_timer = timer_read();
            }
        } else if (layer_state_is(KEYBOARD_P1)) {
            uint16_t mapped_code = 0;
      	    if (clockwise) {
		mapped_code = KC_W;
	    } else {
                mapped_code = KC_Q;
	    }

            if (held_keycode == 0) {
 	        register_code(mapped_code);

	        enc_reverse = 0;
	        held_keycode = mapped_code;
                hold_timer = timer_read();
            } else if (held_keycode != mapped_code) {
	        enc_reverse++;

        	// require two consecutive reverse signals to change direction
	        if (enc_reverse > 1) {
                    unregister_code(held_keycode);
                    register_code(mapped_code);

	  	    enc_reverse = 0;
		    held_keycode = mapped_code;
                    hold_timer = timer_read();
  	        }
            } else {
	        enc_reverse = 0;
	        held_keycode = mapped_code;
                hold_timer = timer_read();
            }
        } else if (layer_state_is(KEYBOARD_P2)) {
            uint16_t mapped_code = 0;
      	    if (clockwise) {
	        mapped_code = KC_I;
	    } else {
                mapped_code = KC_U;
	    }

            if (held_keycode == 0) {
 	        register_code(mapped_code);

	        enc_reverse = 0;
	        held_keycode = mapped_code;
                hold_timer = timer_read();
            } else if (held_keycode != mapped_code) {
	        enc_reverse++;

        	// require two consecutive reverse signals to change direction
	        if (enc_reverse > 1) {
                    unregister_code(held_keycode);
                    register_code(mapped_code);

	  	    enc_reverse = 0;
		    held_keycode = mapped_code;
                    hold_timer = timer_read();
  	        }
            } else {
	        enc_reverse = 0;
	        held_keycode = mapped_code;
                hold_timer = timer_read();
            }
        } else if (layer_state_is(NINEKEY_P1) || layer_state_is(NINEKEY_P2)) {
            // not bound
        }
    }
    return true;
}

// custom keypress behavior
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode){
        case TOGGLE_BUTTON:
	    // K13
	    if (layer_state_is(STANDARD_P1) || layer_state_is(STANDARD_P2)) {
                if (record->event.pressed) {
                    is_toggled ^= 1;
	            if (is_toggled) {
			// zero-indexed button id
			uint8_t joystick_button = 14;
			joystick_status.buttons[joystick_button / 8] |= 1 << (joystick_button % 8);
			joystick_status.status |= JS_UPDATED;
                    } else {
			uint8_t joystick_button = 15;
			joystick_status.buttons[joystick_button / 8] |= 1 << (joystick_button % 8);
			joystick_status.status |= JS_UPDATED;
                    }
	        } else {
	            if (is_toggled) {
			uint8_t joystick_button = 14;
			joystick_status.buttons[joystick_button / 8] &= ~(1 << (joystick_button % 8));
			joystick_status.status |= JS_UPDATED;
                    } else {
			uint16_t joystick_button = 15;
			joystick_status.buttons[joystick_button / 8] &= ~(1 << (joystick_button % 8));
			joystick_status.status |= JS_UPDATED;
                    }
	        }
	    } else if (layer_state_is(INVERTED_P1)) {
		// inverted p1
                if (record->event.pressed) {
                    is_toggled ^= 1;
	            if (is_toggled) {
                        register_code(KC_LSFT);
                    } else {
                        register_code(KC_LCTL);
                    }
	        } else {
	            if (is_toggled) {
                        unregister_code(KC_LSFT);
                    } else {
                        unregister_code(KC_LCTL);
                    }
	        }
	    } else if (layer_state_is(INVERTED_P2)) {
		//inverted p2
                if (record->event.pressed) {
                    is_toggled ^= 1;
	            if (is_toggled) {
                        register_code(KC_RSFT);
                    } else {
                        register_code(KC_RCTL);
                    }
	        } else {
	            if (is_toggled) {
                        unregister_code(KC_RSFT);
                    } else {
                        unregister_code(KC_RCTL);
                    }
	        }
	    } else if (layer_state_is(BMS_P1) || layer_state_is(BMS_P2)) {
                if (record->event.pressed) {
                    is_toggled ^= 1;
                    if (is_toggled) {
			// zero-indexed button id
                        uint8_t joystick_button = 14;
                        joystick_status.buttons[joystick_button / 8] |= 1 << (joystick_button % 8);
                        joystick_status.status |= JS_UPDATED;
                    } else {
                        uint8_t joystick_button = 15;
                        joystick_status.buttons[joystick_button / 8] |= 1 << (joystick_button % 8);
                        joystick_status.status |= JS_UPDATED;
                    }
                } else {
                    if (is_toggled) {
                        uint8_t joystick_button = 14;
                        joystick_status.buttons[joystick_button / 8] &= ~(1 << (joystick_button % 8));
                        joystick_status.status |= JS_UPDATED;
                    } else {
                        uint16_t joystick_button = 15;
                        joystick_status.buttons[joystick_button / 8] &= ~(1 << (joystick_button % 8));
                        joystick_status.status |= JS_UPDATED;
                    }
                }
	    } else if (layer_state_is(KEYBOARD_P1)) {
                if (record->event.pressed) {
                    is_toggled ^= 1;
	            if (is_toggled) {
                        register_code(KC_W);
                    } else {
                        register_code(KC_Q);
                    }
	        } else {
	            if (is_toggled) {
                        unregister_code(KC_W);
                    } else {
                        unregister_code(KC_Q);
                    }
	        }
	    } else if (layer_state_is(KEYBOARD_P2)) {
                if (record->event.pressed) {
                    is_toggled ^= 1;
	            if (is_toggled) {
                        register_code(KC_I);
                    } else {
                        register_code(KC_U);
                    }
	        } else {
	            if (is_toggled) {
                        unregister_code(KC_I);
                    } else {
                        unregister_code(KC_U);
                    }
	        }
	    } else if (layer_state_is(NINEKEY_P1) || layer_state_is(NINEKEY_P2)) {
		// unbound
	    }
            break;
	case KC_E: case KC_R: case KC_T: case KC_O: case KC_P: case KC_LBRC: case JS_BUTTON8: case JS_BUTTON9: case JS_BUTTON10: case JS_BUTTON15:
	    // K10, K11, K12
            if (record->event.pressed)
                mode_swap++;
            else
                mode_swap--;
	    break;
	case KC_A: case KC_DOT: case JS_BUTTON11: case JS_BUTTON12:
	    // White 1
	    if (record->event.pressed)
                mode_swap_ninekey = 1;
            else
                mode_swap_ninekey = 0;
            break;
	case KC_D: case KC_Z: case JS_BUTTON7:
	    // White 2
	    if (record->event.pressed)
                mode_swap_standard = 1;
            else
                mode_swap_standard = 0;
            break;
	case KC_G: case KC_C: case JS_BUTTON1:
	    // White 3
	    if (record->event.pressed)
                mode_swap_inverted = 1;
            else
                mode_swap_inverted = 0;
            break;
	case KC_J: case KC_B: case JS_BUTTON3:
	    // White 4
	    if (record->event.pressed)
                mode_swap_bms = 1;
            else
                mode_swap_bms = 0;
            break;
	case KC_L: case KC_M: case JS_BUTTON5:
	    // White 5
	    if (record->event.pressed)
                mode_swap_keyboard = 1;
            else
                mode_swap_keyboard = 0;
            break;
	case KC_F: case KC_H: case KC_N: case KC_V: case JS_BUTTON0: case JS_BUTTON2: case JS_BUTTON4:
	    // Black 2 + Black 3
	    if (record->event.pressed)
                mode_swap_p2++;
            else
                mode_swap_p2--;
            break;
    }

    // switch active layer when any white key + e keys are pressed
    // switch player mode when middle two black keys + e keys are pressed
    if (mode_swap == 3) {

	// save default player mode to eeprom
	if (mode_swap_p2 == 2) {
	    is_player_two ^= 1;
	    if (is_player_two) {
		set_single_persistent_default_layer(STANDARD_P2);
		layer_move(STANDARD_P2);
	    } else {
		set_single_persistent_default_layer(STANDARD_P1);
		layer_move(STANDARD_P1);
	    }
	}

        if (is_player_two) {
	    if (mode_swap_standard == 1) {
                layer_move(STANDARD_P2);
	    } else if (mode_swap_inverted == 1) {
	        layer_move(INVERTED_P2);
	    } else if (mode_swap_bms == 1) {
	        layer_move(BMS_P2);
	    } else if (mode_swap_keyboard == 1) {
	        layer_move(KEYBOARD_P2);
	    } else if (mode_swap_ninekey == 1) {
	        layer_move(NINEKEY_P2);
	    }
        } else {
	    if (mode_swap_standard == 1) {
                layer_move(STANDARD_P1);
	    } else if (mode_swap_inverted == 1) {
	        layer_move(INVERTED_P1);
	    } else if (mode_swap_bms == 1) {
	        layer_move(BMS_P1);
	    } else if (mode_swap_keyboard == 1) {
	        layer_move(KEYBOARD_P1);
	    } else if (mode_swap_ninekey == 1) {
	        layer_move(NINEKEY_P1);
	    }
	}

	// reset everything after layer switch
        x_axis_val = 0;
        hold_timer = 0;
        held_keycode = 0;
	enc_reverse = 0;
	is_toggled = 0;

        joystick_status.axes[0] = 0;
        joystick_status.status |= JS_UPDATED;

	clear_keyboard();
    }
    return true;
}
