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
#include <string.h>
#include <ctype.h>

unicode_config_t unicode_config;
static uint8_t saved_mods;
#ifdef AUDIO_ENABLE
  #ifdef UNICODE_LINUX_SONG
    float linux_song[][2] = UNICODE_LINUX_SONG;
  #endif
  #ifdef UNICODE_WINDOWS_SONG
    float windows_song[][2] = UNICODE_WINDOWS_SONG;
  #endif
  #ifdef UNICODE_WIN_COMPOSE_SONG
    float win_compose_song[][2] = UNICODE_WIN_COMPOSE_SONG;
  #endif
  #ifdef UNICODE_OSX_SONG
    float osx_song[][2] = UNICODE_OSX_SONG;
  #endif
  #ifdef UNICODE_OSX_RALT_SONG
    float osx_ralt_song[][2] = UNICODE_OSX_RALT_SONG;
  #endif
#endif


void set_unicode_input_mode(uint8_t os_target) {
  unicode_config.input_mode = os_target;
  eeprom_update_byte(EECONFIG_UNICODEMODE, os_target);
}

uint8_t get_unicode_input_mode(void) {
  return unicode_config.input_mode;
}

void unicode_input_mode_init(void) {
  unicode_config.raw = eeprom_read_byte(EECONFIG_UNICODEMODE);
}

__attribute__((weak))
void unicode_input_start(void) {
  saved_mods = get_mods(); // Save current mods
  clear_mods(); // Unregister mods to start from a clean state

  switch(unicode_config.input_mode) {
  case UC_OSX:
    register_code(KC_LALT);
    break;
  case UC_OSX_RALT:
    register_code(KC_RALT);
    break;
  case UC_LNX:
    register_code(KC_LCTL);
    register_code(KC_LSFT);
    tap_code(KC_U);
    unregister_code(KC_LSFT);
    unregister_code(KC_LCTL);
    break;
  case UC_WIN:
    register_code(KC_LALT);
    tap_code(KC_PPLS);
    break;
  case UC_WINC:
    tap_code(KC_RALT);
    tap_code(KC_U);
  }
  wait_ms(UNICODE_TYPE_DELAY);
}

__attribute__((weak))
 void unicode_input_finish(void) {
  switch(unicode_config.input_mode) {
    case UC_OSX:
    case UC_WIN:
    unregister_code(KC_LALT);
      break;
    case UC_OSX_RALT:
      unregister_code(KC_RALT);
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
    tap_code(hex_to_keycode(digit));
  }
}

void send_unicode_hex_string(const char *str) {
  if (!str) { return; } // Safety net

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

bool process_record_unicode_common(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
      case UNICODE_MODE_OSX:
      set_unicode_input_mode(UC_OSX);
        #if defined(AUDIO_ENABLE) && defined(UNICODE_OSX_SONG)
          PLAY_SONG(UNICODE_OSX_SONG);
        #endif
        break;
      case UNICODE_MODE_LNX:
        set_unicode_input_mode(UC_LNX);
        #if defined(AUDIO_ENABLE) && defined(UNICODE_LINUX_SONG)
          PLAY_SONG(UNICODE_LINUX_SONG);
        #endif
        break;
      case UNICODE_MODE_WIN:
        set_unicode_input_mode(UC_WIN);
        #if defined(AUDIO_ENABLE) && defined(UNICODE_WINDOWS_SONG)
          PLAY_SONG(UNICODE_WINDOWS_SONG);
        #endif
        break;
      case UNICODE_MODE_WINC:
        set_unicode_input_mode(UC_WINC);
        #if defined(AUDIO_ENABLE) && defined(UNICODE_WIN_COMPOSE_SONG)
          PLAY_SONG(UNICODE_WIN_COMPOSE_SONG);
        #endif
        break;
      case UNICODE_MODE_OSX_RALT:
        set_unicode_input_mode(UC_OSX_RALT);
        #if defined(AUDIO_ENABLE) && defined(UNICODE_OSX_RALT_SONG)
          PLAY_SONG(UNICODE_OSX_RALT_SONG);
        #endif
        break;
    }
  }
  #ifdef UNICODE_ENABLE
    return process_unicode(keycode, record);
  #endif
  #ifdef UCIS_ENABLE
    return process_ucis(keycode, record);
  #endif
  #ifdef UNICODEMAP_ENABLE
    return process_unicode_map(keycode, record);
  #endif
  return true;
}
