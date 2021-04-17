
#include QMK_KEYBOARD_H
#include <stdio.h>
#include "lily58.h"

#define L_BASE 0
#define L_LOWER (1 << 1)
#define L_RAISE (1 << 2)
#define L_ADJUST (1 << 3)
#define L_ADJUST_TRI (L_ADJUST | L_RAISE | L_LOWER)

const char *read_layer_state(void) {
  switch (layer_state)
  {
  case L_BASE:
    return "Layer: Default";
    break;
  case L_RAISE:
    return "Layer: Raise";
    break;
  case L_LOWER:
    return "Layer: Lower";
    break;
  case L_ADJUST:
  case L_ADJUST_TRI:
    return "Layer: Adjust";
    break;
  }
  
  return "Layer: Undefined";
}
