/* Copyright 2019
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
#include "process_haptic.h"

__attribute__((weak)) bool get_haptic_enabled_key(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
#    ifdef NO_HAPTIC_MOD
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            if (record->tap.count == 0) return false;
            break;
        case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
            if (record->tap.count != TAPPING_TOGGLE) return false;
            break;
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            if (record->tap.count == 0) return false;
            break;
        case KC_LCTRL ... KC_RGUI:
        case QK_MOMENTARY ... QK_MOMENTARY_MAX:
#    endif
#    ifdef NO_HAPTIC_FN
        case KC_FN0 ... KC_FN31:
#    endif
#    ifdef NO_HAPTIC_ALPHA
        case KC_A ... KC_Z:
#    endif
#    ifdef NO_HAPTIC_PUNCTUATION
        case KC_ENTER:
        case KC_ESCAPE:
        case KC_BSPACE:
        case KC_SPACE:
        case KC_MINUS:
        case KC_EQUAL:
        case KC_LBRACKET:
        case KC_RBRACKET:
        case KC_BSLASH:
        case KC_NONUS_HASH:
        case KC_SCOLON:
        case KC_QUOTE:
        case KC_GRAVE:
        case KC_COMMA:
        case KC_SLASH:
        case KC_DOT:
        case KC_NONUS_BSLASH:
#    endif
#    ifdef NO_HAPTIC_LOCKKEYS
        case KC_CAPSLOCK:
        case KC_SCROLLLOCK:
        case KC_NUMLOCK:
#    endif
#    ifdef NO_HAPTIC_NAV
        case KC_PSCREEN:
        case KC_PAUSE:
        case KC_INSERT:
        case KC_DELETE:
        case KC_PGDOWN:
        case KC_PGUP:
        case KC_LEFT:
        case KC_UP:
        case KC_RIGHT:
        case KC_DOWN:
        case KC_END:
        case KC_HOME:
#    endif
#    ifdef NO_HAPTIC_NUMERIC
        case KC_1 ... KC_0:
#    endif
         return false;
    }
    return true;
}

bool process_haptic(uint16_t keycode, keyrecord_t *record) {
    if (keycode == HPT_ON && record->event.pressed) {
        haptic_enable();
    }
    if (keycode == HPT_OFF && record->event.pressed) {
        haptic_disable();
    }
    if (keycode == HPT_TOG && record->event.pressed) {
        haptic_toggle();
    }
    if (keycode == HPT_RST && record->event.pressed) {
        haptic_reset();
    }
    if (keycode == HPT_FBK && record->event.pressed) {
        haptic_feedback_toggle();
    }
    if (keycode == HPT_BUZ && record->event.pressed) {
        haptic_buzz_toggle();
    }
    if (keycode == HPT_MODI && record->event.pressed) {
        haptic_mode_increase();
    }
    if (keycode == HPT_MODD && record->event.pressed) {
        haptic_mode_decrease();
    }
    if (keycode == HPT_DWLI && record->event.pressed) {
        haptic_dwell_increase();
    }
    if (keycode == HPT_DWLD && record->event.pressed) {
        haptic_dwell_decrease();
    }
    if (keycode == HPT_CONT && record->event.pressed) {
        haptic_toggle_continuous();
    }
    if (keycode == HPT_CONI && record->event.pressed) {
        haptic_cont_increase();
    }
    if (keycode == HPT_COND && record->event.pressed) {
        haptic_cont_decrease();
    }

    if (haptic_get_enable()) {
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
