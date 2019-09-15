#include QMK_KEYBOARD_H
#include <stdio.h>
#include "crkbd.h"
#include "ninjonas.h"

char layer_state_str[24];

const char *read_layer_state(void) {
  switch (biton32(layer_state))
  {
  case _QWERTY:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Qwerty");
    break;
  case _RAISE:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Raise");
    break;
  case _LOWER:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Lower");
    break;
  case _ADJUST:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Adjust");
    break;
  default:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Undef-%ld", layer_state);
    break;
  }

  return layer_state_str;
}