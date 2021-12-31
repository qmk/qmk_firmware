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
#include "altlocal_keys.h"
#include "tap_hold.h"
#include "locales.h"

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

__attribute__((weak)) bool process_record_secrets(uint16_t keycode, keyrecord_t *record) { return true; }


// Defines actions for my global custom keycodes. Defined in ericgebhart.h file
// Then runs the _keymap's record handier if not processed here
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed

#ifdef OLED_ENABLE
  process_record_user_oled(keycode, record);
#endif  // OLED

  if (!process_caps_word(keycode, record)) { return false; }
  if (!process_alt_local_key(keycode, record)) { return false; }
  process_tap_hold_user(keycode, record);

  if (process_record_keymap(keycode, record) && process_record_secrets(keycode, record)) {
    switch (keycode) {

      /*   // Handle the key translations for Dvorak on bepo. It's best if these are the first */
      /*   // enums after SAFE_RANGE. */
      /* case ALT_LOCAL_KEYS_START ... ALT_LOCAL_KEYS_END: */
      /*   if(record->event.pressed) */
      /*     send_keycode(keycode); */
      /*   unregister_code(keycode); */
      /*   break; */

      // Set the default layer. eeprom if shifted.
      // this relies on the order of the kc_enums and the enum for
      // the layers to match. This is for the KC_DVORAK type keycodes.
    case FIRST_LAYER ... END_OF_LAYERS:
      if (record->event.pressed) {
        uint8_t mods = mod_config(get_mods() | get_oneshot_mods());
        if (!mods) {
          default_layer_set(1UL << (keycode - FIRST_LAYER));
        } else if (mods & MOD_MASK_SHIFT) {
          set_single_persistent_default_layer(1UL << (keycode - FIRST_LAYER));
        }
      }
      break;

    case KC_SET_BASE:
      // set the current default base to eeprom.
      if (record->event.pressed) {
        set_single_persistent_default_layer(get_highest_layer(default_layer_state));
      }
      break;

      // choose a different set of default layers based on locales.
    case KC_NEXT_LOCALE:
      // choose another locale and set the default base to the first layer.
      if (!record->event.pressed) {
        if (current_locale + 1 < LOCALES_END){
          current_locale++;
        }else{
          current_locale = 0;
        }
        default_layer_set(1UL << LOCALE_LAYER_RANGE[0]);
      }
      return false;
      break;

      // choose a different base layer based on locales.
      // simply iterates over the list and sets the default layer.
    case KC_NEXT_BASE_LAYER:
      if (!record->event.pressed) {
        uint8_t current = get_highest_layer(default_layer_state);
        if (current < LOCALE_LAYER_RANGE[1]){
          current++;
        }else{
          current = LOCALE_LAYER_RANGE[0];
        }
        default_layer_set(1UL << current);
      }
      return false;
      break;

    case KC_RESET:
      if (!record->event.pressed) {
        reset_keyboard();
      }
      return false;
      break;

    case KC_SPACETEST:  // test something.
      // default_layer_set(1UL << _BEAKL);
      // tap_code16(LSFT(KC_SPACE));
      break;

      //#include "tap_hold.def"



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
