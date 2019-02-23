#pragma once
#ifndef DISABLE_RGB_MATRIX_ALPHAS_MODS
#include "rgb_matrix_types.h"

// alphas = color1, mods = color2
void rgb_matrix_alphas_mods(const rgb_led* leds, const rgb_config_t* config) {
    RGB rgb1 = hsv_to_rgb( (HSV){ .h = config->hue, .s = config->sat, .v = config->val } );
    RGB rgb2 = hsv_to_rgb( (HSV){ .h = (config->hue + 180) % 360, .s = config->sat, .v = config->val } );

    for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
        if ( leds[i].matrix_co.raw < 0xFF ) {
            if ( leds[i].modifier ) {
                rgb_matrix_set_color( i, rgb2.r, rgb2.g, rgb2.b );
            } else {
                rgb_matrix_set_color( i, rgb1.r, rgb1.g, rgb1.b );
            }
        }
    }
}

#endif // DISABLE_RGB_MATRIX_ALPHAS_MODS
