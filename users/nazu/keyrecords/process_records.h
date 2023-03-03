/* Copyright 2023 Tom Sennewald (@beelzebubi)
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once
#include "nazu.h"

enum userspace_custom_keycodes {
    KC_QWERTY = QK_USER,    // change to QWERTY layer
    KC_COLEMAK,             // change to COLEMAK layer
    KC_COLEMAK_DH,          // change to COLEMAK DH layer
    KC_DVORAK,              // change to Dvorak layer
    KC_CAD,
    KC_SWAP,                // SWAP to MACOS mods
    KC_NORM,                // UNSWAP MACOS mods
    KC_R1,                  // wildcard to swap modifier in WIN/UNIX/MACOS
    KC_R2,                  // wildcard to swap modifier in WIN/UNIX/MACOS
    US_SPC,                 // blank to modify KC_SPC
    US_RSFT,                // blank to modify KC_RSFT
};

// bool process_record_secrets(uint16_t keycode, keyrecord_t *record);
// bool process_record_keymap(uint16_t keycode, keyrecord_t *record);

/* Aliases for longer keycodes */
#define KC_CAD	LALT(LCTL(KC_DEL))
#define CA_QUOT LCA(KC_QUOT)
#define CA_SCLN LCA(KC_SCLN)
#define KC_CTLE LCTL_T(KC_ESC)
#define LT_SPCF LT(_FN1_60, KC_SPC)
#define LT_BPCF LT(_FN1_60, KC_BSPC)
#define CA_COPY LCTL(KC_C)
#define CA_PSTE LCTL(KC_V)
#define LALT_F4 LM(_FN2, MOD_LALT)

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

#define QWERTY KC_QWERTY
#define DVORAK KC_DVORAK
#define COLEMAK KC_COLEMAK
#define CLMKDH KC_COLEMAK_DH

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

#ifdef TAP_DANCE_ENABLE
#   define TD_TESC TD(TD_ESC)
#   define TD_TWIN TD(TD_WIN)
#   define TD_TCTL TD(TD_RCTL)
#   define TD_CAPS TD(TD_LSFT_CAPS)
#   define TD_SPC TD(TD_SPACE_DOT)
#else // TAP_DANCE_ENABLE
#   define TD_TESC KC_ESC
#   define TD_TWIN KC_LGUI
#   define TD_TCTL KC_LCTL
#   define TD_CAPS KC_LSFT
#   define TD_SPC KC_SPACE
#endif // TAP_DANCE_ENABLE

