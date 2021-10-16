/* Copyright 2021 dsanchezseco
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

#define JOY_INITIAL_DELAY 20            // 20ms delay until first joystick action
// #define JOY_REPEAT_RATE 250             //repeat every 250ms, 4 times per second.  Delete this for single press
#define JOY_BUTTON_SINGLE_ACTION 1      //The button by itself will only act once.  Delete this to repeat while held like the directions.

#define TAP_CODE_DELAY 200              // add 100ms to key release for better key register

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
};

enum alias_keycodes {
    FUN1 = LCTL(KC_A),
    FUN2 = LCTL(KC_O),
    FUN3 = LCTL(KC_U),
    FUN4 = LCTL(KC_I),
    SEL1 = LCTL(KC_D),
    SEL2 = LCTL(KC_H),
    SEL3 = LCTL(KC_T),
    SEL4 = LCTL(KC_N),
    SEL5 = LCTL(KC_SCLN),
    N1 = RCTL(KC_1),
    N2 = RCTL(KC_2),
    N3 = RCTL(KC_3),
    N4 = RCTL(KC_4),
    N5 = RCTL(KC_5),
    N6 = RCTL(KC_6),
    N7 = RCTL(KC_7),
    N8 = RCTL(KC_8),
    N9 = RCTL(KC_9),
    N0 = RCTL(KC_0),
    ENT = RCTL(KC_LBRC),
    CRL = RCTL(KC_RBRC),
    COM1P = LCTL(KC_Q),
    COM2P = LCTL(KC_J),
    UP = LCTL(KC_K),
    DOWN = LCTL(KC_X),
    D_UP = LCTL(KC_M),
    D_RIGHT = LCTL(KC_R),
    D_DOWN = LCTL(KC_V),
    D_LEFT = LCTL(KC_P),
    D_PUSH = RCTL(KC_W),
};

enum custom_keycodes {
    DOB_UP = SAFE_RANGE,
    DOB_RIGHT,
    DOB_DOWN,
    DOB_LEFT,
    DOB_PUSH,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        FUN1,   FUN2,       FUN3,       FUN4,       SEL1,
        N1,     N2,         N3,         COM1P,      SEL2,
        N4,     N5,         N6,         COM2P,      SEL3,
        N7,     N8,         N9,         UP,         SEL4,
        CRL,    N0,         ENT,        DOWN,       SEL5,
        DOB_UP, DOB_LEFT,   DOB_DOWN,   DOB_RIGHT,  DOB_PUSH
    ),
};

void led_keypress_update(pin_t led_pin, uint16_t keycode, keyrecord_t *record) {
    // When a key is pressed turn on the LED, when released turn it off
    writePin(led_pin, !record->event.pressed);
}


void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* Encoder on the LEFT */
        if (clockwise) {
            tap_code16(RCTL(KC_A));
        } else {
            tap_code16(RCTL(KC_O));
        }
    } else if (index == 1) { /* Encoder on the RIGHT */
        if (clockwise) {
            tap_code16(RCTL(KC_U));
        } else {
            tap_code16(RCTL(KC_I));
        }
    } else if (index == 2) { /* Encoder on the RIGHT */
        if (clockwise) {
            tap_code16(RCTL(KC_H));
        } else {
            tap_code16(RCTL(KC_D));
        }
    }
}


bool joy_pins_active[5] = {false};  //track which pins are active
bool joy_first_move = false;  //activates a delay in matrix_scan_user()
bool joy_held = false;
uint16_t joy_timer = 0;

void process_joystick(void) { 
	if (joy_pins_active[0]) {
		//JOY_N code
        register_code16(D_UP);
	}
	if (joy_pins_active[1]) {
		//JOY_E code
        register_code16(D_RIGHT);
    }
	if (joy_pins_active[2]) {
		//JOY_S code
        register_code16(D_DOWN);
    }
	if (joy_pins_active[3]) {
		//JOY_W code
        register_code16(D_LEFT);
	}

    //if N, E, S, or W is active, do nothing
    for (int i=0; i<4; i++) if (joy_pins_active[i]) return;
    register_code16(D_PUSH);
    //JOY_P code will run here if only the button is pressed.
    
    #ifdef JOY_BUTTON_SINGLE_ACTION
        joy_held = false;
    #endif
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	if (DOB_UP <= keycode && keycode <= DOB_PUSH) {  //if a joystick pin changes state
		if (record->event.pressed) {  //if that pin turned on
			joy_pins_active[keycode - DOB_UP] = true;  //set that pin's bool to true
			joy_first_move = true;  //set a flag for matrix_scan_user() to begin an initial delay
			joy_timer = timer_read();  //set joy_timer to the current time
			joy_held = true;  //the joystick is held down
		} else {  //when that pin is released.
			joy_pins_active[keycode - DOB_UP] = false;  //set that pin's bool to false
			joy_held = false;  //the joystick is no longer held down
            clear_keyboard();
		}
	}

    // Update LED state
    led_keypress_update(LED, keycode, record);
    return true;
};

/* If the joystick is in a moved position, check if it was just moved.
 * The first action should be done as soon as possible, so we check against JOY_INITIAL_DELAY
 * We then call process_joystick(), which will check which direction the joystick is and act accordingly.
 * Set joy_first_move to false so it knows to check against the repeat rate instead of initial delay.
 * If you have JOY_REPEAT_RATE defined, it will call process_joystick() every JOY_REPEAT_RATE milliseconds as long as the joystick is held.
 */
void matrix_scan_user(void) {
	if (joy_held) {
		if (joy_first_move && timer_elapsed(joy_timer) > JOY_INITIAL_DELAY) {
			joy_first_move = false;
			joy_timer = timer_read();
			process_joystick();
		}
#ifdef JOY_REPEAT_RATE
		else if (timer_elapsed(joy_timer) > JOY_REPEAT_RATE) {
			joy_timer = timer_read();
			process_joystick();
		}			
#endif  //JOY_REPEAT_RATE
    }
}