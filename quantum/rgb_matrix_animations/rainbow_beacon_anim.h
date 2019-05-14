#ifndef DISABLE_RGB_MATRIX_RAINBOW_BEACON
RGB_MATRIX_EFFECT(RAINBOW_BEACON)
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

bool RAINBOW_BEACON(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);

  HSV hsv = { 0, rgb_matrix_config.sat, rgb_matrix_config.val };
  uint16_t time = scale16by8(g_rgb_counters.tick, rgb_matrix_config.speed / 4);
  int16_t cos_value = 2 * (cos8(time) - 128);
  int16_t sin_value = 2 * (sin8(time) - 128);
  for (uint8_t i = led_min; i < led_max; i++) {
    RGB_MATRIX_TEST_LED_FLAGS();
    hsv.h = ((g_led_config.point[i].y - 32) * cos_value + (g_led_config.point[i].x - 112) * sin_value) / 128 + rgb_matrix_config.hue;
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
  }
  return led_max < DRIVER_LED_TOTAL;
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif // DISABLE_RGB_MATRIX_RAINBOW_BEACON
