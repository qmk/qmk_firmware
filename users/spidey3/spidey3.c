#include QMK_KEYBOARD_H

#include <spidey3.h>

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

// If console is enabled, it will print the matrix position and status of each key pressed
// dprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);

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
	dprint("SPIDEY3: SPI_LNX\n");
        set_single_persistent_default_layer(_BASE);
	layer_off(_OSX);
#if defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE)
        set_unicode_input_mode(UC_LNX);
#endif
        return false;
      case SPI_OSX:
	dprint("SPIDEY3: SPI_OSX\n");
        set_single_persistent_default_layer(_OSX);
#if defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE)
        set_unicode_input_mode(UC_OSX);
#endif
        return false;
      case SPI_WIN:
	dprint("SPIDEY3: SPI_WIN\n");
        set_single_persistent_default_layer(_BASE);
	layer_off(_OSX);
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

layer_state_t default_layer_state_set_user(layer_state_t state) {
#ifdef RGBLIGHT_ENABLE
  return default_layer_state_set_user_rgb(state);
#else
  return state;
#endif
}

layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef RGBLIGHT_ENABLE
  return layer_state_set_user_rgb(state);
#else
  return state;
#endif
}

bool led_update_user(led_t led_state) {
#ifdef RGBLIGHT_ENABLE
  return led_update_user_rgb(led_state);
#else
  return true;
#endif
}

