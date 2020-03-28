#include "sigul.h"

#if (__has_include("secrets.h") && !defined(NO_SECRETS))
#include "secrets.h"
#else
// `PROGMEM const char secret[][x]` may work better, but it takes up more space in the firmware
// And I'm not familiar enough to know which is better or why...
static const char * const secrets[] = { // note that in drashna docs the array is called secret (singular) but I got variable not defined error while compiling
  "placeholder0",
  "placeholder1",
  "placeholder2",
  "placeholder3",
  "placeholder4"
};
#endif

// alias first and last secret in enumeration
#define KC_SECRET_FIRST SECRET0
#define KC_SECRET_LAST SECRET4

bool process_record_secrets(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_SECRET_FIRST ... KC_SECRET_LAST: // Secrets!  Externally defined strings, not stored in repo
      if (!record->event.pressed) {
        send_string_with_delay(secrets[keycode - KC_SECRET_FIRST], MACRO_TIMER); // note: in drashna docs the array here is called secret and in secrets.h secrets
      }
      return false;
      break;
     }
  return true;
}
