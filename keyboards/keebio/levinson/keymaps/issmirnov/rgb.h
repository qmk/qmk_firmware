#pragma once
#include "quantum.h"
#include "issmirnov.h"

// Welcome animation when keyboard boots
void keyboard_post_init_rgb(void);

// If rgb enabled, set underglow for layer
uint32_t layer_state_set_rgb(uint32_t state);

// Enhance matrix scan code. Note: keep this light, since it runs every 100ms
void matrix_scan_rgb(void);

// Light up SHIFT and GUI indicator when pressed.
void set_rgb_indicators(uint8_t this_mod, uint8_t this_osm);
