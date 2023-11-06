#pragma once
/*
  Copyright 2018 Eric Gebhart <e.a.gebhart@gmail.com>

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

uint8_t gr(uint16_t);
void send_keycode(uint16_t);
bool process_alt_local_key(uint16_t keycode, keyrecord_t* record);

#define MOD_NONE 0x00

#define GR(x) (x-SAFE_RANGE)
// indexs for the keycode translation table.

#define MK_KEY(KCNAME, KC1, MOD1, KC2, MOD2)    \
  [GR(KCNAME)] = {{KC1, MOD1}, {KC2, MOD2}},

#define MK_SKEY(KCNAME, KC1, KC2)   \
  [GR(KCNAME)] = {{KC1, MOD_NONE}, {KC2, MOD_NONE}},

#define UNSHIFTED_KEY(key)  key_translations[gr(key)][0][0]
#define UNSHIFTED_MODS(key) key_translations[gr(key)][0][1]
#define SHIFTED_KEY(key)    key_translations[gr(key)][1][0]
#define SHIFTED_MODS(key)   key_translations[gr(key)][1][1]
