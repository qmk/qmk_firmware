#include "klackygears.h"



bool process_record_user(uint16_t keycode, keyrecord_t *record) {
/*
 if (!process_record_dynamic_macro(keycode, record)) {
        return false;
    }
*/
  switch (keycode) {
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
    break;

    case MAKEK:
      if (record->event.pressed) {
        SEND_STRING("make helix:klackygears");
      }
    break;

    case MAKEKF:
      if (record->event.pressed) {
        SEND_STRING("make helix:klackygears:dfu");
      }

    break;

  case KC_DVORAK:
    if (record->event.pressed) {
      set_single_persistent_default_layer(_DVORAK);
    }
    break;
  case KC_ALTDVK:
    if (record->event.pressed) {
      set_single_persistent_default_layer(_ALTDVK);
    }
    break;
  case KC_QWERTY:
    if (record->event.pressed) {
      set_single_persistent_default_layer(_QWERTY);
    }
    break;
  }



      return true;
}


