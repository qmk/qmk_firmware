#include "ridingqwerty.h"

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

__attribute__ ((weak))
bool process_record_secrets(uint16_t keycode, keyrecord_t *record) {
  return true;
}

uint16_t user_key_timer;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case RG_QUOT:
      if (record->event.pressed) {
        user_key_timer = timer_read();
        layer_on(_NUMBER);
        register_mods(MOD_BIT(KC_RGUI));
      } else {
        unregister_mods(MOD_BIT(KC_RGUI));
        layer_off(_NUMBER);
	if (timer_elapsed(user_key_timer) < TAPPING_TERM) {
          register_code(KC_QUOT);
	  unregister_code(KC_QUOT);
	}
      }
      return false; break;
  }
  return process_record_keymap(keycode, record) &&
    process_record_secrets(keycode, record);
}
