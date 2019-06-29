#include "_example.h"

void matrix_init_user(void) {
#ifdef BOOTLOADER_CATERINA
   // This will disable the red LEDs on the ProMicros
   setPinOutput(D5);
   writePinHigh(D5);
   setPinOutput(B0);
   writePinHigh(B0);
#endif
};

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
    case WOW:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_WOW);
      }
      return false;
    case DESTINY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DESTINY);
      }
      return false;
  }
  return true;
};