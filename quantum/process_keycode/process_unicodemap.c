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
uint16_t unicodemap_index(uint16_t keycode) {
  if (keycode >= QK_UNICODEMAP_PAIR) {
    // Keycode is a pair: extract index based on Shift / Caps Lock state
    uint16_t index = keycode - QK_UNICODEMAP_PAIR;

    bool shift = unicode_saved_mods & MOD_MASK_SHIFT, caps = IS_HOST_LED_ON(USB_LED_CAPS_LOCK);
    if (shift ^ caps) { index >>= 7; }

    return index & 0x7F;
  } else {
    // Keycode is a regular index
    return keycode - QK_UNICODEMAP;
  }
}

bool process_unicodemap(uint16_t keycode, keyrecord_t *record) {
  if (keycode >= QK_UNICODEMAP && keycode <= QK_UNICODEMAP_PAIR_MAX && record->event.pressed) {
    unicode_input_start();

    uint32_t code = pgm_read_dword(unicode_map + unicodemap_index(keycode));
    uint8_t input_mode = get_unicode_input_mode();

    if (code > 0x10FFFF || (code > 0xFFFF && input_mode == UC_WIN)) {
      // Character is out of range supported by the platform
      unicode_input_cancel();
    } else if (code > 0xFFFF && input_mode == UC_OSX) {
      // Convert to UTF-16 surrogate pair on Mac
      code -= 0x10000;
      uint32_t lo = code & 0x3FF, hi = (code & 0xFFC00) >> 10;
      register_hex32(hi + 0xD800);
      register_hex32(lo + 0xDC00);
      unicode_input_finish();
    } else {
      register_hex32(code);
      unicode_input_finish();
    }
  }
  return true;
}
