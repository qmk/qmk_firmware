/* Copyright 2021 stevendlander
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
#include QMK_KEYBOARD_H

#ifndef NUMPAD_LAYER
#define NUMPAD_LAYER 1
#endif

#ifndef DISABLE_CUSTOM_NUMSLCK_KEYCODE

enum custom_keycodes {
    NUMSLCK = QK_USER_0, // Num Lock on shift, Scroll Lock regularly
};

// Mod key detection
#define MODS_SHIFT_MASK (MOD_BIT(KC_LSFT)|MOD_BIT(KC_RSFT))
#define MODS_ALT_MASK (MOD_BIT(KC_LALT)|MOD_BIT(KC_RALT))

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case NUMSLCK: {
            if (record->event.pressed) {
                if (keyboard_report->mods & MODS_SHIFT_MASK) {
                    tap_code(KC_NUM);
                } else {
                    register_code(KC_SCRL);
                }
            } else {
                unregister_code(KC_SCRL);
            }
            break;
        }
    }

    return process_record_user(keycode, record);
}

#endif

#ifndef DISABLE_NUMPAD_LAYER

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        static bool num_state = false;
        if (num_state != led_state.num_lock) {
            if (led_state.num_lock) {
                layer_on(NUMPAD_LAYER);
            } else { 
                layer_off(NUMPAD_LAYER);
            }
            num_state = led_state.num_lock;
        }

        led_update_ports(led_state);
    }
    return res;
}

#endif
