// Copyright 2023 Allen Choi (@thunderbird2086)
// SPDX-License-Identifier: GPL-2.0-or-later

#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
#   include QMK_KEYBOARD_H

#   include "keycodes.h"

#   ifdef RGBLIGHT_ENABLE

const rgblight_segment_t PROGMEM _rgb_layer_0[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 56, HSV_BLUE}
);
const rgblight_segment_t PROGMEM _rgb_layer_1[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 56, HSV_GREEN}
);
const rgblight_segment_t PROGMEM _rgb_layer_2[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 56, HSV_YELLOW}
);

const rgblight_segment_t* const PROGMEM _rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    _rgb_layer_0,
    _rgb_layer_1,
    _rgb_layer_2
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = _rgb_layers;
}

void set_rgb_by_layer(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _CODE));
    rgblight_set_layer_state(1, layer_state_cmp(state, _FUNCTION));
    rgblight_set_layer_state(2, layer_state_cmp(state, _ADJUST));
}

#   else

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    for (uint8_t i = led_min; i < led_max; i++) {
        switch(get_highest_layer(layer_state|default_layer_state)) {
            case _CODE:
                rgb_matrix_set_color(i, RGB_BLUE);
                break;
            case _FUNCTION:
                rgb_matrix_set_color(i, RGB_GREEN);
                break;
            case _ADJUST:
                rgb_matrix_set_color(i, RGB_YELLOW);
                    //  RGB_WHITE caused crash
                break;
            default:
                break;
        }
    }
    return false;
}

#   endif
#endif
