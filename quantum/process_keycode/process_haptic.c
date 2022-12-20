/* Copyright 2021 QMK
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
#include "haptic.h"
#include "process_haptic.h"
#include "quantum_keycodes.h"
#include "action_tapping.h"
#include "usb_device_state.h"

__attribute__((weak)) bool get_haptic_enabled_key(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
#ifdef NO_HAPTIC_MOD
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            if (record->tap.count == 0) return false;
            break;
        case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
            if (record->tap.count != TAPPING_TOGGLE) return false;
            break;
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            if (record->tap.count == 0) return false;
            break;
        case KC_LEFT_CTRL ... KC_RIGHT_GUI:
        case QK_MOMENTARY ... QK_MOMENTARY_MAX:
        case QK_LAYER_MOD ... QK_LAYER_MOD_MAX:
#endif
#ifdef NO_HAPTIC_ALPHA
        case KC_A ... KC_Z:
#endif
#ifdef NO_HAPTIC_PUNCTUATION
        case KC_ENTER:
        case KC_ESCAPE:
        case KC_BACKSPACE:
        case KC_SPACE:
        case KC_MINUS:
        case KC_EQUAL:
        case KC_LEFT_BRACKET:
        case KC_RIGHT_BRACKET:
        case KC_BACKSLASH:
        case KC_NONUS_HASH:
        case KC_SEMICOLON:
        case KC_QUOTE:
        case KC_GRAVE:
        case KC_COMMA:
        case KC_SLASH:
        case KC_DOT:
        case KC_NONUS_BACKSLASH:
#endif
#ifdef NO_HAPTIC_LOCKKEYS
        case KC_CAPS_LOCK:
        case KC_SCROLL_LOCK:
        case KC_NUM_LOCK:
#endif
#ifdef NO_HAPTIC_NAV
        case KC_PRINT_SCREEN:
        case KC_PAUSE:
        case KC_INSERT:
        case KC_DELETE:
        case KC_PAGE_DOWN:
        case KC_PAGE_UP:
        case KC_LEFT:
        case KC_UP:
        case KC_RIGHT:
        case KC_DOWN:
        case KC_END:
        case KC_HOME:
#endif
#ifdef NO_HAPTIC_NUMERIC
        case KC_1 ... KC_0:
#endif
            return false;
    }
    return true;
}

bool process_haptic(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case QK_HAPTIC_ON:
                haptic_enable();
                break;
            case QK_HAPTIC_OFF:
                haptic_disable();
                break;
            case QK_HAPTIC_TOGGLE:
                haptic_toggle();
                break;
            case QK_HAPTIC_RESET:
                haptic_reset();
                break;
            case QK_HAPTIC_FEEDBACK_TOGGLE:
                haptic_feedback_toggle();
                break;
            case QK_HAPTIC_BUZZ_TOGGLE:
                haptic_buzz_toggle();
                break;
            case QK_HAPTIC_MODE_NEXT:
                haptic_mode_increase();
                break;
            case QK_HAPTIC_MODE_PREVIOUS:
                haptic_mode_decrease();
                break;
            case QK_HAPTIC_DWELL_UP:
                haptic_dwell_increase();
                break;
            case QK_HAPTIC_DWELL_DOWN:
                haptic_dwell_decrease();
                break;
            case QK_HAPTIC_CONTINUOUS_TOGGLE:
                haptic_toggle_continuous();
                break;
            case QK_HAPTIC_CONTINUOUS_UP:
                haptic_cont_increase();
                break;
            case QK_HAPTIC_CONTINUOUS_DOWN:
                haptic_cont_decrease();
                break;
        }
    }

    if (haptic_get_enable() && ((!HAPTIC_OFF_IN_LOW_POWER) || (usb_device_state == USB_DEVICE_STATE_CONFIGURED))) {
        if (record->event.pressed) {
            // keypress
            if (haptic_get_feedback() < 2 && get_haptic_enabled_key(keycode, record)) {
                haptic_play();
            }
        } else {
            // keyrelease
            if (haptic_get_feedback() > 0 && get_haptic_enabled_key(keycode, record)) {
                haptic_play();
            }
        }
    }

    return true;
}
