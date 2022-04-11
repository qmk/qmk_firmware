#include "mutecivilian.h"  // replace with your keymap's "h" file, or whatever file stores the keycodes

#if (__has_include("features/secrets.h") && !defined(NO_SECRETS))
#include "features/secrets.h"
#else
// `PROGMEM const char secret[][x]` may work better, but it takes up more space in the firmware
// And I'm not familiar enough to know which is better or why...
static const char * const secrets[] = {
  "test1",
  "test2"
};
#endif

bool process_record_secrets(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_SECRET_1 ... KC_SECRET_2: // Secrets!  Externally defined strings, not stored in repo
      if (!record->event.pressed) {
        send_string_with_delay(secrets[keycode - KC_SECRET_1], MACRO_TIMER);
      }
      return false;
      break;
  }
  return true;
}
