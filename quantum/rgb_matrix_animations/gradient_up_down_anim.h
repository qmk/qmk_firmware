#pragma once
#ifndef DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#include "rgb_matrix_types.h"

void rgb_matrix_gradient_up_down(const rgb_led* leds, const rgb_config_t* config) {
    int16_t h1 = config->hue;
    int16_t h2 = (config->hue + 180) % 360;
    int16_t deltaH = h2 - h1;

    // Take the shortest path between hues
    if ( deltaH > 127 )
    {
        deltaH -= 256;
    }
    else if ( deltaH < -127 )
    {
        deltaH += 256;
    }
    // Divide delta by 4, this gives the delta per row
    deltaH /= 4;

    int16_t s1 = config->sat;
    int16_t s2 = config->hue;
    int16_t deltaS = ( s2 - s1 ) / 4;

    HSV hsv = { .h = 0, .s = 255, .v = config->val };
    RGB rgb;
    Point point;
    for ( int i=0; i<DRIVER_LED_TOTAL; i++ )
    {
        // map_led_to_point( i, &point );
        point = leds[i].point;
        // The y range will be 0..64, map this to 0..4
        uint8_t y = (point.y>>4);
        // Relies on hue being 8-bit and wrapping
        hsv.h = config->hue + ( deltaH * y );
        hsv.s = config->sat + ( deltaS * y );
        rgb = hsv_to_rgb( hsv );
        rgb_matrix_set_color( i, rgb.r, rgb.g, rgb.b );
    }
}
#endif // DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
