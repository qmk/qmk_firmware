/* Copyright 2018 Jarred Steenvoorden
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "jarred.h"
#include "version.h"

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

bool lowerPressed, raisePressed;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
    case LOWER:
    case RAISE:
      // Both lower and raise activate the same layer
      if (record->event.pressed) {
        layer_on(_LW);
      } else {
        layer_off(_LW);
      }
      
      // But keep track of each to active adjust layer
      if (keycode == LOWER) {
        lowerPressed = record->event.pressed;
      } else {
        raisePressed = record->event.pressed;
      }
      
      // When both are pressed, activate adjust
      if (lowerPressed && raisePressed) {
        layer_on(_NP);
      } else {
        layer_off(_NP);
      }
      
      break;
    
    case NUMPAD:
        if (record->event.pressed) {
          layer_on(_NP);
        } else {
          layer_off(_NP);
        }
        break;
    
    case NAVI:
      if (record->event.pressed) {
        layer_on(_NV);
      } else {
        layer_off(_NV);
        
        // Release mods set by ALT_TAB and CTL_TAB
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
      }
      break;
    
    case VRSN: // Prints firmware version
      if (record->event.pressed) {
        send_string_with_delay_P(PSTR(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION ", Built on: " QMK_BUILDDATE), MACRO_TIMER);
      }
      break;
      
    case ALT_TAB:
      if (record->event.pressed) {
        register_code(KC_LALT);
        tap_code(KC_TAB);
      }
      break;
      
    case CTL_TAB:
      if (record->event.pressed) {
        register_code(KC_LCTL);
        tap_code(KC_TAB);
      }
      break;
  }

  return process_record_keymap(keycode, record);
}
