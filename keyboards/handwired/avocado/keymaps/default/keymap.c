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

typedef union {
  uint32_t raw;
  struct {
    bool     reverse_scroll_y :1;
    uint8_t  scroll_threshold :4;
    uint8_t  cursor_multiplier :4;
  };
} user_config_t;

user_config_t user_config;

#define cursor_mode 0
#define carret_mode 1
#define scroll_mode 2
uint8_t track_mode = cursor_mode; // 0 Mousecursor; 1 arrowkeys/carret; 2 scrollwheel; 3 sound/brightness
int16_t cum_x = 0;
int16_t cum_y = 0;
int16_t sensor_x = 0;
int16_t sensor_y = 0;

// Thresholds help to move only horizontal or vertical. When accumulated distance reaches threshold, only move one discrete value in direction with bigger delta.
uint8_t	carret_threshold = 48;		 // higher means slower
#define CARRET_STEP 5

#define SCROLL_DEFAULT 8
uint8_t	scroll_threshold = SCROLL_DEFAULT;
#define SCROLL_STEP 2
#define SCROLL_MIN 2
#define SCROLL_MAX 14
bool reverse_scroll_y = true;

#define CPI_DEFAULT 5
uint16_t cursor_multiplier = CPI_DEFAULT;
#define CPI_MAX 15
#define CPI_MIN 1
#define CPI_STEP 1
int8_t last_v = 0;

int16_t cur_factor;
bool mouse_scroll_need_move = false;
bool mouse_v_plus = false;

float mouse_move_x_left = 0;
float mouse_move_y_left = 0;

void update_user_config_from_local(void) {
    user_config.cursor_multiplier = cursor_multiplier;
    user_config.scroll_threshold = scroll_threshold;
    user_config.reverse_scroll_y = reverse_scroll_y;
    eeconfig_update_user(user_config.raw);
}

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
    _FN,
    _FN2
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
    KC_SCROLL_INVERSE,
	KC_MOUSEMODE_CURSOR,
	KC_MOUSEMODE_SCROLL,
	KC_MOUSEMODE_ARROW,
	KC_MOUSEMODE_SCROLL_ON_PRESS,
	KC_MOUSEMODE_ARROW_ON_PRESS,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        LCTL(KC_UP),    LCTL(KC_DOWN),      LCTL(KC_LEFT),  LCTL(KC_RIGHT),
        KC_ESC,         MO(_FN2),           KC_BTN3,        KC_MOUSEMODE_SCROLL_ON_PRESS,
        KC_BTN1,    LALT(KC_Y)    ,   MO(_FN),        LGUI(LSFT(KC_A)),                    KC_BTN2
    ),
    [_FN] = LAYOUT(
        RGB_HUI,    RGB_HUD,   RGB_VAI,    RGB_VAD,
        RGB_TOG,    RGB_MODE_FORWARD,    RGB_SAI, RGB_SAD,
        KC_CPI_UP,  KC_CPI_DOWN,  MO(_FN),   KC_SCROLLSPEED_DOWN,  KC_SCROLLSPEED_UP
    ),
    [_FN2] = LAYOUT(
        LGUI(LSFT(LCTL(KC_4))),   LGUI(LSFT(KC_4)), LCTL(LSFT(KC_TAB)),    LCTL(KC_TAB),
        KC_SPACE,    KC_NO,    KC_ENTER, LGUI(KC_W),
        KC_SCROLL_INVERSE,  KC_NO,  KC_NO,  LGUI(LSFT(KC_V)),   LGUI(KC_LEFT)
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
            #ifdef CONSOLE_ENABLE
            uprintf("left %d\n",record->event.pressed);
            #endif
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
                #ifdef CONSOLE_ENABLE
                uprintf("cursor_multiplier %d\n",cursor_multiplier);
                #endif
                update_user_config_from_local();
            }
			return false;

		case KC_CPI_STD:
            if (record->event.pressed) {
                cursor_multiplier = CPI_DEFAULT;
                update_user_config_from_local();
            }
			return false;

		case KC_CPI_UP:
            if (record->event.pressed) {
                cursor_multiplier = cursor_multiplier >= CPI_MAX ? CPI_MAX : cursor_multiplier + CPI_STEP;
                if (carret_threshold>CARRET_STEP) {
                    carret_threshold += CARRET_STEP;
                }
                #ifdef CONSOLE_ENABLE
                uprintf("cursor_multiplier %d\n",cursor_multiplier);
                #endif
                update_user_config_from_local();
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
        case KC_SCROLLSPEED_UP:
            if (record->event.pressed) {
                scroll_threshold = scroll_threshold <= SCROLL_MIN ? SCROLL_MIN : scroll_threshold - SCROLL_STEP;
                #ifdef CONSOLE_ENABLE
                uprintf("scroll_threshold %d\n",scroll_threshold);
                #endif
                update_user_config_from_local();
            }
            return false;
        case KC_SCROLLSPEED_DOWN:
            if (record->event.pressed) {
                scroll_threshold = scroll_threshold >= SCROLL_MAX ? SCROLL_MAX : scroll_threshold + SCROLL_STEP;
                #ifdef CONSOLE_ENABLE
                uprintf("scroll_threshold %d\n",scroll_threshold);
                #endif
                update_user_config_from_local();
            }
            return false;
        case KC_SCROLL_INVERSE:
            if (record->event.pressed) {
                reverse_scroll_y = !reverse_scroll_y;
                #ifdef CONSOLE_ENABLE
                uprintf("reverse_scroll_y %d\n",reverse_scroll_y);
                #endif
                update_user_config_from_local();
            }
            return false;
    }
    return true;
}


void keyboard_post_init_user(void) {
  user_config.raw = eeconfig_read_user();
#ifdef CONSOLE_ENABLE
uprintf("reverse_scroll_y init %d\n",user_config.reverse_scroll_y);
uprintf("scroll_threshold init %d\n",user_config.scroll_threshold);
uprintf("cursor_multiplier init %d\n",user_config.cursor_multiplier);
#endif
    if (user_config.scroll_threshold == 0 || user_config.cursor_multiplier == 0) {
        cursor_multiplier = CPI_DEFAULT;
        scroll_threshold = SCROLL_DEFAULT;
        reverse_scroll_y = true;
        update_user_config_from_local();
    }
    cursor_multiplier = user_config.cursor_multiplier;
    scroll_threshold = user_config.scroll_threshold;
    reverse_scroll_y = user_config.reverse_scroll_y;
}
void eeconfig_init_user(void) {
    cursor_multiplier = CPI_DEFAULT;
    scroll_threshold = SCROLL_DEFAULT;
    reverse_scroll_y = true;
    update_user_config_from_local();
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
        cur_factor = cursor_multiplier;
        #ifdef CONSOLE_ENABLE
        if (sensor_x!=0 || sensor_y !=0) {
            uprintf("sensor_xy %d %d\n",sensor_x,sensor_y);
        }
        #endif

        float move_x = sensor_y * cur_factor / 10.0 + mouse_move_x_left;
        int sign_x = move_x >= 0 ? 1 : -1;
        mouse_move_x_left = sign_x * ((move_x * sign_x) - (int)(move_x*sign_x));
		mouse_report.x = CLAMP_HID((int)move_x);

        float move_y = sensor_x * cur_factor / 10.0 + mouse_move_y_left;
        int sign_y = move_y >= 0 ? 1 : -1;
        mouse_move_y_left = sign_y * ((move_y * sign_y) - (int)(move_y*sign_y));
		mouse_report.y = CLAMP_HID((int)move_y);

        mouse_scroll_need_move = true;
        break;
    case carret_mode:
        cur_factor = carret_threshold;
        tap_tb(KC_RIGHT, KC_LEFT, KC_UP, KC_DOWN);
        break;
    case scroll_mode:
        cur_factor = scroll_threshold * 10;
        if(abs(cum_x) + abs(cum_y) >= cur_factor) {
            if(abs(cum_x) > abs(cum_y)) {
                mouse_report.h = sign(cum_x) * (abs(cum_x) + abs(cum_y)) / cur_factor;
                #ifdef CONSOLE_ENABLE
                uprintf("mouse_report.h %d\n",mouse_report.h);
                #endif
            } else {
                mouse_report.v = (reverse_scroll_y ? -1 : 1) * sign(cum_y) * (abs(cum_x) + abs(cum_y)) / cur_factor * (sign(cum_y)>0 ? 5 : 1) + (sign(cum_y)==sign(last_v) ? last_v / 2 : 0);
                if (mouse_scroll_need_move) {
                    mouse_report.y = (mouse_v_plus? +1 : -1) * 20;
                    mouse_v_plus = !mouse_v_plus;
                    if (mouse_v_plus == true) {
                        mouse_scroll_need_move = false;
                    }
                }
                #ifdef CONSOLE_ENABLE
                uprintf("mouse_report.v %d\n",mouse_report.v);
                #endif
            }
            last_v = mouse_report.v;
            cum_x = 0;
            cum_y = 0;
        } else {
            mouse_report.v = 0;
            mouse_report.h = 0;
        }
        break;
    default:
        break;
    }
                #ifdef CONSOLE_ENABLE
                if (mouse_report.x != 0 || mouse_report.y!=0) {
                    uprintf("mouse_report.x y %d %d\n",mouse_report.x,mouse_report.y);
                }
                #endif
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
    sensor_x = nx;
    sensor_y = ny;
}

void pointing_device_task(void) {
#ifndef POLLING
	if ( is_keyboard_master() && false )
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
