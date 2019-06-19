#pragma once
#include "quantum.h"
#include "colors_bs.h"
#ifdef RGB_MATRIX_ENABLE
#   include "rgb_matrix.h"
#endif

// Define Layer for Lighting functions
#define _LIGHT 14

#ifdef RGB_MATRIX_ENABLE
#define LED_FLAG_ALL_KEYS 0x05

void rgb_matrix_layer_helper(uint8_t red, uint8_t green, uint8_t blue, uint8_t led_type);
void rgb_matrix_cycle_flag(void);
#endif

void keyboard_post_init_rgb(void);
void rgb_layer_helper(uint8_t hue, uint8_t sat, uint8_t val);

layer_state_t layer_state_set_rgb(layer_state_t state);
// layer_state_t default_layer_state_set_rgb(layer_state_t state);
