/* Copyright 2023 a_marmot
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
* along with this program.  If not, see &lt;http://www.gnu.org/licenses/&gt;.
*/

#include QMK_KEYBOARD_H
#include <is31fl3731.h>
#include <stdio.h>

enum custom_keycodes {
    RT_TOGG = SAFE_RANGE,
    RT_RSET,
    RT_PREV,
    RT_NEXT,
    RT_SEND,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┌───┬───┬───┬───┐
     * │Esc│ 1 │ 2 │ 3 │ 4 │
     * ├───┼───┼───┼───┼───┤
     * │Tab│ q │ w │ e │ r │
     * ├───┼───┼───┼───┼───┤
     * │Ctl│ a │ s │ d │ f │
     * ├───┼───┼───┼───┼───┤
     * │Shi│ z │ x │ c │ v │
     * ├───┼───┼───┼───┼───┤
     * │Alt│ ↑ │ ↓ │ → │ ← │
     * ├───┴───┴───┴───┴───┤
     * │Spa                │
     * └───────────────────┘
     */
    [0] = LAYOUT_keypad(
        KC_ESC, KC_1, KC_2, KC_3, KC_4,
        RT_TOGG, RT_RSET, RT_PREV, RT_NEXT, RT_SEND,
        KC_CAPS, KC_A, KC_S, KC_D, KC_F,
        KC_LSFT, KC_Z, KC_X, KC_C, TO(1),
        KC_LALT, KC_UP, KC_DOWN, KC_RIGHT, KC_LEFT,
        KC_SPACE
    ),
//Layer 1 allows user to enter bootloader mode without disassembling the keypad. 
//DO NOT compile without a path to this layer! 
     [1] = LAYOUT_keypad(
         TO(0), TO(0), TO(0), TO(0), TO(0),
        TO(0), TO(0), QK_BOOT, TO(0), TO(0),
        TO(0), TO(0), TO(0), TO(0), TO(0),
        TO(0), TO(0), TO(0), TO(0), TO(0),
        TO(0), TO(0), TO(0), TO(0), TO(0),
        TO(0)
    )  
};

static bool    rgb_test_mode   = false;
static uint8_t rgb_led_index   = 0;
static uint8_t rgb_color_index = 0;

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (rgb_test_mode) {
        for (uint8_t i = led_min; i <= led_max; ++i) {
            uint8_t r = 0, g = 0, b = 0;
            if (i == rgb_led_index) {
                r = (rgb_color_index == 0) ? 0xFF : 0;
                g = (rgb_color_index == 1) ? 0xFF : 0;
                b = (rgb_color_index == 2) ? 0xFF : 0;
            }
            rgb_matrix_set_color(i, r, g, b);
        }     
    } 
    
    else { 
    	for (uint8_t i = led_min; i < led_max; i++) {
        	switch(get_highest_layer(layer_state|default_layer_state)) {
            	case 1:
                	rgb_matrix_set_color(i, RGB_BLUE);
                	break;
            	case 0:
                	rgb_matrix_set_color(i, RGB_YELLOW);
                	break;
            	default:
                	break;
            }
        }
	}
	
    return false;
}

static char send_buf[32];

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (record->event.pressed) {
        switch (keycode) {
            case RT_TOGG:
                rgb_test_mode = !rgb_test_mode;
                return false;

            case RT_RSET:
                rgb_led_index   = 0;
                rgb_color_index = 0;
                return false;

            case RT_PREV:
                if (rgb_color_index > 0) {
                    rgb_color_index--;
                } else {
                    rgb_color_index = 2;
                    if (rgb_led_index > 0) {
                        rgb_led_index--;
                    } else {
                        rgb_led_index = RGB_MATRIX_LED_COUNT - 1;
                    }
                }
                return false;

            case RT_NEXT:
                if (++rgb_color_index > 2) {
                    rgb_color_index = 0;
                    if (++rgb_led_index >= RGB_MATRIX_LED_COUNT) {
                        rgb_led_index = 0;
                    }
                }
                return false;

            case RT_SEND:
                if (rgb_led_index < RGB_MATRIX_LED_COUNT) {
                    // IS31FL3731-specific code here
                    is31_led led = g_is31_leds[rgb_led_index];
                    uint8_t  reg = (rgb_color_index == 0) ? led.r : ((rgb_color_index == 1) ? led.g : led.b);
                    sprintf(send_buf, "C%d_%d", ((reg - 0x24) >> 4) + 1, ((reg - 0x24) & 0x0F) + 1);
                } else {
                    static const char colors[3] = {'R', 'G', 'B'};
                    sprintf(send_buf, "+%d,%c", rgb_led_index - RGB_MATRIX_LED_COUNT, colors[rgb_color_index]);
                }
                send_string(send_buf);
                return false;
        }
    }
    return true;
}