/* Copyright 2023 Christoph Jabs (BifbofII)
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

#include "keyrecords/wrappers.h"
#include "keyrecords/keycodes.h"
#ifdef RGBLIGHT_ENABLE
#    include "rgblights.h"
#endif

// ====== Unicode ======
// Character names
enum unicode_names {
    SAE, // ä
    CAE, // Ä
    SUE, // ü
    CUE, // Ü
    SOE, // ö
    COE, // Ö
    SS,  // ß
    EUR, // €
    CPR  // ©
};

// Unicode map
extern const uint32_t unicode_map[];

// ====== Layers ======
enum userspace_layers {
    _QWERTY = 0, // QWERTY layer
    _COLEMAK,    // COLEMAK layer
    _DVORAK,     // DVORAK layer
#ifdef GAMING_ENABLE
    _GAMING, // Gaming layer
#endif
    _UNICODE, // Layer with unicode characters
    _FUNC,    // Function layer with arrows
#ifdef TRI_LAYER_ENABLE
    _LOWER = TRI_LAYER_LOWER_LAYER, // Lower layer with symbols
    _UPPER, // Upper layer with numbers
#else
    _FUNC2, // Second function layer
#endif
    _ADJUST, // Layer for keyboard settings
};
