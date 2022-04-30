/* Copyright 2022 Daniel Weeks (@xanimos)
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

#include <print.h>
#include <string.h>

#define MILLISECONDS_IN_SECOND 1000

// These are just to make it neater to use builtin HSV values in the keymap
#define RED {HSV_RED}
#define CORAL {HSV_CORAL}
#define ORANGE {HSV_ORANGE}
#define GOLDEN {HSV_GOLDENROD}
#define GOLD {HSV_GOLD}
#define YELLOW {HSV_YELLOW}
#define CHART {HSV_CHARTREUSE}
#define GREEN {HSV_GREEN}
#define SPRING {HSV_SPRINGGREEN}
#define TURQ {HSV_TURQUOISE}
#define TEAL {HSV_TEAL}
#define CYAN {HSV_CYAN}
#define AZURE {HSV_AZURE}
#define BLUE {HSV_BLUE}
#define PURPLE {HSV_PURPLE}
#define MAGENT {HSV_MAGENTA}
#define PINK {HSV_PINK}

//========================================================== CONFIGURABLE DEFAULTS ==========================================================
#define RGB_DEFAULT_TIME_OUT 30
#define RGB_FAST_MODE_TIME_OUT 3
#define RGB_TIME_OUT_MAX 600
#define RGB_TIME_OUT_MIN 10
#define RGB_TIME_OUT_STEP 10

extern rgb_config_t rgb_matrix_config;
bool disable_layer_color;

bool rgb_enabled_flag;                  // Current LED state flag. If false then LED is off.
bool rgb_time_out_enable;               // Idle LED toggle enable. If false then LED will not turn off after idle timeout.
bool rgb_time_out_fast_mode_enabled;    // Enable flag for RGB timeout fast mode
bool rgb_time_out_user_value;           // This holds the toggle value set by user with ROUT_TG. It's necessary as RGB_TOG changes timeout enable.
uint16_t rgb_time_out_seconds;          // Idle LED timeout value, in seconds not milliseconds
uint16_t rgb_time_out_saved_seconds;    // The saved user config for RGB timeout period
led_flags_t rgb_time_out_saved_flag;    // Store LED flag before timeout so it can be restored when LED is turned on again.

enum layout_names {
    _KL=0,       // Keys Layout: The main keyboard layout that has all the characters
    _FL,         // Function Layout: The function key activated layout with default functions and some added ones
    _GL,         // GIT Layout: GIT shortcuts and macros
    _NUMPAD,     // Numpad Layout: Adds a numpad to the keys
};

// Tap Dance keycodes
enum td_keycodes {
    TD_FN_SWITCH = 0
};

// Define a type containing as many tapdance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_HOLD,
    TD_DOUBLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// Declare your tapdance functions:

// Function to determine the current tapdance state
td_state_t cur_dance(qk_tap_dance_state_t *state);

// `finished` and `reset` functions for each tapdance keycode
void fn_tap_finished(qk_tap_dance_state_t *state, void *user_data);
void fn_tap_reset(qk_tap_dance_state_t *state, void *user_data);

enum ctrl_keycodes {
    MD_BOOT = SAFE_RANGE,  // Restart into bootloader after hold timeout
    ROUT_TG,               // Timeout Toggle. Toggle idle LED time out on or off
    ROUT_VI,               // Timeout Value Increase. Increase idle time out before LED disabled
    ROUT_VD,               // Timeout Value Decrease. Decrease idle time out before LED disabled
    ROUT_FM,               // RGB timeout fast mode toggle
    TOG_NPD,               // Toggle Numpad On/Off
    COPY_ALL,              // Copy all text using ctrl(a+c)
};

enum string_macro_keycodes {
    // The start of this enum should always be equal to end of ctrl_keycodes + 1
    G_INIT = COPY_ALL + 1, // git init
    G_CLONE,               // git clone
    G_ADD,                 // git add
    G_DIFF,                // git diff
    G_RESET,               // git reset --soft
    G_BRANH,               // git branch list
    G_CHECK,               // git checkout
    G_REMTE,               // git remote add
    G_FETCH,               // git fetch
    G_PULL,                // git pull
    G_PUPST,               // git pull upstream
    G_PUSH,                // git push
    G_PSORG,               // git push -u origin
    G_PSFWL,               // git push --force-with-lease
    G_COMM,                // git commit
    G_COMSG,               // git commit -m ": [TFS-]"
    G_STAT,                // git status
    G_LOG,                 // git log
};




