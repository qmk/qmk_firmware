/* Copyright 2019-2021 Konstantin Đorđević <vomindoraan@gmail.com>
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

#include "quantum.h"
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
    #include "rgb.h"
#endif
#ifdef TAP_DANCE_ENABLE
    #include "tap_dance.h"
#endif
#if defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE)
    #include "unicode.h"
#endif

#ifdef LAYER_FN
    #define FN      MO(L_FN)
    #define FNLK    TG(L_FN)
    #define FN_CAPS LT(L_FN, KC_CAPS)
    #define FN_ESC  LT(L_FN, KC_ESC)
    #define FN_FNLK TT(L_FN)
#endif

#ifdef LAYER_NUMPAD
    #define NUMPAD TG(L_NUMPAD)
#endif

#define BREAK LCTL(KC_PAUS)
#define SYSRQ LALT(KC_PSCR)

#define MV_UP   LCTL(KC_UP)
#define MV_DOWN LCTL(KC_DOWN)
#define MV_LEFT LCTL(KC_LEFT)
#define MV_RGHT LCTL(KC_RGHT)
#define TOP     LCTL(KC_HOME)
#define BOTTOM  LCTL(KC_END)
#define TAB_PRV LCTL(KC_PGUP)
#define TAB_NXT LCTL(KC_PGDN)
#define DEL_PRV LCTL(KC_BSPC)
#define DEL_NXT LCTL(KC_DEL)

#define DST_ADD LCTL(LGUI(KC_D))
#define DST_REM LCTL(LGUI(KC_F4))
#define DST_PRV LCTL(LGUI(KC_LEFT))
#define DST_NXT LCTL(LGUI(KC_RGHT))
#ifndef DST_MOD_MASK
    #define DST_MOD_MASK MOD_MASK_SHIFT
#endif

#define LCT_CPS LCTL_T(KC_CAPS)
#define RSF_SLS RSFT_T(KC_SLSH)

// Clear mods, perform action, restore mods
#define CLEAN_MODS(action) {       \
        uint8_t mods = get_mods(); \
        clear_mods();              \
        action;                    \
        set_mods(mods);            \
    }

enum layers_user {
    L_BASE,
#ifdef LAYER_FN
    L_FN,
#endif
#ifdef LAYER_NUMPAD
    L_NUMPAD,
#endif

    LAYERS_KEYMAP,
};

enum keycodes_user {
    CLEAR = SAFE_RANGE,
    DST_P_R,
    DST_N_A,

    RANGE_KEYMAP,
};

void keyboard_pre_init_keymap(void);
void eeconfig_init_keymap(void);
void keyboard_post_init_keymap(void);

layer_state_t layer_state_set_keymap(layer_state_t state);

void led_set_keymap(uint8_t usb_led);
bool led_update_keymap(led_t led_state);

bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
