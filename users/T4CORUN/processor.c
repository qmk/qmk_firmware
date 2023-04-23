#include "processor.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  #ifdef KEYLOG_ENABLE
  if (record->event.pressed) {
    add_keylog(keycode);
  }
  #endif //KEYLOG_ENABLE
  
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {  
          default_layer_set(1UL<<_QWERTY);
      }
      return false;
    case CLMAKDH:
      if (record->event.pressed) {
          default_layer_set(1UL<<_COLEMAK_DH);
      }
      return false;
  }
  return true;
}