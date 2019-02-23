#pragma once
#ifndef DISABLE_RGB_MATRIX_DUAL_BEACON
#include "rgb_matrix_types.h"

void rgb_matrix_dual_beacon(const rgb_counters* counters, const rgb_led* leds, const rgb_config_t* config) {
    HSV hsv = { .h = config->hue, .s = config->sat, .v = config->val };
    RGB rgb;
    Point point;
    double cos_value = cos(counters->tick * M_PI / 128) / 32;
    double sin_value =  sin(counters->tick * M_PI / 128) / 112;
    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
        point = leds[i].point;
        hsv.h = ((point.y - 32.0)* cos_value + (point.x - 112.0) * sin_value) * (180) + config->hue;
        rgb = hsv_to_rgb( hsv );
        rgb_matrix_set_color( i, rgb.r, rgb.g, rgb.b );
    }
}

#endif // DISABLE_RGB_MATRIX_DUAL_BEACON
