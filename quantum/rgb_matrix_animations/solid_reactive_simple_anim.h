#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED
#ifndef DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
RGB_MATRIX_EFFECT(SOLID_REACTIVE_SIMPLE)
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

bool SOLID_REACTIVE_SIMPLE(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);

  HSV hsv = { rgb_matrix_config.hue, rgb_matrix_config.sat, 0 };
  // Max tick based on speed scale ensures results from scale16by8 with rgb_matrix_config.speed are no greater than 255
  uint16_t max_tick = 65535 / rgb_matrix_config.speed;
  for (uint8_t i = led_min; i < led_max; i++) {
    RGB_MATRIX_TEST_LED_FLAGS();
    uint16_t tick = max_tick;
    // Reverse search to find most recent key hit
    for (int8_t j = g_last_hit_tracker.count - 1; j >= 0; j--) {
      if (g_last_hit_tracker.index[j] == i && g_last_hit_tracker.tick[j] < tick) {
        tick = g_last_hit_tracker.tick[j];
        break;
      }
    }

    uint16_t  offset = scale16by8(tick, rgb_matrix_config.speed);
    hsv.v = scale8(255 - offset, rgb_matrix_config.val);
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
  }
  return led_max < DRIVER_LED_TOTAL;
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif // DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#endif // RGB_MATRIX_KEYREACTIVE_ENABLED
