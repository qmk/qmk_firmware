#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED
#if !defined(DISABLE_RGB_MATRIX_SPLASH) || !defined(DISABLE_RGB_MATRIX_MULTISPLASH)

#ifndef DISABLE_RGB_MATRIX_SPLASH
RGB_MATRIX_EFFECT(SPLASH)
#endif

#ifndef DISABLE_RGB_MATRIX_MULTISPLASH
RGB_MATRIX_EFFECT(MULTISPLASH)
#endif

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS


static bool rgb_matrix_multisplash_range(uint8_t start, effect_params_t* params) {
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
      uint16_t effect = scale16by8(g_last_hit_tracker.tick[j], rgb_matrix_config.speed) - dist;
      if (effect > 255)
        effect = 255;
      hsv.h += effect;
      hsv.v = qadd8(hsv.v, 255 - effect);
    }
    hsv.v = scale8(hsv.v, rgb_matrix_config.val);
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
  }
  return led_max < DRIVER_LED_TOTAL;
}

bool MULTISPLASH(effect_params_t* params) {
  return rgb_matrix_multisplash_range(0, params);
}

bool SPLASH(effect_params_t* params) {
  return rgb_matrix_multisplash_range(qsub8(g_last_hit_tracker.count, 1), params);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif // !defined(DISABLE_RGB_MATRIX_SPLASH) || !defined(DISABLE_RGB_MATRIX_MULTISPLASH)
#endif // RGB_MATRIX_KEYREACTIVE_ENABLED
