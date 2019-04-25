#pragma once
#ifndef DISABLE_RGB_MATRIX_ALPHAS_MODS

extern const rgb_led g_rgb_leds[DRIVER_LED_TOTAL];
extern rgb_config_t rgb_matrix_config;

// alphas = color1, mods = color2
bool rgb_matrix_alphas_mods(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);

  HSV hsv = { rgb_matrix_config.hue, rgb_matrix_config.sat, rgb_matrix_config.val };
  RGB rgb1 = hsv_to_rgb(hsv);
  hsv.h += rgb_matrix_config.speed;
  RGB rgb2 = hsv_to_rgb(hsv);

  for (uint8_t i = led_min; i < led_max; i++) {
    if (g_rgb_leds[i].modifier) {
      rgb_matrix_set_color(i, rgb2.r, rgb2.g, rgb2.b);
    } else {
      rgb_matrix_set_color(i, rgb1.r, rgb1.g, rgb1.b);
    }
  }
  return led_max < DRIVER_LED_TOTAL;
}

#endif // DISABLE_RGB_MATRIX_ALPHAS_MODS
