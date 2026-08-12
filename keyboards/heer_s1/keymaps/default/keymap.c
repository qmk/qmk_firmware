// Copyright 2026 Heer (@heer)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    L_BASE,
    L_MEDIA,
    L_EDIT,
    L_SYS,
};

// The bottom-right key advances to the next layer and wraps, so all four are
// reachable using nothing but standard keycodes.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [L_BASE] = LAYOUT(
        TO(L_MEDIA), TO(L_BASE),
        KC_1,    KC_2,    KC_3,    KC_4,
        KC_5,    KC_6,    KC_7,    KC_8,
        KC_9,    KC_0,    KC_MINS, KC_EQL,
        KC_BSPC, KC_ENT,  KC_ESC,  TO(L_MEDIA)
    ),

    [L_MEDIA] = LAYOUT(
        TO(L_EDIT), TO(L_BASE),
        KC_MPLY, KC_MSTP, KC_MPRV, KC_MNXT,
        KC_VOLD, KC_VOLU, KC_MUTE, _______,
        KC_BRID, KC_BRIU, _______, _______,
        _______, _______, _______, TO(L_EDIT)
    ),

    [L_EDIT] = LAYOUT(
        TO(L_SYS), TO(L_BASE),
        LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V),
        LCTL(KC_A), LCTL(KC_S), LCTL(KC_F), LCTL(KC_H),
        LCTL(KC_N), LCTL(KC_W), LCTL(KC_T), LCTL(KC_P),
        KC_DEL,     KC_HOME,    KC_END,     TO(L_SYS)
    ),

    [L_SYS] = LAYOUT(
        TO(L_BASE), TO(L_BASE),
        KC_F1,   KC_F2,   KC_F3,   KC_F4,
        KC_F5,   KC_F6,   KC_F7,   KC_F8,
        KC_F9,   KC_F10,  KC_F11,  KC_F12,
        KC_PSCR, KC_SCRL, KC_PAUS, TO(L_BASE)
    ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [L_BASE]  = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),       ENCODER_CCW_CW(KC_LEFT, KC_RGHT) },
    [L_MEDIA] = { ENCODER_CCW_CW(KC_MPRV, KC_MNXT),       ENCODER_CCW_CW(KC_BRID, KC_BRIU) },
    [L_EDIT]  = { ENCODER_CCW_CW(LCTL(KC_Z), LCTL(KC_Y)), ENCODER_CCW_CW(KC_UP,   KC_DOWN) },
    [L_SYS]   = { ENCODER_CCW_CW(KC_F11,  KC_F12),        ENCODER_CCW_CW(KC_PGDN, KC_PGUP) },
};
#endif
