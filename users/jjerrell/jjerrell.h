/**
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
#include "muse.h"

#include "process_records.h"
#include "wrappers.h"

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
    _GAME,
    LAYER_SAFE_RANGE,
};

void matrix_scan_keymap(void);
layer_state_t layer_state_set_keymap(layer_state_t state);
void dip_switch_update_keymap(uint8_t index, bool active);
bool music_mask_keymap(uint16_t keycode);
layer_state_t default_layer_state_set_keymap(layer_state_t state);
void startup_keymap(void);
void shutdown_keymap(void);
void music_on_keymap(void);
