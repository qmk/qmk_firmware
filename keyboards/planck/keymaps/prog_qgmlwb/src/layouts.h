// Copyright 2022 David Kristoffersen (@davidkristoffersen)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include QMK_KEYBOARD_H

#include "davidkristoffersen.h"

#include "normal.h"
#include "qgmlwb.h"
#include "special.h"

#define KEYMAP const uint16_t PROGMEM

// Layouts enum
enum keyboard_layouts {
    QGMLWB_NO,
    QGMLWB_US,

    QWERTY,
    COLEMAK,
    DVORAK,

    NORMAL_LOWER,
    NORMAL_RAISE,

    QGMLWB_NO_LOWER,
    QGMLWB_US_LOWER,

    QGMLWB_NO_RAISE,
    QGMLWB_US_RAISE,

    ADJUST,
    NUMPAD,
};

// Layouts keycodes
#define lower MO(NORMAL_LOWER)
#define raise MO(NORMAL_RAISE)

#define QNLower MO(QGMLWB_NO_LOWER)
#define QELower MO(QGMLWB_US_LOWER)

#define QNRaise MO(QGMLWB_NO_RAISE)
#define QERaise MO(QGMLWB_US_RAISE)

#define adjust MO(ADJUST)
#define numpad MO(NUMPAD)

extern KEYMAP keymaps [][MATRIX_ROWS][MATRIX_COLS];
