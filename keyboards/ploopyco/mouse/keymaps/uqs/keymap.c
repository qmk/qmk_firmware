// Copyright 2022 Ulrich Spörlein (@uqs)
// SPDX-License-Identifier: GPL-2.0-or-later
// vi:et sw=4:

#include QMK_KEYBOARD_H

enum custom_keycodes {
    DBL_CLK_NO = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // This works fine in xev(1) or a browser, but not in the game where I
        // would want it. Maybe need to increase the delay? Also needs to be
        // rewritten to use Deferred Execution.
        case DBL_CLK_NO:
            if (record->event.pressed) {
                tap_code(KC_BTN2);
                wait_ms(150);
                tap_code(KC_BTN2);
                wait_ms(300);
                tap_code(KC_N);
            }
            return false;
    }
    return true;
}


// Layout is:
// left-most, M1, M3, M2, right-most, fwd, back (on side), tiny middle one

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(KC_E, KC_BTN1, KC_BTN3, KC_BTN2, KC_LSFT, KC_BTN4, KC_BTN5, DF(1)),  // shooters
    [1] = LAYOUT(KC_1, KC_BTN1, KC_Y, KC_BTN2, DBL_CLK_NO, KC_N, KC_Y, DF(0)),        // stardew valley, sword on 1
};
