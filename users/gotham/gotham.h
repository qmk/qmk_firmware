/* Copyright 2020 Gautham Yerroju <gautham.yerroju@gmail.com>
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

#include <stdbool.h>
#include "version.h"
#include "wrappers.h"
#include "process_records.h"

#ifdef COMBO_ENABLE
#    include "combos.h"
#endif

#ifdef OLED_DRIVER_ENABLE
#    include "oled_utils.h"
#endif

#ifdef ENCODER_ENABLE
#    include "encoder_utils.h"
#endif

#ifdef POINTING_DEVICE_ENABLE
#    include "pointing_devices.h"
#endif

enum userspace_layers {
    _QWERTY = 0,
#ifdef ENABLE_LAYOUT_COLEMAK
    _COLEMAK,
#endif
#ifdef ENABLE_LAYOUT_COLEMAK_DH
    _COLEMAK_DH,
#endif
#ifdef ENABLE_LAYOUT_COLEMAK_DHM
    _COLEMAK_DHM,
#endif
#ifdef ENABLE_LAYOUT_DVORAK
    _DVORAK,
#endif
#ifdef ENABLE_LAYOUT_WORKMAN
    _WORKMAN,
#endif
#ifdef ENABLE_LAYOUT_NORMAN
    _NORMAN,
#endif
    _GAME,
    _GAMENAV,
    _GAMENUM,
    _LOWER,
    _RAISE,
    _ADJUST,
    _MOUSE,
};
#define LAYOUT_COUNT _GAME // Used for layout cycling, this should be the layer immediately after the last keyboard layout layer.

bool is_mac_mode(void);
void set_mac_mode(bool);

void          keyboard_pre_init_keymap(void);
void          matrix_init_keymap(void);
void          keyboard_post_init_keymap(void);
void          matrix_scan_keymap(void);
void          suspend_power_down_keymap(void);
void          suspend_wakeup_init_keymap(void);
layer_state_t layer_state_set_keymap(layer_state_t state);
layer_state_t default_layer_state_set_keymap(layer_state_t state);
bool          led_update_keymap(led_t led_state);
