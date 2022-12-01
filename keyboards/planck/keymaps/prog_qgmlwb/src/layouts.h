// Copyright 2022 David Kristoffersen (@davidkristoffersen)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include QMK_KEYBOARD_H

#include "davidkristoffersen.h"
#include "enums.h"

#include "normal.h"
#include "qgmlwb.h"
#include "special.h"

#define KEYMAP const uint16_t PROGMEM

// Layouts keycodes
#define lower MO(NORMAL_LOWER)
#define raise MO(NORMAL_RAISE)

#define QLower MO(QGMLWB_LOWER)
#define QRaise MO(QGMLWB_RAISE)

#define adjust MO(ADJUST)
#define numpad MO(NUMPAD)

extern KEYMAP keymaps [][MATRIX_ROWS][MATRIX_COLS];
