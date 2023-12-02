//rgb_matrix_mode(RGB_MATRIX_CUSTOM_my_off_effect);

RGB_MATRIX_EFFECT(my_off_effect)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// A simple effect for LEDs to start off, without affecting the global hsv brightness
static bool my_off_effect(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  for (uint8_t i = led_min; i < led_max; i++) {
    rgb_matrix_set_color(i, 0x00, 0x00, 0x00);
  }
  return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
