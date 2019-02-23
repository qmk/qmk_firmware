#pragma once
#ifndef DISABLE_RGB_MATRIX_RAINBOW_BEACON
#include "rgb_matrix_types.h"

void rgb_matrix_rainbow_beacon(const rgb_counters* counters, const rgb_led* leds, const rgb_config_t* config) {
    HSV hsv = { .h = config->hue, .s = config->sat, .v = config->val };
    RGB rgb;
    Point point;
    double speed = 1.5 * (config->speed == 0 ? 1 : config->speed);
    double cos_value = speed * cos(counters->tick * M_PI / 128);
    double sin_value = speed * sin(counters->tick * M_PI / 128);
    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
        point = leds[i].point;
        hsv.h = (point.y - 32.0) * cos_value + (point.x - 112.0) * sin_value + config->hue;
        rgb = hsv_to_rgb( hsv );
        rgb_matrix_set_color( i, rgb.r, rgb.g, rgb.b );
    }
}

#endif // DISABLE_RGB_MATRIX_RAINBOW_BEACON
