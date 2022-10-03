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

#include "num_word.h"

static bool is_num_word_on = false;

bool is_num_word_enabled(void) {
    return is_num_word_on;
}

void enable_num_word(uint8_t num_layer) {
    if (is_num_word_on) {
        return;
    }
    is_num_word_on = true;
    layer_on(num_layer);
}

void disable_num_word(uint8_t num_layer) {
    if (!is_num_word_on) {
        return;
    }
    is_num_word_on = false;
    layer_off(num_layer);
}

void toggle_num_word(uint8_t num_layer) {
    if (is_num_word_on) {
        disable_num_word(num_layer);
    }
    else {
        enable_num_word(num_layer);
    }
}

bool should_terminate_num_word(uint16_t keycode, const keyrecord_t *record) {
    switch (keycode) {
        // Keycodes which should not disable num word mode.
        // We could probably be more brief with these definitions by using
        // a couple more ranges, but I believe "explicit is better than
        // implicit"
        case KC_1 ... KC_0:
        case KC_EQL:
        case KC_MINS:
        case KC_PLUS:
        case KC_DOT:
        case KC_COMM:
        // Misc
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


bool process_record_num_word(uint16_t keycode, const keyrecord_t *record, uint8_t num_layer) {
    // nothing in this feature will activate if the behavior is not on,
    // so allow QMK to handle the event as usual
    if (!is_num_word_on) {
        return true;
    }

    // Nothing else acts on key release, either
    if (!record->event.pressed) {
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

    if (should_terminate_num_word(keycode, record)) {
        disable_num_word(num_layer);
    }

    return true;
}
