#include "bocaj.h"
#include QMK_KEYBOARD_H

uint16_t copy_paste_timer;
uint16_t grave_layer_timer;
uint16_t heal_layer_timer;

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

// Defines actions tor my global custom keycodes. Defined in bocaj.h file
// Then runs the _keymap's record handler if not processed here
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
/*     case KC_MWRK:
      if (!record->event.pressed) {
        set_single_persistent_default_layer(_WORKMAN);
#if (defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE) || defined(UCIS_ENABLE))
        BOCAJ_UNICODE_MODE = 0;
#endif
        layer_move(0);
        ergodox_blink_all_leds();
      }
      break;
    case KC_WWRK:
      if (!record->event.pressed) {
        set_single_persistent_default_layer(_WINWORKMAN);
#if (defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE) || defined(UCIS_ENABLE))
        BOCAJ_UNICODE_MODE = 4;
#endif
        layer_move(0);
        ergodox_blink_all_leds();
      }
      break;
    case KC_MQWR:
      if (!record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
#if (defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE) || defined(UCIS_ENABLE))
        BOCAJ_UNICODE_MODE = 0;
#endif
        layer_move(0);
        ergodox_blink_all_leds();
      }
      break; */
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
        send_string_with_delay_P(PSTR("make " QMK_KEYBOARD ":" QMK_KEYMAP), 10);
        if (temp_mod & MODS_SHIFT_MASK) {
          #if defined(BOOTLOADER_HALFKAY)
            send_string_with_delay_P(PSTR(":teensy"), 10);
          #endif // bootloader options
        }
        if (temp_mod & MODS_CTRL_MASK) { send_string_with_delay_P(PSTR(" -j8 --output-sync"), 10); }
        send_string_with_delay_P(PSTR(SS_TAP(X_ENTER)), 10);
        set_mods(temp_mod);
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
        SEND_STRING("->");
      }
      return false;
      break;
    case LM_GRAVE:
      if (record->event.pressed) {
        grave_layer_timer = timer_read();
      } else {
        if (timer_elapsed(grave_layer_timer) < TAPPING_TERM) {
          uint8_t temp_mod = get_mods();
          uint8_t one_shot = get_oneshot_mods();
          clear_mods();
          if (temp_mod & MODS_SHIFT_MASK || one_shot & MODS_SHIFT_MASK) {
            register_code(KC_LSFT);
            tap(KC_GRAVE);
            unregister_code(KC_LSFT);
          } else {
            tap(KC_GRAVE);
          }
          set_mods(temp_mod);
        } else {
          layer_move(0);
        }
      }
      return false;
      break;
    case LM_DFLT:
      if (record->event.pressed) {
        heal_layer_timer = timer_read();
        if (timer_elapsed(heal_layer_timer) > TAPPING_TERM) {
          layer_on(0);
        }
      } else {
        if (timer_elapsed(heal_layer_timer) < TAPPING_TERM) {
            tap(KC_Q);
        } else {
          layer_off(0);
        }
      }
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
        send_unicode_hex_string("00AF 005C 005F 0028 30C4 0029 005F 002F 00AF");
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
