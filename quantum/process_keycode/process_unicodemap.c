/* Copyright 2017 Jack Humbert
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

#include "process_unicodemap.h"
#include "process_unicode_common.h"

void register_hex32(uint32_t hex) {
  bool onzerostart = true;
  for(int i = 7; i >= 0; i--) {
    if (i <= 3) {
      onzerostart = false;
    }
    uint8_t digit = ((hex >> (i*4)) & 0xF);
    if (digit == 0) {
      if (!onzerostart) {
        register_code(hex_to_keycode(digit));
        unregister_code(hex_to_keycode(digit));
      }
    } else {
      register_code(hex_to_keycode(digit));
      unregister_code(hex_to_keycode(digit));
      onzerostart = false;
    }
  }
}

__attribute__((weak))
void unicodemap_input_error() {}

bool process_unicodemap(uint16_t keycode, keyrecord_t *record) {
  if ((keycode & QK_UNICODEMAP) == QK_UNICODEMAP && record->event.pressed) {
    uint16_t index = keycode - QK_UNICODEMAP;
    uint32_t code = pgm_read_dword(unicode_map + index);
    uint8_t input_mode = get_unicode_input_mode();

    if (code > 0xFFFF && code <= 0x10FFFF && input_mode == UC_OSX) {
      // Convert to UTF-16 surrogate pair
      code -= 0x10000;
      uint32_t lo = code & 0x3FF, hi = (code & 0xFFC00) >> 10;

      unicode_input_start();
      register_hex32(hi + 0xD800);
      register_hex32(lo + 0xDC00);
      unicode_input_finish();
    } else if ((code > 0x10FFFF && input_mode == UC_OSX) || (code > 0xFFFFF && input_mode == UC_LNX)) {
      // Character is out of range supported by the OS
      unicodemap_input_error();
    } else {
      unicode_input_start();
      register_hex32(code);
      unicode_input_finish();
    }
  }
  return true;
}
