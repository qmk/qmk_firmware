#include <art.h>

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}



bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CTRL_CTV:
      if (record->event.pressed) {
        if ( get_mods() & MOD_MASK_SHIFT ) {
          clear_mods();
          SEND_STRING(SS_LCTL("ctv"));
        } else {
          SEND_STRING(SS_LCTL("ctv") SS_TAP(X_ENTER));
        }
      }
      break;
  }

  return process_record_keymap(keycode, record);
}