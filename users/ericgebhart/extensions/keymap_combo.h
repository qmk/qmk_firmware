#pragma once
/*
  Copyright 2018-2022 Eric Gebhart <e.a.gebhart@gmail.com>

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
// Keymap helpers
void process_combo_event(uint16_t combo_index, bool pressed);


// define reference layers per layer.
#define REF_LAYER(LAYER, REF_LAYER)             \
  case LAYER: return REF_LAYER;

#define K_ENUM(name, key, ...) name,
#define K_DATA(name, key, ...) const uint16_t PROGMEM cmb_##name[] = {__VA_ARGS__, COMBO_END};
#define K_COMB(name, key, ...) [name] = COMBO(cmb_##name, key),

#define A_ENUM(name, string, ...) name,
#define A_DATA(name, string, ...) const uint16_t PROGMEM cmb_##name[] = {__VA_ARGS__, COMBO_END};
#define A_COMB(name, string, ...) [name] = COMBO_ACTION(cmb_##name),
#define A_ACTI(name, string, ...)         \
    case name:                            \
        if (pressed) SEND_STRING(string); \
        break;

#define A_TOGG(name, layer, ...)          \
    case name:                            \
        if (pressed) layer_invert(layer); \
        break;

#define BLANK(...)
// Generate data needed for combos/actions
// Create Enum
#define COMBO_REF_LAYER BLANK
#undef COMB
#undef SUBS
#undef TOGG
#define COMB K_ENUM
#define SUBS A_ENUM
#define TOGG A_ENUM
enum combos {
#include "combos.def"
    COMBO_LENGTH
};
// Export length to combo module
uint16_t COMBO_LEN = COMBO_LENGTH;

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
#if defined( CONSOLE_ENABLE) && defined(CONSOLE_KEY_LOGGER_ENABLE)
  if (pressed) {
    combo_t *combo = &key_combos[combo_index];
    uint8_t idx = 0;
    uint16_t combo_keycode;
    while ((combo_keycode = pgm_read_word(&combo->keys[idx])) != COMBO_END) {
      uprintf("0x%04X,NA,NA,%u,%u,0x%02X,0x%02X,0\n",
              combo_keycode,
              /* <missing row information> */
              /* <missing column information> */
              get_highest_layer(layer_state),
              pressed,
              get_mods(),
              get_oneshot_mods()
              );
      idx++;
    }
  }
#endif
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

#define COMB BLANK
#define SUBS BLANK
#define TOGG BLANK

#undef COMBO_REF_LAYER
#define COMBO_REF_LAYER REF_LAYER

uint16_t combo_ref_from_layer(uint16_t layer){
  switch (biton32(layer_state)){
#include "combos.def"

#ifdef COMBO_REF_DEFAULT
  default: return COMBO_REF_DEFAULT;
#else
  default: return layer;
#endif
  }
}
