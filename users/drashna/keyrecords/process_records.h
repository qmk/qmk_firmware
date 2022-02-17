// Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include "drashna.h"

#if defined(KEYBOARD_handwired_tractyl_manuform)
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

bool process_record_secrets(uint16_t keycode, keyrecord_t *record);
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
void post_process_record_keymap(uint16_t keycode, keyrecord_t *record);
#ifdef CUSTOM_UNICODE_ENABLE
bool process_record_unicode(uint16_t keycode, keyrecord_t *record);
#endif

#define LOWER     MO(_LOWER)
#define RAISE     MO(_RAISE)
#define ADJUST    MO(_ADJUST)
#define TG_MODS   OS_TOGG
#define TG_GAME   TG(_GAMEPAD)
#define TG_DBLO   TG(_DIABLO)
#define OS_LWR    OSL(_LOWER)
#define OS_RSE    OSL(_RAISE)

#define KC_SEC1   KC_SECRET_1
#define KC_SEC2   KC_SECRET_2
#define KC_SEC3   KC_SECRET_3
#define KC_SEC4   KC_SECRET_4
#define KC_SEC5   KC_SECRET_5

#define QWERTY    KC_QWERTY
#define DVORAK    KC_DVORAK
#define COLEMAK   KC_COLEMAK
#define COLEMAKDH KC_COLEMAK_DH

#define DEFLYR1   FIRST_DEFAULT_LAYER_KEYCODE
#define DEFLYR2   (FIRST_DEFAULT_LAYER_KEYCODE + 1)
#define DEFLYR3   (FIRST_DEFAULT_LAYER_KEYCODE + 2)
#define DEFLYR4   (FIRST_DEFAULT_LAYER_KEYCODE + 3)
#if LAST_DEFAULT_LAYER_KEYCODE > (FIRST_DEFAULT_LAYER_KEYCODE + 3)
#    define DEFLYR5 (FIRST_DEFAULT_LAYER_KEYCODE + 4)
#    define DEFLYR6 (FIRST_DEFAULT_LAYER_KEYCODE + 5)
#    define DEFLYR7 (FIRST_DEFAULT_LAYER_KEYCODE + 6)
#    define DEFLYR8 (FIRST_DEFAULT_LAYER_KEYCODE + 7)
#    if LAST_DEFAULT_LAYER_KEYCODE > (FIRST_DEFAULT_LAYER_KEYCODE + 7)
#        define DEFLYR9  (FIRST_DEFAULT_LAYER_KEYCODE + 8)
#        define DEFLYR10 (FIRST_DEFAULT_LAYER_KEYCODE + 9)
#        define DEFLYR11 (FIRST_DEFAULT_LAYER_KEYCODE + 10)
#        define DEFLYR12 (FIRST_DEFAULT_LAYER_KEYCODE + 11)
#    endif
#endif

#define KC_RESET RESET
#define KC_RST   KC_RESET

#ifdef SWAP_HANDS_ENABLE
#    define KC_C1R3 SH_T(KC_TAB)
#elif defined(DRASHNA_LP)
#    define KC_C1R3 TG(_GAMEPAD)
#else  // SWAP_HANDS_ENABLE
#    define KC_C1R3 KC_TAB
#endif  // SWAP_HANDS_ENABLE

#define BK_LWER LT(_LOWER, KC_BSPC)
#define SP_LWER LT(_LOWER, KC_SPC)
#define DL_RAIS LT(_RAISE, KC_DEL)
#define ET_RAIS LT(_RAISE, KC_ENTER)

/* OSM keycodes, to keep things clean and easy to change */
#define KC_MLSF OSM(MOD_LSFT)
#define KC_MRSF OSM(MOD_RSFT)

#define OS_LGUI OSM(MOD_LGUI)
#define OS_RGUI OSM(MOD_RGUI)
#define OS_LSFT OSM(MOD_LSFT)
#define OS_RSFT OSM(MOD_RSFT)
#define OS_LCTL OSM(MOD_LCTL)
#define OS_RCTL OSM(MOD_RCTL)
#define OS_LALT OSM(MOD_LALT)
#define OS_RALT OSM(MOD_RALT)
#define OS_MEH  OSM(MOD_MEH)
#define OS_HYPR OSM(MOD_HYPR)

#define ALT_APP ALT_T(KC_APP)

#define MG_NKRO MAGIC_TOGGLE_NKRO


/*
Custom Keycodes for Diablo 3 layer
But since TD() doesn't work when tap dance is disabled
We use custom codes here, so we can substitute the right stuff
*/
#ifdef TAP_DANCE_ENABLE
#    define KC_D3_1 TD(TD_D3_1)
#    define KC_D3_2 TD(TD_D3_2)
#    define KC_D3_3 TD(TD_D3_3)
#    define KC_D3_4 TD(TD_D3_4)
#else  // TAP_DANCE_ENABLE
#    define KC_D3_1 KC_1
#    define KC_D3_2 KC_2
#    define KC_D3_3 KC_3
#    define KC_D3_4 KC_4
#endif  // TAP_DANCE_ENABLE
