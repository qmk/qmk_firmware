/*
Copyright 2017 Christopher Courtney <drashna@live.com> @drashna
Copyright 2020 Jacob Jerrell <jacob.jerrell@gmail.com> @JacobJerrell

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

#include "version.h"
#include "eeprom.h"
#include "process_records.h"
#include "wrappers.h"
#if defined(RGB_MATRIX_ENABLE)
#    include "rgb_matrix_stuff.h"
#endif

/* Define layer names */
enum userspace_layers {
    _WORKMAN = 0,
    _QWERTY,
    _WWORKMAN,
    _WQWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
    _MOD,
    LAYER_SAFE_RANGE,
};

#define MODS_SHIFT_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))
#define MODS_CTRL_MASK   (MOD_BIT(KC_LCTL)|MOD_BIT(KC_RCTRL))
#define MODS_ALT_MASK    (MOD_BIT(KC_LALT)|MOD_BIT(KC_RALT))
#define MODS_GUI_MASK    (MOD_BIT(KC_LGUI)|MOD_BIT(KC_RGUI))

bool          mod_key_press_timer(uint16_t code, uint16_t mod_code, bool pressed);
bool          mod_key_press(uint16_t code, uint16_t mod_code, bool pressed, uint16_t this_timer);
void          matrix_init_keymap(void);
void          shutdown_keymap(void);
void          suspend_power_down_keymap(void);
void          suspend_wakeup_init_keymap(void);
void          matrix_scan_keymap(void);
layer_state_t layer_state_set_keymap(layer_state_t state);
layer_state_t default_layer_state_set_keymap(layer_state_t state);
void          led_set_keymap(uint8_t usb_led);
void          eeconfig_init_keymap(void);
bool          hasAllBitsInMask(uint8_t value, uint8_t mask);

// clang-format off
#ifdef KEYBOARD_planck_ez
typedef union {
    uint32_t raw;
    struct {
        bool    rgb_layer_change     :1;
        bool    rgb_matrix_idle_anim :1;
    };
} userspace_config_t;
// clang-format on

extern userspace_config_t userspace_config;
#endif
