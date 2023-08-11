#include "quantum.h"
#include <stdio.h>

// in the future, should use (1U<<_LAYER_NAME) instead, but needs to be moved to keymap,c
#define _0_QWERTY 0
#define _1_SYMBOLS_NUMPAD 2
#define _2_MOUSE_MEDIA 4
#define _3_NAV 8
#define _4_FN 16
#define _5_GRAVE_RGB 32
#define _6_GAMING 64

char layer_state_str[24];

const char *read_layer_state(void) {
  switch (layer_state)
  {
  case _0_QWERTY:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Default");
    break;
  case _1_SYMBOLS_NUMPAD:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Symb/Numpad");
    break;
  case _2_MOUSE_MEDIA:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Mouse/Media");
    break;
  case _3_NAV:
  snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Nav");
    break;
  case _4_FN:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: FN/Nav");
    break;
  case _5_GRAVE_RGB:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: RGB");
    break;
  case _6_GAMING:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Gaming");
    break;
  default:
#if defined (LAYER_STATE_32BIT)
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Undef-%ld", layer_state);
#else
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Undef-%d", layer_state);
#endif
  }

  return layer_state_str;
}
