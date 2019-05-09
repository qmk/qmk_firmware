#pragma once
#ifndef DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON

extern rgb_counters_t g_rgb_counters;
extern led_config_t g_led_config;
extern rgb_config_t rgb_matrix_config;

bool rgb_matrix_rainbow_moving_chevron(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);

  HSV hsv = { 0, rgb_matrix_config.sat, rgb_matrix_config.val };
  uint8_t time = scale16by8(g_rgb_counters.tick, rgb_matrix_config.speed / 4);
  for (uint8_t i = led_min; i < led_max; i++) {
    RGB_MATRIX_TEST_LED_FLAGS();
    hsv.h = abs8(g_led_config.point[i].y - 32) + (g_led_config.point[i].x - time) + rgb_matrix_config.hue;
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
  }
  return led_max < DRIVER_LED_TOTAL;
}

#endif // DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
