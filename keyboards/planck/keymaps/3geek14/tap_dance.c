/* Copyright 2023 Pi Fisher
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

#include "tap_dance.h"

/* Dot Dots
 *
 * Tapping the period key three times quickly results in an ellipsis. Any
 * other number of taps is that many periods. Holding the key acts normally,
 * as the KC_DOT code stays registered.
 *
 * In order to have periods show up immediately for an easier flow when
 * typing, the *_each function (unregisters and) registers KC_DOT each time,
 * so the *_finished function needs to send KC_BACKSPACE to delete the
 * periods before it sends the ellipsis character. Unfortunately, this
 * interacts poorly with tools like Google Docs which already have an
 * ellipsis replacement. With Google Docs, typing three periods results in
 * an ellipsis, the first backspace undoes the replacement (leaving three
 * periods), and the end result is a period followed by an ellipsis.
 */
static bool dot_held;

void dot_dots_each(tap_dance_state_t *state, void *user_data) {
    if (state->count > 1) {
        unregister_code(KC_DOT);
    }
    register_code(KC_DOT);
}

void dot_dots_finished(tap_dance_state_t *state, void *user_data) {
    uint8_t mods = get_mods() | get_oneshot_mods() | get_weak_mods();
    if (!mods && state->count == 3) {
        unregister_code(KC_DOT);
        tap_code(KC_BACKSPACE);
        tap_code(KC_BACKSPACE);
        tap_code(KC_BACKSPACE);
        send_unicode_string("…"); // ellipsis
    } else {
        if (state->pressed) {
            dot_held = true;
        } else {
            unregister_code(KC_DOT);
            dot_held = false;
        }
    }
}

void dot_dots_reset(tap_dance_state_t *state, void *user_data) {
    if(dot_held) {
        unregister_code(KC_DOT);
        dot_held = false;
    }
}

/* Dashes
 *
 * Tap twice for en dash or thrice for em dash. No other behaviours
 * result in any visible behaviour.
 */
void dashes_finished(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 2:
            send_unicode_string("–"); // en dash
            break;
        case 3:
            send_unicode_string("—"); // em dash
            break;
        default:
            break;
    }
}

tap_dance_action_t tap_dance_actions[] = {
    // Tap once for period, thrice for ellipsis
    [TD_DOT_DOTS] = ACTION_TAP_DANCE_FN_ADVANCED(dot_dots_each, dot_dots_finished, dot_dots_reset),
    // Tap once for hyphen, twice for en dash, thrice for em dash
    [TD_DASHES] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dashes_finished, NULL),
};
