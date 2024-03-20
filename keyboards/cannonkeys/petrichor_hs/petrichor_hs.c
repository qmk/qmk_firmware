// Copyright 2023 Andrew Kannan
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "petrichor_hs.h"

const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_RED}
);
const rgblight_segment_t PROGMEM my_numlock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 1, HSV_GREEN}
);
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {2, 1, HSV_BLUE}
);

// This layer does not exist
const rgblight_segment_t PROGMEM ghost_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {3, 1, HSV_BLUE}
);


const rgblight_segment_t* const PROGMEM enabled_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_capslock_layer,
    my_numlock_layer,
    my_layer1_layer
);

const rgblight_segment_t* const PROGMEM disabled_rgb_layers[] = RGBLIGHT_LAYERS_LIST(ghost_layer);

bool indicators_enabled = true;


void keyboard_post_init_kb(void) {
    keyboard_post_init_user();
    rgblight_layers = enabled_rgb_layers;
}

bool led_update_kb(led_t led_state) {
    led_update_user(led_state);
    rgblight_set_layer_state(0, led_state.caps_lock);
    rgblight_set_layer_state(1, led_state.num_lock);
    return true;
}

layer_state_t default_layer_state_set_kb(layer_state_t state) {
    state = default_layer_state_set_user(state);
    rgblight_set_layer_state(2, layer_state_cmp(state, 1));
    return state;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case RLAY_TOGG:
        if(indicators_enabled){
            rgblight_layers = disabled_rgb_layers;
            indicators_enabled = false;
        } else {
            rgblight_layers = enabled_rgb_layers;
            indicators_enabled = true;
        }
        return false;
    default:
        break;
  }
  return process_record_user(keycode, record);
}
