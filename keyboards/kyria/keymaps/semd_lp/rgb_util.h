#pragma once

#include "keycodes.h"
#include "quantum.h"

void rgb_layers_init(void);
layer_state_t rgb_set_layer_state(layer_state_t);
bool rgb_set_led_state(led_t led_state);
