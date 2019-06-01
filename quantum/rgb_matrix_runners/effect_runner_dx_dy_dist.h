#pragma once

typedef void (*dx_dy_dist_f)(HSV* hsv, int16_t dx, int16_t dy, uint8_t dist, uint8_t time);

bool effect_runner_dx_dy_dist(effect_params_t* params, dx_dy_dist_f effect_func) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);

  HSV hsv = { rgb_matrix_config.hue, rgb_matrix_config.sat, rgb_matrix_config.val };
  uint8_t time = scale16by8(g_rgb_counters.tick, rgb_matrix_config.speed / 2);
  for (uint8_t i = led_min; i < led_max; i++) {
    RGB_MATRIX_TEST_LED_FLAGS();
    int16_t dx = g_led_config.point[i].x - k_rgb_matrix_center.x;
    int16_t dy = g_led_config.point[i].y - k_rgb_matrix_center.y;
    uint8_t dist = sqrt16(dx * dx + dy * dy);
    effect_func(&hsv, dx, dy, dist, time);
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
  }
  return led_max < DRIVER_LED_TOTAL;
}
