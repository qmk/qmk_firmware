#include "ericgebhart.h"
#include "caps_word.h"


__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

__attribute__((weak)) bool process_record_secrets(uint16_t keycode, keyrecord_t *record) { return true; }

// These keybards reverse the usual row column orientation of the key matrix
// Keylogging cares.
#if defined(KEYBOARD_ergodox_ez) || defined(KEYBOARD_keebio_iris_rev2)
#    define REVERSE_ROW_COL true
#endif

// Split keyboards need to trigger on key-up for edge-case issue
// record event.pressed is reversed (complement) for split keyboards
#ifndef SPLIT_KEYBOARD
#    define SPLIT_EVENT_COMP record->event.pressed
#else
#    define SPLIT_EVENT_COMP !record->event.pressed
#endif

uint16_t tap_taplong_timer;

inline void tap_taplong(uint16_t kc1, uint16_t kc2, keyrecord_t *record) {
  if (record->event.pressed) {
    tap_taplong_timer = timer_read();
  } else {
    if (timer_elapsed(tap_taplong_timer) > TAPPING_TERM) {
      tap_code16(kc2);
    } else {
      tap_code16(kc1);
    }
  }
}

/* for (){}[]""''<>``. tap for open. Hold for open and close, ending inbetween. */
/* Assumes a one character length.                                              */
inline void open_openclose(uint16_t kc1, uint16_t kc2, keyrecord_t *record) {
  if (record->event.pressed) {
    tap_taplong_timer = timer_read();
  }else{
    if (timer_elapsed(tap_taplong_timer) > TAPPING_TERM) {
      tap_code16(kc1);
      tap_code16(kc2);
      tap_code16(KC_LEFT);
    } else {
      tap_code16(kc1);
    }
  }
}

// Defines actions for my global custom keycodes. Defined in ericgebhart.h file
// Then runs the _keymap's record handier if not processed here
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed

#ifdef OLED_DRIVER_ENABLE
  process_record_user_oled(keycode, record);
#endif  // OLED

  if (!process_caps_word(keycode, record)) { return false; }

  if (process_record_keymap(keycode, record) && process_record_secrets(keycode, record)) {
    switch (keycode) {
      // Handle the key translations for Dvorak on bepo. It's best if these are the first
      // enums after SAFE_RANGE.
    case DB_1:
    case DB_2:
    case DB_3:
    case DB_4:
    case DB_5:
    case DB_6:
    case DB_7:
    case DB_8:
    case DB_9:
    case DB_0:
    case DB_GRV:
    case DB_SCOLON:
    case DB_SLASH:
    case DB_BACKSLASH:
    case DB_EQL:
    case DB_DOT:
    case DB_COMM:
    case DB_QUOT:
    case DB_MINUS:
    case DB_LPRN:
    case DB_RPRN:
    case DB_LBRC:
    case DB_RBRC:
    case BQ_COMM: // beakl on qwerty
    case BQ_DOT:
    case BQ_QUOT:
    case BB_COMM: // beakl on bepo
    case BB_DOT:
    case BB_QUOT:
      if(record->event.pressed)
        send_keycode(keycode);
      unregister_code(keycode);
      break;

    case KC_DVORAK ... KC_BEPO:
      if (record->event.pressed) {
        uint8_t mods = mod_config(get_mods() | get_oneshot_mods());
        if (!mods) {
          default_layer_set(keycode - KC_DVORAK);
        } else if (mods & MOD_MASK_SHIFT) {
          set_single_persistent_default_layer(keycode - KC_DVORAK);
          // } else if (mods & MOD_MASK_CTRL) {
          // set_single_persistent_default_layer(keycode - KC_DVORAK + 8);
        }
      }
      break;

    case KC_MAKE:  // Compiles the firmware, and adds the flash command based on keyboard bootloader
      if (!record->event.pressed) {
#               ifndef MAKE_BOOTLOADER
        uint8_t temp_mod = mod_config(get_mods());
        uint8_t temp_osm = mod_config(get_oneshot_mods());
        clear_mods();
        clear_oneshot_mods();
#               endif

        send_string_with_delay_P(PSTR("bin/qmk"), TAP_CODE_DELAY);

#               ifndef MAKE_BOOTLOADER
        if ((temp_mod | temp_osm) & MOD_MASK_SHIFT)
#               endif
          {
            send_string_with_delay_P(PSTR(" flash "), TAP_CODE_DELAY);
#               ifndef MAKE_BOOTLOADER
          } else {
          send_string_with_delay_P(PSTR(" compile "), TAP_CODE_DELAY);
#               endif
        }
        send_string_with_delay_P(PSTR("-kb " QMK_KEYBOARD " -km " QMK_KEYMAP), TAP_CODE_DELAY);

#               ifdef RGB_MATRIX_SPLIT_RIGHT
        send_string_with_delay_P(PSTR(" RGB_MATRIX_SPLIT_RIGHT=yes"), TAP_CODE_DELAY);

#                   ifndef OLED_DRIVER_ENABLE
        send_string_with_delay_P(PSTR(" OLED_DRIVER_ENABLE=no"), TAP_CODE_DELAY);
#                   endif
#               endif
        send_string_with_delay_P(PSTR(SS_TAP(X_ENTER)), TAP_CODE_DELAY);
      }

      break;



    case KC_RESET: // Custom RESET code
      if (!record->event.pressed) {
        reset_keyboard();
      }
      return false;
      break;


    case EPRM: // Resets EEPROM
      if (record->event.pressed) {
        eeconfig_init();
        default_layer_set(1UL<<eeconfig_read_default_layer());
        layer_state_set(layer_state);
      }
      return false;
      break;

      // tap or long tap for different key.
    case KC_CCCV:  // One key copy/paste
      tap_taplong(LCTL(KC_C), LCTL(KC_V), record);
      break;

    case BP_CCCV:  // One key copy/paste
      tap_taplong(LCTL(BP_C), LCTL(BP_V), record);
      break;

    case KC_CTCN:  // New TaB/Window
      tap_taplong(LCTL(KC_T), LCTL(KC_N), record);
      break;

    case BP_CTCN:  // New TaB/Window
      tap_taplong(LCTL(BP_T), LCTL(BP_N), record);
      break;

    case KC_CWCQ:  // Close Tab-window/Quit
      tap_taplong(LCTL(KC_W), LCTL(KC_Q), record);
      break;

    case BP_CWCQ:  // Close Tab-window/Quit
      tap_taplong(LCTL(BP_W), LCTL(BP_Q), record);
      break;

    case KC_XM_PORD:  // Xmonad scratch pads or desktop
      tap_taplong(LGUI(KC_E), LGUI(KC_T), record);
      break;

    case BP_XM_PORD:  // Xmonad scratch pads or desktop
      tap_taplong(LGUI(BP_E), LGUI(BP_T), record);
      break;

    case KC_OCPRN:
      open_openclose(KC_LPRN, KC_RPRN, record);
      break;

    case BP_OCPRN:
      open_openclose(DB_LPRN, DB_RPRN, record);
      break;

    case KC_OCBRC:
      open_openclose(KC_LBRC, KC_RBRC, record);
      break;

    case BP_OCBRC:
      open_openclose(KC_RBRC, KC_LBRC, record);
      break;

    case KC_OCCBR:
      open_openclose(KC_LCBR, KC_RCBR, record);
      break;

    case BP_OCCBR:
      open_openclose(BP_LCBR, BP_RCBR, record);
      break;

    case KC_OCDQUO:
      open_openclose(KC_DQUO, KC_DQUO, record);
      break;

    case BP_OCDQUO:
      open_openclose(BP_DQUO, BP_DQUO, record);
      break;

    case KC_OCQUOT:
      open_openclose(KC_QUOT, KC_QUOT, record);
      break;

    case BP_OCQUOT:
      open_openclose(BP_QUOT, BP_QUOT, record);
      break;

    case KC_OCGRV:
      open_openclose(KC_GRAVE, KC_GRAVE, record);
      break;

    case BP_OCGRV:
      open_openclose(BP_GRV, BP_GRV, record);
      break;

    case KC_OCLTGT:
      open_openclose(KC_LT, KC_GT, record);
      break;

    case BP_OCLTGT:
      open_openclose(BP_LDAQ, BP_RDAQ, record);
      break;




      //Turn shift backspace into delete.
      /* case KC_BSPC: */
      /*   { */
      /*     // Initialize a boolean variable that keeps track */
      /*     // of the delete key status: registered or not? */
      /*     static bool delkey_registered; */
      /*     if (record->event.pressed) { */
      /*       uint8_t mod_state = get_mods(); */
      /*       // Detect the activation of either shift keys */
      /*       if (mod_state & MOD_MASK_SHIFT) { */
      /*         // First temporarily canceling both shifts so that */
      /*         // shift isn't applied to the KC_DEL keycode */
      /*         del_mods(MOD_MASK_SHIFT); */
      /*         register_code(KC_DEL); */
      /*         // Update the boolean variable to reflect the status of KC_DEL */
      /*         delkey_registered = true; */
      /*         // Reapplying modifier state so that the held shift key(s) */
      /*         // still work even after having tapped the Backspace/Delete key. */
      /*         set_mods(mod_state); */
      /*         return false; */
      /*       } */
      /*     } else { // on release of KC_BSPC */
      /*       // In case KC_DEL is still being sent even after the release of KC_BSPC */
      /*       if (delkey_registered) { */
      /*         unregister_code(KC_DEL); */
      /*         delkey_registered = false; */
      /*         return false; */
      /*       } */
      /*     } */
      /*     // Let QMK process the KC_BSPC keycode as usual outside of shift */
      /*     return true; */
      /*   } */


#       ifdef UNICODE_ENABLE
    case UC_FLIP:  // (ノಠ痊ಠ)ノ彡┻━┻
      if (record->event.pressed) {
        send_unicode_string("(ノಠ痊ಠ)ノ彡┻━┻");
      }
      break;
    case UC_TABL:  // ┬─┬ノ( º _ ºノ)
      if (record->event.pressed) {
        send_unicode_string("┬─┬ノ( º _ ºノ)");
      }
      break;
    case UC_SHRG:  // ¯\_(ツ)_/¯
      if (record->event.pressed) {
        send_unicode_string("¯\\_(ツ)_/¯");
      }
      break;
    case UC_DISA:  // ಠ_ಠ
      if (record->event.pressed) {
        send_unicode_string("ಠ_ಠ");
      }
      break;
#       endif
    }
  }
  return true;
}
