// Copyright 2026 Connor Gallopo (@connorgallopo)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#define RGB_MATRIX_LED_COUNT 76

typedef enum {
    TENET_ORIENTATION_REGULAR  = 0,
    TENET_ORIENTATION_SOUTHPAW = 1,
} tenet_orientation_t;

// Reads PA15: HIGH = regular, LOW = southpaw.
tenet_orientation_t tenet_read_orientation(void);

// OLED custom-text API. `text` must be null-terminated; anything past
// TENET_OLED_TEXT_MAX_LEN-1 bytes is truncated. Persisted in the keyboard
// EEPROM datablock.
#define TENET_OLED_TEXT_MAX_LEN 16
#define TENET_OLED_TEXT_DEFAULT "TENET QMK"

const char *tenet_oled_text_get(void);
void        tenet_oled_text_set(const char *text);

enum tenet_keycodes {
    KC_OLED_EDIT = QK_KB_0,
    KC_OLED_L,                 // left OLED key — holding as part of a chord
    KC_OLED_R,                 // right OLED key — holding as part of a chord
    TENET_KC_SAFE_RANGE,
};
