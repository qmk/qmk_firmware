// Copyright 2023 @miketronic -- Mike B <mxb540@gmail.com>
// SPDX-License-Identifier: GPL-2.0+

#include "miketronic.h"

// Add reconfigurable functions here, for keymap customization
// This allows for a global, userspace functions, and continued
// customization of the keymap.  Use _keymap instead of _user
// functions in the keymaps


// In keymaps, instead of writing _user functions, write _keymap functions
// The __attribute__((weak)) allows for empty definitions here, and during
// compilation, if these functions are defined elsewhere, they are written
// over. This allows to include custom code from keymaps in the generic code
// in this file.




__attribute__ ((weak)) void matrix_init_keymap(void) { }
__attribute__ ((weak)) void matrix_scan_keymap(void) { }
__attribute__ ((weak)) void led_set_keymap(uint8_t usb_led) { }

__attribute__ ((weak)) layer_state_t layer_state_set_keymap (layer_state_t state) {
    return state;
}
// Init effect for RGB boards only
void matrix_init_user(void) {
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
#endif
    matrix_init_keymap();
}


/*

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
#ifdef CONSOLE_ENABLE
    uprintf("LAYER: %u\n", state);
#endif
    return state;
}
 */
