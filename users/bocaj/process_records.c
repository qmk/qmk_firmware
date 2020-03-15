#include "bocaj.h"
#include QMK_KEYBOARD_H

uint16_t braces_timer;
bool is_hyper_active = false;

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

__attribute__ ((weak))
void matrix_scan_secrets(void) {}

// Defines actions tor my global custom keycodes. Defined in bocaj.h file
// Then runs the _keymap's record handler if not processed here
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CTL_FN1:
        if (!record->event.pressed) {
            register_code(KC_LCTRL);
            tap(KC_F1);
            unregister_code(KC_LCTRL);
        }
        break;
    case MC_PRNS:
        if (!record->event.pressed) {
            uint8_t temp_mod = get_mods();
            clear_mods();
            SEND_STRING("()");
            tap(KC_LEFT);
            set_mods(temp_mod);
        }
        break;
    case MC_BRCS:
        if (!record->event.pressed) {
            uint8_t temp_mod = get_mods();
            clear_mods();
            if (temp_mod & MODS_SHIFT_MASK) {
                SEND_STRING("{}");
            } else {
                SEND_STRING("[]");
            }
            tap(KC_LEFT);
            set_mods(temp_mod);
        }
        break;
    case MC_BPRN:
        if (!record->event.pressed) {
            uint8_t temp_mod = get_mods();
            clear_mods();
            SEND_STRING(")(");
            tap(KC_LEFT);
            set_mods(temp_mod);
        }
        break;
    case MC_BBRC:
        if (!record->event.pressed) {
            uint8_t temp_mod = get_mods();
            clear_mods();
            if (temp_mod & MODS_SHIFT_MASK) {
                SEND_STRING("}{");
            } else {
                SEND_STRING("][");
            }
            tap(KC_LEFT);
            set_mods(temp_mod);
        }
        break;
    case KC_MWRK:
      if (!record->event.pressed) {
        set_single_persistent_default_layer(_WORKMAN);
        #if (defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE) || defined(UCIS_ENABLE))
          set_unicode_input_mode(0);
        #endif
        layer_move(0);
        ergodox_blink_all_leds();
      }
      break;
    case KC_WWRK:
      if (!record->event.pressed) {
        set_single_persistent_default_layer(_WINWORKMAN);
        #if (defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE) || defined(UCIS_ENABLE))
          set_unicode_input_mode(4);
        #endif
        layer_move(0);
        ergodox_blink_all_leds();
      }
      break;
    case KC_MQWR:
      if (!record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
        #if (defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE) || defined(UCIS_ENABLE))
          set_unicode_input_mode(0);
        #endif
        layer_move(0);
        ergodox_blink_all_leds();
      }
      break;
    case KC_GAME:
      if (!record->event.pressed) {
        uint8_t temp_mod = get_mods();
        clear_mods();
        if (temp_mod & MODS_SHIFT_MASK) {
          layer_move(_DIABLO);
        } else {
          layer_move(_POE);
        }
        set_mods(temp_mod);
      }
      break;
    case MC_LOCK:
      if (!record->event.pressed) {
        layer_move(0);
        SEND_STRING(SS_LCTRL(SS_LGUI("q")));
      }
      break;
    case KC_MAKE:  // Compiles the firmware, and adds the flash command based on keyboard bootloader
      if (!record->event.pressed) {
        uint8_t temp_mod = get_mods();
        clear_mods();
        send_string_with_delay_P(PSTR("make " QMK_KEYBOARD ":" QMK_KEYMAP), MACRO_TIMER);
        send_string_with_delay_P(PSTR(SS_TAP(X_ENTER)), MACRO_TIMER);
        set_mods(temp_mod);
        layer_move(0);
      }
      break;
    case KC_DCLR:  // reset all Diablo timers, disabling them
#ifdef TAP_DANCE_ENABLE
      if (record->event.pressed) {
        uint8_t dtime;
        for (dtime = 0; dtime < 4; dtime++) {
          diablo_key_time[dtime] = diablo_times[0];
        }
      }
#endif // TAP_DANCE_ENABLE
      break;
    case JJ_ARRW:
      if (!record->event.pressed) {
        uint8_t temp_mod = get_mods();
        clear_mods();
        if (temp_mod & MODS_SHIFT_MASK) {
          SEND_STRING("=>");
        } else {
          SEND_STRING("->");
        }
        set_mods(temp_mod);
      }
      return false;
      break;
#ifdef UNICODE_ENABLE
    case UC_FLIP: // (ノಠ痊ಠ)ノ彡┻━┻
      if (record->event.pressed) {
        send_unicode_hex_string("0028 30CE 0CA0 75CA 0CA0 0029 30CE 5F61 253B 2501 253B");
      }
      break;
    case UC_TABL: // ┬─┬ノ( º _ ºノ)
      if (record->event.pressed) {
        send_unicode_hex_string("252C 2500 252C 30CE 0028 0020 00BA 0020 005F 0020 00BA 30CE 0029");
      }
      break;
    case UC_SHRG: // ¯\_(ツ)_/¯
      if (record->event.pressed) {
        send_unicode_hex_string("00AF 005C 005F 0028 30C4 0029 005F");
        SEND_STRING("/"); // Because Microsoft Teams sucks and uses UC_OSX+/ as the accessibility key
        send_unicode_hex_string("00AF");
      }
      break;
    case UC_DISA: // ಠ_ಠ
      if (record->event.pressed) {
        send_unicode_hex_string("0CA0 005F 0CA0");
      }
      break;
#endif
  }
  return process_record_keymap(keycode, record);
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

    // Mac copy line down (Leader -> d, d)
    SEQ_TWO_KEYS(KC_D, KC_D) {
      // Get to end of current line
      register_code(KC_LGUI);
      tap(KC_RIGHT);
      // Select to the beginning of the line
      register_code(KC_LSHIFT);
      tap(KC_LEFT);
      unregister_code(KC_LSHIFT);
      // Copy (LGUI is still held)
      tap(KC_C);
      // Back to the end
      tap(KC_RIGHT);
      unregister_code(KC_LGUI);
      // Make new line
      tap(KC_ENTER);
      // Paste
      SEND_STRING(SS_LGUI("v"));
    }

    // XCode one-hand run project (or browser refresh)
    SEQ_TWO_KEYS(KC_H, KC_R) {
      SEND_STRING(SS_LGUI("r"));
    }

    SEQ_ONE_KEY(KC_B) {
      SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION " ");
      tap(KC_ENTER);
      SEND_STRING ("Built at: " QMK_BUILDDATE);
    }

    // Good luck figuring out what these go to... ;)
    SEQ_TWO_KEYS(KC_J, KC_J) {
        SEND_STRING("jj@p.com");
        tap(KC_TAB);
    }
    SEQ_TWO_KEYS(KC_B, KC_B) {
        SEND_STRING("bc@p.com");
        tap(KC_TAB);
    }
    SEQ_TWO_KEYS(KC_Z, KC_Z) {
        SEND_STRING("Zz$1111111");
        tap(KC_ENTER);
    }
    SEQ_TWO_KEYS(KC_J, KC_P) {
        SEND_STRING("jp@p.com");
        tap(KC_TAB);
    }
    SEQ_TWO_KEYS(KC_T, KC_T) {
        SEND_STRING("Test123@123");
        tap(KC_ENTER);
    }
#ifndef NO_SECRETS
    matrix_scan_secrets();
#endif // !NO_SECRETS
  }

#ifdef TAP_DANCE_ENABLE  // Run Diablo 3 macro checking code.
  run_diablo_macro_check();
#endif // TAP_DANCE_ENABLE

  matrix_scan_keymap();
}
