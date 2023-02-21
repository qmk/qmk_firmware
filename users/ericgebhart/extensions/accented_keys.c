/*
  Copyright 2022 Eric Gebhart <e.a.gebhart@gmail.com>

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

#include USERSPACE_H
#include "accented_keys.h"
#include <stdint.h>
#include <stdbool.h>

static inline void tap_accented_letter(uint16_t letter, uint16_t dead_key) {
    uint8_t mod_state = get_mods();
    uint8_t oneshot_mod_state = get_oneshot_mods();
    del_mods(MOD_MASK_SHIFT);
    del_oneshot_mods(MOD_MASK_SHIFT);
    tap_code16(dead_key);
    set_mods(mod_state);
    set_oneshot_mods(oneshot_mod_state);
    tap_code(letter);
}

#undef ACCENTED
#define ACCENTED(KC, K1, DEAD_KEY)              \
  case KC:                                      \
  if (record->event.pressed) {                  \
    tap_accented_letter(K1, DEAD_KEY);          \
  }                                             \
  return false;


bool process_accent_keys(uint16_t keycode, keyrecord_t* record) {
  switch(keycode){
#ifdef ACCENTED_KEYS_ENABLE
#include "accented_keys.def"
#endif
  }
  return true;
}
