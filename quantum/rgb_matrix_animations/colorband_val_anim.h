#ifndef DISABLE_RGB_MATRIX_BAND_VAL
RGB_MATRIX_EFFECT(BAND_VAL)
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

bool BAND_VAL(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);

  HSV hsv = { rgb_matrix_config.hue, rgb_matrix_config.sat, 0 };
  uint8_t time = scale16by8(g_rgb_counters.tick, rgb_matrix_config.speed / 4);
  for (uint8_t i = led_min; i < led_max; i++) {
    RGB_MATRIX_TEST_LED_FLAGS();
    int16_t v = rgb_matrix_config.val - abs(scale8(g_led_config.point[i].x, 228) + 28 - time) * 8;
    hsv.v = v < 0 ? 0 : v;
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
  }
  return led_max < DRIVER_LED_TOTAL;
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif // DISABLE_RGB_MATRIX_BAND_VAL
