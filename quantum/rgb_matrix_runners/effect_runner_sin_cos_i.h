#pragma once

typedef HSV (*sin_cos_i_f)(HSV hsv, int8_t sin, int8_t cos, uint8_t i, uint8_t time);

bool effect_runner_sin_cos_i(effect_params_t* params, sin_cos_i_f effect_func) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);

  uint16_t time = scale16by8(g_rgb_counters.tick, rgb_matrix_config.speed / 4);
  int8_t cos_value = cos8(time) - 128;
  int8_t sin_value = sin8(time) - 128;
  for (uint8_t i = led_min; i < led_max; i++) {
    RGB_MATRIX_TEST_LED_FLAGS();
    RGB rgb = hsv_to_rgb(effect_func(rgb_matrix_config.hsv, cos_value, sin_value, i, time));
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
  }
  return led_max < DRIVER_LED_TOTAL;
}
