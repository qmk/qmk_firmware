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

#include "process_unicode_common.h"
#include "eeprom.h"
#include <ctype.h>
#include <string.h>

static uint8_t input_mode;
static uint8_t saved_mods;

void unicode_input_mode_init(void) {
  static bool first_flag = false;
  if (!first_flag) {
    input_mode = eeprom_read_byte(EECONFIG_UNICODEMODE);
    first_flag = true;
  }
}

uint8_t get_unicode_input_mode(void) {
  return input_mode;
}

void set_unicode_input_mode(uint8_t mode) {
  input_mode = mode;
  eeprom_update_byte(EECONFIG_UNICODEMODE, mode);
}

__attribute__((weak))
void unicode_input_start(void) {
  saved_mods = get_mods(); // Save current mods
  clear_mods(); // Unregister mods to start from a clean state

  switch(input_mode) {
  case UC_OSX:
    register_code(UNICODE_OSX_KEY);
    break;
  case UC_LNX:
    register_code(KC_LCTL);
    register_code(KC_LSFT);
    tap_code(KC_U); // TODO: Replace with tap_code16(LCTL(LSFT(KC_U))); and test
    unregister_code(KC_LSFT);
    unregister_code(KC_LCTL);
    break;
  case UC_WIN:
    register_code(KC_LALT);
    tap_code(KC_PPLS);
    break;
  case UC_WINC:
    tap_code(UNICODE_WINC_KEY);
    tap_code(KC_U);
    break;
  }

  wait_ms(UNICODE_TYPE_DELAY);
}

__attribute__((weak))
void unicode_input_finish(void) {
  switch(input_mode) {
  case UC_OSX:
    unregister_code(UNICODE_OSX_KEY);
    break;
  case UC_WIN:
    unregister_code(KC_LALT);
    break;
  case UC_LNX:
    tap_code(KC_SPC);
    break;
  }

  set_mods(saved_mods); // Reregister previously set mods
}

__attribute__((weak))
uint16_t hex_to_keycode(uint8_t hex) {
  if (hex == 0x0) {
    return KC_0;
  } else if (hex < 0xA) {
    return KC_1 + (hex - 0x1);
  } else {
    return KC_A + (hex - 0xA);
  }
}

void register_hex(uint16_t hex) {
  for(int i = 3; i >= 0; i--) {
    uint8_t digit = ((hex >> (i*4)) & 0xF);
    register_code(hex_to_keycode(digit));
    unregister_code(hex_to_keycode(digit));
  }
}

void send_unicode_hex_string(const char *str) {
  if (!str) { return; }

  while (*str) {
    // Find the next code point (token) in the string
    for (; *str == ' '; str++);
    size_t n = strcspn(str, " "); // Length of the current token
    char code_point[n+1];
    strncpy(code_point, str, n);
    code_point[n] = '\0'; // Make sure it's null-terminated

    // Normalize the code point: make all hex digits lowercase
    for (char *p = code_point; *p; p++) {
      *p = tolower((unsigned char)*p);
    }

    // Send the code point as a Unicode input string
    unicode_input_start();
    send_string(code_point);
    unicode_input_finish();

    str += n; // Move to the first ' ' (or '\0') after the current token
  }
}
