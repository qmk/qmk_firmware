// Copyright 2025 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"

#ifdef RGBLIGHT_ENABLE
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
  {5, 2, HSV_WHITE}
);
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
  my_capslock_layer
);

void keyboard_post_init_kb(void) {
  rgblight_layers = my_rgb_layers;
  keyboard_post_init_user();
}
bool led_update_kb(led_t led_state) {
  bool res = led_update_user(led_state);
  if (res) {
    rgblight_set_layer_state(0, led_state.caps_lock);
  }
  return res;
}
#endif
