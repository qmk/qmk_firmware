#include "process_unicode.h"
#include "action_util.h"

bool process_unicode(uint16_t keycode, keyrecord_t *record) {
  if (keycode > QK_UNICODE && record->event.pressed) {
    uint16_t unicode = keycode & 0x7FFF;
    unicode_input_start();
    register_hex(unicode);
    unicode_input_finish();
  }
  return true;
}

