// secrets.c
#include "ninjonas.h"

static const char * const secret[] = {
  "BLANK1",
  "BLANK2",
  "BLANK3",
  "BLANK4",
  "BLANK5"
};

bool process_record_secrets(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case M_XXX1...M_XXX5:
      if (record->event.pressed) {
        send_string(secret[keycode - M_XXX1]);
      }
      break;
  }
  return true;
}
