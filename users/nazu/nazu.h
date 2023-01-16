/* Copyright 2023 Tom Sennewald (@beelzebubi)
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once
#include QMK_KEYBOARD_H

#include "keyrecords/wrappers.h"
#include "keyrecords/process_records.h"

/* Tap Dance definitions */
#ifdef TAP_DANCE_ENABLE
#   include "keyrecords/tap_dances.h"
#endif

// /* OLED definitions */
// #ifdef OLED_ENABLE
// #   include "oled/oled.h"
// #endif

/* Define layer names */
enum userspace_layers {
    _QWERTY = 0,    // QWERTY layout for WIN or UNIX
    _COLEMAK,       // Colemak lazout
    _COLEMAK_DH,    // Colemak DHS layout
    _FN1,           //
    _FN2,           //
    _MEDIA,         //
    _LOWER,         //
    _RAISE,         //
    _ADJUST,        //
};


