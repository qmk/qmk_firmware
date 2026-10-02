// Copyright 2026 Kyle Schwarz (Zeranoe)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(LCTL(KC_C), LCTL(KC_V), KC_ENT)
};
