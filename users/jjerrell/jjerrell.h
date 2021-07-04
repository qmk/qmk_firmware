/**
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright (C) 2021 Jerrell, Jacob <@jjerrell>
 * 
 * This file is part of qmk_firmware.
 * 
 * qmk_firmware is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * qmk_firmware is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with qmk_firmware.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once
#include QMK_KEYBOARD_H

/** QMK Includes **/
#include "version.h"
#include "eeprom.h"

/** Userspace Includes **/
#include "process_records.h"
#include "matrix_scans.h"
#include "wrappers.h"
#if defined(RGB_MATRIX_ENABLE)
#    include "rgb_matrix_stuff.h"
#endif

/************************* Userspace Layers *************************
 *    Keymaps can define additional layers by making the first case
 * equal to `LAYER_SAFE_RANGE`           
 ********************************************************************/
enum userspace_layers {
    _WORKMAN,
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
    _SPECIAL,
    LAYER_SAFE_RANGE,
};

/********************** Custom Helper Methods **********************/

// bool          mod_key_press_timer(uint16_t code, uint16_t mod_code, bool pressed);
// bool          mod_key_press(uint16_t code, uint16_t mod_code, bool pressed, uint16_t this_timer);

/************************* Keymap Methods **************************/

void          matrix_init_keymap(void);
void          eeconfig_init_keymap(void);

void          shutdown_keymap(void);
void          suspend_power_down_keymap(void);
void          suspend_wakeup_init_keymap(void);

layer_state_t layer_state_set_keymap(layer_state_t state);
layer_state_t default_layer_state_set_keymap(layer_state_t state);
void          led_set_keymap(uint8_t usb_led);

/************************** EEPROM Config **************************/
#ifdef ENABLE_USERSPACE_CONFIG
typedef union userspace_config_t {
    uint32_t raw;
    struct {
        bool    rgb_layer_change     :1;
        bool    rgb_matrix_idle_anim :1;
    };
} userspace_config_t;
#endif // ENABLE_USERSPACE_CONFIG
extern userspace_config_t userspace_config;
