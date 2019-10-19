
#include QMK_KEYBOARD_H
#include <stdio.h>
#include "crkbd.h"

// in the future, should use (1U<<_LAYER_NAME) instead, but needs to be moved to keymap,c
#define L_BASE 0
#define R_BASE 1
#define L_LOWER 2
#define R_LOWER 3
#define L_RAISE 4
#define R_RAISE 5
#define L_ADJUST 8
#define R_ADJUST 16
#define L_ADJUST_TRI 24

char layer_state_str[24];

const char *read_layer_state(void) {
  switch (layer_state)
  {
  case L_BASE:
  case R_BASE:
  rgblight_sethsv(120, 100, 85);
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Hacking Away");
    break;
  case L_RAISE:
  case R_RAISE:
  rgblight_sethsv(220, 100, 85);
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Numbers");
    break;
  case L_LOWER:
  case R_LOWER:
  rgblight_sethsv(120, 200, 85);
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Symbols");
    break;
  case L_ADJUST:
  case L_ADJUST_TRI:
  rgblight_sethsv(120, 100, 185);
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: One Hand");
    break;
  default:
    rgblight_sethsv(220, 200, 185);
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Undef-%ld", layer_state);
  }

  return layer_state_str;
}
