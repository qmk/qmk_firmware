#pragma once
#include "rgb_matrix_types.h"

void rgb_matrix_solid_color(const rgb_config_t* config) {
    HSV hsv = { .h = config->hue, .s = config->sat, .v = config->val };
    RGB rgb = hsv_to_rgb( hsv );
    rgb_matrix_set_color_all( rgb.r, rgb.g, rgb.b );
}
