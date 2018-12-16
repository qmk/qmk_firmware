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

__attribute__((weak))
const uint32_t PROGMEM unicode_map[] = {
};

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
void unicode_map_input_error() {}

bool process_unicode_map(uint16_t keycode, keyrecord_t *record) {
  unicode_input_mode_init();
  uint8_t input_mode = get_unicode_input_mode();
  if ((keycode & QK_UNICODE_MAP) == QK_UNICODE_MAP && record->event.pressed) {
    const uint32_t* map = unicode_map;
    uint16_t index = keycode - QK_UNICODE_MAP;
    uint32_t code = pgm_read_dword(&map[index]);
    if (code > 0xFFFF && code <= 0x10ffff && (input_mode == UC_OSX || input_mode == UC_OSX_RALT)) {
      // Convert to UTF-16 surrogate pair
      code -= 0x10000;
      uint32_t lo = code & 0x3ff;
      uint32_t hi = (code & 0xffc00) >> 10;
      unicode_input_start();
      register_hex32(hi + 0xd800);
      register_hex32(lo + 0xdc00);
      unicode_input_finish();
    } else if ((code > 0x10ffff && (input_mode == UC_OSX || input_mode == UC_OSX_RALT)) || (code > 0xFFFFF && input_mode == UC_LNX)) {
      // when character is out of range supported by the OS
      unicode_map_input_error();
    } else {
      unicode_input_start();
      register_hex32(code);
      unicode_input_finish();
    }
  }
  return true;
}
