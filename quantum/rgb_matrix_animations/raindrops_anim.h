#pragma once
#ifndef DISABLE_RGB_MATRIX_RAINDROPS
#include "rgb_matrix_types.h"

extern rgb_counters g_rgb_counters;
extern rgb_config_t rgb_matrix_config;

static void set_color(int i) {
  int16_t h1 = rgb_matrix_config.hue;
  int16_t h2 = (rgb_matrix_config.hue + 180) % 360;
  int16_t deltaH = h2 - h1;
  deltaH /= 4;

  // Take the shortest path between hues
  if (deltaH > 127) {
    deltaH -= 256;
  } else if (deltaH < -127) {
    deltaH += 256;
  }

  int16_t s1 = rgb_matrix_config.sat;
  int16_t s2 = rgb_matrix_config.sat;
  int16_t deltaS = (s2 - s1) / 4;

  HSV hsv;
  hsv.h = h1 + (deltaH * (rand() & 0x03));
  hsv.s = s1 + (deltaS * (rand() & 0x03));
  // Override brightness with global brightness control
  hsv.v = rgb_matrix_config.val;

  RGB rgb = hsv_to_rgb(hsv);
  rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
}

void rgb_matrix_raindrops(bool initialize) {
  if (!initialize) {
    // Change one LED every tick, make sure speed is not 0
    uint8_t led_to_change = ((g_rgb_counters.tick) & (0x0A / (rgb_matrix_config.speed == 0 ? 1 : rgb_matrix_config.speed))) == 0 ? rand() % (DRIVER_LED_TOTAL) : 255;
    set_color(led_to_change);
  } else {
    for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
      set_color(i);
    }
  }
}

#endif // DISABLE_RGB_MATRIX_RAINDROPS
