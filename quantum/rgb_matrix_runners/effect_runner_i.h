#pragma once

typedef void (*i_f)(HSV* hsv, uint8_t i, uint8_t time);

bool effect_runner_i(effect_params_t* params, rgb_config_t* config, i_f effect_func) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);

  HSV hsv = { config->hue, config->sat, config->val };
  uint8_t time = scale16by8(g_rgb_counters.tick, config->speed / 4);
  for (uint8_t i = led_min; i < led_max; i++) {
    RGB_MATRIX_TEST_LED_FLAGS();
    effect_func(&hsv, i, time);
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
  }
  return led_max < DRIVER_LED_TOTAL;
}
