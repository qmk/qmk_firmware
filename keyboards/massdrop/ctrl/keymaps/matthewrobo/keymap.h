/*
QMK Firmware Massdrop CTRL M-AS Keymap
Copyright (C) 2020 matthewrobo

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

// HID has not yet been implemented for this keyboard
// #include "raw_hid.h"

#define MILLISECONDS_IN_SECOND 1000

// These are just to make it neater to use builtin HSV values in the keymap
// clang-format off
#define WHITE {HSV_WHITE}
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
#define HSV_CREAM 24, 240, 255
#define CREAM {HSV_CREAM}
#define HSV_9B59B5 208, 192, 255
#define M9B59B5 {HSV_9B59B5}
// clang-format on

#define LT_CAPS LT(_NL, KC_CAPS)
#define _LAYER_ KC_TRNS

//========================================================== CONFIGURABLE DEFAULTS ==========================================================
extern bool         g_suspend_state;
extern rgb_config_t rgb_matrix_config;
bool                disable_layer_color;

bool rgb_enabled_flag;  // Current LED state flag. If false then LED is off.

enum layout_names {
    _KL = 0,  // Keys Layout: The main keyboard layout that has all the characters
    _NL,      // Navigation Layout: Cursor keys and numpad inputs
    _FL,      // Function Layout: The function key activated layout with default functions and some added ones
};

enum ctrl_keycodes {
    U_T_AUTO = SAFE_RANGE,  // USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR,               // USB Toggle Automatic GCR control
    DBG_TOG,                // DEBUG Toggle On / Off
    DBG_MTRX,               // DEBUG Toggle Matrix Prints
    DBG_KBD,                // DEBUG Toggle Keyboard Prints
    DBG_MOU,                // DEBUG Toggle Mouse Prints
    MD_BOOT,                // Restart into bootloader after hold timeout
    MAS_CRM,
    MAS_PRP,
    MAS_RED,
    MAS_GRN,
    MAS_BLU,
    MAS_CYN,
    MAS_MGT,
    MAS_YEL,
    MAS_KEY,
    MAS_WHT,
};
