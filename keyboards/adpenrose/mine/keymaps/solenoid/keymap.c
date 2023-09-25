// Copyright 2022 Arturo Avila (@Arturo Avila)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_all(
                                                                                                                                                                                              HF_TOGG,
        KC_ESC,    KC_F1,   KC_F2,    KC_F3,    KC_F4,   KC_F5,   KC_F6,       KC_F7,   KC_F8,   KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_HOME,   KC_END,         KC_NUM, KC_PSLS, KC_PAST, KC_PMNS, 
        KC_GRV,    KC_1,    KC_2,     KC_3,     KC_4,    KC_5,    KC_6,        KC_7,    KC_8,    KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,                   KC_P7,  KC_P8,   KC_P9,   KC_PPLS,
        KC_TAB,    KC_Q,    KC_W,     KC_E,     KC_R,    KC_T,                 KC_Y,    KC_U,    KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC, KC_BSLS,          KC_P4,  KC_P5,   KC_P6,
        KC_CAPS,   KC_A,    KC_S,     KC_D,     KC_F,    KC_G,                 KC_H,    KC_J,    KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_NUHS, KC_ENT,           KC_P1,  KC_P2,   KC_P3,   KC_PENT,
        KC_LSFT,   MO(1), KC_Z,     KC_X,     KC_C,    KC_V,    KC_B,        KC_B,    KC_N,    KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,            KC_UP,         KC_P0,   KC_PDOT, 
        KC_LCTL,   KC_LGUI,                     KC_LALT, KC_SPC,               KC_SPC,  KC_RALT, KC_RGUI,  KC_RCTL,                                KC_LEFT, KC_DOWN,  KC_RIGHT  
    ),

    [1] = LAYOUT_all(
                                                                                                                                                                                                                             KC_TRNS,
        QK_BOOT,   KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,   KC_TRNS,   KC_TRNS,       KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_PSCR,  KC_DEL,               KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS, 
        KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,   KC_TRNS,   KC_TRNS,       KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,                        KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
        KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,   KC_TRNS,                  KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,              KC_TRNS,  KC_TRNS,   KC_TRNS,
        KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,   KC_TRNS,                  KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,              KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
        KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,     KC_TRNS,   KC_TRNS,   KC_TRNS,       KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,             KC_TRNS,             KC_TRNS,   KC_TRNS, 
        KC_TRNS,   KC_TRNS,                           KC_TRNS,   KC_TRNS,                  KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,                                    KC_TRNS, KC_TRNS,  KC_TRNS 
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] =  { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) }
};
#endif

#ifdef HAPTIC_ENABLE
bool get_haptic_enabled_key(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_VOLU ... KC_VOLD:
            return false;
    }
    return true;
}
#endif
