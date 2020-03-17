#include QMK_KEYBOARD_H

#include <spidey3.h>

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

// If console is enabled, it will print the matrix position and status of each key pressed
// #ifdef CONSOLE_ENABLE
//   if (debug_enable) {
//     uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
//   }
// #endif

  if (record->event.pressed) {
    switch (keycode) {
#ifndef NO_DEBUG
      // Re-implement this here, but fix the persistence!
      case DEBUG:
        debug_enable ^= 1;
        if (debug_enable) {
          print("DEBUG: enabled.\n");
        } else {
          print("DEBUG: disabled.\n");
        }
        eeconfig_update_debug(debug_config.raw);
#endif
        return false;
      case SPI_LNX:
#ifdef CONSOLE_ENABLE
	if (debug_enable) { print("SPIDEY3: SPI_LNX\n"); }
#endif
        set_single_persistent_default_layer(_BASE);
#if defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE)
        set_unicode_input_mode(UC_LNX);
#endif
        return false;
      case SPI_OSX:
#ifdef CONSOLE_ENABLE
	if (debug_enable) { print("SPIDEY3: SPI_OSX\n"); }
#endif
        set_single_persistent_default_layer(_OSX);
#if defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE)
        set_unicode_input_mode(UC_OSX);
#endif
        return false;
      case SPI_WIN:
#ifdef CONSOLE_ENABLE
	if (debug_enable) { print("SPIDEY3: SPI_WIN\n"); }
#endif
        set_single_persistent_default_layer(_BASE);
#if defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE)
        set_unicode_input_mode(UC_WINC);
#endif
        return false;
    }
  }

#ifdef RGBLIGHT_ENABLE
  bool res = process_record_user_rgb(keycode, record);
  if (!res) return false;
#endif

  return true;
}

