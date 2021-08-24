/* Copyright 2021 Joshua T.
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

#include "caps_word.h"

static bool is_caps_word_on = false;

bool is_caps_word_enabled(void) {
    return is_caps_word_on;
}

void enable_caps_word(void) {
    if (is_caps_word_on) return;
    is_caps_word_on = true;
    tap_code(KC_CAPS);
}

void disable_caps_word(void) {
    if (!is_caps_word_on) return;
    is_caps_word_on = false;
    tap_code(KC_CAPS);
}

void toggle_caps_word(void) {
    if (is_caps_word_on) {
        disable_caps_word();
    }
    else {
        enable_caps_word();
    }
}

bool should_terminate_caps_word(uint16_t keycode, const keyrecord_t *record) {
    switch (keycode) {
        // Keycodes which should not disable caps word mode
        case KC_A ... KC_Z:
        case KC_1 ... KC_0:
        case KC_MINS:
        case KC_UNDS:
        case KC_BSPC:
            return false;

        default:
            if (record->event.pressed) {
                return true;
            }
            return false;
    }

    // Should be unreachable
    return false;
}


bool process_record_caps_word(uint16_t keycode, const keyrecord_t *record) {
    // Nothing in this function acts on key release
    if (!record->event.pressed) {
        return true;
    }

    // Handle the custom keycodes that go with this feature
    if (keycode == CAPWORD) {
        enable_caps_word();
        return false;
    }

    // If the behavior isn't enabled and the keypress isn't a keycode to
    // toggle the behavior, allow QMK to handle the keypress as usual
    if (!is_caps_word_on) {
        return true;
    }

    // Get the base keycode of a mod or layer tap key
    switch (keycode) {
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
        case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
            // Earlier return if this has not been considered tapped yet
            if (record->tap.count == 0)
                return true;
            keycode = keycode & 0xFF;
            break;
        default:
            break;
    }

    if (should_terminate_caps_word(keycode, record)) {
        disable_caps_word();
    }

    return true;
}
