#pragma once
#ifndef DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON

extern rgb_counters g_rgb_counters;
extern const rgb_led g_rgb_leds[DRIVER_LED_TOTAL];
extern rgb_config_t rgb_matrix_config;

void rgb_matrix_rainbow_moving_chevron(void) {
  HSV hsv = { rgb_matrix_config.hue, rgb_matrix_config.sat, rgb_matrix_config.val };
  double speed = 1.5 * (rgb_matrix_config.speed == 0 ? 1 : rgb_matrix_config.speed);
  double cos_value = speed * cos(128 * M_PI / 128);
  double sin_value = speed * sin(128 * M_PI / 128);
  double multiplier = (g_rgb_counters.tick / 256.0 * 224);
  for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
    Point point = g_rgb_leds[i].point;
    hsv.h = abs(point.y - 32.0) * sin_value + (point.x - multiplier) * cos_value + rgb_matrix_config.hue;
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
  }
}

#endif // DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
