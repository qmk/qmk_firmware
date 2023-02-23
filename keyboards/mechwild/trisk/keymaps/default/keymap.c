// Copyright 2022 Kyle McCreery (@kylemccreery)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layer_names {
    _BASE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_MUTE, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, RGB_RMOD, RGB_MOD, RGB_TOG
    )
};

void keyboard_post_init_user(void) {
 HSV hsv = {0, 255, 255};
 RGB rgb = hsv_to_rgb(hsv);
 for (uint8_t i = 13; i <= 17; i++) {
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][2][2] = {
    [_BASE] =  { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),  ENCODER_CCW_CW(KC_VOLD, KC_VOLU)      }
};
#endif
