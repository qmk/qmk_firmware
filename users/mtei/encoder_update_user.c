// Copyright (c) 2022 Takeshi Ishii (mtei@github)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

/* weak reference */ __attribute__((weak))
int get_encoder_over_count(void);

bool encoder_update_user(uint8_t index, bool clockwise) {
#ifndef ENCODER_DETECT_OVER_SPEED
    switch (index) {
    /* Left side encoder */
    case 0: tap_code(clockwise ? KC_LEFT : KC_RGHT); break;
    /* Right side encoder */
    case 1: tap_code(clockwise ? KC_DOWN : KC_UP); break;
    }
#else
    // Is there a get_encoder_over_count() in quantum/encoder.c
    if (get_encoder_over_count != NULL) {
        int enc_over = get_encoder_over_count();
        for (; enc_over > 0; enc_over--) {
            tap_code(KC_MINUS);
        }
    }
    switch (index) {
    case 0: tap_code(clockwise ? KC_A : KC_B); break;
    case 1: tap_code(clockwise ? KC_C : KC_D); break;
    case 2: tap_code(clockwise ? KC_E : KC_F); break;
    case 3: tap_code(clockwise ? KC_G : KC_H); break;
    }
#endif
    return true;
}
