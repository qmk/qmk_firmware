#include "klackygears.h"


//void my_custom_function(void) {
//}


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
        // when keycode QMKBEST is pressed
        SEND_STRING("make helix:klackygears");
      }
    break;

    case MAKEKF:
      if (record->event.pressed) {
        // when keycode QMKBEST is pressed
        SEND_STRING("make helix:klackygears:dfu");
      }

    break;
  }



      return true;
}



