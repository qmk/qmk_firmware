// Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include "christrotter.h"

#if defined(KEYBOARD_handwired_tractyl_manuform_ct) && defined(POINTING_DEVICE_ENABLE)
#    define PLACEHOLDER_SAFE_RANGE KEYMAP_SAFE_RANGE
#else
#    define PLACEHOLDER_SAFE_RANGE SAFE_RANGE
#endif


// TODO need to remove these layer keycodes...
enum userspace_custom_keycodes {
//    KC_QWERTY,                                // Sets default layer to QWERTY
//    FIRST_DEFAULT_LAYER_KEYCODE = KC_QWERTY,  // Sets default layer to QWERTY
//    KC_COLEMAK_DH,                            // Sets default layer to COLEMAK
//    KC_COLEMAK,                               // Sets default layer to COLEMAK
//    KC_DVORAK,                                // Sets default layer to DVORAK
//    LAST_DEFAULT_LAYER_KEYCODE = KC_DVORAK,   // Sets default layer to WORKMAN
    KC_ACCEL,
    NEW_SAFE_RANGE                            // use "NEWPLACEHOLDER for keymap specific codes
};

//bool set_scrolling = false;
// bool process_record_secrets(uint16_t keycode, keyrecord_t *record);
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
void post_process_record_keymap(uint16_t keycode, keyrecord_t *record);
#ifdef CUSTOM_UNICODE_ENABLE
bool process_record_unicode(uint16_t keycode, keyrecord_t *record);
#endif
