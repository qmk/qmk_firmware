#include "quantum.h"
#include "333fred.h"

void matrix_init_rgb(void) {
  rgblight_enable_noeeprom();
  rgblight_sethsv_noeeprom_purple();
}

void layer_state_set_rgb(uint32_t state) {
  switch (biton32(state)) {
    case BASE:
      rgblight_sethsv_noeeprom_purple();
      break;
    case SYMB:
      rgblight_sethsv_noeeprom_blue();
      break;
    case VIM:
      rgblight_sethsv_noeeprom_green();
      break;
    case GAME:
      rgblight_sethsv_noeeprom_red();
      break;
  }
}
