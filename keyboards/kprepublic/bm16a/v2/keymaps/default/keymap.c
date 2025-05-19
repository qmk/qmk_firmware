// Copyright 2022 fauxpark (@fauxpark)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_4x4(
        KC_P7,   KC_P8,   KC_P9,   KC_PMNS,
        KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        KC_P0,   KC_PDOT, KC_SPC,  MO(1)
    ),
    [1] = LAYOUT_ortho_4x4(
        QK_BOOT, KC_PAST, KC_PSLS, _______,
        RM_TOGG, RM_NEXT, RM_HUEU, RM_HUED,
        RM_SATU, RM_SATD, RM_VALU, RM_VALD,
        _______, _______, _______, _______
  )
};
