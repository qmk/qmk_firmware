// Copyright 2024 ZSA Technology Labs, Inc <@zsa>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#if COMMUNITY_MODULE_ORYX_ENABLE == TRUE
#    include <oryx.h>
#endif

ASSERT_COMMUNITY_MODULES_MIN_API_VERSION(1, 1, 0);

extern const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3];

RGB keycolors_hsv_to_rgb_with_value(HSV hsv) {
    RGB   rgb = hsv_to_rgb(hsv);
    float f   = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
    return (RGB){f * rgb.r, f * rgb.g, f * rgb.b};
}

static void keycolors_set_layer_color(int layer) {
    for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        HSV hsv = {
            .h = pgm_read_byte(&ledmap[layer][i][0]),
            .s = pgm_read_byte(&ledmap[layer][i][1]),
            .v = pgm_read_byte(&ledmap[layer][i][2]),
        };
        if (!hsv.h && !hsv.s && !hsv.v) {
            rgb_matrix_set_color(i, 0, 0, 0);
        } else {
            RGB rgb = keycolors_hsv_to_rgb_with_value(hsv);
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
}

bool rgb_matrix_indicators_user(void) {
#if COMMUNITY_MODULE_ORYX_ENABLE == TRUE
    if (rawhid_state.rgb_control) {
        return false;
    }
#endif

    if (!keyboard_config.disable_layer_led) {
        switch (biton32(layer_state)) {
            case 1:
                keycolors_set_layer_color(1);
                break;
            case 2:
                keycolors_set_layer_color(2);
                break;
            default:
                if (rgb_matrix_get_flags() == LED_FLAG_NONE) {
                    rgb_matrix_set_color_all(0, 0, 0);
                }
        }
    } else {
        if (rgb_matrix_get_flags() == LED_FLAG_NONE) {
            rgb_matrix_set_color_all(0, 0, 0);
        }
    }

    return true;
}
