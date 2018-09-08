#include "wanleg.h"

// Defines actions for my global custom keycodes. Defined in wanleg.h file
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
    case ONEHAND:
    if (record->event.pressed) {
      set_single_persistent_default_layer(ONE);
      }
      return false;
      break;
    case QWERTY75:
    if (record->event.pressed) {
      set_single_persistent_default_layer(QW75);
      }
      return false;
      break;
    case GHERKIN75:
    if (record->event.pressed) {
      set_single_persistent_default_layer(GK75);
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
	case SUBTER75:
      if (record->event.pressed) {
        layer_on(SUB75);
      } else {
        layer_off(SUB75);
      }
      return false;
      break;
	case SUPRA75:
      if (record->event.pressed) {
        layer_on(SUP75);
      } else {
        layer_off(SUP75);
      }
      return false;
      break;
	case NUMBER75:
      if (record->event.pressed) {
        layer_on(NUM75);
      } else {
        layer_off(NUM75);
      }
      return false;
      break;
	case DIRECTION75:
      if (record->event.pressed) {
        layer_on(DIR75);
      } else {
        layer_off(DIR75);
      }
      return false;
      break;
	case ETCETERA75:
      if (record->event.pressed) {
        layer_on(ETC75);
      } else {
        layer_off(ETC75);
      }
      return false;
      break;
	case FUNCTION75:
      if (record->event.pressed) {
        layer_on(FN75);
      } else {
        layer_off(FN75);
      }
      return false;
      break;
  }
  return true;
}

/// Turn off LEDs on ProMicros of Let's Split ///
// LEDs only on by default on Let's Split
// Add reconfigurable functions here, for keymap customization
// This allows for a global, userspace functions, and continued
// customization of the keymap.  Use _keymap instead of _user
// functions in the keymaps
__attribute__ ((weak))
void matrix_init_keymap(void) {}

// Call user matrix init, then call the keymap's init function
void matrix_init_user(void) {
#if defined(KEYBOARD_lets_split_rev2)
  DDRD &= ~(1<<5);
  PORTD &= ~(1<<5);

  DDRB &= ~(1<<0);
  PORTB &= ~(1<<0);
#endif
  matrix_init_keymap();
}