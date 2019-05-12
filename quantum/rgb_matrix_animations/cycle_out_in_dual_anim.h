#ifndef DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
RGB_MATRIX_EFFECT(CYCLE_OUT_IN_DUAL)
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

bool CYCLE_OUT_IN_DUAL(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);

  HSV hsv = { 0, rgb_matrix_config.sat, rgb_matrix_config.val };
  uint8_t time = scale16by8(g_rgb_counters.tick, rgb_matrix_config.speed / 4);
  for (uint8_t i = led_min; i < led_max; i++) {
    RGB_MATRIX_TEST_LED_FLAGS();
    int16_t dx = 56 - abs8(g_led_config.point[i].x - 112);
    int16_t dy = g_led_config.point[i].y - 32;
    uint8_t dist = sqrt16(dx * dx + dy * dy);
    hsv.h = 3 * dist + time;
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
  }
  return led_max < DRIVER_LED_TOTAL;
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif // DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
