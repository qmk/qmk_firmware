#include QMK_KEYBOARD_H
#include "split_util.h"
#include "keymap_xrows.h"
#ifdef SSD1306OLED
  #include "oled.h"
#endif

// keymaps definitions are moved to keymap_Xrows.c.

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case KC_LOCK:
      if (record->event.pressed) {
        if (get_enable_kc_lang()) {
          SEND_STRING( SS_LCTRL(SS_LSFT(SS_TAP(X_POWER))) );
        } else {
          SEND_STRING( SS_LGUI("l") );
        }
      }
      return false;
  }
  return true;
}

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
    case _EDVORAKJ1:
    case _EDVORAKJ2:
      // _EDVORAKJ1 & J2 are same colored
      rgblight_sethsv_noeeprom_white();
      break;
    case _LOWER:
      rgblight_sethsv_noeeprom_red();
      break;
    case _RAISE:
      rgblight_sethsv_noeeprom_blue();
      break;
    case _ADJUST:
      rgblight_sethsv_noeeprom_green();
      break;
    default: //  for any other layers, or the default layer
      rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_GRADIENT + 3);
      rgblight_sethsv_noeeprom_red();
      break;
  }
  return state;
}
#endif
