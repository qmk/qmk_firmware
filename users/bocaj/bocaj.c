#include "bocaj.h"
#include "eeprom.h"
#include "version.h"
#include "tap_dances.h"

static uint16_t copy_paste_timer;
userspace_config_t userspace_config;

/* *** *** *** ***  *
 * Helper Functions *
 * *** *** *** ***  */
void tap(uint16_t keycode){ register_code(keycode); unregister_code(keycode); };

// Add reconfigurable functions here, for keymap customization
// This allows for a global, userspace functions, and continued
// customization of the keymap.  Use _keymap instead of _user
// functions in the keymaps
__attribute__ ((weak))
void matrix_init_keymap(void) {}

__attribute__ ((weak))
void startup_keymap(void) {}

__attribute__ ((weak))
void suspend_power_down_keymap(void) {}

__attribute__ ((weak))
void suspend_wakeup_init_keymap(void) {}

__attribute__ ((weak))
void matrix_scan_keymap(void) {}

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

__attribute__ ((weak))
bool process_record_secrets(uint16_t keycode, keyrecord_t *record) {
  return true;
}


__attribute__ ((weak))
uint32_t layer_state_set_keymap (uint32_t state) {
  return state;
}

__attribute__ ((weak))
uint32_t default_layer_state_set_keymap (uint32_t state) {
  return state;
}

__attribute__ ((weak))
void led_set_keymap(uint8_t usb_led) {}

// Call user matrix init, set default RGB colors and then
// call the keymap's init function
void matrix_init_user(void) {
  userspace_config.raw = eeprom_read_byte(EECONFIG_USERSPACE);
  matrix_init_keymap();
}

void startup_user (void) {
  startup_keymap();
}

void suspend_power_down_user(void)
{
    suspend_power_down_keymap();
}

void suspend_wakeup_init_user(void)
{
  suspend_wakeup_init_keymap();
  #ifdef KEYBOARD_ergodox_ez
  wait_ms(10);
  #endif
}

LEADER_EXTERNS();
// No global matrix scan code, so just run keymap's matrix
// scan function
void matrix_scan_user(void) {
  static bool has_ran_yet;
  if (!has_ran_yet) {
    has_ran_yet = true;
    startup_user();
  }
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    // Mac Save (Leader -> s)
    SEQ_ONE_KEY(KC_S) {
      SEND_STRING(SS_LGUI("s"));
    }

    // Mac copy line down (Leader -> d, d)
    SEQ_TWO_KEYS(KC_D, KC_D) {
      register_code(KC_LSHIFT);
      register_code(KC_HOME);
      unregister_code(KC_HOME);
      unregister_code(KC_LSHIFT);
      SEND_STRING(SS_LGUI("c"));
      tap(KC_END);
      tap(KC_ENTER);
      SEND_STRING(SS_LGUI("v"));
    }

    // Mac copy line up (Leader -> u, u)
    SEQ_TWO_KEYS(KC_U, KC_U) {
      register_code(KC_LSHIFT);
      register_code(KC_HOME);
      unregister_code(KC_HOME);
      unregister_code(KC_LSHIFT);
      SEND_STRING(SS_LGUI("c"));
      tap(KC_UP);
      tap(KC_END);
      tap(KC_ENTER);
      SEND_STRING(SS_LGUI("v"));
    }

    // Mac VS Debug
    SEQ_ONE_KEY(KC_D) {
      tap(KC_F5);
    }

    // Mac VS Stop Debug
    SEQ_TWO_KEYS(KC_S, KC_D) {
      register_code(KC_LSHIFT);
      tap(KC_F5);
      unregister_code(KC_LSHIFT);
    }

    // Start Diablo 3
    SEQ_ONE_KEY(KC_3) {
      SEND_STRING(SS_LCTRL(" "));
      SEND_STRING("Diablo");
      tap(KC_ENTER);
    }

    SEQ_ONE_KEY(KC_B) {
      SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      tap(KC_ENTER);
      SEND_STRING ("Built at: " QMK_BUILDDATE " - File Location: " __BASE_FILE__);
      tap(KC_ENTER);
#ifndef __UNIX__
      SEND_STRING ("Probably compiled on Home PC");
#else
      SEND_STRING ("Probably compiled on Work Laptop");
#endif
    }
  }

#ifdef TAP_DANCE_ENABLE  // Run Diablo 3 macro checking code.
  run_diablo_macro_check();
#endif // TAP_DANCE_ENABLE

  matrix_scan_keymap();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  /* uint8_t default_layer = 0;
  default_layer = eeconfig_read_default_layer(); */
  switch (keycode) {
    case JJ_COPY:
      if (!record->event.pressed) {
        SEND_STRING(SS_LGUI("c"));
      }
      return false;
      break;
    case JJ_PSTE:
      if (!record->event.pressed) {
        SEND_STRING(SS_LGUI("v"));
      }
      return false;
      break;
    case JJ_ARRW:
      if (!record->event.pressed) {
        SEND_STRING("->");
      }
      return false;
      break;
    case KC_DCLR:
#ifdef TAP_DANCE_ENABLE
      if (record->event.pressed) {
        uint8_t dtime;
        for (dtime = 0; dtime < 4; dtime++) {
          diablo_key_time[dtime] = diablo_times[0];
        }
      }
#endif // !TAP_DANCE_ENABLE
      return false;
      break;
    case KC_CCCV:
      if (record->event.pressed) {
        copy_paste_timer = timer_read();
      } else {
        if (timer_elapsed(copy_paste_timer) > TAPPING_TERM) { // Hold, copy
          SEND_STRING(SS_LGUI("c"));
        } else {
          SEND_STRING(SS_LGUI("v"));
        }
      }
      return false;
      break;
  }
  return process_record_keymap(keycode, record);
}
