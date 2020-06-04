#include "ajp10304.h"

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

   switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistant_default_layer_set(1UL<<_QWERTY);
      }
      return false;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case MLWR:
      if (record->event.pressed) {
        layer_on(_LOWER);
        layer_on(_MLWR);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        layer_off(_MLWR);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case MRSE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        layer_on(_MRSE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        layer_off(_MRSE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case MFNC:
      if (record->event.pressed) {
        layer_on(_FUNC);
        layer_on(_MFNC);
      } else {
        layer_off(_FUNC);
        layer_off(_MFNC);
      }
      return false;
    case MFNC2:
      if (record->event.pressed) {
        layer_on(_FUNC2);
        layer_on(_MFNC2);
      } else {
        layer_off(_FUNC2);
        layer_off(_MFNC2);
      }
      return false;
    }
  return true;
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t keycode, uint8_t opt) {
  // These would trigger when you hit a key mapped as M(0)
  if (record->event.pressed) {
    switch(keycode) {
      case 0: // Some custom string here
        SEND_STRING("");
        return false;

      case 1: // Word Select
        SEND_STRING(SS_DOWN(X_LCTRL) SS_TAP(X_RIGHT) SS_DOWN(X_LSHIFT) SS_TAP(X_LEFT) SS_UP(X_LSHIFT) SS_UP(X_LCTRL));
        return false;

      case 2: // Word Select Mac
        SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_RIGHT) SS_DOWN(X_LSHIFT) SS_TAP(X_LEFT) SS_UP(X_LSHIFT) SS_UP(X_LALT));
        return false;

      case 3: // Line Select
        SEND_STRING(SS_TAP(X_HOME) SS_DOWN(X_LSHIFT) SS_TAP(X_END) SS_UP(X_LSHIFT));
        return false;

      case 4: // Line Select Mac
        SEND_STRING(SS_LCTRL("a") SS_DOWN(X_LSHIFT) SS_LCTRL("e") SS_UP(X_LSHIFT));
        return false;

      case 5: // Line Delete
        SEND_STRING(SS_TAP(X_HOME) SS_DOWN(X_LSHIFT) SS_TAP(X_END) SS_UP(X_LSHIFT));
        SEND_STRING(SS_TAP(X_BSPACE));
        return false;

      case 6: // Line Delete Mac
        SEND_STRING(SS_LCTRL("a") SS_DOWN(X_LSHIFT) SS_LCTRL("e") SS_UP(X_LSHIFT));
        SEND_STRING(SS_TAP(X_BSPACE));
        return false;

      case 7: // Duplicate Selection
        SEND_STRING(SS_LCTRL("c") SS_TAP(X_RIGHT) SS_LCTRL("v"));
        return false;

      case 8: // Duplicate Selection Mac
        SEND_STRING(SS_LGUI("c") SS_TAP(X_RIGHT) SS_LGUI("v"));
        return false;

      case 9: // Join line
        SEND_STRING(SS_TAP(X_END) SS_TAP(X_DELETE));
        return false;

      case 10: // Join line Mac
        SEND_STRING(SS_LCTRL("e") SS_TAP(X_DELETE));
        return false;

      case 98: // Print mode
        SEND_STRING("PC");
        return false;

      case 99: // Print mode
        SEND_STRING("OSX");
        return false;
    }
  }
  return MACRO_NONE;
};
