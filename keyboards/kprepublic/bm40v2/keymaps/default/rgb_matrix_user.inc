// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)
RGB_MATRIX_EFFECT(qwerty)
RGB_MATRIX_EFFECT(lower)
RGB_MATRIX_EFFECT(raise)
RGB_MATRIX_EFFECT(adjust)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool qwerty(effect_params_t* params) {
//   RGB_MATRIX_USE_LIMITS(led_min, led_max);
//   for (uint8_t i = led_min; i < led_max; i++) {
//     rgb_matrix_set_color(i, 0, 255, 255);
//   }
    rgb_matrix_set_color(0, 255, 0, 0);
    rgb_matrix_set_color(35, 0, 255, 0);
  //return rgb_matrix_check_finished_leds(led_max);
  return 1;
}

static bool lower(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  for (uint8_t i = led_min; i < led_max; i++) {
    rgb_matrix_set_color(i, 255, 0, 255);
  }
  return rgb_matrix_check_finished_leds(led_max);
}

static bool raise(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  for (uint8_t i = led_min; i < led_max; i++) {
    rgb_matrix_set_color(i, 255, 255, 0);
  }
  return rgb_matrix_check_finished_leds(led_max);
}

static bool adjust(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  for (uint8_t i = led_min; i < led_max; i++) {
    rgb_matrix_set_color(i, 255, 0, 0);
  }
  return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
