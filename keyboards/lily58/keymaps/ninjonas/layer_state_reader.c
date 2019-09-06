#include QMK_KEYBOARD_H
#include <stdio.h>
#include "lily58.h"
#include "ninjonas.h"

char layer_state_str[24];

const char *read_layer_state(void) {
  switch (biton32(layer_state))
  {
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
    switch (biton32(default_layer_state)) {
        case _COLEMAK:
           snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Colemak");
           break;
        case _DVORAK:
           snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Dvorak");
           break;
         case _QWERTY:
            snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Qwerty");
            break;
        default:
            snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Undef-%ld", layer_state);
    }
  }

  return layer_state_str;
}