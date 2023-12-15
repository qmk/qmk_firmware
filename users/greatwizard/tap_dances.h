/* Copyright 2020 Guillaume Gérard
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

#include QMK_KEYBOARD_H
#include "greatwizard.h"

typedef struct {
    bool    is_press_action;
    uint8_t state;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP,
    TRIPLE_TAP,
    TRIPLE_HOLD
};

enum {
#ifdef TAP_DANCE_LALT_GIT
    TD_LALT_GIT,
#endif
#ifdef TAP_DANCE_LSFT_CAPS
    TD_LSFT_CAPS,
#    ifdef LAYERS_PROGRAMMER
    TD_PG_LSFT_CAPS,
#    endif
#endif
};

uint8_t cur_dance(tap_dance_state_t *state);

#ifdef TAP_DANCE_LALT_GIT
void lalt_finished(tap_dance_state_t *state, void *user_data);
void lalt_reset(tap_dance_state_t *state, void *user_data);
#    define TD_LALT TD(TD_LALT_GIT)
#endif

#ifdef TAP_DANCE_LSFT_CAPS
#    ifdef LAYERS_PROGRAMMER
void pg_lsft_finished(tap_dance_state_t *state, void *user_data);
void pg_lsft_reset(tap_dance_state_t *state, void *user_data);
#    endif
#endif

#ifdef TAP_DANCE_LSFT_CAPS
#    define TD_LSCP TD(TD_LSFT_CAPS)
#endif
