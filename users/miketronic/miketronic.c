// Copyright 2023 @miketronic -- Mike B <mxb540@gmail.com>
// SPDX-License-Identifier: GPL-2.0+

#include "miketronic.h"


// Init effect for RGB boards only
// https://github.com/qmk/qmk_firmware/blob/master/docs/custom_quantum_functions.md
void keyboard_post_init_user(void) {
#ifdef RGB_MATRIX_ENABLE
    rgblight_enable_noeeprom(); // enables Rgb, without saving settings
    rgblight_sethsv_noeeprom(180, 255, 255); // sets the color to teal/cyan without saving
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
#endif
    keyboard_post_init_keymap();
}


__attribute__ ((weak)) layer_state_t layer_state_set_keymap (layer_state_t state) {
    return state;
}
layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _SYMB);
    state = layer_state_set_keymap(state);
#ifdef CONSOLE_ENABLE
    uprintf("LAYER: %u\n", state);
#endif
    return state;
}