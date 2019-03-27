#include "quantum.h"
#include "333fred.h"

void matrix_init_rgb(void) {
  rgblight_enable_noeeprom();
  rgblight_sethsv_noeeprom(270, 255, 20);
}

void layer_state_set_rgb(uint32_t state) {
  switch (biton32(state)) {
    case BASE:
      // purple
      rgblight_sethsv_noeeprom(270, 255, 20);
      break;
    case SYMB:
      // blue
      rgblight_sethsv_noeeprom(240, 255, 20);
      break;
    case VIM:
      // green
      rgblight_sethsv_noeeprom(120, 255, 20);
      break;
    case GAME:
      // red
      rgblight_sethsv_noeeprom(0, 255, 20);
      break;
  }
}
