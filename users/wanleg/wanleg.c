#include "wanleg.h"

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Defines actions tor my global custom keycodes. Defined in wanleg.h file
// Then runs the _keymap's record handier if not processed here
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QW);
      }
      return false;
      break;
    case GHERKIN:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_GK);
      }
      return false;
      break;
    case gGHERKIN:
      if (record->event.pressed) {
        set_single_persistent_default_layer(gGK);
      }
      return false;
      break;
    case SUBTER:
      if (record->event.pressed) {
        layer_on(SUB);
      } else {
        layer_off(SUB);
      }
      return false;
      break;
    case SUPRA:
      if (record->event.pressed) {
        layer_on(SUP);
      } else {
        layer_off(SUP);
      }
      return false;
      break;
	case NUMBER:
      if (record->event.pressed) {
        layer_on(NUM);
      } else {
        layer_off(NUM);
      }
      return false;
      break;
	case DIRECTION:
      if (record->event.pressed) {
        layer_on(DIR);
      } else {
        layer_off(DIR);
      }
      return false;
      break;
	case ETCETERA:
      if (record->event.pressed) {
        layer_on(ETC);
      } else {
        layer_off(ETC);
      }
      return false;
      break;
  case gNUMBER:
      if (record->event.pressed) {
        layer_on(gNUM);
      } else {
        layer_off(gNUM);
      }
      return false;
      break;
  case gDIRECTION:
      if (record->event.pressed) {
        layer_on(gDIR);
      } else {
        layer_off(gDIR);
      }
      return false;
      break;
	case gETCETERA:
      if (record->event.pressed) {
        layer_on(gETC);
      } else {
        layer_off(gETC);
      }
      return false;
      break;

  }
  return true;
}
