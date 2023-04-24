// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>
#ifdef VIA_ENABLE
#    include "via.h"
#endif
#include "quantum_keycodes.h"

enum custom_keycodes {
    KC_LOPTN = QK_KB_0, // TECH DEBT: Starts at QK_KB_2 to maintain ordering with VIA definitions. See #19884. Revert to QK_KB_0 when VIA catches up with QMK.
    KC_ROPTN,
    KC_LCMMD,
    KC_RCMMD,
    KC_SIRI,
    KC_TASK_VIEW,
    KC_FILE_EXPLORER,
    KC_SCREEN_SHOT,
    KC_CORTANA
};

#define KC_TASK KC_TASK_VIEW
#define KC_FLXP KC_FILE_EXPLORER
#define KC_SNAP KC_SCREEN_SHOT
#define KC_CRTA KC_CORTANA

typedef struct PACKED {
    uint8_t len;
    uint8_t keycode[3];
} key_combination_t;

void housekeeping_task_keychron(void);
bool process_record_keychron(uint16_t keycode, keyrecord_t *record);
