// Copyright 2023 KiwiKey
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_WHOM,   KC_CALC,   KC_MYCM,    // Launch application:  Browser    - Calculator - My Computer
        KC_MPLY,   KC_MPRV,   KC_MNXT,    // Media track control: Play/Pause - Prev Track - Next Track
        MO(1),     LCTL(KC_C),LCTL(KC_V), //                      FN(1)      - Copy       - Paste
        KC_MUTE,   KC_HOME
    ),
    [1] = LAYOUT(
        RGB_TOG,   RGB_RMOD,  RGB_MOD,
        _______,   RGB_VAD,   RGB_VAI,
        _______,   MO(2),     _______,
        _______,   _______
    ),
    [2] = LAYOUT(
        _______,   _______,   _______,
        _______,   _______,   _______,
        _______,   _______,   MO(3),
        _______,   _______
    ),
    [3] = LAYOUT(
        QK_BOOT,   _______,   _______,
        _______,   _______,   _______,
        _______,   _______,   _______,
        _______,   _______
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][2][2] = {
    [0] = { ENCODER_CCW_CW( KC_VOLD,  KC_VOLU ), ENCODER_CCW_CW( KC_PGUP,  KC_PGDN ) },
    [1] = { ENCODER_CCW_CW( RGB_VAD,  RGB_VAI ), ENCODER_CCW_CW( RGB_RMOD, RGB_MOD ) },
    [2] = { ENCODER_CCW_CW( _______,  _______ ), ENCODER_CCW_CW( _______,  _______ ) },
    [3] = { ENCODER_CCW_CW( _______,  _______ ), ENCODER_CCW_CW( _______,  _______ ) }
};
#endif
