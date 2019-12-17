/*
Copyright 2019 Batuhan Başerdem <baserdem.batuhan@gmail.com> @bbaserdem
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

#include "quantum.h"
#ifdef AUDIO_ENABLE             // Audio stuff
    #include "audio_stuff.h"
#endif
#ifdef BACKLIGHT_ENABLE         // Backlight LED
    #include "backlight_stuff.h"
#endif
#include "macro_stuff.h"       // Double press keys
#ifdef MOUSEKEY_ENABLE          // Functions for mouse key emulation
    #include "mouse_emulation.h"
#endif
#include "process_records.h"    // Keycodes
#ifdef RGBLIGHT_ENABLE          // RGB backlight stuff
    #include "rgb_bl_stuff.h"
#endif
#ifdef RGB_MATRIX_ENABLE         // RGB individual key light
    #include "rgb_key_stuff.h"
#endif
#if (__has_include("secret.h")) && !defined(NO_SECRETS) // Secret macros
    #include "secrets.h"
#endif
#ifdef TAP_DANCE_ENABLE         // Tap dance functions
    #include "tap_dances.h"
#endif
#if (defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE) || defined(UCIS_ENABLE))
    #include "unicode_usage.h"
#endif
#include "wrappers.h"           // Layouts

/// Using enum kinda screws things up?
enum userspace_layers {
    _BA = 0,    // Base layer
    _GA,        // Game layer
    _NU,        // Numbers layer
    _SE,        // Settings layer
    _MO,        // Mouse emulation
    _MU,        // Music mode
};
//*/

// Function definitions that are findable
void matrix_init_keymap(void);
void shutdown_keymap(void);
void suspend_power_down_keymap(void);
void suspend_wakeup_init_keymap(void);
void matrix_scan_keymap(void);
uint32_t layer_state_set_keymap(uint32_t state);
uint32_t default_layer_state_set_keymap (uint32_t state);
void led_set_keymap(uint8_t usb_led);
void eeconfig_init_keymap(void);

// Record keyboard state in this variable, I don't know why I need union,
//  typedef struct screws things up a bit.
typedef union {
    uint32_t raw;
    struct {
        bool        lock_flag       :1;     // Current layer is locked?
        bool        game_flag       :1;     // Game layer was on previously?
        bool        rgb_blt_state   :1;     // (Backlight)  On load state?
        bool        rgb_blt_toggle  :1;     //              Is light on?
        bool        rgb_mat_state   :1;     // (Matrix)     On load state?
        bool        rgb_mat_toggle  :1;     //              Is light on?
        uint8_t     rgb_blt_mode    :6;     // (Backlight)  Animation mode
        uint8_t     rgb_blt_sat     :8;     //              Saturation
        uint8_t     rgb_blt_val     :8;     //              Brightness
        uint8_t     rgb_blt_speed   :8;     //              Speed
        uint8_t     rgb_mat_mode    :6;     // (Matrix)     Animation mode
        uint8_t     rgb_mat_sat     :8;     //              Saturation
        uint8_t     rgb_mat_val     :8;     //              Brightness
        uint8_t     rgb_mat_speed   :8;     //              Speed
        uint16_t    rgb_blt_hue     :9;     // (Backlight)  Hue
        uint16_t    rgb_mat_hue     :9;     // (Matrix)     Hue
    };
} userspace_config_t;

extern userspace_config_t userspace_config;

// Custom keycodes, with fallback

// Tap Dance
#ifdef TAP_DANCE_ENABLE
#define K_NU_GA TD(NUG)
#define K_SE_MO TD(SEM)
#else
#define K_NU_GA MO(_NU)
#define K_SE_MO MO(_SE)
#endif

#define XXX     KC_NO

// Define short macros
#define UNDO    LCTL(KC_Z)
#define REDO    LCTL(KC_Y)
#define COPY    LCTL(KC_C)
#define CUT     LCTL(KC_X)
#define PASTE   LCTL(KC_V)

// Rename mouse keys with 7 letters
#ifdef MOUSEKEY_ENABLE
#define MO_S_N  KC_MS_WH_UP
#define MO_S_S  KC_MS_WH_DOWN
#define MO_S_E  KC_MS_WH_RIGHT
#define MO_S_W  KC_MS_WH_LEFT
#define MO_N    KC_MS_UP
#define MO_S    KC_MS_DOWN
#define MO_E    KC_MS_RIGHT
#define MO_W    KC_MS_LEFT
#define MO_CL_L KC_MS_BTN1
#define MO_CL_R KC_MS_BTN2
#define MO_CL_M KC_MS_BTN3
#define MO_CL_4 KC_MS_BTN4
#define MO_CL_5 KC_MS_BTN5
#define MO_AC_0 KC_MS_ACCEL0
#define MO_AC_1 KC_MS_ACCEL1
#define MO_AC_2 KC_MS_ACCEL2
#else
#define MO_S_N  KC_NO
#define MO_S_S  KC_NO
#define MO_S_E  KC_NO
#define MO_S_W  KC_NO
#define MO_N    KC_NO
#define MO_S    KC_NO
#define MO_E    KC_NO
#define MO_W    KC_NO
#define MO_CL_L KC_NO
#define MO_CL_R KC_NO
#define MO_CL_M KC_NO
#define MO_CL_1 KC_NO
#define MO_CL_2 KC_NO
#define MO_AC_0 KC_NO
#define MO_AC_1 KC_NO
#define MO_AC_2 KC_NO
#endif

// Rename music keys for consistency
#ifdef AUDIO_ENABLE
#define MU_REC  KC_LCTL
#define MU_STOP KC_LALT
#define MU_PLAY KC_LGUI
#define MU_PLAY KC_LGUI
#define MU_FAST KC_UP
#define MU_SLOW KC_DOWN
#define MU_MASK KC_A
#else
#define MU_REC  KC_NO
#define MU_STOP KC_NO
#define MU_PLAY KC_NO
#define MU_PLAY KC_NO
#define MU_FAST KC_NO
#define MU_SLOW KC_NO
#define MU_MASK KC_NO
#endif

// Define UTF shortcuts here
#ifdef UNICODE_ENABLE
#define PHY_HBR UC(0x0127)
#define PHY_DEG UC(0x00b0)
#define CUR_LIR UC(0x20ba)
#define CUR_BIT UC(0x20bf)
#define CUR_EUR UC(0x20ac)
#define CUR_BPN UC(0x00a3)
#define CUR_YEN UC(0x00a5)
#define KC_ELLP UC(0x2026)
#else
#define PHY_HBR KC_NO
#define PHY_DEG KC_NO
#define CUR_LIR KC_NO
#define CUR_BIT KC_NO
#define CUR_EUR KC_NO
#define CUR_BPN KC_NO
#define CUR_YEN KC_NO
#define KC_ELLP MANUAL_ELLIPSIS
#endif
