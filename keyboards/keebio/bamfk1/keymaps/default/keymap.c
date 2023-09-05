// Copyright 2021 Danny Nguyen (@nooges)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _MAIN,
    _FN1,
    _FN2,
    _FN3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MAIN] = LAYOUT(
        RGB_MOD,            // Big Switch
        TL_LOWR, KC_MUTE    // Encoder presses
    ),
    [_FN1] = LAYOUT(
        KC_B,               // Big Switch
        _______, KC_C       // Encoder presses
    ),
    [_FN2] = LAYOUT(
        _______,            // Big Switch
        _______, _______    // Encoder presses
    ),
    [_FN3] = LAYOUT(
        _______,            // Big Switch
        _______, _______    // Encoder presses
    )
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =   { ENCODER_CCW_CW(KC_DOWN, KC_UP), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [1] =   { ENCODER_CCW_CW(KC_PGDN, KC_PGUP), ENCODER_CCW_CW(_______, _______)  },
    [2] =   { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)  },
    [3] =   { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)  }
};
#endif
