#ifndef DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
RGB_MATRIX_EFFECT(GRADIENT_UP_DOWN)
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

bool GRADIENT_UP_DOWN(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);

  HSV hsv = { 0, rgb_matrix_config.sat, rgb_matrix_config.val };
  uint8_t scale = scale8(64, rgb_matrix_config.speed);
  for (uint8_t i = led_min; i < led_max; i++) {
    RGB_MATRIX_TEST_LED_FLAGS();
    // The y range will be 0..64, map this to 0..4
    // Relies on hue being 8-bit and wrapping
    hsv.h = rgb_matrix_config.hue + scale * (g_led_config.point[i].y >> 4);
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
  }
  return led_max < DRIVER_LED_TOTAL;
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif // DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
