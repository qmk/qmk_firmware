/* Copyright 2021 Christian C. Berclaz
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
#pragma once

#include QMK_KEYBOARD_H

// Custom layers
enum default_layers {
    _QWERTY_MAC,    // QWERTY Mac base layout
    _MAC_NAV_1,     // Mac Navigation layer 1
    _MAC_NAV_2,     // Mac Navigation layer 2
    _QWERTY_WIN,    // QWERTY Windows base layout
    _WIN_NAV_1,     // Windows Navigation layer 1
    _WIN_NAV_2,     // Windows Navigation layer 2
    _QWERTY_LINUX,  // QWERTY Linux base layout
    _LINUX_NAV_1,   // Linux Navigation layer 1
    _LINUX_NAV_2,   // Linux Navigation layer 2
    _RAISE,         // Raise layer on ortho
    _LOWER,         // Lower layer on ortho
    _MOUSE,         // Mouse key layer
    _EX_MOUSE,      // Mouse key layer (exlusive)
    _NUM,           // Numerical layer (for 40% layouts)
    _ADJUST_MAC,    // Synonym
    _ADJUST_WIN,    // Adjust for Windows
    _ADJUST_LINUX,  // Adjust for Linux
    _CONFIG,        // Keyboard configuation layer
};

// Custom keys
enum custom_keycodes {
    QWERTY = SAFE_RANGE,  // Key that allows to fall back to the default layer
    KC_WF1,
    KC_WF2,
    KC_WF3,
    KC_WF4,
    KC_WF5,
    KC_WF6,
    KC_WF7,
    KC_WF8,
    KC_WF9,
    KC_WF10,
    KC_WF11,
    KC_WF12,
    DF_M_P,   // Make Mac layer the default persistent layer
    DF_L_P,   // Make Linux layer the default persistent layer
    DF_W_P,   // Make Windows layer the default persistent layer
    WIN_SWT,  // Function keys F1 to F12 behave as expected
    MAC_SWT,  // Function keys F1 to F12 behave as expected if Apple Fn is sent
    INV_AFN,  // Inverse KC_APPLE_FN
    CU_BSPC,  // Acts as normal Backspace and Delete when shifted
    CU_SPBC,  // Acts as normal Space and Backspace when shifted
    NEW_SAFE_RANGE
};

// set the permissive hold if not already set
#ifndef PERMISSIVE_HOLD
#    define PERMISSIVE_HOLD
#endif

// when defined GRAVE_ESC will always act as ESC when CTRL is held.
// we ensure it to be set
#ifndef GRAVE_ESC_CTRL_OVERRIDE
#    define GRAVE_ESC_CTRL_OVERRIDE
#endif

#ifndef GRAVE_ESC_ALT_OVERRIDE
#   define GRAVE_ESC_ALT_OVERRIDE
#endif

#ifndef GRAVE_ESC_GUI_OVERRIDE
#   define GRAVE_ESC_GUI_OVERRIDE
#endif

// RGB standard colors
// CAPS LOCK color  - Warm white
#define RGB_CAPS_R 0xe6
#define RGB_CAPS_G 0x87
#define RGB_CAPS_B 0x19

// NAV 1 color - Blue
#define RGB_NAV1_R 0x33
#define RGB_NAV1_G 0x66
#define RGB_NAV1_B 0xff

// NAV 2 color - Purple
#define RGB_NAV2_R 0x99
#define RGB_NAV2_G 0x33
#define RGB_NAV2_B 0xff

// ADJ color  - Green
#define RGB_ADJ_R 0x33
#define RGB_ADJ_G 0xcc
#define RGB_ADJ_B 0x33

// NUM color  - Cyan
#define RGB_NUM_R 0x00
#define RGB_NUM_G 0xff
#define RGB_NUM_B 0xff

// MOUSE color - Orange
#define RGB_MSE_R 0xff
#define RGB_MSE_G 0x26
#define RGB_MSE_B 0x00

#define CHAR_MOVE KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT
#define LINE_MOVE KC_HOME, KC_PGDN, KC_PGUP, KC_END

#define MAC_NAV _______, S_SHIFT, _______, M_NAV_2, _______
#define LINUX_NAV _______, S_SHIFT, _______, L_NAV_2, _______
#define WIN_NAV _______, S_SHIFT, _______, W_NAV_2, _______

#define TWO_TRS _______, _______
#define THREE_TRS TWO_TRS, _______
#define FOUR_TRS THREE_TRS, _______
#define FIVE_TRS FOUR_TRS, _______
#define SIX_TRS FIVE_TRS, _______
#define SEVEN_TRS SIX_TRS, _______

#define TWO_NOP XXXXXXX, XXXXXXX
#define THREE_NOP TWO_NOP, XXXXXXX
#define FOUR_NOP THREE_NOP, XXXXXXX
#define FIVE_NOP FOUR_NOP, XXXXXXX
#define SIX_NP FIVE_NOP, XXXXXXX
#define SEVEN_NOP SIX_NOP, XXXXXXX

#define KC_FUNC KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12

// #define CPS_CTL     CTL_T(KC_CAPS)
#define TAB_CTL CTL_T(KC_TAB)
#define ADJ_M MO(_ADJUST_MAC)
#define ADJ_L MO(_ADJUST_LINUX)
#define ADJ_W MO(_ADJUST_WIN)
#define CONFIG MO(_CONFIG)
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define TMUX LT(_TMUX, KC_SCLN)
#define VIM LT(_VIM, KC_V)
#define S_SHIFT SFT_T(KC_S)
#define A_SHIFT SFT_T(KC_A)
#define R_SHIFT RSFT_T(KC_BSLS)
#define QUT_SFT RSFT_T(KC_QUOT)
#define GUI_BSL RGUI_T(KC_BSLS)
#define ALT_BSL RALT_T(KC_BSLS)
#define BSL_RSE LT(_RAISE, KC_BSLS)
#define S_MOUSE LT(_MOUSE, KC_S)
#define A_MOUSE LT(_MOUSE, KC_A)

#define END_F_M LT(_ADJUST_MAC, KC_END)
#define END_F_L LT(_ADJUST_LINUX, KC_END)
#define END_F_W LT(_ADJUST_WIN, KC_END)
#define SPC_LWR LT(_LOWER, KC_SPC)
#define SPC_RSE LT(_RAISE, KC_SPC)
#define SLS_SFT RSFT_T(KC_SLSH)
#define FN_NUM LT(_ADJUST, KC_NO)

#define L_MOD LT(_RAISE, KC_SPC)  // for split space bar, left bar
#define R_MOD LT(_LOWER, KC_SPC)  // for split space bar, right bar
//#define R_MOD       RCTL_T(KC_SPC)  // for split space bar, right bar

#ifndef SHIFT_ENABLE
#define CU_BSPC KC_BSPC
#define CU_SPBC KC_SPC
#endif

// This section is copied from SpacebarRacercar userspace to insert the
// smart shift keycode, this is governed by the SHIFT_ENABLE switch
#ifdef SHIFT_ENABLE

// Normal shift status
#    define SHIFT_NORM(kc1, kc2)          \
        if (record->event.pressed) {      \
            if (lshift || rshift) {       \
                register_code(KC_LSFT);   \
                unregister_code(kc2);     \
                register_code(kc2);       \
            } else {                      \
                unregister_code(KC_LSFT); \
                unregister_code(kc1);     \
                register_code(kc1);       \
            }                             \
        } else {                          \
            unregister_code(kc1);         \
            unregister_code(kc2);         \
        }                                 \
        return false;

// Inverted shift status
#    define SHIFT_SWITCH(kc1, kc2)        \
        if (record->event.pressed) {      \
            if (lshift || rshift) {       \
                unregister_code(KC_LSFT); \
                unregister_code(kc2);     \
                register_code(kc2);       \
            } else {                      \
                register_code(KC_LSFT);   \
                unregister_code(kc1);     \
                register_code(kc1);       \
            }                             \
        } else {                          \
            unregister_code(kc1);         \
            unregister_code(kc2);         \
            if (lshift || rshift)         \
                register_code(KC_LSFT);   \
            else                          \
                unregister_code(KC_LSFT); \
        }                                 \
        return false;

// Always shifted
#    define SHIFT_ALL(kc1, kc2)           \
        if (record->event.pressed) {      \
            register_code(KC_LSFT);       \
            if (lshift || rshift) {       \
                unregister_code(kc2);     \
                register_code(kc2);       \
            } else {                      \
                unregister_code(kc1);     \
                register_code(kc1);       \
            }                             \
        } else {                          \
            unregister_code(kc1);         \
            unregister_code(kc2);         \
            if (lshift || rshift)         \
                register_code(KC_LSFT);   \
            else                          \
                unregister_code(KC_LSFT); \
        }                                 \
        return false;

// Never shifted
#    define SHIFT_NO(kc1, kc2)            \
        if (record->event.pressed) {      \
            unregister_code(KC_LSFT);     \
            if (lshift || rshift) {       \
                unregister_code(kc2);     \
                register_code(kc2);       \
            } else {                      \
                unregister_code(kc1);     \
                register_code(kc1);       \
            }                             \
        } else {                          \
            unregister_code(kc1);         \
            unregister_code(kc2);         \
            if (lshift || rshift)         \
                register_code(KC_LSFT);   \
            else                          \
                unregister_code(KC_LSFT); \
        }                                 \
        return false;

#endif

// Mouse
#ifdef MOUSEKEY_ENABLE
#    ifdef TAP_DANCE_ENABLE

// mouse parameters setup
#        define MK_KINETIC_SPEED
#        define MOUSEKEY_WHEEL_TIME_TO_MAX 80

// Tap Dance declarations
enum {
    TD_LSHIFT_MOUSE,
    TD_CTRL_CAPS,
    TD_ADJ_M_NUM,
    TD_ADJ_L_NUM,
    TD_ADJ_W_NUM,
};

// Define the keycode for the mouse tap dance
#        define SFT_MSE TD(TD_LSHIFT_MOUSE)
#        define CPS_CTL TD(TD_CTRL_CAPS)
#        define TG_MSE TG(_EX_MOUSE)
#        define TG_NUM TG(_NUM)
#        define TD_ADJM TD(TD_ADJ_M_NUM)
#        define TD_ADJL TD(TD_ADJ_L_NUM)
#        define TD_ADJW TD(TD_ADJ_W_NUM)

#    else

#        define SFT_MSE KC_RSFT
#        define TG_MSE _______
#        define CPS_CTL CTL_T(KC_CAPS)

#    endif
#endif

//#define TAPPING_TOGGLE 2
#define M_TG_N1 TG(_MAC_NAV_1)
#define L_TG_N1 TG(_LINUX_NAV_1)
#define W_TG_N1 TG(_WIN_NAV_1)
#define M_TG_N2 TG(_MAC_NAV_2)
#define L_TG_N2 TG(_LINUX_NAV_2)
#define W_TG_N2 TG(_WIN_NAV_2)

#define DF_MAC DF(_QWERTY_MAC)
#define DF_WIN DF(_QWERTY_WIN)
#define DF_LNX DF(_QWERTY_LINUX)

// Mac only definitions
#define M_NAV_1 LT(_MAC_NAV_1, KC_D)
#define M_NAV_2 MO(_MAC_NAV_2)
#define M_F_WRD A(KC_RIGHT)
#define M_B_WRD A(KC_LEFT)

// Linux only definitions
#define L_NAV_1 LT(_LINUX_NAV_1, KC_D)
#define L_NAV_2 MO(_LINUX_NAV_2)
#define L_F_WRD A(KC_RIGHT)
#define L_B_WRD A(KC_LEFT)

// Windows only definitions
#define W_NAV_1 LT(_WIN_NAV_1, KC_D)
#define W_NAV_2 MO(_WIN_NAV_2)
#define W_F_WRD C(KC_RIGHT)
#define W_B_WRD C(KC_LEFT)
