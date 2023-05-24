#include "stanrc85.h"

void matrix_init_user(void) {
  rgblight_setrgb(0xFF, 0x00, 0x00);
};

layer_state_t layer_state_set_user(layer_state_t state) {
  switch (biton32(state)) {
    case 0:
      rgblight_setrgb (0xFF, 0x00, 0x00);
      break;
    case 1:
      rgblight_setrgb (0x00, 0xFF, 0x00);
      break;
    case 2:
      rgblight_setrgb (0x00, 0x00, 0xFF);
      break;
    case 3:
      rgblight_setrgb (0xFF, 0xFF, 0xFF);
      break;
    case 4:
      rgblight_setrgb (0xFF, 0x00, 0xFF);
      break;
    default: //  for any other layers, or the default layer
      rgblight_setrgb (0xFF, 0x00, 0x00);
      break;
    }
  return state;
}
