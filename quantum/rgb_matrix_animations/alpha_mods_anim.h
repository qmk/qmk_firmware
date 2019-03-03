#pragma once
#ifndef DISABLE_RGB_MATRIX_ALPHAS_MODS

extern const rgb_led g_rgb_leds[DRIVER_LED_TOTAL];
extern rgb_config_t rgb_matrix_config;

// alphas = color1, mods = color2
void rgb_matrix_alphas_mods(void) {
  HSV hsv1 = { rgb_matrix_config.hue, rgb_matrix_config.sat, rgb_matrix_config.val };
  HSV hsv2 = { (rgb_matrix_config.hue + 180) % 360, rgb_matrix_config.sat, rgb_matrix_config.val };
  RGB rgb1 = hsv_to_rgb(hsv1);
  RGB rgb2 = hsv_to_rgb(hsv2);

  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    if (g_rgb_leds[i].matrix_co.raw < 0xFF) {
      if (g_rgb_leds[i].modifier) {
        rgb_matrix_set_color(i, rgb2.r, rgb2.g, rgb2.b);
      } else {
        rgb_matrix_set_color(i, rgb1.r, rgb1.g, rgb1.b);
      }
    }
  }
}

#endif // DISABLE_RGB_MATRIX_ALPHAS_MODS
