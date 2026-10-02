// Copyright 2024 Richard George
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum unicode_names {
    UE_LOW,  // ü
    UE_HIGH, // Ü
    AE_LOW,  // ä
    AE_HIGH, // Ä
    OE_LOW,  // ö
    OE_HIGH, // Ö
    SZ_LOW,  // ß
    SZ_HIGH, // ẞ
    EURO,    // €
};

const uint32_t PROGMEM unicode_map[] = {
    [UE_LOW]  = 0x00FC, // ü
    [UE_HIGH] = 0x00DC, // Ü
    [AE_LOW]  = 0x00E4, // ä
    [AE_HIGH] = 0x00C4, // Ä
    [OE_LOW]  = 0x00F6, // ö
    [OE_HIGH] = 0x00D6, // Ö
    [SZ_LOW]  = 0x00DF, // ß
    [SZ_HIGH] = 0x1E9E, // ẞ
    [EURO]    = 0x20AC, // €
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SCRL, KC_PAUS,

        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_INS,  KC_HOME, KC_PGUP,
                                                                                                                           KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,

        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,  KC_END,  KC_PGDN,
                                                                                                                           KC_P7,   KC_P8,   KC_P9,   KC_PPLS,

        MO(1),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS,          KC_P4,   KC_P5,   KC_P6,

        KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_P1,   KC_P2,   KC_P3,   KC_PENT,

        KC_LCTL, KC_LALT,                   KC_SPC,                    KC_RALT, KC_LGUI,          KC_LEFT, KC_DOWN, KC_RGHT,          KC_P0,   KC_PDOT
    ),

    [1] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLU,
                                                                                                                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

        KC_TRNS, KC_TRNS, KC_TRNS, UM(EURO), KC_TRNS, KC_TRNS, KC_TRNS, UP(UE_LOW, UE_HIGH), KC_TRNS, UP(OE_LOW, OE_HIGH), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLD,
                                                                                                                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

        KC_TRNS, UP(AE_LOW, AE_HIGH), UP(SZ_LOW, SZ_HIGH), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_END, KC_TRNS, KC_TRNS
    )
};

void matrix_init_user(void) {
    set_unicode_input_mode(UNICODE_MODE_LINUX);
}
