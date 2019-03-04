#pragma once
#ifndef DISABLE_RGB_MATRIX_CYCLE_ALL

extern rgb_counters g_rgb_counters;
extern const rgb_led g_rgb_leds[DRIVER_LED_TOTAL];
extern rgb_config_t rgb_matrix_config;

void rgb_matrix_cycle_all(void) {
  uint8_t offset = (g_rgb_counters.tick << rgb_matrix_config.speed) & 0xFF;
  // Relies on hue being 8-bit and wrapping
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    // map_index_to_led(i, &led);
    rgb_led led = g_rgb_leds[i];
    if (led.matrix_co.raw < 0xFF) {
      uint16_t offset2 = g_rgb_counters.key_hit[i] << 2;
      offset2 = (offset2 <= 63) ? (63 - offset2) : 0;

      HSV hsv = { offset + offset2, 255, rgb_matrix_config.val };
      RGB rgb = hsv_to_rgb(hsv);
      rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
  }
}

#endif // DISABLE_RGB_MATRIX_CYCLE_ALL
