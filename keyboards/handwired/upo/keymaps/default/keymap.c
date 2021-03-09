/* Copyright 2020 Tomohisa Takaoka
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
#include <math.h>

/***************************
 * Trackball related defines
 **************************/

#include "pointing_device.h"
#include "../../pmw3360/pmw3360.h"

#define cursor_mode 0
#define carret_mode 1
#define scroll_mode 2
uint8_t track_mode = cursor_mode; // 0 Mousecursor; 1 arrowkeys/carret; 2 scrollwheel; 3 sound/brightness
#define sound_brightness_mode 3
uint8_t prev_track_mode = 0;
bool integration_mode = false;
int16_t cum_x = 0;
int16_t cum_y = 0;
int16_t sensor_x = 0;
int16_t sensor_y = 0;

// Thresholds help to move only horizontal or vertical. When accumulated distance reaches threshold, only move one discrete value in direction with bigger delta.
uint8_t	carret_threshold = 48;		 // higher means slower
uint16_t carret_threshold_inte = 340; // in integration mode higher threshold
#define CARRET_STEP 5

#define regular_smoothscroll_factor 8
bool smooth_scroll = true;
uint8_t	scroll_threshold = 800 / regular_smoothscroll_factor;	// divide if started smooth
uint16_t scroll_threshold_inte = 1200 / regular_smoothscroll_factor;

uint16_t cursor_multiplier = 50;	// adjust cursor speed
uint16_t cursor_multiplier_inte = 20;
#define CPI_STEP 10

int16_t cur_factor;
#define SCROLL_STEP 10

bool reverse_scroll_y = true;

/***************************
 * Mouse pressed
 **************************/

void on_mouse_button(uint8_t mouse_button, bool pressed) {
	report_mouse_t report = pointing_device_get_report();

	if(pressed)
		report.buttons |= mouse_button;
	else
		report.buttons &= ~mouse_button;
	pointing_device_set_report(report);
	pointing_device_send();
}

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN
};




// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
    QMKURL,
	KC_CPI_DOWN,
	KC_CPI_STD,
	KC_CPI_UP,
	KC_SCROLLSPEED_DOWN,
	KC_SCROLLSPEED_UP,
	KC_SMO_SC,
	KC_MOUSEMODE_CURSOR,
	KC_MOUSEMODE_SCROLL,
	KC_MOUSEMODE_ARROW,
	KC_MOUSEMODE_BRIGHTNESS,
	KC_MOUSEMODE_SCROLL_ON_PRESS,
	KC_MOUSEMODE_ARROW_ON_PRESS,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        RGB_TOG,    RGB_HUI,    RGB_SAI,
        KC_CPI_UP,   KC_CPI_DOWN,    KC_MOUSEMODE_SCROLL_ON_PRESS,   KC_MOUSEMODE_ARROW_ON_PRESS,
        KC_BTN1,   MO(_FN),    KC_BTN3,   KC_BTN2
    ),
    [_FN] = LAYOUT(
        RGB_MODE_FORWARD,    RGB_HUD,    RGB_SAD,
        KC_SCROLLSPEED_UP,   KC_SCROLLSPEED_DOWN,    KC_SPC,   KC_SPC,
        KC_BTN1,   MO(_FN),    KC_BTN3,   KC_BTN2
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
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
		// handle mouse
		case KC_BTN1:
			on_mouse_button(MOUSE_BTN1, record->event.pressed);
			return false;

		case KC_BTN2:
			on_mouse_button(MOUSE_BTN2, record->event.pressed);
			return false;

		case KC_BTN3:
			on_mouse_button(MOUSE_BTN3, record->event.pressed);
			return false;

		case KC_BTN4:
			on_mouse_button(MOUSE_BTN4, record->event.pressed);
			return false;

		case KC_BTN5:
			on_mouse_button(MOUSE_BTN5, record->event.pressed);
			return false;

		case KC_CPI_DOWN:
            if (record->event.pressed) {
                if (cursor_multiplier > CPI_STEP) {
                    cursor_multiplier = cursor_multiplier - CPI_STEP;
                }
                carret_threshold += CARRET_STEP;
            }
			return false;

		case KC_CPI_STD:
			cursor_multiplier = 250;
			return false;

		case KC_CPI_UP:
            if (record->event.pressed) {
                cursor_multiplier = cursor_multiplier + CPI_STEP;
                if (carret_threshold>CARRET_STEP) {
                    carret_threshold += CARRET_STEP;
                }

            }
			return false;

		case KC_SMO_SC:
			if (record->event.pressed) {
				if (smooth_scroll) {
				scroll_threshold = scroll_threshold * regular_smoothscroll_factor;
				scroll_threshold_inte = scroll_threshold_inte * regular_smoothscroll_factor;
				smooth_scroll = false;
				} else {
				scroll_threshold = scroll_threshold / regular_smoothscroll_factor;
				scroll_threshold_inte = scroll_threshold_inte / regular_smoothscroll_factor;
				smooth_scroll = true;
				}
			}
            return false;
        case KC_MOUSEMODE_CURSOR:
            track_mode = cursor_mode;
            return false;
        case KC_MOUSEMODE_SCROLL:
            track_mode = scroll_mode;
            return false;
        case KC_MOUSEMODE_SCROLL_ON_PRESS:
            if (record->event.pressed) {
                track_mode = scroll_mode;
            } else {
                track_mode = cursor_mode;
            }
            return false;
        case KC_MOUSEMODE_ARROW_ON_PRESS:
            if (record->event.pressed) {
                track_mode = carret_mode;
            } else {
                track_mode = cursor_mode;
            }
            return false;
        case KC_MOUSEMODE_ARROW:
            track_mode = carret_mode;
            return false;
        case KC_MOUSEMODE_BRIGHTNESS:
            track_mode = sound_brightness_mode;
            return false;
        case KC_SCROLLSPEED_UP:
            if (record->event.pressed) {
                scroll_threshold += SCROLL_STEP;
            }
            return false;
        case KC_SCROLLSPEED_DOWN:
            if (record->event.pressed) {
                scroll_threshold -= SCROLL_STEP;
            }
            return false;
    }
    return true;
}

/***************************
 * Trackball handling
 **************************/

int max(int num1, int num2) { return (num1 > num2 ) ? num1 : num2; }
int min(int num1, int num2) { return (num1 > num2 ) ? num2 : num1; }

int8_t sign(int x) { return (x > 0) - (x < 0); }
int8_t CLAMP_HID(int value) { return value < -127 ? -127 : value > 127 ? 127 : value; }

void tap_code_fast(uint8_t code) {
	register_code(code);
	// Dont do this:
	// if (code == KC_CAPS) {
	//	 wait_ms(TAP_HOLD_CAPS_DELAY);
	// } else {
	//	 wait_ms(TAP_CODE_DELAY);
	// }
	unregister_code(code);
}

void tap_tb(uint8_t keycode0, uint8_t keycode1, uint8_t keycode2, uint8_t keycode3) {
	if(abs(cum_x) + abs(cum_y) >= cur_factor){
		if(abs(cum_x) > abs(cum_y)) {
			if(cum_x > 0) {
				for (int8_t i = 0; i <= (abs(cum_x) + abs(cum_y)) / cur_factor; i++) {
					tap_code_fast(keycode0);
					cum_x = max(cum_x - cur_factor, 0);
				}
				cum_y = 0;
			} else {
				for (int8_t i = 0; i <= (abs(cum_x) + abs(cum_y)) / cur_factor; i++) {
					tap_code_fast(keycode1);
					cum_x = min(cum_x + cur_factor, 0);
				}
				cum_y = 0;
			}
		} else {
			if(cum_y > 0) {
				for (int8_t i = 0; i <= (abs(cum_x) + abs(cum_y)) / cur_factor; i++) {
					tap_code_fast(keycode2);
					cum_y = max(cum_y - cur_factor, 0);
					}
				cum_x = 0;
			} else {
				for (int8_t i = 0; i <= (abs(cum_x) + abs(cum_y)) / cur_factor; i++) {
					tap_code_fast(keycode3);
					cum_y = min(cum_y + cur_factor, 0);
				}
				cum_x = 0;
			}
		}
	}
}

void handle_pointing_device_modes(void){
	report_mouse_t mouse_report = pointing_device_get_report();
    cum_x += sensor_y;
    cum_y -= sensor_x;
    switch (track_mode)
    {
    case cursor_mode:
		if (integration_mode)
			cur_factor = cursor_multiplier_inte;
		else
			cur_factor = cursor_multiplier;
		mouse_report.x = CLAMP_HID( sensor_y * cur_factor / 100);
		mouse_report.y = CLAMP_HID( sensor_x * cur_factor / 100);
        break;
    case carret_mode:
        if (integration_mode)
            cur_factor = carret_threshold_inte;
        else
            cur_factor = carret_threshold;
        tap_tb(KC_RIGHT, KC_LEFT, KC_UP, KC_DOWN);
        break;
    case scroll_mode:
        if (integration_mode)
            cur_factor = scroll_threshold_inte;
        else
            cur_factor = scroll_threshold;
        if(abs(cum_x) + abs(cum_y) >= cur_factor) {
            if(abs(cum_x) > abs(cum_y)) {
                mouse_report.h = sign(cum_x) * (abs(cum_x) + abs(cum_y)) / cur_factor;
            } else {
                mouse_report.v = (reverse_scroll_y ? -1 : 1) * sign(cum_y) * (abs(cum_x) + abs(cum_y)) / cur_factor;
            }
            cum_x = 0;
            cum_y = 0;
        }
        break;
    case sound_brightness_mode:
        cur_factor = carret_threshold;
        tap_tb(KC_BRIGHTNESS_UP, KC_BRIGHTNESS_DOWN, KC_AUDIO_VOL_UP, KC_AUDIO_VOL_DOWN);
    default:
        break;
    }
	pointing_device_set_report(mouse_report);
	pointing_device_send();
}

void get_sensor_data(void) {
	if(!is_keyboard_master())
		return;
	report_pmw_t pmw_report = pmw_get_report();
    float r = 0.0 * M_PI / 180.0;
    float nx = pmw_report.x * cos(r) - pmw_report.y * sin(r);
    float ny = pmw_report.y * cos(r) + pmw_report.x * sin(r);
	if (integration_mode) {
		sensor_x += nx;
		sensor_y += ny;
	} else {
		sensor_x = nx;
		sensor_y = ny;
	}
}

void pointing_device_task(void) {
    // #ifdef CONSOLE_ENABLE
    //         uprintf("t");
    // #endif
#ifndef POLLING
	if ( is_keyboard_master() && integration_mode )
		handle_pointing_device_modes();
#else
	get_sensor_data();
	handle_pointing_device_modes();
#endif
}

#ifndef POLLING
	ISR(INT2_vect) {
		get_sensor_data();
		handle_pointing_device_modes();
	}
#endif
