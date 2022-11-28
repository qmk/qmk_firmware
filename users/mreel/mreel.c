/*
Copyright 2022 Tibo Loete, aka Mister Eel <mistermister1111@hotmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#include "mreel.h"
#include "custom_keycodes.h"
#include "unicode.h"
#include "mac_win_parity.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_TAB:
        case KC_LCTL:
        case KC_Q:
            if (layer_state_is(_WIN)) {
                return process_record_parity(keycode, record);
            }
            return true;

        case UC_UCIS:                                           // Start UCIS Unicode input
            if (record->event.pressed) {
                if (!layer_state_is(_WIN)) {tap_code16(C(LOPT(KC_BSLS)));} // 1↓
                qk_ucis_start();
            }
            return false;

        case UC_TRMI ... UC_COL:                                // Unicodemap keycodes
            if (record->event.pressed) {
                if (!layer_state_is(_WIN)) {tap_code16(C(LOPT(KC_BSLS)));} // 1↓
                process_record_unicodemap(keycode, record);
            }
            return true;

        case CK_BWRD ... CK_FLSH:                               // Custom keycodes (often to have different behaviour on windows/macos with a single keycode)
            if (record->event.pressed) {
                process_record_custom_key(keycode, record);
            }
            return true;
    }
    return true;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case UC_TRMI ... UC_COL:
    if (record->event.pressed) {
        if (!layer_state_is(_WIN)) {tap_code16(C(LOPT(KC_BSLS)));} // 2↓
    }
  }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    if (IS_LAYER_ON(_WIN)) {
        set_unicode_input_mode(UC_WINC); // 3↓
    } else {
        set_unicode_input_mode(UC_MAC); // 3↓
    }
  return state;
}

// 1: Switch to unicode hex input on macos
// 2: Switch back to normal input on macos
// 3: Synchronise unicode input and win/macos layer
