// Copyright (C) 2021 Jerrell, Jacob <@jjerrell>
// 
// This file is part of qmk_firmware.
// 
// qmk_firmware is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// qmk_firmware is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with qmk_firmware.  If not, see <http://www.gnu.org/licenses/>.

#pragma once
#include "jjerrell.h"

#if defined(KEYMAP_SAFE_RANGE)
#    define PLACEHOLDER_SAFE_RANGE KEYMAP_SAFE_RANGE
#else
#    define PLACEHOLDER_SAFE_RANGE SAFE_RANGE
#endif

enum userspace_keycodes {
    KC_ARROW = PLACEHOLDER_SAFE_RANGE, // `->`
    KC_MAKE,       // Runs the keyboard's make command
    KC_QWERTY,     // Default Layer -> QWERTY
    KC_WORKMAN,    // Default Layer -> Workman
    KC_VRSN,       // Print QMK Firmware and board info
    RGB_IDL,       // Toggle RGB Idle animations
    RGB_TGL,       // Toggle RGB Layer Indication
    KC_CCCV,       // One key copy/paste,
    KC_GAME,       // To game layer. If on game layer, cycle game layers
    NEW_SAFE_RANGE // use NEW_SAFE_RANGE for keymap specific codes
};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record);

