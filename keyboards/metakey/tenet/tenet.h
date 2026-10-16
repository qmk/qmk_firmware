// Copyright 2026 Connor Gallopo (@connorgallopo)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

typedef enum {
    TENET_ORIENTATION_REGULAR  = 0,
    TENET_ORIENTATION_SOUTHPAW = 1,
} tenet_orientation_t;

// PA15 is pulled low when the daughterboard sits on the southpaw side.
tenet_orientation_t tenet_read_orientation(void);

// OLED text, persisted in the keyboard EEPROM block.
#define TENET_OLED_TEXT_MAX_LEN 16
#define TENET_OLED_TEXT_DEFAULT "TENET QMK"

const char *tenet_oled_text_get(void);
void        tenet_oled_text_set(const char *text);

// Side indicator LEDs, last two entries of the RGB layout.
#define TENET_LED_IND_L 73
#define TENET_LED_IND_R 74

enum tenet_keycodes {
    KC_OLED_EDIT = QK_KB_0,
    KC_OLED_L,
    KC_OLED_R,
};
