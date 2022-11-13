
#include QMK_KEYBOARD_H
#include <stdio.h>
#include "lily58.h"

#define L_BASE 0
#define L_FN (1 << 1)

char layer_state_str[24];

const char *read_layer_state(void) {
  switch (layer_state)
  {
  case L_BASE:
    snprintf(layer_state_str, sizeof(layer_state_str), "DEF");
    break;
  case L_FN:
    snprintf(layer_state_str, sizeof(layer_state_str), " FN");
    break;
  default:
    snprintf(layer_state_str, sizeof(layer_state_str), "UN-%u", layer_state);
  }

  return layer_state_str;
}
