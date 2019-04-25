#pragma once
#ifndef DISABLE_RGB_MATRIX_BREATHING

extern rgb_counters_t g_rgb_counters;
extern rgb_config_t rgb_matrix_config;

bool rgb_matrix_breathing(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);

  uint16_t time = scale16by8(g_rgb_counters.tick, rgb_matrix_config.speed / 8);
  uint8_t val = scale8(abs8(sin8(time) - 128) * 2, rgb_matrix_config.val);
  HSV hsv = { rgb_matrix_config.hue, rgb_matrix_config.sat, val };
  RGB rgb = hsv_to_rgb(hsv);
  for (uint8_t i = led_min; i < led_max; i++) {
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
  }
  return led_max < DRIVER_LED_TOTAL;
}

#endif // DISABLE_RGB_MATRIX_BREATHING
