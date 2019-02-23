#pragma once
#ifndef DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#include "rgb_matrix_types.h"

void rgb_matrix_rainbow_moving_chevron(const rgb_counters* counters, const rgb_led* leds, const rgb_config_t* config) {
    HSV hsv = { .h = config->hue, .s = config->sat, .v = config->val };
    RGB rgb;
    Point point;
    uint8_t r = 128;
    double speed = 1.5 * (config->speed == 0 ? 1 : config->speed);
    double cos_value = speed * cos(r * M_PI / 128);
    double sin_value = speed * sin(r * M_PI / 128);
    double multiplier = (counters->tick / 256.0 * 224);
    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
        point = leds[i].point;
        hsv.h = abs(point.y - 32.0) * sin_value + (point.x - multiplier) * cos_value + config->hue;
        rgb = hsv_to_rgb( hsv );
        rgb_matrix_set_color( i, rgb.r, rgb.g, rgb.b );
    }
}

#endif // DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
