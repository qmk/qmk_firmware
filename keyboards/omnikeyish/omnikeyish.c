#include "omnikeyish.h"

void keyboard_pre_init_user(void) {
  dynamic_macro_init();
}

void keyboard_post_init_user(void) {
  /* Customise these values to desired behaviour */
  //debug_enable = true;
  //debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;

#ifdef DYNAMIC_MACRO_EEPROM_STORAGE
  /* Restore macros from eeprom */
  dynamic_macro_load_eeprom_all();
#endif

  /* Send numlock keycode to attempt to force numlock back on. */
  register_code(KC_NUMLOCK);
  unregister_code(KC_NUMLOCK);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!process_record_dynamic_macro(keycode, record)) {
    return false;
  }

  return true;
}
