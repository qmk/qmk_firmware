// !!! DO NOT ADD #pragma once !!! //

// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)

RGB_MATRIX_EFFECT(turn_off_rgb)
RGB_MATRIX_EFFECT(kb_reset_rgb)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// e.g: A simple effect, self-contained within a single method
static bool turn_off_rgb(effect_params_t *params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  for (uint8_t i = led_min; i < led_max; i++) {
    rgb_matrix_set_color(i, 0x00, 0x00, 0x00);
  }
  return rgb_matrix_check_finished_leds(led_max);
}

// e.g: A more complex effect, relying on external methods and state, with
// dedicated init and run methods
static uint8_t some_global_state;
static void kb_reset_rgb_init(effect_params_t* params) {
  some_global_state = 0;
}
static bool kb_reset_rgb_run(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  some_global_state++;
  if(some_global_state&0x01){
      for (uint8_t i = led_min; i < led_max; i++)
        rgb_matrix_set_color(i, 0, 0, 0);
  }
  else{
      for (uint8_t i = led_min; i < led_max; i++) 
        rgb_matrix_set_color(i, 0xc0, 0xc0, 0xc0);
  }
  if(some_global_state>=7)
    rgb_matrix_init();
  return rgb_matrix_check_finished_leds(led_max);
}

static bool kb_reset_rgb(effect_params_t* params) {
  if (params->init) kb_reset_rgb_init(params);
  return kb_reset_rgb_run(params);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
