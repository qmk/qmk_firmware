#pragma once

extern rgb_config_t rgb_matrix_config;

void rgb_matrix_solid_color(void) {
  HSV hsv = { rgb_matrix_config.hue, rgb_matrix_config.sat, rgb_matrix_config.val };
  RGB rgb = hsv_to_rgb(hsv);
  rgb_matrix_set_color_all(rgb.r, rgb.g, rgb.b);
}
