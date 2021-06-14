
#include "rs.h"

// process_record_user is like process_record_user for keymaps including this file.
__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

// rgb_mod_changed_keymap is called any time the RGB mod has been changed.
__attribute__ ((weak))
void rgb_mod_changed_keymap(void) {
}

// keylog_set_keymap is called for every key press.
__attribute__ ((weak))
void keylog_set_keymap(uint16_t keycode, keyrecord_t *record) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    keylog_set_keymap(keycode, record);
  }

  switch (keycode) {
  case NEQL: // !=
    if (record->event.pressed) {
      SEND_STRING("!=");
    }
    return false;
  case LPLT: // ( or < with shift
    if (record->event.pressed) {
      if (get_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))) {
        // <
        tap_code(KC_COMM); // shift is already registered
      } else {
        // (
        register_mods(MOD_BIT(KC_LSFT));
        tap_code(KC_9);
        unregister_mods(MOD_BIT(KC_LSFT));
      }
    }
    return false;
  case RPGT: // ) or > with shift
    if (record->event.pressed) {
      if (get_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))) {
        // <
        tap_code(KC_DOT); // shift is already registered
      } else {
        // )
        register_mods(MOD_BIT(KC_LSFT));
        tap_code(KC_0);
        unregister_mods(MOD_BIT(KC_LSFT));
      }
    }
    return false;
#ifdef RGBLIGHT_ENABLE
  case RGB_MOD:
      if (record->event.pressed) {
        rgblight_step();
        rgb_mod_changed_keymap();
      }
    return false;
  case RGBRST:
      if (record->event.pressed) {
        eeconfig_update_rgblight_default();
        rgblight_enable();
        rgb_mod_changed_keymap();
      }
    return false;
#endif
  }
  return process_record_keymap(keycode, record);
}