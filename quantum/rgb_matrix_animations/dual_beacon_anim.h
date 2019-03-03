#pragma once
#ifndef DISABLE_RGB_MATRIX_DUAL_BEACON

extern rgb_counters g_rgb_counters;
extern const rgb_led g_rgb_leds[DRIVER_LED_TOTAL];
extern rgb_config_t rgb_matrix_config;

void rgb_matrix_dual_beacon() {
  HSV hsv = { rgb_matrix_config.hue, rgb_matrix_config.sat, rgb_matrix_config.val };
  double cos_value = cos(g_rgb_counters.tick * M_PI / 128) / 32 * 180;
  double sin_value = sin(g_rgb_counters.tick * M_PI / 128) / 112 * 180;
  for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
    Point point = g_rgb_leds[i].point;
    hsv.h = ((point.y - 32.0) * cos_value + (point.x - 112.0) * sin_value) + rgb_matrix_config.hue;
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
  }
}

#endif // DISABLE_RGB_MATRIX_DUAL_BEACON
