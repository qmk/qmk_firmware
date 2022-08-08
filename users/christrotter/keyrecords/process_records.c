// Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "christrotter.h"
#include "print.h"

#ifdef __AVR__
#    include <avr/wdt.h>
#endif

uint16_t copy_paste_timer;

// Defines actions tor my global custom keycodes. Defined in drashna.h file
// Then runs the _keymap's record handier if not processed here

/**
 * @brief Keycode handler for keymaps
 *
 * This handles the keycodes at the keymap level, useful for keyboard specific customization
 */
__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }
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
    // #ifdef CONSOLE_ENABLE
    //     uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    // #endif 
    if (!(process_record_keymap(keycode, record)
#ifdef CUSTOM_RGB_MATRIX
          && process_record_user_rgb_matrix(keycode, record)
#endif
#if defined(CUSTOM_POINTING_DEVICE)
          && process_record_pointing(keycode, record)
#endif
          && true)) {
        return false;
    }
    // now we check for specific keycodes...
    switch (keycode) {
            case LT(0,KC_TILD):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LCMD(KC_TILD)); // hold for command+letter
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
//            case LT(0,KC_S):
//            if (!record->tap.count && record->event.pressed) {
//                tap_code16(LCMD(KC_S)); // hold for command+letter
//                return false;
//            }
//            return true;             // Return true for normal processing of tap keycode
//            case LT(0,KC_Z):
//            if (!record->tap.count && record->event.pressed) {
//                tap_code16(LCMD(KC_Z)); // hold for command+letter
//                return false;
//            }
//            return true;             // Return true for normal processing of tap keycode
//            case LT(0,KC_X):
//            if (!record->tap.count && record->event.pressed) {
//                tap_code16(LCMD(KC_X)); // hold for command+letter
//                return false;
//            }
//            return true;             // Return true for normal processing of tap keycode
//            case LT(0,KC_C):
//            if (!record->tap.count && record->event.pressed) {
//                tap_code16(LCMD(KC_C)); // hold for command+letter
//                return false;
//            }
//            return true;             // Return true for normal processing of tap keycode
//            case LT(0,KC_V):
//            if (!record->tap.count && record->event.pressed) {
//                tap_code16(LCMD(KC_V)); // hold for command+letter
//                return false;
//            }
//            return true;
//            case LT(0,KC_B):
//            if (!record->tap.count && record->event.pressed) {
//                tap_code16(LCMD(KC_B)); // hold for command+letter
//                return false;
//            }
//            return true;
//            case LT(0,KC_A):
//            if (!record->tap.count && record->event.pressed) {
//                tap_code16(LCMD(KC_A)); // hold for command+letter
//                return false;
//            }
//            return true;
//            case LT(0,KC_R):
//            if (!record->tap.count && record->event.pressed) {
//                tap_code16(LCMD(KC_R)); // hold for command+letter
//                return false;
//            }
//            return true;
//            case LT(0,KC_W):
//            if (!record->tap.count && record->event.pressed) {
//                tap_code16(LCMD(KC_W)); // hold for command+letter
//                return false;
//            }
//            return true;
//            case LT(0,KC_K):
//            if (!record->tap.count && record->event.pressed) {
//                tap_code16(LCMD(KC_K)); // hold for command+letter
//                return false;
//            }
//            return true;
//            case LT(0,KC_L):
//            if (!record->tap.count && record->event.pressed) {
//                tap_code16(LCMD(KC_L)); // hold for command+letter
//                return false;
//            }
//            return true;
//            case LT(0,KC_T):
//            if (!record->tap.count && record->event.pressed) {
//                tap_code16(LCMD(KC_T)); // hold for command+letter
//                return false;
//            }
//            return true;
//            case LT(0,KC_F):
//            if (!record->tap.count && record->event.pressed) {
//                tap_code16(LCMD(KC_F)); // hold for command+letter
//                return false;
//            }
//            return true;
            case LT(0,KC_N):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LCMD(LSFT(KC_N))); // hold for command+letter
                return false;
            }
            return true;
//            case LT(0,KC_I):
//            if (!record->tap.count && record->event.pressed) {
//                tap_code16(LCMD(KC_I)); // hold for command+letter
//                return false;
//            }
//            return true;
            case LT(0,KC_MPLY):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_MNXT); // hold for command+letter
                return false;
            }
            return true;
    }
    return true;
}

__attribute__((weak)) void post_process_record_keymap(uint16_t keycode, keyrecord_t *record) {}
void                       post_process_record_user(uint16_t keycode, keyrecord_t *record) { post_process_record_keymap(keycode, record); }
