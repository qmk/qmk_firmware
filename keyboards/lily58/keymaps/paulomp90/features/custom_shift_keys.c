/* Copyright 2023 Paulo Pereira
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

#include "custom_shift_keys.h"

bool process_custom_shift_keys(uint16_t keycode, keyrecord_t *record) {
  static uint16_t registered_keycode = KC_NO;

  // If a custom shift key is registered, then this event is either
  // releasing it or manipulating another key at the same time. Either way,
  // we release the currently registered key.
  if (registered_keycode != KC_NO) {
    unregister_code16(registered_keycode);
    registered_keycode = KC_NO;
  }

  if (record->event.pressed) {  // Press event.
    const uint8_t mods = get_mods();
#ifndef NO_ACTION_ONESHOT
    if ((mods | get_weak_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT) {
#else
    if ((mods | get_weak_mods()) & MOD_MASK_SHIFT) {  // Shift is held.
#endif  // NO_ACTION_ONESHOT
      // Continue default handling if this is a tap-hold key being held.
      if ((IS_QK_MOD_TAP(keycode) || IS_QK_LAYER_TAP(keycode)) &&
          record->tap.count == 0) {
        return true;
      }

      // Search for a custom shift key whose keycode is `keycode`.
      for (int i = 0; i < NUM_CUSTOM_SHIFT_KEYS; ++i) {
        if (keycode == custom_shift_keys[i].keycode) {
          registered_keycode = custom_shift_keys[i].shifted_keycode;
          if (IS_QK_MODS(registered_keycode) &&  // Should key be shifted?
              (QK_MODS_GET_MODS(registered_keycode) & MOD_LSFT) != 0) {
            register_code16(registered_keycode);  // If so, press directly.
          } else {
            // If not, cancel shift mods, press the key, and restore mods.
            del_weak_mods(MOD_MASK_SHIFT);
#ifndef NO_ACTION_ONESHOT
            del_oneshot_mods(MOD_MASK_SHIFT);
#endif  // NO_ACTION_ONESHOT
            unregister_mods(MOD_MASK_SHIFT);
            register_code16(registered_keycode);
            set_mods(mods);
          }
          return false;
        }
      }
    }
  }

  return true;  // Continue with default handling.
}
