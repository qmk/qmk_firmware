#ifndef DISABLE_RGB_MATRIX_BREATHING
RGB_MATRIX_EFFECT(BREATHING)
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

bool BREATHING(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);

  uint16_t time = scale16by8(g_rgb_counters.tick, rgb_matrix_config.speed / 8);
  uint8_t val = scale8(abs8(sin8(time) - 128) * 2, rgb_matrix_config.val);
  HSV hsv = { rgb_matrix_config.hue, rgb_matrix_config.sat, val };
  RGB rgb = hsv_to_rgb(hsv);
  for (uint8_t i = led_min; i < led_max; i++) {
    RGB_MATRIX_TEST_LED_FLAGS();
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
  }
  return led_max < DRIVER_LED_TOTAL;
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif // DISABLE_RGB_MATRIX_BREATHING
