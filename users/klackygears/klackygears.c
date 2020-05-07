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
        SEND_STRING("make " QMK_KEYBOARD ":" QMK_KEYMAP);
      }
    break;

    case MAKEKF:
      if (!record->event.pressed) {
      SEND_STRING(("make " QMK_KEYBOARD ":" QMK_KEYMAP));
      #if defined(KEYBOARD_viterbi)
        SEND_STRING((":dfu" SS_TAP(X_ENTER)));
      #else

          #if defined(__arm__)
            SEND_STRING((":dfu-util"));
          #elif defined(BOOTLOADER_DFU)
            SEND_STRING((":dfu"));
          #elif defined(BOOTLOADER_HALFKAY)
            SEND_STRING((":teensy"));
          #elif defined(BOOTLOADER_CATERINA)
            SEND_STRING((":avrdude"));
          #endif // bootloader options
      #endif

    }

    break;


    case SHRUG:
      if (record->event.pressed) {
        SEND_STRING(":Shrug:");
        //send_unicode_hex_string(0x2122);
      }
    break;

  case KC_MACBASE:
    if (record->event.pressed) {
      set_single_persistent_default_layer(_MACBASE);
    }
    break;

  case KC_WINBASE:
    if (record->event.pressed) {
      set_single_persistent_default_layer(_WINBASE);
    }
    break;

  case KC_QWERTY:
    if (record->event.pressed) {
      set_single_persistent_default_layer(_QWERTY);
    }
    break;

 case KC_GAMER:
    if (record->event.pressed) {
      set_single_persistent_default_layer(_GAMER);
    }
    break;

case KC_GAMR1:
    if (record->event.pressed) {
      set_single_persistent_default_layer(_GAMR1);
    }
    break;

case KC_GAMR2:
    if (record->event.pressed) {
      set_single_persistent_default_layer(_GAMR2);
    }
    break;
  }

      return true;
}


