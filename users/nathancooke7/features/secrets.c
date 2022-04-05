#include "nathancooke7.h"  // replace with your keymap's "h" file, or whatever file stores the keycodes
#include "secrets.h"

bool process_record_secrets(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_SECRET_1 ... KC_SECRET_2: // Secrets!  Externally defined strings, not stored in repo
      if (!record->event.pressed) {
       clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
        send_string_with_delay(secrets[keycode - KC_SECRET_1], MACRO_TIMER);
      }
      return false;
      break;
  }
  return true;
}
