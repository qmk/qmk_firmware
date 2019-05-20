#pragma once

#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED

typedef void (*reactive_splash_f)(HSV* hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick);

bool effect_runner_reactive_splash(uint8_t start, effect_params_t* params, reactive_splash_f effect_func) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);

  HSV hsv = { 0, rgb_matrix_config.sat, 0 };
  uint8_t count = g_last_hit_tracker.count;
  for (uint8_t i = led_min; i < led_max; i++) {
    RGB_MATRIX_TEST_LED_FLAGS();
    hsv.h = rgb_matrix_config.hue;
    hsv.v = 0;
    for (uint8_t j = start; j < count; j++) {
      int16_t dx = g_led_config.point[i].x - g_last_hit_tracker.x[j];
      int16_t dy = g_led_config.point[i].y - g_last_hit_tracker.y[j];
      uint8_t dist = sqrt16(dx * dx + dy * dy);
      uint16_t tick = scale16by8(g_last_hit_tracker.tick[j], rgb_matrix_config.speed);
      effect_func(&hsv, dx, dy, dist, tick);
    }
    hsv.v = scale8(hsv.v, rgb_matrix_config.val);
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
  }
  return led_max < DRIVER_LED_TOTAL;
}

#endif // RGB_MATRIX_KEYREACTIVE_ENABLED
