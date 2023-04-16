/* Copyright 2022 @ Teimor Epstein
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
#include "tap_dance_setup.h"

td_state_t current_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        /* Key has not been interrupted, but the key is still held. Means you w ant to send a 'HOLD'. */
        else
            return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        /* TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
           action when hitting 'pp'. Suggested use case for this return value is when you want to send two
           keystrokes of the key, and not the 'double tap' action/macro. */
        if (state->interrupted)
            return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed)
            return TD_DOUBLE_HOLD;
        else
            return TD_DOUBLE_TAP;
    }

    /* Assumes no one is trying to type the same letter three times (at least not quickly).
      If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
      an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP' */
    if (state->count == 3) {
        if (state->interrupted)
            return TD_TRIPLE_SINGLE_TAP;
        else if (state->pressed)
            return TD_TRIPLE_HOLD;
        else
            return TD_TRIPLE_TAP;

    } else
        return TD_UNKNOWN;
}
