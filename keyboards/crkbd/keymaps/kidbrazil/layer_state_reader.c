
#include QMK_KEYBOARD_H
#include <stdio.h>
#include "crkbd.h"

// in the future, should use (1U<<_LAYER_NAME) instead, but needs to be moved to keymap,c
char layer_state_str[24];

const char *read_layer_state(void) {
  switch (layer_state)
  {
  case 0:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer | [ QWRTY ]");
    break;
  case 2:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer | [ NUMBERS ]");
    break;
  case 4:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer | [ SYMBOLS ]");
    break;
  case 6:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer | [ DOUBLETROUBLES ]");
    break;
  case 8:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer | [ GAMING ]");
    break;
  case 24:
  case 12:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer | [ WEAPONS ]");
    break;
  default:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer | Undef-%ld", layer_state);
  }

  return layer_state_str;
}
