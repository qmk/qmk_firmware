#pragma once
#ifdef RGB_MATRIX_KEYPRESSES
#ifndef DISABLE_RGB_MATRIX_SOLID_REACTIVE

extern rgb_counters g_rgb_counters;
extern rgb_config_t rgb_matrix_config;

void rgb_matrix_solid_reactive(void) {
  HSV hsv = { rgb_matrix_config.hue, 255, rgb_matrix_config.val };
  // Relies on hue being 8-bit and wrapping
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    uint16_t offset2 = g_rgb_counters.key_hit[i] << 2;
    offset2 = (offset2 <= 130) ? (130 - offset2) : 0;

    hsv.h = rgb_matrix_config.hue + offset2;
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
  }
}

#endif // DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#endif // RGB_MATRIX_KEYPRESSES
