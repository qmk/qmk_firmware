/* Copyright 2021 Kyle Xiao
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

#ifdef TAP_DANCE_ENABLE
void qk_tap_dance_tap_hold_on_each_tap(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_tap_hold_t *kc = (qk_tap_dance_tap_hold_t *)user_data;

    // second tap within term, pseudo reset tap dance
    if (state->count == 2) {
        tap_code16(kc->t);
        state->count = 1;
        state->timer = timer_read();
    }
}

void qk_tap_dance_tap_hold_on_finish(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_tap_hold_t *kc = (qk_tap_dance_tap_hold_t *)user_data;

    kc->tapped = state->interrupted || !state->pressed;
    if (kc->tapped) {
        register_code16(kc->t);
    } else {
        register_code16(kc->h);
    }
}

void qk_tap_dance_tap_hold_on_reset(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_tap_hold_t *kc = (qk_tap_dance_tap_hold_t *)user_data;

    if (kc->tapped) {
        unregister_code16(kc->t);
    } else {
        unregister_code16(kc->h);
    }
    kc->tapped = true;
}
#endif
