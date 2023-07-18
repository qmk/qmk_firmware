/*
Copyright 2023 @mroukema

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
#include USERSPACE_H

void _handle_custom_shifted_key(keyrecord_t *record, uint16_t base_keycode, uint16_t shifted_code);

bool handle_custom_shifted_key(keyrecord_t *record, uint16_t base_keycode, uint16_t shifted_code);

bool process_custom_shifted_keys(uint16_t keycode, keyrecord_t *record);

// Define C Macros to transform .def data
#define BLANK(...)
#define CSK_ENUM(custom_key, ...) custom_key,
#define CSMK_ENUM(mod, custom_key, ...) custom_key,
#define CSK_PROG(custom_key, base_key, shifted_key)                                     \
    case custom_key:                                                                    \
        return handle_custom_shifted_key(record, base_key, shifted_key);

#define CSMK_PROG(mod, custom_key, base_key, shifted_key)                               \
    case mod(custom_key):                                                               \
        if (record->tap.count) {                                                        \
                return handle_custom_shifted_key(record, base_key, shifted_key);        \
        }                                                                               \
        break;

// Generate data needed for custom keycodes

// Create Enum
#undef CUSTOM_KEYCODE
#undef CUSTOM_SHIFTABLE_KEYCODE
#undef CUSTOM_SHIFTABLE_MOD_KEYCODE
#define CUSTOM_KEYCODE CSK_ENUM
#define CUSTOM_SHIFTABLE_KEYCODE CSK_ENUM
#define CUSTOM_SHIFTABLE_MOD_KEYCODE CSMK_ENUM
enum custom_keycodes {
    __START = SAFE_RANGE,
#include "users/mroukema/defs/custom_keycodes.def"
    NEW_SAFE_RANGE
};
#undef CUSTOM_KEYCODE
#undef CUSTOM_SHIFTABLE_KEYCODE
#undef CUSTOM_SHIFTABLE_MOD_KEYCODE
