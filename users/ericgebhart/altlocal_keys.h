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

// for the creation of dvorak keys on an Bepo keyboard at the OS layer.
// so we can create an array of reasonable size
// for our translation keys. We have to create a
// good range of numbers
#define GR(x) (x-SAFE_RANGE)

// void tap(uint16_t keycode){ register_code(keycode); unregister_code(keycode); };

uint8_t gr(uint16_t);
void send_keycode(uint16_t);

#define MOD_NONE 0x00

// indexs for the keycode translation table.
#define UNSHIFTED_KEY(key)  key_translations[gr(key)][0][0]
#define UNSHIFTED_MODS(key) key_translations[gr(key)][0][1]
#define SHIFTED_KEY(key)    key_translations[gr(key)][1][0]
#define SHIFTED_MODS(key)   key_translations[gr(key)][1][1]
