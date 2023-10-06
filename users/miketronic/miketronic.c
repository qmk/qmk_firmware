// Copyright 2023 @miketronic -- Mike B <mxb540@gmail.com>
// SPDX-License-Identifier: GPL-2.0+

#include "miketronic.h"


__attribute__ ((weak)) void keyboard_post_init_keymap(void) { }

// Init effect for RGB boards only
void keyboard_post_init_user(void) {
#ifdef RGB_MATRIX_ENABLE
    rgblight_enable_noeeprom(); // enables Rgb, without saving settings
    rgblight_sethsv_noeeprom(HSV_ORANGE); // sets the color without saving
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
#endif
    keyboard_post_init_keymap();
}