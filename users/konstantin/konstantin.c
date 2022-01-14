/* Copyright 2019-2021 Konstantin Đorđević <vomindoraan@gmail.com>
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

#include "konstantin.h"

__attribute__((weak))
void keyboard_pre_init_keymap(void) {}

void keyboard_pre_init_user(void) {
    keyboard_pre_init_keymap();
}

__attribute__((weak))
void eeconfig_init_keymap(void) {}

void eeconfig_init_user(void) {
    eeconfig_init_keymap();
}

__attribute__((weak))
void keyboard_post_init_keymap(void) {}

void keyboard_post_init_user(void) {
    keyboard_post_init_keymap();
}

__attribute__((weak))
layer_state_t layer_state_set_keymap(layer_state_t state) {
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    state = layer_state_set_keymap(state);

#ifdef LAYER_NUMPAD
    bool numpad = IS_LAYER_ON_STATE(state, L_NUMPAD);
    bool num_lock = IS_HOST_LED_ON(USB_LED_NUM_LOCK);
    if (numpad != num_lock) {
        tap_code(KC_NLCK);  // Toggle Num Lock to match Numpad layer state
    }
#endif

    return state;
}

__attribute__((weak))
void led_set_keymap(uint8_t usb_led) {}

void led_set_user(uint8_t usb_led) {
    led_set_keymap(usb_led);
}

__attribute__((weak))
bool led_update_keymap(led_t led_state) {
    return true;
}

bool led_update_user(led_t led_state) {
    return led_update_keymap(led_state);
}

__attribute__((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_keymap(keycode, record)) {
        return false;
    }

    switch (keycode) {
        uint16_t kc;
#ifdef LAYER_FN
        static bool fn_lock = false;

    case FNLK:
        if (record->event.pressed) {
            fn_lock = !IS_LAYER_ON(L_FN);  // Fn layer will be toggled after this
        }
        break;

    case FN_FNLK:
        if (record->event.pressed && record->tap.count == TAPPING_TOGGLE) {
            fn_lock = !IS_LAYER_ON(L_FN);
        }
        break;
#endif

    case KC_ESC:
        if (record->event.pressed) {
#ifdef LAYER_NUMPAD  // Disable Numpad layer before Fn layer
            if (IS_LAYER_ON(L_NUMPAD)) {
                layer_off(L_NUMPAD);
                return false;
            }
#endif
#ifdef LAYER_FN
            if (IS_LAYER_ON(L_FN) && fn_lock) {
                layer_off(L_FN);
                return fn_lock = false;
            }
#endif
        }
        break;

    case CLEAR:
        if (record->event.pressed) {
            CLEAN_MODS(
                SEND_STRING(SS_LCTL("a") SS_TAP(X_DELETE));
            )
        }
        break;

    case DST_P_R:
        kc = (get_mods() & DST_MOD_MASK) ? DST_REM : DST_PRV;
        CLEAN_MODS(
            (record->event.pressed ? register_code16 : unregister_code16)(kc);
        )
        break;

    case DST_N_A:
        kc = (get_mods() & DST_MOD_MASK) ? DST_ADD : DST_NXT;
        CLEAN_MODS(
            (record->event.pressed ? register_code16 : unregister_code16)(kc);
        )
        break;
    }

    return true;
}
