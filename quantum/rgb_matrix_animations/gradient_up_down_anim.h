#pragma once
#ifndef DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN

extern const rgb_led g_rgb_leds[DRIVER_LED_TOTAL];
extern rgb_config_t rgb_matrix_config;

void rgb_matrix_gradient_up_down() {
  int16_t h1 = rgb_matrix_config.hue;
  int16_t h2 = (rgb_matrix_config.hue + 180) % 360;
  int16_t deltaH = h2 - h1;

  // Take the shortest path between hues
  if (deltaH > 127) {
    deltaH -= 256;
  } else if (deltaH < -127) {
    deltaH += 256;
  }
  // Divide delta by 4, this gives the delta per row
  deltaH /= 4;

  int16_t s1 = rgb_matrix_config.sat;
  int16_t s2 = rgb_matrix_config.hue;
  int16_t deltaS = (s2 - s1) / 4;

  HSV hsv = { 0, 255, rgb_matrix_config.val };
  RGB rgb;
  Point point;
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    // map_led_to_point( i, &point );
    point = g_rgb_leds[i].point;
    // The y range will be 0..64, map this to 0..4
    uint8_t y = (point.y >> 4);
    // Relies on hue being 8-bit and wrapping
    hsv.h = rgb_matrix_config.hue + (deltaH * y);
    hsv.s = rgb_matrix_config.sat + (deltaS * y);
    rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
  }
}
#endif // DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
