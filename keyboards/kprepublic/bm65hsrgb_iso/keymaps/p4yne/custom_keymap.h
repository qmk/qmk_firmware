/* Copyright 2019 ash0x0 2021 peepeetee, deadolus 2022 p4yne
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

#include "print.h"
#include <string.h>
// HID has not yet been implemented for this keyboard
// #include "raw_hid.h"

#define MILLISECONDS_IN_SECOND 1000

// Custom HSV values
#define C_HSV_WINERED        0, 255,  85
#define C_HSV_DARKGOLD      36, 255,  85
#define C_HSV_DARKBLUE     170, 255,  85

// Default color HSV Values (for inspiration)
// #define HSV_AZURE       132, 102, 255
// #define HSV_BLACK         0,   0,   0
// #define HSV_BLUE        170, 255, 255
// #define HSV_CHARTREUSE   64, 255, 255
// #define HSV_CORAL        11, 176, 255
// #define HSV_CYAN        128, 255, 255
// #define HSV_GOLD         36, 255, 255
// #define HSV_GOLDENROD    30, 218, 218
// #define HSV_GREEN        85, 255, 255
// #define HSV_MAGENTA     213, 255, 255
// #define HSV_ORANGE       28, 255, 255
// #define HSV_PINK        234, 128, 255
// #define HSV_PURPLE      191, 255, 255
// #define HSV_RED           0, 255, 255
// #define HSV_SPRINGGREEN 106, 255, 255
// #define HSV_TEAL        128, 255, 128
// #define HSV_TURQUOISE   123,  90, 112
// #define HSV_WHITE         0,   0, 255
// #define HSV_YELLOW       43, 255, 255
// #define HSV_OFF         HSV_BLACK


//========================================================== CONFIGURABLE DEFAULTS ==========================================================
#define RGB_DEFAULT_TIME_OUT 30
#define RGB_FAST_MODE_TIME_OUT 3
#define RGB_TIME_OUT_MAX 600
#define RGB_TIME_OUT_MIN 10
#define RGB_TIME_OUT_STEP 10

bool disable_layer_color;

uint8_t dfa_state;  //state for my language switching DFA


bool rgb_enabled_flag;                  // Current LED state flag. If false then LED is off.
bool rgb_time_out_enable;               // Idle LED toggle enable. If false then LED will not turn off after idle timeout.
bool rgb_time_out_fast_mode_enabled;    // Enable flag for RGB timeout fast mode
bool rgb_time_out_user_value;           // This holds the toggle value set by user with ROUT_TG. It's necessary as RGB_TOG changes timeout enable.
uint16_t rgb_time_out_seconds;          // Idle LED timeout value, in seconds not milliseconds
uint16_t rgb_time_out_saved_seconds;    // The saved user config for RGB timeout period
led_flags_t rgb_time_out_saved_flag;    // Store LED flag before timeout so it can be restored when LED is turned on again.
