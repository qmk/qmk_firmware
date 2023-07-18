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

// Keymap helpers
// define reference layers per layer.
#define REF_LAYER_FOR_LAYER(LAYER, REF_LAYER)   \
  case LAYER: return REF_LAYER;

#define DEF_REF_LAYER(LAYER)                    \
  default: return LAYER;

#define K_ENUM(name, key, ...) name,
#define K_DATA(name, key, ...) const uint16_t PROGMEM cmb_##name[] = {__VA_ARGS__, COMBO_END};
#define K_COMB(name, key, ...) [name] = COMBO(cmb_##name, key),

#define A_ENUM(name, string, ...) name,
#define A_DATA(name, string, ...) const uint16_t PROGMEM cmb_##name[] = {__VA_ARGS__, COMBO_END};
#define A_COMB(name, string, ...) [name] = COMBO_ACTION(cmb_##name),
#define A_ACTI(name, string, ...)               \
    case name:                                  \
        if (pressed) SEND_STRING(string);           \
        break;

#define A_TOGG(name, layer, ...)                \
    case name:                                    \
        if (pressed) layer_invert(layer);             \
        break;

#define BLANK(...)

// Generate data needed for combos/actions
// Create Enum
#undef COMB
#undef SUBS
#undef TOGG
#define COMB K_ENUM
#define SUBS A_ENUM
#define TOGG A_ENUM
enum combos {
#include "combos.def"
    COMBOS_LENGTH
};


// Fill combo array
combo_t key_combos[COMBOS_LENGTH];

// Fill QMK hook
void process_combo_event(uint16_t combo_index, bool pressed);


// Allow reference layers per layer.
uint8_t combo_ref_from_layer(uint8_t current_layer);

#undef COMB
#undef SUBS
#undef TOGG
