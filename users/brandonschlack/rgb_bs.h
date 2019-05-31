#pragma once
#include "quantum.h"
#ifdef RGB_MATRIX_ENABLE
  #include "rgb_matrix.h"
#endif

// RGB Colors
#define RGB_LSR_PURPLE   0x3C, 0x16, 0x8C
#define RGB_LSR_PINK     0xF2, 0x1B, 0x7F
#define RGB_LSR_INDIGO   0x23, 0x1B, 0x59
#define RGB_LSR_CYAN     0x2F, 0xC1, 0xE1
#define RGB_LSR_VIOLET   0x53, 0x36, 0xBF

// layer_state_t layer_state_set_rgb(layer_state_t state);
// layer_state_t default_layer_state_set_rgb(layer_state_t state);

// void rgb_matrix_hsv_layer (uint8_t hue, uint8_t sat, uint8_t val);
void rgb_matrix_layer_helper (uint8_t red, uint8_t green, uint8_t blue, uint8_t led_type);
