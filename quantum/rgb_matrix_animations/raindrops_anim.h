#pragma once
#ifndef DISABLE_RGB_MATRIX_RAINDROPS
#include "rgb_matrix_types.h"

extern rgb_counters_t g_rgb_counters;
extern rgb_config_t rgb_matrix_config;

static void raindrops_set_color(int i) {
  HSV hsv = { 0 , rgb_matrix_config.sat, rgb_matrix_config.val };

  // Take the shortest path between hues
  int16_t deltaH = ((rgb_matrix_config.hue + 180) % 360 - rgb_matrix_config.hue) / 4;
  if (deltaH > 127) {
    deltaH -= 256;
  } else if (deltaH < -127) {
    deltaH += 256;
  }

  hsv.h = rgb_matrix_config.hue + (deltaH * (rand() & 0x03));
  RGB rgb = hsv_to_rgb(hsv);
  rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
}

bool rgb_matrix_raindrops(effect_params_t* params) {
  if (!params->init) {
    // Change one LED every tick, make sure speed is not 0
    if (scale16by8(g_rgb_counters.tick, qadd8(rgb_matrix_config.speed, 16)) % 10 == 0) {
      raindrops_set_color(rand() % DRIVER_LED_TOTAL);
    }
    return false;
  }

  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  for (int i = led_min; i < led_max; i++) {
    raindrops_set_color(i);
  }
  return led_max < DRIVER_LED_TOTAL;
}

#endif // DISABLE_RGB_MATRIX_RAINDROPS
