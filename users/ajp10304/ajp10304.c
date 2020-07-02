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
    case M_CUSTOM:
        if (record->event.pressed) {
            SEND_STRING("Custom text here");
        }
        break;
    case M_WORD_SEL:
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LCTRL) SS_TAP(X_RIGHT) SS_DOWN(X_LSHIFT) SS_TAP(X_LEFT) SS_UP(X_LSHIFT) SS_UP(X_LCTRL));
        }
        break;
    case M_WORD_SEL_MAC:
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_RIGHT) SS_DOWN(X_LSHIFT) SS_TAP(X_LEFT) SS_UP(X_LSHIFT) SS_UP(X_LALT));
        }
        break;
    case M_LINE_SEL:
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_HOME) SS_DOWN(X_LSHIFT) SS_TAP(X_END) SS_UP(X_LSHIFT));
        }
        break;
    case M_LINE_SEL_MAC:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTRL("a") SS_DOWN(X_LSHIFT) SS_LCTRL("e") SS_UP(X_LSHIFT));
        }
        break;
    case M_LINE_DEL:
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_HOME) SS_DOWN(X_LSHIFT) SS_TAP(X_END) SS_UP(X_LSHIFT));
            SEND_STRING(SS_TAP(X_BSPACE));
        }
        break;
    case M_LINE_DEL_MAC:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTRL("a") SS_DOWN(X_LSHIFT) SS_LCTRL("e") SS_UP(X_LSHIFT));
            SEND_STRING(SS_TAP(X_BSPACE));
        }
        break;
    case M_DUP:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTRL("c") SS_TAP(X_RIGHT) SS_LCTRL("v"));
         }
         break;
    case M_DUP_MAC:
        if (record->event.pressed) {
            SEND_STRING(SS_LGUI("c") SS_TAP(X_RIGHT) SS_LGUI("v"));
        }
        break;
    case M_JOIN:
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_END) SS_TAP(X_DELETE));
        }
        break;
    case M_JOIN_MAC:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTRL("e") SS_TAP(X_DELETE));
        }
        break;
    case M_MODE:
        if (record->event.pressed) {
            SEND_STRING("PC");
        }
        break;
    case M_MODE_MAC:
        if (record->event.pressed) {
            SEND_STRING("OSX");
        }
        break;
  }
  return true;
}
