#pragma once
#ifndef DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS

extern rgb_counters g_rgb_counters;
extern const rgb_led g_rgb_leds[DRIVER_LED_TOTAL];
extern rgb_config_t rgb_matrix_config;

void rgb_matrix_jellybean_raindrops(bool initialize) {
  // Change one LED every tick, make sure speed is not 0
  uint8_t led_to_change = (g_rgb_counters.tick & (0x0A / (rgb_matrix_config.speed == 0 ? 1 : rgb_matrix_config.speed))) == 0 ? rand() % (DRIVER_LED_TOTAL) : 255;

  for (int i = 0; i < DRIVER_LED_TOTAL; i++)
  {
    // If initialize, all get set to random colors
    // If not, all but one will stay the same as before.
    if (initialize || i == led_to_change)
    {
      HSV hsv = { rand() & 0xFF , rand() & 0xFF, rgb_matrix_config.val };
      RGB rgb = hsv_to_rgb(hsv);
      rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
  }
}

#endif // DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
