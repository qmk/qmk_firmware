/*
  Copyright 2020 Joel Elkins <joel@elkins.com>

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

#include QMK_KEYBOARD_H

// Secrets

#if !defined(NO_SECRETS) && __has_include("secrets.h")
#  define DO_SECRETS
#endif

void send_secret_string(uint8_t n);

// standard layers

enum jdelkins_layers {
    _QWERTY = 0,
    _RPT,
    _GAME,
    _FUNC,
    _KP,
    _SECRETS,
    _ADJUST,
    _LAYER_MAX
};

// key definitions

typedef union {
        uint32_t raw;
        struct {
                bool system_mac :1;
        };
} user_config_t;

extern user_config_t user_config;

static inline void do_mac_key(uint16_t norm_key, uint16_t mac_key, keyrecord_t *record) {
    uint16_t key = user_config.system_mac ? mac_key : norm_key;
    if (record->event.pressed)
        register_code16(key);
    else
        unregister_code16(key);
}

enum jdelkins_keycodes {
    KB_MAKE = SAFE_RANGE,
    KB_FLSH,
    KB_VRSN,
    KB_BOOT,
    FW_WRD,
    BK_WRD,
    KB_BOL,
    KB_EOL,
    TG_SYS,
    KB_COPY,
    KB_PASTE,
    MY_GUI,
    MY_ALT,
    MY_RGUI,
    MY_RALT,
    MY_CALC,

#ifdef DO_SECRETS
    KC_SECRET_1,
    KC_SECRET_2,
    KC_SECRET_3,
    KC_SECRET_4,
    KC_SECRET_5,
    KC_SECRET_6,
#endif

    USER_SAFE_RANGE,
};

#ifdef DO_SECRETS
#  define KC_SEC1 KC_SECRET_1
#  define KC_SEC2 KC_SECRET_2
#  define KC_SEC3 KC_SECRET_3
#  define KC_SEC4 KC_SECRET_4
#  define KC_SEC5 KC_SECRET_5
#  define KC_SEC6 KC_SECRET_6
#else
#  define KC_SEC1 KC_NO
#  define KC_SEC2 KC_NO
#  define KC_SEC3 KC_NO
#  define KC_SEC4 KC_NO
#  define KC_SEC5 KC_NO
#  define KC_SEC6 KC_NO
#endif

#define MODS_SHIFT (get_mods() & MOD_MASK_SHIFT)
#define MODS_CTRL  (get_mods() & MOD_MASK_CTRL)
#define MODS_ALT   (get_mods() & MOD_MASK_ALT)
#define MODS_GUI   (get_mods() & MOD_MASK_GUI)

#define MY_CAPS LCTL_T(KC_CAPS)
#define MY_SPC  LT(_FUNC, KC_SPC)

#define NUMLOCK_ON host_keyboard_led_state().num_lock
#define CAPSLOCK_ON host_keyboard_led_state().caps_lock

#ifdef TAP_DANCE_ENABLE

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD = 2,
    DOUBLE_TAP = 3,
    DOUBLE_HOLD = 4,
    DOUBLE_SINGLE_TAP = 5, //send two single taps
    TRIPLE_TAP = 6,
    TRIPLE_HOLD = 7
};

int cur_dance(tap_dance_state_t *state);      // prefer tap
int hold_cur_dance(tap_dance_state_t *state); // prefer hold

#endif // TAP_DANCE_ENABLE
