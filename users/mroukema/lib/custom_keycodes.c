/*
Copyright 2023 @mroukema

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

#include "custom_keycodes.h"

void _handle_custom_shifted_key(keyrecord_t *record, uint16_t base_keycode, uint16_t shifted_code) {
    if (record->event.pressed) {
        if (get_mods() & MOD_BIT(KC_LSFT) || get_mods() & MOD_BIT(KC_RSFT)) {
            int shift_mod = get_mods() & (MOD_MASK_SHIFT);
            del_mods(shift_mod);
            register_code16(shifted_code);
            add_mods(shift_mod);
        } else {
            register_code16(base_keycode);
        }
    } else {
        unregister_code16(shifted_code);
        unregister_code16(base_keycode);
    }
}

bool handle_custom_shifted_key(keyrecord_t *record, uint16_t base_keycode, uint16_t shifted_code) {
    _handle_custom_shifted_key(record, base_keycode, shifted_code);
    return false;
}

/*
 * Create funtion to handle keypress events for custom keys
 * This will need to be called from your process_record_user(...) in keymap.c
 *
 *  bool process_record_user(uint16_t keycode, keyrecord_t *record) {
 *      switch (keycode) {
 *          case: ...   // catch any cases you want to handle yourself
 *          default:    // all other keycodes can be passed along to process_custom_shifted_keys
 *             return process_custom_shifted_keys(keycode, record);
 *      }
 * };
 */
#define CUSTOM_KEYCODE BLANK
#define CUSTOM_SHIFTABLE_KEYCODE CSK_PROG
#define CUSTOM_SHIFTABLE_MOD_KEYCODE CSMK_PROG
bool process_custom_shifted_keys(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
#include "users/mroukema/defs/custom_keycodes.def"
    }
    return true;
}
#undef CUSTOM_SHIFTABLE_KEYCODE
#undef CUSTOM_SHIFTABLE_MOD_KEYCODE
#undef CUSTOM_KEYCODE
