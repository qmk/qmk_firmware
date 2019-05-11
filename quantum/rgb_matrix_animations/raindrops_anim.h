#ifndef DISABLE_RGB_MATRIX_RAINDROPS
RGB_MATRIX_EFFECT(RAINDROPS)
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static void raindrops_set_color(int i, effect_params_t* params, rgb_config_t* config) {
  if (!HAS_ANY_FLAGS(g_led_config.flags[i], params->flags)) return;
  HSV hsv = { 0 , config->sat, config->val };

  // Take the shortest path between hues
  int16_t deltaH = ((config->hue + 180) % 360 - config->hue) / 4;
  if (deltaH > 127) {
    deltaH -= 256;
  } else if (deltaH < -127) {
    deltaH += 256;
  }

  hsv.h = config->hue + (deltaH * (rand() & 0x03));
  RGB rgb = hsv_to_rgb(hsv);
  rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
}

bool RAINDROPS(effect_params_t* params, rgb_config_t* config) {
  if (!params->init) {
    // Change one LED every tick, make sure speed is not 0
    if (scale16by8(g_rgb_counters.tick, qadd8(config->speed, 16)) % 10 == 0) {
      raindrops_set_color(rand() % DRIVER_LED_TOTAL, params, config);
    }
    return false;
  }

  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  for (int i = led_min; i < led_max; i++) {
    raindrops_set_color(i, params, config);
  }
  return led_max < DRIVER_LED_TOTAL;
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif // DISABLE_RGB_MATRIX_RAINDROPS
