// Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "christrotter.h"
//#include "version.h"
#include "print.h"

#ifdef __AVR__
#    include <avr/wdt.h>
#endif

uint16_t copy_paste_timer;
bool     host_driver_disabled = false;
// Defines actions tor my global custom keycodes. Defined in drashna.h file
// Then runs the _keymap's record handier if not processed here

/**
 * @brief Keycode handler for keymaps
 *
 * This handles the keycodes at the keymap level, useful for keyboard specific customization
 */
__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }
// __attribute__((weak)) bool process_record_secrets(uint16_t keycode, keyrecord_t *record) { return true; }

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
    // not sure why you have this 'if not a record return false' block...
    if (!(process_record_keymap(keycode, record)
#ifdef CUSTOM_RGB_MATRIX
          && process_record_user_rgb_matrix(keycode, record)
#endif
#ifdef CUSTOM_UNICODE_ENABLE
          && process_record_unicode(keycode, record)
#endif
#if defined(CUSTOM_POINTING_DEVICE)
          && process_record_pointing(keycode, record)
#endif
          && true)) {
        return false;
    }
    // now we check for specific keycodes...
    switch (keycode) {
//         case FIRST_DEFAULT_LAYER_KEYCODE ... LAST_DEFAULT_LAYER_KEYCODE:
//             if (record->event.pressed) {
//                 uint8_t mods = mod_config(get_mods() | get_oneshot_mods());
//                 if (!mods) {
//                     set_single_persistent_default_layer(keycode - FIRST_DEFAULT_LAYER_KEYCODE);
// #if LAST_DEFAULT_LAYER_KEYCODE > (FIRST_DEFAULT_LAYER_KEYCODE + 3)
//                 } else if (mods & MOD_MASK_SHIFT) {
//                     set_single_persistent_default_layer(keycode - FIRST_DEFAULT_LAYER_KEYCODE + 4);
// #    if LAST_DEFAULT_LAYER_KEYCODE > (FIRST_DEFAULT_LAYER_KEYCODE + 7)
// 
//                 } else if (mods & MOD_MASK_CTRL) {
//                     set_single_persistent_default_layer(keycode - FIRST_DEFAULT_LAYER_KEYCODE + 8);
// #    endif
// #endif
//                 }
//             }
//             break;
            case LT(0,KC_TILD):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LCMD(KC_TILD)); // Intercept hold function to send Ctrl-X
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
            case LT(0,KC_S):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LCMD(KC_S)); // Intercept hold function to send Ctrl-X
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
            case LT(0,KC_Z):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LCMD(KC_Z)); // Intercept hold function to send Ctrl-X
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
            case LT(0,KC_X):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LCMD(KC_X)); // Intercept hold function to send Ctrl-X
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
            case LT(0,KC_C):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LCMD(KC_C)); // Intercept hold function to send Ctrl-X
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
            case LT(0,KC_V):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LCMD(KC_V)); // Intercept hold function to send Ctrl-X
                return false;
            }
            return true;
            case LT(0,KC_B):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LCMD(KC_B)); // Intercept hold function to send Ctrl-X
                return false;
            }
            return true;
            case LT(0,KC_A):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LCMD(KC_A)); // Intercept hold function to send Ctrl-X
                return false;
            }
            return true;
            case LT(0,KC_R):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LCMD(KC_R)); // Intercept hold function to send Ctrl-X
                return false;
            }
            return true;
            case LT(0,KC_W):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LCMD(KC_W)); // Intercept hold function to send Ctrl-X
                return false;
            }
            return true;
            case LT(0,KC_K):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LCMD(KC_K)); // Intercept hold function to send Ctrl-X
                return false;
            }
            return true;
            case LT(0,KC_L):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LCMD(KC_L)); // Intercept hold function to send Ctrl-X
                return false;
            }
            return true;
            case LT(0,KC_T):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LCMD(KC_T)); // Intercept hold function to send Ctrl-X
                return false;
            }
            return true;
            case LT(0,KC_F):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LCMD(KC_F)); // Intercept hold function to send Ctrl-X
                return false;
            }
            return true;
            case LT(0,KC_N):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LCMD(LSFT(KC_N))); // Intercept hold function to send Ctrl-X
                return false;
            }
            return true;
    }
    return true;
}


__attribute__((weak)) void post_process_record_keymap(uint16_t keycode, keyrecord_t *record) {}
void                       post_process_record_user(uint16_t keycode, keyrecord_t *record) { post_process_record_keymap(keycode, record); }
