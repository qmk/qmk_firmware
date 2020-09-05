#include "badger.h"

bool      _capsLockState;
int       _currentLayer;

__attribute__ ((weak))
void keyboard_post_init_user(void) {
  _capsLockState = false;
  _currentLayer = _QWERTY_MAC;
  layer_on(_currentLayer);
}

__attribute__ ((weak))
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CS_RIGHT:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT(SS_TAP(X_B)SS_TAP(X_ENTER)));
        return false;
      }
      break;
    case CS_DOWN:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT(SS_TAP(X_V)SS_TAP(X_ENTER)));
        return false;
      }
      break;
    case KC_CAPS:
      if (record->event.pressed) {
        _capsLockState = !_capsLockState;
        return true;
      }
      break;
    default:
      return true;
  }
  return true;
}