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

// Create custom keycodes with arbitrary shifted and unshifted keys.
// originally for dvorak on bepo. But used by beakl on qwerty now too.

// Why?: Because the keycodes are actually defined on the computer. So
// if you are trying to have dvorak, or beakl on bepo-fr, the shifted keys
// are wrong. But, I want my dvorak, so this allows the pairing of keys into
// a keycode that has shifted and non shifted behavior, outside of what the
// locale map says on the computer.
//
// These are the keys for dvorak on bepo.  column one is the keycode and mods for
// the unshifted key, the second column is the keycode and mods for the shifted key.
// GR is Good Range.  It subtracts SAFE_RANGE from the keycode so we can make a
// reasonably sized array without difficulties. The macro is for the constant declarations
// the function is for when we use it.

//make an alt_local_keys.def   - see the example.
// Include this file where you have your process_record_user function,
// call process_alt_local_key inside your process_record_user.

#include USERSPACE_H
#include "altlocal_keys.h"

const uint16_t key_translations[][2][2] = {
#include "altlocal_keys.def"
};

uint8_t gr(uint16_t kc){
  return (kc - SAFE_RANGE);
}

// send the right keycode for the right mod.
// remove the mods we are taking care of,
// send our keycodes then restore them.
// all so we can make dvorak keys from bepo keycodes.
void send_keycode(uint16_t kc){
  uint8_t tmp_mods = get_mods();
  bool is_shifted = ( tmp_mods & (MOD_BIT(KC_LSFT)|MOD_BIT(KC_RSFT)) );

  // need to turn of the shift if it is on.
  unregister_mods((MOD_BIT(KC_LSFT)|MOD_BIT(KC_RSFT)));
  if(is_shifted){
    register_mods(SHIFTED_MODS(kc));
    register_code16(SHIFTED_KEY(kc));
    unregister_code16(SHIFTED_KEY(kc));
    unregister_mods(SHIFTED_MODS(kc));
  } else{
    register_mods(UNSHIFTED_MODS(kc));
    register_code16(UNSHIFTED_KEY(kc));
    unregister_code16(UNSHIFTED_KEY(kc));
    unregister_mods(UNSHIFTED_MODS(kc));
  }
  clear_mods();
  register_mods(tmp_mods);
}

bool process_alt_local_key(uint16_t keycode, keyrecord_t* record) {
  switch(keycode){
  case ALT_LOCAL_KEYS_START ... ALT_LOCAL_KEYS_END:
    if(record->event.pressed)
      send_keycode(keycode);
    unregister_code(keycode);
    break;
  }
  return (true);
}
