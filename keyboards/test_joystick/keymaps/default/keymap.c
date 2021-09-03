/* Copyright 2021 marby3
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
#include "analog.h"
#include "pointing_device.h"

//CHANGE THIS
char arrow_keys[4] = {KC_UP, KC_LEFT, KC_DOWN, KC_RIGHT}; // up, left, down, right

static uint8_t joystickMode = 0;
static uint8_t joystick_modes = 3; // amount of modes
static int actuation = 255; // actuation point for arrows (0-511)
static int joystickThreshold = 6; // Value to prevent joystick drift
static int joystickResolution = 24; // Decide the movement speed of the joystick

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    JSMODE = SAFE_RANGE,
};

bool arrows[4];

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        JSMODE
    ),
    [_FN] = LAYOUT(
        KC_NO
    )
};


//joystick config
joystick_config_t joystick_axes[JOYSTICK_AXES_COUNT] = {
    [0] = JOYSTICK_AXIS_VIRTUAL,
    [1] = JOYSTICK_AXIS_VIRTUAL
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
    case JSMODE:
        if (record->event.pressed) {
            joystickMode++;
            if (joystickMode == joystick_modes){
                joystickMode = 0;
            }
        }
    }
    return true;
}

void joystick_task(){
	switch (joystickMode) {
	case 0: // gamepad
		joystick_status.axes[0] = analogReadPin(B6)/4 - 128;
		joystick_status.axes[1] = analogReadPin(B5)/4 - 128;
		joystick_status.status |= JS_UPDATED;
        send_joystick_packet(&joystick_status);
		break;
    case 1: // arrows
        if (!arrows[0] && analogReadPin(B5) - 512 > actuation){
            arrows[0] = true;
            register_code16(arrow_keys[2]);
        }
        else if (arrows[0] &&  analogReadPin(B5) - 512 < actuation){
            arrows[0] = false;
            unregister_code16(arrow_keys[2]);
        }
        if (!arrows[1] && analogReadPin(B5) - 512 < -actuation){
            arrows[1] = true;
            register_code16(arrow_keys[0]);
        }
        else if (arrows[1] && analogReadPin(B5) - 512 > -actuation){
            arrows[1] = false;
            unregister_code16(arrow_keys[0]);
        }
        if (!arrows[2] && analogReadPin(B6) - 512 > actuation){
            arrows[2] = true;
            register_code16(arrow_keys[3]);
        }
        else if (arrows[2] &&  analogReadPin(B6) - 512 < actuation){
            arrows[2] = false;
            unregister_code16(arrow_keys[3]);
        }
        if (!arrows[3] && analogReadPin(B6) - 512 < -actuation){
            arrows[3] = true;
            register_code16(arrow_keys[1]);
        }
        else if (arrows[3] && analogReadPin(B6) - 512 > -actuation){
            arrows[3] = false;
            unregister_code16(arrow_keys[1]);
        }
        break;
    case 2: // mouse
        ;
        report_mouse_t currentReport = pointing_device_get_report();
        currentReport.x = (analogReadPin(B6) - 512) / joystickResolution;
        currentReport.y = (analogReadPin(B5) - 512) / joystickResolution;
        if (currentReport.x < joystickThreshold && currentReport.x > -joystickThreshold){
            currentReport.x = 0;
        }
        if (currentReport.y < joystickThreshold && currentReport.y > -joystickThreshold){
            currentReport.y = 0;
        }
        pointing_device_set_report(currentReport);
        pointing_device_send();
        break;
	}
}
