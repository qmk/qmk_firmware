#pragma once
#ifdef RGB_MATRIX_KEYPRESSES
#ifndef DISABLE_RGB_MATRIX_SOLID_REACTIVE
#include "rgb_matrix_types.h"

void rgb_matrix_solid_reactive(const rgb_counters* counters, const rgb_config_t* config) {
  HSV hsv = { .h = config->hue, .s = 255, .v = config->val };
  RGB rgb;
	// Relies on hue being 8-bit and wrapping
	for ( int i=0; i<DRIVER_LED_TOTAL; i++ )
	{
		uint16_t offset2 = counters->key_hit[i]<<2;
		offset2 = (offset2<=130) ? (130-offset2) : 0;

		hsv.h = config->hue + offset2;
		rgb = hsv_to_rgb( hsv );
		rgb_matrix_set_color( i, rgb.r, rgb.g, rgb.b );
	}
}

#endif // DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#endif // RGB_MATRIX_KEYPRESSES
