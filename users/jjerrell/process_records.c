/**
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright (C) 2021 Jerrell, Jacob <@jjerrell>
 * 
 * This file is part of qmk_firmware.
 * 
 * qmk_firmware is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * qmk_firmware is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with qmk_firmware.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "jjerrell.h"
#include <print.h>

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }
__attribute__((weak)) bool process_record_secrets(uint16_t keycode, keyrecord_t *record) { return true; }
__attribute__((weak)) bool process_record_user_rgb_matrix(uint16_t keycode, keyrecord_t *record) { return true; }

/**
 * This checks the keymap function first in case a userspace keycode needs overridden.
 * Then it checks secrets (default `true` if disabled), rgb (default true if disabled).
 * If all 3 methods return true, the keycodes implemented here will be checked.
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (process_record_keymap(keycode, record) 
            && process_record_secrets(keycode, record)
            && process_record_user_rgb_matrix(keycode, record)) {
        uint8_t mods = get_mods(); // Store modifiers
        clear_mods(); // Clear them so they don't mess with strings sent below

        switch (keycode) {
            case KC_ARROW:
                if (!record->event.pressed) {
                    send_string_with_delay_P(PSTR("->"), TAP_CODE_DELAY);
                }
                return false;
                break;
            case KC_MAKE:
                if (!record->event.pressed) {
                    send_string_with_delay_P(PSTR("qmk compile "), TAP_CODE_DELAY);
                    send_string_with_delay_P(PSTR("-kb " QMK_KEYBOARD), TAP_CODE_DELAY);
                    send_string_with_delay_P(PSTR(SS_TAP(X_ENTER)), TAP_CODE_DELAY);
                } 
                return false;
                break;
            case KC_QWERTY:
                if (!record->event.pressed) {
                    set_single_persistent_default_layer(_QWERTY);
                }
                return false;
                break;
            case KC_WORKMAN:
                if (!record->event.pressed) {
                    set_single_persistent_default_layer(_WORKMAN);
                }
                return false;
                break;
            case KC_VRSN:
                if (!record->event.pressed) {
                    send_string_with_delay_P(PSTR(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION ", Built on: " QMK_BUILDDATE), TAP_CODE_DELAY);
                }
                return false;
                break;
            case RGB_IDL:
                if (!record->event.pressed) {
                    userspace_config.rgb_layer_change ^= 1;
                    dprintf("rgblight layer change [EEPROM]: %u\n", userspace_config.rgb_layer_change);
                    eeconfig_update_user(userspace_config.raw);
                    if (userspace_config.rgb_layer_change) {
                        rgblight_enable_noeeprom();
                        layer_state_set(layer_state);  // This is needed to immediately set the layer color (looks better)
                    } else {
                        rgblight_disable_noeeprom();
                    }
                }
                return false;
                break;
            case RGB_TOG:
                if (!record->event.pressed) {
#    if defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_KEYCODES)
                    rgb_matrix_toggle();
#    endif
                }
                return false;
                break;
        }
        set_mods(mods); // Restore the held modifiers
    }
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif
    // No custom keycodes were recorded (or they didn't return false)
    return true;
}
