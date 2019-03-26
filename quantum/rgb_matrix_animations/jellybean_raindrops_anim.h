#pragma once
#ifndef DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS

extern rgb_counters_t g_rgb_counters;
extern const rgb_led g_rgb_leds[DRIVER_LED_TOTAL];
extern rgb_config_t rgb_matrix_config;

static void jellybean_raindrops_set_color(int i) {
  HSV hsv = { rand() & 0xFF , rand() & 0xFF, rgb_matrix_config.val };
  RGB rgb = hsv_to_rgb(hsv);
  rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
}

bool rgb_matrix_jellybean_raindrops(effect_params_t* params) {
  if (!params->init) {
    // Change one LED every tick, make sure speed is not 0
    if (scale16by8(g_rgb_counters.tick, qadd8(rgb_matrix_config.speed, 16)) % 5 == 0) {
      jellybean_raindrops_set_color(rand() % DRIVER_LED_TOTAL);
    }
    return false;
  }

  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  for (int i = led_min; i < led_max; i++) {
    jellybean_raindrops_set_color(i);
  }
  return led_max < DRIVER_LED_TOTAL;
}

#endif // DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
