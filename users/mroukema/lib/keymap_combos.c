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
#include "keymap_combos.h"

// Generate data needed for combos/actions

// Bake combos into mem
#undef COMB
#undef SUBS
#undef TOGG
#define COMB K_DATA
#define SUBS A_DATA
#define TOGG A_DATA
#include "combos.def"
#undef COMB
#undef SUBS
#undef TOGG

// Fill combo array
#define COMB K_COMB
#define SUBS A_COMB
#define TOGG A_COMB
combo_t key_combos[] = {
#include "combos.def"
};
#undef COMB
#undef SUBS
#undef TOGG

// Fill QMK hook
#define COMB BLANK
#define SUBS A_ACTI
#define TOGG A_TOGG
void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
#include "combos.def"
    }

    // Allow user overrides per keymap
#if __has_include("inject.h")
# include "inject.h"
#endif
}
#undef COMB
#undef SUBS
#undef TOGG

// Allow reference layers per layer.
#define COMB BLANK
#define SUBS BLANK
#define TOGG BLANK

#undef DEFAULT_REF_LAYER
#undef COMBO_REF_LAYER
#define COMBO_REF_LAYER REF_LAYER_FOR_LAYER
#define DEFAULT_REF_LAYER DEF_REF_LAYER

uint8_t combo_ref_from_layer(uint8_t current_layer){
    switch (current_layer){
#include "combos.def"
    }
    return current_layer;
}

#undef COMB
#undef SUBS
#undef TOGG
#undef COMBO_REF_LAYER
#undef DEFAULT_REF_LAYER
