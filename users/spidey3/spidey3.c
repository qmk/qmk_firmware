#include QMK_KEYBOARD_H

#include "spidey3.h"
#include "version.h"
#include <stdlib.h>

static bool rand_seeded = false;

uint16_t spi_replace_mode = SPI_NORMAL;

bool process_record_glyph_replacement(uint16_t keycode, keyrecord_t *record, uint32_t baseAlphaLower, uint32_t baseAlphaUpper, uint32_t zeroGlyph, uint32_t baseNumberOne, uint32_t spaceGlyph) {
    uint8_t temp_mod = get_mods();
#ifndef NO_ACTION_ONESHOT
    uint8_t temp_osm = get_oneshot_mods();
#else
    uint8_t temp_osm = 0;
#endif
    if ((((temp_mod | temp_osm) & (MOD_MASK_CTRL | MOD_MASK_ALT | MOD_MASK_GUI))) == 0) {
        switch (keycode) {
          case KC_A ... KC_Z:
            if (record->event.pressed) {
                clear_mods();
#ifndef NO_ACTION_ONESHOT
                clear_oneshot_mods();
#endif

                unicode_input_start();
                uint32_t base = ((temp_mod | temp_osm) & MOD_MASK_SHIFT) ? baseAlphaUpper : baseAlphaLower;
                register_hex32(base + (keycode - KC_A));
                unicode_input_finish();

                set_mods(temp_mod);
            }
            return false;
          case KC_0:
            if ((temp_mod | temp_osm) & MOD_MASK_SHIFT) {  // skip shifted numbers, so that we can still use symbols etc.
                return true;
            }
            if (record->event.pressed) {
                unicode_input_start();
                register_hex32(zeroGlyph);
                unicode_input_finish();
            }
            return false;
          case KC_1 ... KC_9:
            if ((temp_mod | temp_osm) & MOD_MASK_SHIFT) {  // skip shifted numbers, so that we can still use symbols etc.
                return true;
            }
            if (record->event.pressed) {
                unicode_input_start();
                register_hex32(baseNumberOne + (keycode - KC_1));
                unicode_input_finish();
            }
            return false;
          case KC_SPACE:
            if (record->event.pressed) {
                unicode_input_start();
                register_hex32(spaceGlyph);  // em space
                unicode_input_finish();
            }
            return false;
        }
    }

    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

// If console is enabled, it will print the matrix position and status of each key pressed
// dprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);

  if (!rand_seeded) {
    srand(record->event.time % keycode);
    rand_seeded = true;
  }

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

      case CH_CPNL: host_consumer_send(AL_CONTROL_PANEL); return false;
      case CH_ASST: host_consumer_send(AL_ASSISTANT); return false;
      case CH_SUSP: tap_code16(LGUI(LSFT(KC_L))); return true;

      case SPI_LNX:
	dprint("SPI_LNX\n");
        set_single_persistent_default_layer(_BASE);
	layer_off(_OSX);
#if defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE)
        set_unicode_input_mode(UC_LNX);
#endif
        break;
      case SPI_OSX:
	dprint("SPI_OSX\n");
        set_single_persistent_default_layer(_OSX);
#if defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE)
        set_unicode_input_mode(UC_OSX);
#endif
        break;
      case SPI_WIN:
	dprint("SPI_WIN\n");
        set_single_persistent_default_layer(_BASE);
	layer_off(_OSX);
#if defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE)
        set_unicode_input_mode(UC_WINC);
#endif
        break;

      case SPI_NORMAL ... SPI_FRAKTR:
	spi_replace_mode = (spi_replace_mode == keycode) ? SPI_NORMAL: keycode;
	dprintf("spi_replace_mode = %u\n");
        break;
    }
  } else {
    switch (keycode) {
      case CH_CPNL:
      case CH_ASST:
        host_consumer_send(0);
        return false;
    }
  }

  switch (keycode) {
    case KC_A ... KC_0:
    case KC_SPACE:
      switch (spi_replace_mode) {
        case SPI_WIDE:
          return process_record_glyph_replacement(keycode, record, 0xFF41, 0xFF21, 0xFF10, 0xFF11, 0x2003);
        case SPI_SCRIPT:
          return process_record_glyph_replacement(keycode, record, 0x1D4EA, 0x1D4D0, 0x1D7CE, 0x1D7CF, 0x2002);
        case SPI_BLOCKS:
          return process_record_glyph_replacement(keycode, record, 0x1F170, 0x1F170, '0', '1', 0x2002);
        case SPI_CIRCLE:
          return process_record_glyph_replacement(keycode, record, 0x1F150, 0x1F150, '0', '1', 0x2002);
        case SPI_SQUARE:
          return process_record_glyph_replacement(keycode, record, 0x1F130, 0x1F130, '0', '1', 0x2002);
        case SPI_PARENS:
          return process_record_glyph_replacement(keycode, record, 0x1F110, 0x1F110, '0', '1', 0x2002);
        case SPI_FRAKTR:
          return process_record_glyph_replacement(keycode, record, 0x1D586, 0x1D56C, '0', '1', 0x2002);
      }
  }

#ifdef RGBLIGHT_ENABLE
  bool res = process_record_user_rgb(keycode, record);
  if (!res) return false;
#endif

  return true;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef RGBLIGHT_ENABLE
  post_process_record_user_rgb(keycode, record);
#endif
  return;
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

#if defined(CONSOLE_ENABLE) && !defined(NO_DEBUG)
#if defined(SPI_DEBUG_SCAN_RATE)
static uint32_t matrix_timer      = 0;
static uint32_t matrix_scan_count = 0;
static uint32_t last_matrix_scan_count = 0;
static bool reported_version = false;
#define SPI_SCAN_RATE_INTERVAL 10
void matrix_scan_user(void) {
  matrix_scan_count++;
  if (debug_enable) {
    uint32_t timer_now = timer_read32();
    if (matrix_timer == 0) {
      matrix_timer = timer_now;
      last_matrix_scan_count = matrix_scan_count;
      matrix_scan_count = 0;
    } else if (TIMER_DIFF_32(timer_now, matrix_timer) > SPI_SCAN_RATE_INTERVAL * 1000) {
      matrix_timer = timer_now;
      last_matrix_scan_count = matrix_scan_count;
      matrix_scan_count = 0;
      if (!reported_version) {
        uprintln(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION ", Built on: " QMK_BUILDDATE);
        reported_version = true;
      }
      uprintf("scan rate: %u/s\n", last_matrix_scan_count / SPI_SCAN_RATE_INTERVAL);
    }
  } else {
    matrix_timer = 0;
  }
}
#else
static uint32_t matrix_scan_count = 0;
static bool reported_version = false;
void matrix_scan_user(void) {
  matrix_scan_count++;
  if (!reported_version && matrix_scan_count > 300) {
    uprintln(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION ", Built on: " QMK_BUILDDATE);
    reported_version = true;
  }
}
#endif
#endif
