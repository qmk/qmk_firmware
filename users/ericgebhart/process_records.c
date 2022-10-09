/*
  Copyright 2018 Eric Gebhart <e.a.gebhart@gmail.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "ericgebhart.h"
#include "caps_word.h"
#include "g/keymap_combo.h"

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

__attribute__((weak)) bool process_record_secrets(uint16_t keycode, keyrecord_t *record) { return true; }


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

#ifdef OLED_ENABLE
  process_record_user_oled(keycode, record);
#endif  // OLED

  if (!process_caps_word(keycode, record)) { return false; }

  if (process_record_keymap(keycode, record) && process_record_secrets(keycode, record)) {
    switch (keycode) {

      // Handle the key translations for Dvorak on bepo. It's best if these are the first
      // enums after SAFE_RANGE.
    case DB_1 ... BB_QUOT:
      if(record->event.pressed)
        send_keycode(keycode);
      unregister_code(keycode);
      break;

      // Set the default layer. eeprom if shifted.
    case KC_DVORAK ... KC_BEPO:
      if (record->event.pressed) {
        uint8_t mods = mod_config(get_mods() | get_oneshot_mods());
        if (!mods) {
          default_layer_set(1UL << (keycode - KC_DVORAK));
        } else if (mods & MOD_MASK_SHIFT) {
          set_single_persistent_default_layer(1UL << (keycode - KC_DVORAK));
        }
      }
      break;


    case KC_RESET: // Custom RESET code
      if (!record->event.pressed) {
        reset_keyboard();
      }
      return false;
      break;

    case KC_SPACETEST:  // test something.
      // default_layer_set(1UL << _BEAKL);
      // tap_code16(LSFT(KC_SPACE));
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


      // Open on tap and Open with close and back arrow on hold.
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


#ifdef UNICODE_ENABLE
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
#endif
    }
  }
  return true;
}
