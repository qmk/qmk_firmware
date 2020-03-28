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
    case PHONE ... SVIV: // Secrets!  Externally defined strings, not stored in repo
      if (!record->event.pressed) {
        send_string_with_delay(secrets[keycode - PHONE], MACRO_TIMER);
      }
      return false;
      break;
     }
  return true;
}

bool process_record_recrets(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  
    case PHONE:
      if (record->event.pressed) {
          SEND_STRING("3931044785");
      }
      return false;
      break;

    case DESK:
      if (record->event.pressed) {
          SEND_STRING("desk" SS_LALT(";") "silviogulizia.com");
      }
      return false;
      break;

    case SGCOM:
      if (record->event.pressed) {
          SEND_STRING("https" SS_LSFT(".")SS_LSFT("7")SS_LSFT("7")"silviogulizia.com");
      }
      return false;
      break;

    case VIVERE:
      if (record->event.pressed) {
          SEND_STRING("https" SS_LSFT(".") SS_LSFT("7") SS_LSFT("7") "vivereintenzionalmente.com");
      }
      return false;
      break;
    
    case SVIV:
      if (record->event.pressed) {
          SEND_STRING("silvio" SS_LALT(";") "vivereintenzionalmente.com");
      }
      return false;
      break;
    
  }
  return true;
};

