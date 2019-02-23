#pragma once
#ifndef DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#include "rgb_matrix_types.h"

void rgb_matrix_cycle_left_right(const rgb_counters* counters, const rgb_led* leds, const rgb_config_t* config) {
    uint8_t offset = ( counters->tick << config->speed ) & 0xFF;
    HSV hsv = { .h = 0, .s = 255, .v = config->val };
    RGB rgb;
    Point point;
    rgb_led led;
    for ( int i=0; i<DRIVER_LED_TOTAL; i++ )
    {
        // map_index_to_led(i, &led);
        led = leds[i];
        if (led.matrix_co.raw < 0xFF) {
            uint16_t offset2 = counters->key_hit[i]<<2;
            offset2 = (offset2<=63) ? (63-offset2) : 0;

            // map_led_to_point( i, &point );
            point = leds[i].point;
            // Relies on hue being 8-bit and wrapping
            hsv.h = point.x + offset + offset2;
            rgb = hsv_to_rgb( hsv );
            rgb_matrix_set_color( i, rgb.r, rgb.g, rgb.b );
        }
    }
}

#endif
