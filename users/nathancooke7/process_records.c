// Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "nathancooke7.h"
#include "version.h"

// Defines actions tor my global custom keycodes. Defined in drashna.h file
// Then runs the _keymap's record handier if not processed here

/**
 * @brief Keycode handler for keymaps
 *
 * This handles the keycodes at the keymap level, useful for keyboard specific customization
 */
__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }
__attribute__((weak)) bool process_record_secrets(uint16_t keycode, keyrecord_t *record) { return true; }

/**
 * @brief Main user keycode handler
 *
 * This handles all of the keycodes for the user, including calling feature handlers.
 *
 * @param keycode Keycode from matrix
 * @param record keyrecord_t data structure
 * @return true Continue processing keycode and send to host
 * @return false Stop process keycode and do not send to host
 */

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static bool tAuNtTeXt = false;
  static uint16_t my_combo_timer;

  if (tAuNtTeXt) {
    if (record->event.pressed) {
      if (keycode != KC_SPC) {
        tap_code(KC_CAPS);
      }
    }
  }

  switch (keycode) {
    case SARCASM:
      if (record->event.pressed) {
        tAuNtTeXt = !tAuNtTeXt;
        if (tAuNtTeXt) {
          tap_code(KC_CAPS);
        }
        else if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {
          tap_code(KC_CAPS);
        }
      }
      return false;
    case V_DRAG:
      if(record->event.pressed) {
        my_combo_timer = timer_read();
        register_code(DRAGSCROLL_MODE); // Change the key to be held here
        /* register_code(KC_LCTL); // Change the key to be held here */
      } else {
        unregister_code(DRAGSCROLL_MODE); // Change the key that was held here, too!
        /* unregister_code(KC_LCTL); // Change the key that was held here, too! */
        if (timer_elapsed(my_combo_timer) < TAPPING_TERM) {
          SEND_STRING("v"); // Change the character(s) to be sent on tap here
        }
      }
      return false;
  }
  return process_record_keymap(keycode, record) && process_record_secrets(keycode, record);
}

__attribute__((weak)) void post_process_record_keymap(uint16_t keycode, keyrecord_t *record) {}
void                       post_process_record_user(uint16_t keycode, keyrecord_t *record) { post_process_record_keymap(keycode, record); }
