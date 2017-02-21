#include "process_unicodemap.h"

__attribute__((weak))
const uint32_t PROGMEM unicode_map[] = {
};

void register_hex32(uint32_t hex) {
  uint8_t onzerostart = 1;
  for(int i = 7; i >= 0; i--) {
    if (i <= 3) {
      onzerostart = 0;
    }
    uint8_t digit = ((hex >> (i*4)) & 0xF);
    if (digit == 0) {
      if (onzerostart == 0) {
        register_code(hex_to_keycode(digit));
        unregister_code(hex_to_keycode(digit));
      }
    } else {
      register_code(hex_to_keycode(digit));
      unregister_code(hex_to_keycode(digit));
      onzerostart = 0;
    }
  }
}

__attribute__((weak))
void unicode_map_input_error() {}

bool process_unicode_map(uint16_t keycode, keyrecord_t *record) {
  if ((keycode & QK_UNICODE_MAP) == QK_UNICODE_MAP && record->event.pressed) {
    const uint32_t* map = unicode_map;
    uint16_t index = keycode - QK_UNICODE_MAP;
    uint32_t code = pgm_read_dword_far(&map[index]);
    if (code > 0xFFFF && code <= 0x10ffff && input_mode == UC_OSX) {
      // Convert to UTF-16 surrogate pair
      code -= 0x10000;
      uint32_t lo = code & 0x3ff;
      uint32_t hi = (code & 0xffc00) >> 10;
      unicode_input_start();
      register_hex32(hi + 0xd800);
      register_hex32(lo + 0xdc00);
      unicode_input_finish();
    } else if ((code > 0x10ffff && input_mode == UC_OSX) || (code > 0xFFFFF && input_mode == UC_LNX)) {
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