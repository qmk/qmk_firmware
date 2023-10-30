// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

enum custom_keycodes {
    GRIN_TEAMS = SAFE_RANGE,
    GRIN_SLACK,
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case GRIN_TEAMS:
        if (record->event.pressed) {
            // when keycode GRIN_TEAMS is pressed
            SEND_STRING("(beamingfacewithsmilingeyes)");
        } else {
            // when keycode GRIN_TEAMS is released
        }
        break;

    case GRIN_SLACK:
        if (record->event.pressed) {
            // when keycode GRIN_SLACK is pressed
            SEND_STRING(":grin:");
        } else {
            // when keycode GRIN_SLACK is released
        }
        break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        GRIN_TEAMS,
        GRIN_SLACK
    ),
};
