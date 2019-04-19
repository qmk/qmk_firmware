#pragma once
#if defined(RGB_MATRIX_KEYREACTIVE_ENABLED)
#ifndef DISABLE_RGB_MATRIX_SOLID_REACTIVE

extern rgb_config_t rgb_matrix_config;
extern last_hit_t g_last_hit_tracker;

bool rgb_matrix_solid_reactive(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);

  HSV hsv = { rgb_matrix_config.hue, 255, rgb_matrix_config.val };
  // Max tick based on speed scale ensures results from scale16by8 with rgb_matrix_config.speed are no greater than 255
  uint16_t max_tick = 65535 / rgb_matrix_config.speed;
  // Relies on hue being 8-bit and wrapping
  for (uint8_t i = led_min; i < led_max; i++) {
    uint16_t tick = max_tick;
    for(uint8_t j = 0; j < g_last_hit_tracker.count; j++) {
      if (g_last_hit_tracker.index[j] == i && g_last_hit_tracker.tick[j] < tick) {
        tick = g_last_hit_tracker.tick[j];
        break;
      }
    }

    uint16_t  offset = scale16by8(tick, rgb_matrix_config.speed);
    hsv.h = rgb_matrix_config.hue + qsub8(130, offset);
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
  }
  return led_max < DRIVER_LED_TOTAL;
}

#endif // DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#endif // defined(RGB_MATRIX_KEYREACTIVE_ENABLED)
