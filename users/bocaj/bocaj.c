/*
Copyright 2018 Jacob Jerrell <jacob.jerrell@gmail.com> @JacobJerrell

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

#include "bocaj.h"

userspace_config_t userspace_config;
#if (defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE) || defined(UCIS_ENABLE))
  #define BOCAJ_UNICODE_MODE UC_OSX
#else
  // set to 2 for UC_WIN, set to 4 for UC_WINC
  #define BOCAJ_UNICODE_MODE 2
#endif

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

// __attribute__ ((weak))
// void matrix_scan_secrets(void) {}

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
  userspace_config.raw = eeconfig_read_user();

  #if (defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE) || defined(UCIS_ENABLE))
    set_unicode_input_mode(BOCAJ_UNICODE_MODE);
    get_unicode_input_mode();
  #endif //UNICODE_ENABLE


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

void eeconfig_init_user(void) {
  userspace_config.raw = 0;
  eeconfig_update_user(userspace_config.raw);
  #if (defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE) || defined(UCIS_ENABLE))
    set_unicode_input_mode(BOCAJ_UNICODE_MODE);
    get_unicode_input_mode();
  #else
    eeprom_update_byte(EECONFIG_UNICODEMODE, BOCAJ_UNICODE_MODE);
  #endif
}

// LEADER_EXTERNS();
// // No global matrix scan code, so just run keymap's matrix
// // scan function
// void matrix_scan_user(void) {
//     if(is_hyper_active) {
//         if (timer_elapsed(braces_timer) > 100) {
//             unregister_code(KC_LALT);
//             unregister_code(KC_LSFT);
//             unregister_code(KC_LCTL);
//             unregister_code(KC_LGUI);
//             is_hyper_active = false;
//         }
//     }
//   static bool has_ran_yet;
//   if (!has_ran_yet) {
//     has_ran_yet = true;
//     startup_user();
//   }
//   LEADER_DICTIONARY() {
//     leading = false;
//     leader_end();

//     // Mac copy line down (Leader -> d, d)
//     SEQ_TWO_KEYS(KC_D, KC_D) {
//       // Get to end of current line
//       register_code(KC_LGUI);
//       tap(KC_RIGHT);
//       // Select to the beginning of the line
//       register_code(KC_LSHIFT);
//       tap(KC_LEFT);
//       unregister_code(KC_LSHIFT);
//       // Copy (LGUI is still held)
//       tap(KC_C);
//       // Back to the end
//       tap(KC_RIGHT);
//       unregister_code(KC_LGUI);
//       // Make new line
//       tap(KC_ENTER);
//       // Paste
//       SEND_STRING(SS_LGUI("v"));
//     }

//     // XCode one-hand run project (or browser refresh)
//     SEQ_TWO_KEYS(KC_H, KC_R) {
//       SEND_STRING(SS_LGUI("r"));
//     }

//     SEQ_TWO_KEYS(KC_V, KC_S) {
//       register_code(KC_LGUI);
//       tap(KC_SPACE);
//       unregister_code(KC_LGUI);
//       send_string_with_delay_P(PSTR("vsc"), MACRO_TIMER);
//       tap(KC_ENTER);
//     }

//     SEQ_TWO_KEYS(KC_X, KC_C) {
//       register_code(KC_LGUI);
//       tap(KC_SPACE);
//       unregister_code(KC_LGUI);
//       send_string_with_delay_P(PSTR("xcode"), MACRO_TIMER);
//       tap(KC_ENTER);
//     }

//     SEQ_ONE_KEY(KC_B) {
//       SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION " ");
//       tap(KC_ENTER);
//       SEND_STRING ("Built at: " QMK_BUILDDATE);
//     }
// #ifndef NO_SECRETS
//     matrix_scan_secrets();
// #endif // !NO_SECRETS
//   }

// #ifdef TAP_DANCE_ENABLE  // Run Diablo 3 macro checking code.
//   run_diablo_macro_check();
// #endif // TAP_DANCE_ENABLE

//   matrix_scan_keymap();
// }
