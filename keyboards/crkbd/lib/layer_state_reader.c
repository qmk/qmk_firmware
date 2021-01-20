
#include QMK_KEYBOARD_H
#include <stdio.h>
#include "crkbd.h"

// in the future, should use (1U<<_LAYER_NAME) instead, but needs to be moved to keymap,c
#define L_BASE 0
#define L_NMB 2
#define L_EMACS 4
#define L_META 8
#define L_FN 16
#define L_SCT 32

char layer_state_str[24];

const char *read_layer_state(void) {
  switch (layer_state)
  {
  case L_BASE:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Default");
    break;
  case L_NMB:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Number");
    break;
  case L_EMACS:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Emacs");
    break;
  case L_META:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Meta");
    break;
  case L_FN:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Function");
    break;
  case L_SCT:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Select");
    break;
  default:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Undefined", layer_state);
  }
  return layer_state_str;
}
