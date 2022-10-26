/* Copyright 2021 Jonavin Eng @Jonavin
   Copyright 2022 gourdo1 <gourdo1@outlook.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

// DEFINE MACROS
#define ARRAYSIZE(arr) sizeof(arr) / sizeof(arr[0])

// LAYERS -- Note: to avoid compile problems, make sure total layers matches DYNAMIC_KEYMAP_LAYER_COUNT defined in config.h (where _COLEMAK layer is defined)
enum custom_user_layers {
    _BASE,
    _FN1,
    _NUMPADMOUSE,
    _MOUSEKEY,
    #ifdef GAME_ENABLE
    _GAME
    #endif //GAME_ENABLE
};

#define KC_CAD LALT(LCTL(KC_DEL))
#define LOCKPC LGUI(KC_L)
#define KC_AF4 LALT(KC_F4)
#define KC_TASK LCTL(LSFT(KC_ESC))
#define CT_PGUP RCTL(KC_PGUP)
#define CT_PGDN RCTL(KC_PGDN)
#define CT_HOME RCTL(KC_HOME)
#define CT_END RCTL(KC_END)
#define SWAP_L SGUI(KC_LEFT)                 // Swap application to left display
#define SWAP_R SGUI(KC_RGHT)                 // Swap application to right display

// KEYCODES
enum custom_user_keycodes {
    KC_00 = SAFE_RANGE,
        ENCFUNC,       // Encoder function
        CAPSNUM,       // Capslock key function
        LEFTOFENC,     // Key to the left of the encoder (i.e. F13)
        BELOWENC,      // Key below encoder
        PRNCONF,       // Print verbose statuses of all user_config toggles
        WINLOCK,       // Toggles Windows key on and off
        RGB_TOI,       // Timeout idle time up
        RGB_TOD,       // Timeout idle time down
        RGB_NITE,      // Disables RGB backlighting effects but allows RGB indicators to still work

        TG_CAPS,       // Toggles RGB highlighting of alphas during capslock
        TG_PAD,        // Toggles RGB highlighting of keys on numpad+mousekeys layer
        TG_TDCAP,      // Toggles double tap shift for CapsLock
        TG_DEL,        // Swaps DEL and HOME key locations
        TG_ENC,        // Toggle Encoder button functionality
        TG_ESC,        // Toggle ESC double tap for _BASE layer
        TG_INS,        // Toggle location of INS
        TG_SPCMOD,     // Toggle disabling of modded-SPACE functions
        TG_AUTOCR,     // Toggle AutoCorrect
        TG_ENGCAP,     // Toggle highlighting Non-English letters during CAPSLOCK on ISO boards

        YAHOO,         // yahoo.com
        OUTLOOK,       // outlook.com
        GMAIL,         // gmail.com
        HOTMAIL,       // hotmail.com
        DOTCOM,        // .com

        EMO_SHRUG,     // `\_("/)_/`
        EMO_CONFUSE,   // (*_*)
        EMO_SAD,       // :'-(
        EMO_NERVOUS,   // (~_~;)
        EMO_JOY,       // (^o^)
        EMO_TEARS,     // (T_T)

        KC_TSTOG,      // Tab Scroll Toggle

        NEW_SAFE_RANGE // New safe range for keymap level custom keycodes
};

// Set up boolean variables to track user customizable configuration options
typedef union {
  uint32_t raw;
  struct {
    bool     rgb_hilite_caps :1;
    bool     rgb_hilite_numpad :1;
    bool     esc_double_tap_to_baselyr :1;
    bool     del_right_home_top :1;
    bool     double_tap_shift_for_capslock :1;
    bool     encoder_press_mute_or_media :1;
    bool     ins_on_shft_bkspc_or_del :1;
    bool     disable_space_mods :1;
    bool     autocorrect :1;
    bool     rgb_english_caps :1;
  };
} user_config_t;

user_config_t user_config;

//#define LSFTCAPSWIN TD(TD_LSFT_CAPS_WIN)

// ENCODER ACTIONS
#ifdef ENCODER_ENABLE
void encoder_action_volume(bool clockwise);
void encoder_action_mediatrack(bool clockwise);
void encoder_action_navword(bool clockwise);
void encoder_action_navpage(bool clockwise);

uint8_t get_selected_layer(void);
void encoder_action_layerchange(bool clockwise);

#if defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE)
void encoder_action_rgb_speed(bool clockwise);
void encoder_action_rgb_hue(bool clockwise);
void encoder_action_rgb_saturation(bool clockwise);
void encoder_action_rgb_brightness(bool clockwise);
void encoder_action_rgb_mode(bool clockwise);
#endif // RGB_MATRIX_ENABLE / RGBLIGHT_ENABLE

#ifdef ALTTAB_SCROLL_ENABLE
void encoder_action_alttabscroll(bool clockwise);
void encoder_toggle_alttabscroll(void);
void encoder_tick_alttabscroll(void);
#endif // ALTTAB_SCROLL_ENABLE
#endif // ENCODER_ENABLE

#ifdef RGB_MATRIX_ENABLE
void activate_rgb_nightmode(bool turn_on);
bool get_rgb_nightmode(void);
#endif

// IDLE TIMEOUTS
#ifdef IDLE_TIMEOUT_ENABLE
#define TIMEOUT_THRESHOLD_DEFAULT 15 // default timeout minutes
#define TIMEOUT_THRESHOLD_MAX 140 // upper limits (2 hours and 10 minutes -- no rgb indicators above this value)

//prototype  functions
uint16_t get_timeout_threshold(void);
void timeout_reset_timer(void);
void timeout_update_threshold(bool increase);
void timeout_tick_timer(void);
#endif //IDLE_TIMEOUT_ENABLE

// OTHER FUNCTION PROTOTYPE
void activate_numlock(bool turn_on);