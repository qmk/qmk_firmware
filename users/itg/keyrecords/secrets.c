#include "itg.h"  // replace with your keymap's "h" file, or whatever file stores the keycodes

#if (__has_include("secrets.h") && !defined(NO_SECRETS))
#include "secrets.h"
#else
// `PROGMEM const char secret[][x]` may work better, but it takes up more space in the firmware
// And I'm not familiar enough to know which is better or why...
static const char * const secrets[] = {
  "test1",
  "test2",
  "test3",
  "test4",
  "test5"
};
#endif

bool process_record_secrets(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_SCT1: // Secrets!  Externally defined strings, not stored in repo
      if (!record->event.pressed) {
        clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
        send_string_with_delay(secrets[keycode - KC_SCT1], 10);
      }
      return false;
      break;
  }
  return true;
}
