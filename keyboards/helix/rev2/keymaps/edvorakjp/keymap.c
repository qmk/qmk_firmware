#include QMK_KEYBOARD_H
#include "split_util.h"
#include "keymap_xrows.h"
#ifdef SSD1306OLED
  #include "oled.h"
#endif

// keymaps definitions are moved to keymap_Xrows.c.

#ifdef SSD1306OLED
void matrix_init_keymap(void) {
  //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
  iota_gfx_init(!has_usb());   // turns on the display
}

void matrix_scan_user(void) {
  iota_gfx_task();  // this is what updates the display continuously
}
#endif

#ifdef RGBLIGHT_ENABLE
uint32_t layer_state_set_keymap(uint32_t state) {
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
  switch (biton32(state)) {
    case _LOWER:
      rgblight_sethsv_noeeprom_red();
      break;
    case _RAISE:
      rgblight_sethsv_noeeprom_blue();
      break;
    default: //  for any other layers, or the default layer
      rgblight_mode(RGBLIGHT_MODE_STATIC_GRADIENT + 3);
      rgblight_sethsv_red();
      break;
  }
  return state;
}
#endif
