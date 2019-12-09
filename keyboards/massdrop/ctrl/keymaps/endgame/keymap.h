#include QMK_KEYBOARD_H

// Include for debugging.
#include <print.h>

#define MILLISECONDS_IN_SECOND 1000

//========================================================== CONFIGURABLE DEFAULTS ==========================================================
#define RGB_DEFAULT_TIME_OUT 30
#define RGB_FAST_MODE_TIME_OUT 3
#define RGB_TIME_OUT_MAX 600
#define RGB_TIME_OUT_MIN 10
#define RGB_TIME_OUT_STEP 10

#define _KL 0       // Keys Layout: The main keyboard layout that has all the characters
#define _FL 1       // Function Layout: The function key activated layout with default functions and some added ones
#define _ML 2       // Mouse Layout: Mouse Keys and mouse movement
#define _VL 3       // VIM Layout: VIM shorcuts and macros
#define _GL 4       // GIT Layout: GIT shortcuts and macros
#define _YL 5       // Yakuake Layout: Yakuake drop-down terminal shortcuts and macros
#define _EL 6       // KDE Layout: Shortcuts for KDE desktop using default KDE shortcuts settings

#define TG_NKRO MAGIC_TOGGLE_NKRO //Toggle 6KRO / NKRO mode

#define MODS_SHIFT  (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))
#define MODS_CTRL  (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTRL))
#define MODS_ALT  (get_mods() & MOD_BIT(KC_LALT) || get_mods() & MOD_BIT(KC_RALT))

extern bool g_suspend_state;
extern rgb_config_t rgb_matrix_config;
bool disable_layer_color;

bool rgb_enabled_flag;                  // Current LED state flag. If false then LED is off.
bool rgb_time_out_enable;               // Idle LED toggle enable. If false then LED will not turn off after idle timeout.
bool rgb_time_out_fast_mode_enabled;
bool rgb_time_out_user_value;           // This holds the toggle value set by user with ROUT_TG. It's necessary as RGB_TOG changes timeout enable.
uint16_t rgb_time_out_seconds;          // Idle LED timeout value, in seconds not milliseconds
uint16_t rgb_time_out_saved_seconds;
led_flags_t rgb_time_out_saved_flag;    // Store LED flag before timeout so it can be restored when LED is turned on again.

keymap_config_t keymap_config;

enum tapdance_keycodes {
    TD_LGUI_ML = 0,     // Tap dance key to switch to mouse layer _ML
    TD_LCTRL_TERM,      // Tap dance key to open terminal on LCTRL double press
    TD_RCTRL_TERM,      // Tap dance key to open terminal on RCTRL double press
    TD_LSFT_CAPS,       /* Tap dance key to toggle CAPS LOCK on SHIFT double press
                            Note that this can override some shortcuts in some IDE's.
                            RSFT is left clear of modifications and should replace LSFT in such case */
    TD_F_FIND,          // Tap dance key to send LCTRL+F on KC_F double press
    TD_C_COPY,          // Tap dance key to send LCTRL+C on KC_C double press
    TD_X_CUT,           // Tap dance key to send LCTRL+X on KC_X double press
    TD_V_PASTE,         // Tap dance key to send LCTRL+V on KC_V double press
};

enum ctrl_keycodes {
    U_T_AUTO = SAFE_RANGE, //USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR,              //USB Toggle Automatic GCR control
    DBG_TOG,               //DEBUG Toggle On / Off
    DBG_MTRX,              //DEBUG Toggle Matrix Prints
    DBG_KBD,               //DEBUG Toggle Keyboard Prints
    DBG_MOU,               //DEBUG Toggle Mouse Prints
    MD_BOOT,               //Restart into bootloader after hold timeout
    SEL_CPY,               //Select Copy. Select the word cursor is pointed at and copy, using double mouse click and ctrl+c
    ROUT_TG,               //Timeout Toggle. Toggle idle LED time out on or off
    ROUT_VI,               //Timeout Value Increase. Increase idle time out before LED disabled
    ROUT_VD,               //Timeout Value Decrease. Decrease idle time out before LED disabled
    ROUT_FM,               //RGB timeout fast mode toggle
    COPY_ALL,              //Copy all text using ctrl(a+c)
};
