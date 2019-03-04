#pragma once
#ifndef DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS

extern rgb_counters g_rgb_counters;
extern const rgb_led g_rgb_leds[DRIVER_LED_TOTAL];
extern rgb_config_t rgb_matrix_config;

void rgb_matrix_rainbow_pinwheels(void) {
  HSV hsv = { rgb_matrix_config.hue, rgb_matrix_config.sat, rgb_matrix_config.val };
  double speed = 2 * (rgb_matrix_config.speed == 0 ? 1 : rgb_matrix_config.speed);
  double cos_value = speed * cos(g_rgb_counters.tick * M_PI / 128);
  double sin_value = speed * sin(g_rgb_counters.tick * M_PI / 128);
  for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
    Point point = g_rgb_leds[i].point;
    hsv.h = (point.y - 32.0)* cos_value + (66 - abs(point.x - 112.0)) * sin_value + rgb_matrix_config.hue;
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
  }
}

#endif // DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS
