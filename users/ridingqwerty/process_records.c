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
    case LM_QUOT:
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

/*  moved to process_record_secrets (in secrets.c)
    case FUEL:    if (record->event.pressed) { SEND_STRING(SS_FUEL);    } return false;
    case C0RE:    if (record->event.pressed) { SEND_STRING(SS_C0RE);    } return false;
    case RUSTY:   if (record->event.pressed) { SEND_STRING(SS_RUSTY);   } return false;
    case VAXIS:   if (record->event.pressed) { SEND_STRING(SS_VAXIS);   } return false;
    case MUNKY:   if (record->event.pressed) { SEND_STRING(SS_MUNKY);   } return false;
    case AR1ST:   if (record->event.pressed) { SEND_STRING(SS_AR1ST);   } return false;
    case OS_LAB:  if (record->event.pressed) { SEND_STRING(SS_OS_LAB);  } return false;
    case SYSNOC:  if (record->event.pressed) { SEND_STRING(SS_SYSNOC);  } return false;
    case CDLOCAL: if (record->event.pressed) { SEND_STRING(SS_CDLOCAL); } return false;
*/
  }
  return process_record_keymap(keycode, record) &&
    process_record_secrets(keycode, record);
}
