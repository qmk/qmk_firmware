// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// ===== LED/RGB INDICATOR =====
enum RGB_LAYERS {
    RGBL_CAPS = 0
};

const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_BLUE}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
   [RGBL_CAPS] =  my_capslock_layer
);

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(RGBL_CAPS, led_state.caps_lock);
    return true;
}

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}
