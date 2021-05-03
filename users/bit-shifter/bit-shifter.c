#include "bit-shifter.h"

// Add reconfigurable functions here, for keymap customization
// This allows for a global, userspace functions, and continued
// customization of the keymap.  Use _keymap instead of _user
// functions in the keymaps
__attribute__ ((weak))
void matrix_init_keymap(void) {}

__attribute__ ((weak))
void matrix_scan_keymap(void) {}

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

__attribute__ ((weak))
uint32_t layer_state_set_keymap (uint32_t state) {
  return state;
}

__attribute__ ((weak))
void led_set_keymap(uint8_t usb_led) {}

void matrix_init_user(void) {
  // windows users, to enable UC_WIN:
  // 1. Create a registry key (run regedit) of type REG_SZ called EnableHexNumpad with value 1 under:
  //   - HKEY_CURRENT_USER\Control Panel\Input Method\EnableHexNumpad
  // 2. Reboot
#if (defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE) || defined(UCIS_ENABLE))
//   set_unicode_input_mode(UC_MAC);
#endif //UNICODE_ENABLE
  matrix_init_keymap();
}

// activate leader functionality
LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    // slash :: find
    SEQ_ONE_KEY(KC_SLASH) {
      SEND_STRING(SS_LCTRL(SS_TAP(X_F)));
    }

    // Copy word
    SEQ_TWO_KEYS(KC_W, KC_C) {
      SEND_STRING(SS_LCTRL(SS_TAP(X_LEFT))SS_LSFT(SS_LCTRL(SS_TAP(X_RIGHT)))SS_LCTRL(SS_TAP(X_C)));
    }
    // Copy line
    SEQ_TWO_KEYS(KC_L, KC_C) {
      SEND_STRING(SS_TAP(X_HOME)SS_LSFT(SS_TAP(X_END))SS_LCTRL(SS_TAP(X_C)));
    }
    // Copy all
    SEQ_TWO_KEYS(KC_A, KC_C) {
      SEND_STRING(SS_LCTRL(SS_TAP(X_A)SS_TAP(X_C)));
    }
  }

  matrix_scan_keymap();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef KEYLOGGER_ENABLE
  xprintf("KL: row: %u, column: %u, pressed: %u\n", record->event.key.col, record->event.key.row, record->event.pressed);
#endif //KEYLOGGER_ENABLE

  return process_record_keymap(keycode, record);
}

// Any custom LED code goes here.
// Currently just proxies to `led_update_kb`
bool led_update_user(led_t led_state) {
  bool res = led_update_kb(led_state);
  return res;
}
