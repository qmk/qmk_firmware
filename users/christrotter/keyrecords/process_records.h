// Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include "christrotter.h"

#if defined(KEYBOARD_handwired_tractyl_manuform_ct) && defined(POINTING_DEVICE_ENABLE)
#    define PLACEHOLDER_SAFE_RANGE KEYMAP_SAFE_RANGE
#else
#    define PLACEHOLDER_SAFE_RANGE SAFE_RANGE
#endif

enum userspace_custom_keycodes {
    VRSN = PLACEHOLDER_SAFE_RANGE,            // Prints QMK Firmware and board info
    KC_QWERTY,                                // Sets default layer to QWERTY
    FIRST_DEFAULT_LAYER_KEYCODE = KC_QWERTY,  // Sets default layer to QWERTY
    KC_COLEMAK_DH,                            // Sets default layer to COLEMAK
    KC_COLEMAK,                               // Sets default layer to COLEMAK
    KC_DVORAK,                                // Sets default layer to DVORAK
    LAST_DEFAULT_LAYER_KEYCODE = KC_DVORAK,   // Sets default layer to WORKMAN
    KC_DIABLO_CLEAR,                          // Clears all Diablo Timers
    KC_MAKE,                                  // Run keyboard's customized make command
    KC_RGB_T,                                 // Toggles RGB Layer Indication mode
    RGB_IDL,                                  // RGB Idling animations
    KC_SECRET_1,                              // test1
    KC_SECRET_2,                              // test2
    KC_SECRET_3,                              // test3
    KC_SECRET_4,                              // test4
    KC_SECRET_5,                              // test5
    KC_CCCV,                                  // Hold to copy, tap to paste
    KC_NUKE,                                  // NUCLEAR LAUNCH DETECTED!!!
    UC_FLIP,                                  // (ಠ痊ಠ)┻━┻
    UC_TABL,                                  // ┬─┬ノ( º _ ºノ)
    UC_SHRG,                                  // ¯\_(ツ)_/¯
    UC_DISA,                                  // ಠ_ಠ
    UC_IRNY,
    UC_CLUE,
    KEYLOCK,                                  // Locks keyboard by unmounting driver
    KC_NOMODE,
    KC_WIDE,
    KC_SCRIPT,
    KC_BLOCKS,
    KC_REGIONAL,
    KC_AUSSIE,
    KC_ZALGO,
    KC_ACCEL,
    AUTO_CTN,                                 // Toggle Autocorrect status
    REBOOT,
    NEW_SAFE_RANGE                            // use "NEWPLACEHOLDER for keymap specific codes
};

// bool process_record_secrets(uint16_t keycode, keyrecord_t *record);
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
void post_process_record_keymap(uint16_t keycode, keyrecord_t *record);
#ifdef CUSTOM_UNICODE_ENABLE
bool process_record_unicode(uint16_t keycode, keyrecord_t *record);
#endif
