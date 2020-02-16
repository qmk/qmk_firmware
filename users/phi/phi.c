#include "quantum.h"

#ifdef CUSTOM_MOUSEKEY
#include "custom_mousekey.h"
#endif

__attribute__ ((weak))
bool process_record_keymap (uint16_t keycode, keyrecord_t *record) {
  return true;
}

bool process_record_user (uint16_t keycode, keyrecord_t *record) {
  if (!process_record_keymap(keycode, record)) {
    return false;
  }
 #ifdef CUSTOM_MOUSEKEY
  if (!process_mousekey_accel(keycode, record)) {
    return false;
  }
 #endif
  return true;
}
