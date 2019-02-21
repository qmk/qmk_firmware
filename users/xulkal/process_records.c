#include "process_records.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
#ifdef TRILAYER_ENABLED
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
#endif
      } else {
        layer_off(_LOWER);
#ifdef TRILAYER_ENABLED
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
#endif
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
#ifdef TRILAYER_ENABLED
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
#endif
      } else {
        layer_off(_RAISE);
#ifdef TRILAYER_ENABLED
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
#endif
      }
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
        }
      #endif
      return false;
      break;
  }

  return process_record_keymap(keycode, record) &&
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
    process_record_rgb(keycode, record) &&
#endif // RGBLIGHT_ENABLE;
    true;
}

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}


__attribute__ ((weak))
bool process_record_rgb(uint16_t keycode, keyrecord_t *record) {
  return true;
}
