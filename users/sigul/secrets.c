#include "sigul.h"

#if (__has_include("secrets.h") && !defined(NO_SECRETS))
#include "secrets.h"
#else
// `PROGMEM const char secret[][x]` may work better, but it takes up more space in the firmware
// And I'm not familiar enough to know which is better or why...
static const char * const secret[] = {
  "placeholder1",
  "placeholder2",
  "placeholder3",
  "placeholder4",
  "placeholder5"
};
#endif

bool process_record_secrets(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY: // Secrets!  Externally defined strings, not stored in repo
      if (!record->event.pressed) {
        send_string_with_delay(secret[keycode - QWERTY], MACRO_TIMER);
      }
      return false;
      break;
  }
    case PHONE: // Secrets!  Externally defined strings, not stored in repo
      if (!record->event.pressed) {
        send_string_with_delay(secret[keycode - PHONE], MACRO_TIMER);
      }
      return false;
      break;
  }
    case DESK: // Secrets!  Externally defined strings, not stored in repo
      if (!record->event.pressed) {
        send_string_with_delay(secret[keycode - DESK], MACRO_TIMER);
      }
      return false;
      break;
  }
    case SGCOM: // Secrets!  Externally defined strings, not stored in repo
      if (!record->event.pressed) {
        send_string_with_delay(secret[keycode - SGCOM], MACRO_TIMER);
      }
      return false;
      break;
  }
    case VIVERE: // Secrets!  Externally defined strings, not stored in repo
      if (!record->event.pressed) {
        send_string_with_delay(secret[keycode - VIVERE], MACRO_TIMER);
      }
      return false;
      break;
  }
    case SVIV: // Secrets!  Externally defined strings, not stored in repo
      if (!record->event.pressed) {
        send_string_with_delay(secret[keycode - SVIV], MACRO_TIMER);
      }
      return false;
      break;
  }
  return true;
}
