#include "ajp10304.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
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
            register_mods(MOD_LCTL);
            tap_code(KC_RGHT);
            tap_code16(S(KC_LEFT));
            unregister_mods(MOD_LCTL);
        }
        break;
    case M_WORD_SEL_MAC:
        if (record->event.pressed) {
            register_mods(MOD_LALT);
            tap_code(KC_RGHT);
            tap_code16(S(KC_LEFT));
            unregister_mods(MOD_LALT);
        }
        break;
    case M_LINE_SEL:
        if (record->event.pressed) {
            tap_code(KC_HOME);
            tap_code16(S(KC_END));
        }
        break;
    case M_LINE_SEL_MAC:
        if (record->event.pressed) {
            tap_code16(C(KC_A));
            tap_code16(C(S(KC_E)));
        }
        break;
    case M_LINE_DEL:
        if (record->event.pressed) {
            tap_code(KC_HOME);
            tap_code16(S(KC_END));
            tap_code(KC_BSPC);
        }
        break;
    case M_LINE_DEL_MAC:
        if (record->event.pressed) {
            tap_code16(C(KC_A));
            tap_code16(C(S(KC_E)));
            tap_code(KC_BSPC);
        }
        break;
    case M_DUP:
        if (record->event.pressed) {
            tap_code16(C(KC_C));
            tap_code(KC_RGHT);
            tap_code16(C(KC_V));
         }
         break;
    case M_DUP_MAC:
        if (record->event.pressed) {
            tap_code16(G(KC_C));
            tap_code(KC_RGHT);
            tap_code16(G(KC_V));
        }
        break;
    case M_JOIN:
        if (record->event.pressed) {
            tap_code(KC_END);
            tap_code(KC_DEL);
        }
        break;
    case M_JOIN_MAC:
        if (record->event.pressed) {
            tap_code16(C(KC_E));
            tap_code(KC_DEL);
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
