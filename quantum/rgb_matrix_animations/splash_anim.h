#pragma once
#ifdef RGB_MATRIX_KEYPRESSES
#include "rgb_matrix_types.h"
#if defined(DISABLE_RGB_MATRIX_SPLASH) || defined(DISABLE_RGB_MATRIX_MULTISPLASH)

#ifndef MAX
    #define MAX(X, Y) ((X) > (Y) ? (X) : (Y))
#endif

#ifndef MIN
    #define MIN(X, Y) ((X) < (Y) ? (X) : (Y))
#endif

void rgb_matrix_multisplash(const rgb_counters* counters, const rgb_led* leds, const rgb_config_t* config) {
    // if (g_rgb_counters.any_key_hit < 0xFF) {
        HSV hsv = { .h = rgb_matrix_config.hue, .s = rgb_matrix_config.sat, .v = rgb_matrix_config.val };
        RGB rgb;
        Point point;
        Point last_point;
        for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
            point = leds[i].point;
            uint16_t c = 0, d = 0;
            // if (g_rgb_counters.last_led_count) {
                for (uint8_t last_i = 0; last_i < g_rgb_counters.last_led_count; last_i++) {
                    last_point = leds[g_rgb_counters.last_led_hit[last_i]].point;
                    uint16_t dist = (uint16_t)sqrt(pow(point.x - last_point.x, 2) + pow(point.y - last_point.y, 2));
                    uint16_t effect = (g_rgb_counters.key_hit[g_rgb_counters.last_led_hit[last_i]] << 2) - dist;
                    c += MIN(MAX(effect, 0), 255);
                    d += 255 - MIN(MAX(effect, 0), 255);
                }
            // } else {
            //     d = 255;
            // }
            hsv.h = (rgb_matrix_config.hue + c) % 256;
            hsv.v = MAX(MIN(d, 255), 0);
            rgb = hsv_to_rgb( hsv );
            rgb_matrix_set_color( i, rgb.r, rgb.g, rgb.b );
        }
    // } else {
        // rgb_matrix_set_color_all( 0, 0, 0 );
    // }
}

void rgb_matrix_splash(rgb_counters* counters, const rgb_led* leds, const rgb_config_t* config) {
    g_rgb_counters.last_led_count = MIN(g_rgb_counters.last_led_count, 1);
    rgb_matrix_multisplash(counters, leds, config);
}

#endif // !defined(DISABLE_RGB_MATRIX_SPLASH) && !defined(DISABLE_RGB_MATRIX_MULTISPLASH)
#endif // RGB_MATRIX_KEYPRESSES
