// Written by konstantin: vomindoraan
#include "send_unicode.h"
#include <ctype.h>
#include <string.h>

__attribute__((weak))
void send_unicode_hex_string(const char* str) {
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

// (ノಠ痊ಠ)ノ彡┻━┻
//   send_unicode_hex_string("0028 30CE 0CA0 75CA 0CA0 0029 30CE 5F61 253B 2501 253B");

//Old code
// (╯°□°)╯ ︵ ┻━┻
      #if 0
      register_code(KC_RSFT);
      tap(KC_9);
      unregister_code(KC_RSFT);
      process_unicode((0x256F | QK_UNICODE), record); // Arm
      process_unicode((0x00B0 | QK_UNICODE), record); // Eye
      process_unicode((0x25A1 | QK_UNICODE), record); // Mouth
      process_unicode((0x00B0 | QK_UNICODE), record); // Eye
      register_code(KC_RSFT);
      tap(KC_0);
      unregister_code(KC_RSFT);
      process_unicode((0x256F | QK_UNICODE), record); // Arm
      tap(KC_SPC);
      process_unicode((0x0361 | QK_UNICODE), record); // Flippy
      tap(KC_SPC);
      process_unicode((0x253B | QK_UNICODE), record); // Table
      process_unicode((0x2501 | QK_UNICODE), record); // Table
      process_unicode((0x253B | QK_UNICODE), record); // Table
      #endif


// If you need a good converter: https://r12a.github.io/app-conversion/
uint8_t saved_mods;

void unicode_input_start (void) {
  // save current mods
  saved_mods = get_mods(); // Save current mods
  clear_mods(); // Unregister mods to start from a clean state

  switch(get_unicode_input_mode()) {
  case UC_OSX:
    register_code(KC_LALT);
    break;
  case UC_OSX_RALT:
    register_code(KC_RALT);
    break;
  case UC_LNX:
    register_code(KC_LCTL);
    register_code(KC_LSFT);
    register_code(KC_U);
    unregister_code(KC_U);
    unregister_code(KC_LSFT);
    unregister_code(KC_LCTL);
    break;
  case UC_WIN:
    register_code(KC_LALT);
    register_code(KC_PPLS);
    unregister_code(KC_PPLS);
    break;
  case UC_WINC:
    register_code(KC_RALT);
    unregister_code(KC_RALT);
    register_code(KC_U);
    unregister_code(KC_U);
    break;
  }
  wait_ms(UNICODE_TYPE_DELAY);
}

void unicode_input_finish (void) {
  switch(get_unicode_input_mode()) {
    case UC_OSX:
    case UC_WIN:
      unregister_code(KC_LALT);
      break;
    case UC_OSX_RALT:
      unregister_code(KC_RALT);
      break;
    case UC_LNX:
      register_code(KC_SPC);
      unregister_code(KC_SPC);
      break;
  }

  set_mods(saved_mods); // Reregister previously set mods
}
