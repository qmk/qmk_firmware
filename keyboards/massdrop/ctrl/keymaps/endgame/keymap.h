#include QMK_KEYBOARD_H

#include <print.h>
#include <string.h>
// HID has not yet been implemented for this keyboard
// #include "raw_hid.h"

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

extern bool g_suspend_state;
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
    _ML,         // Mouse Layout: Mouse Keys and mouse movement
    _GL,         // GIT Layout: GIT shortcuts and macros
    _VL,         // VIM Layout: VIM shorcuts and macros
    _YL,         // Yakuake Layout: Yakuake drop-down terminal shortcuts and macros
    _EL,         // KDE Layout: Shortcuts for KDE desktop using default KDE shortcuts settings
};

enum tapdance_keycodes {
    TD_LGUI_ML = 0,     // Tap dance key to switch to mouse layer _ML
    TD_APP_YL,
    TD_CTRL_TERM,       // Tap dance key to open terminal on LCTRL double press
};

enum ctrl_keycodes {
    U_T_AUTO = SAFE_RANGE, // USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR,              // USB Toggle Automatic GCR control
    DBG_TOG,               // DEBUG Toggle On / Off
    DBG_MTRX,              // DEBUG Toggle Matrix Prints
    DBG_KBD,               // DEBUG Toggle Keyboard Prints
    DBG_MOU,               // DEBUG Toggle Mouse Prints
    MD_BOOT,               // Restart into bootloader after hold timeout
    SEL_CPY,               // Select Copy. Select the word cursor is pointed at and copy, using double mouse click and ctrl+c
    ROUT_TG,               // Timeout Toggle. Toggle idle LED time out on or off
    ROUT_VI,               // Timeout Value Increase. Increase idle time out before LED disabled
    ROUT_VD,               // Timeout Value Decrease. Decrease idle time out before LED disabled
    ROUT_FM,               // RGB timeout fast mode toggle
    COPY_ALL,              // Copy all text using ctrl(a+c)
    TERMINAL,              // CTRL+ALT+T
};

enum string_macro_keycodes {
    // The start of this enum should always be equal to end of ctrl_keycodes + 1
    G_INIT = TERMINAL + 1, // git init
    G_CLONE,               // git clone
    G_CONF,                // git config --global
    G_ADD,                 // git add
    G_DIFF,                // git diff
    G_RESET,               // git reset
    G_REBAS,               // git rebase
    G_BRANH,               // git branch
    G_CHECK,               // git checkout
    G_MERGE,               // git merge
    G_REMTE,               // git remote add
    G_FETCH,               // git fetch
    G_PULL,                // git pull
    G_PUSH,                // git push
    G_COMM,                // git commit
    G_STAT,                // git status
    G_LOG,                 // git log
};
