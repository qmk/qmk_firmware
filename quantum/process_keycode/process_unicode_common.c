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

unicode_config_t unicode_config;
#if UNICODE_SELECTED_MODES != -1
static uint8_t selected[] = { UNICODE_SELECTED_MODES };
static uint8_t selected_count = sizeof selected / sizeof *selected;
static uint8_t selected_index;
#endif

void unicode_input_mode_init(void) {
  unicode_config.raw = eeprom_read_byte(EECONFIG_UNICODEMODE);
#if UNICODE_SELECTED_MODES != -1
  #if UNICODE_CYCLE_PERSIST
  // Find input_mode in selected modes
  uint8_t i;
  for (i = 0; i < selected_count; i++) {
    if (selected[i] == unicode_config.input_mode) {
      selected_index = i;
      break;
    }
  }
  if (i == selected_count) {
    // Not found: input_mode isn't selected, change to one that is
    unicode_config.input_mode = selected[selected_index = 0];
  }
  #else
  // Always change to the first selected input mode
  unicode_config.input_mode = selected[selected_index = 0];
  #endif
#endif
  dprintf("Unicode input mode init to: %u\n", unicode_config.input_mode);
}

uint8_t get_unicode_input_mode(void) {
  return unicode_config.input_mode;
}

void set_unicode_input_mode(uint8_t mode) {
  unicode_config.input_mode = mode;
  persist_unicode_input_mode();
  dprintf("Unicode input mode set to: %u\n", unicode_config.input_mode);
}

void cycle_unicode_input_mode(uint8_t offset) {
#if UNICODE_SELECTED_MODES != -1
  selected_index = (selected_index + offset) % selected_count;
  unicode_config.input_mode = selected[selected_index];
  #if UNICODE_CYCLE_PERSIST
  persist_unicode_input_mode();
  #endif
  dprintf("Unicode input mode cycle to: %u\n", unicode_config.input_mode);
#endif
}

void persist_unicode_input_mode(void) {
  eeprom_update_byte(EECONFIG_UNICODEMODE, unicode_config.input_mode);
}

static uint8_t saved_mods;

__attribute__((weak))
void unicode_input_start(void) {
  saved_mods = get_mods(); // Save current mods
  clear_mods(); // Unregister mods to start from a clean state

  switch (unicode_config.input_mode) {
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
  switch (unicode_config.input_mode) {
  case UC_OSX:
    unregister_code(UNICODE_OSX_KEY);
    break;
  case UC_LNX:
    tap_code(KC_SPC);
    break;
  case UC_WIN:
    unregister_code(KC_LALT);
    break;
  case UC_WINC:
    tap_code(KC_ENTER);
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

bool process_unicode_common(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
    case UNICODE_MODE_FORWARD:
      cycle_unicode_input_mode(+1);
      break;
    case UNICODE_MODE_REVERSE:
      cycle_unicode_input_mode(-1);
      break;

    case UNICODE_MODE_OSX:
      set_unicode_input_mode(UC_OSX);
#if defined(AUDIO_ENABLE) && defined(UNICODE_SONG_OSX)
      static float song_osx[][2] = UNICODE_SONG_OSX;
      PLAY_SONG(song_osx);
#endif
      break;
    case UNICODE_MODE_LNX:
      set_unicode_input_mode(UC_LNX);
#if defined(AUDIO_ENABLE) && defined(UNICODE_SONG_LNX)
      static float song_lnx[][2] = UNICODE_SONG_LNX;
      PLAY_SONG(song_lnx);
#endif
      break;
    case UNICODE_MODE_WIN:
      set_unicode_input_mode(UC_WIN);
#if defined(AUDIO_ENABLE) && defined(UNICODE_SONG_WIN)
      static float song_win[][2] = UNICODE_SONG_WIN;
      PLAY_SONG(song_win);
#endif
      break;
    case UNICODE_MODE_BSD:
      set_unicode_input_mode(UC_BSD);
#if defined(AUDIO_ENABLE) && defined(UNICODE_SONG_BSD)
      static float song_bsd[][2] = UNICODE_SONG_BSD;
      PLAY_SONG(song_bsd);
#endif
      break;
    case UNICODE_MODE_WINC:
      set_unicode_input_mode(UC_WINC);
#if defined(AUDIO_ENABLE) && defined(UNICODE_SONG_WINC)
      static float song_winc[][2] = UNICODE_SONG_WINC;
      PLAY_SONG(song_winc);
#endif
      break;
    }
  }
#if   defined(UNICODE_ENABLE)
  return process_unicode(keycode, record);
#elif defined(UNICODEMAP_ENABLE)
  return process_unicodemap(keycode, record);
#elif defined(UCIS_ENABLE)
  return process_ucis(keycode, record);
#else
  return true;
#endif
}
