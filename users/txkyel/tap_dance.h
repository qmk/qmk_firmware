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
#pragma once
#include "txkyel.h"

#ifdef TAP_DANCE_ENABLE
typedef struct {
    uint16_t t;
    uint16_t h;
    bool     tapped;
} qk_tap_dance_tap_hold_t;

#    define ACTION_TAP_HOLD(t, h) \
        { .fn = {qk_tap_dance_tap_hold_on_each_tap, qk_tap_dance_tap_hold_on_finish, qk_tap_dance_tap_hold_on_reset}, .user_data = (void *)&((qk_tap_dance_tap_hold_t){t, h, true}), }
#    define ACTION_TAP_HOLD_CTL(t) ACTION_TAP_HOLD(t, C(t))

void qk_tap_dance_tap_hold_on_each_tap(qk_tap_dance_state_t *state, void *user_data);
void qk_tap_dance_tap_hold_on_finish(qk_tap_dance_state_t *state, void *user_data);
void qk_tap_dance_tap_hold_on_reset(qk_tap_dance_state_t *state, void *user_data);
#endif
