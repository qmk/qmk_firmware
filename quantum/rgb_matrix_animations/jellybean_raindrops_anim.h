#pragma once
#ifndef DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#include "rgb_matrix_types.h"

void rgb_matrix_jellybean_raindrops(bool initialize, const rgb_counters* counters, const rgb_config_t* config) {
    HSV hsv;
    RGB rgb;

    // Change one LED every tick, make sure speed is not 0
    uint8_t led_to_change = ( counters->tick & ( 0x0A / (config->speed == 0 ? 1 : config->speed) ) ) == 0 ? rand() % (DRIVER_LED_TOTAL) : 255;

    for ( int i=0; i<DRIVER_LED_TOTAL; i++ )
    {
        // If initialize, all get set to random colors
        // If not, all but one will stay the same as before.
        if ( initialize || i == led_to_change )
        {
            hsv.h = rand() & 0xFF;
            hsv.s = rand() & 0xFF;
            // Override brightness with global brightness control
            hsv.v = config->val;

            rgb = hsv_to_rgb( hsv );
            rgb_matrix_set_color( i, rgb.r, rgb.g, rgb.b );
        }
    }
}

#endif // DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
