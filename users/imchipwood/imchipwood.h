/* Copyright 2021 imchipwood
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

#include "quantum.h"

// change the tapping term to a little bit quicker
#ifdef TAPPING_TERM
  #undef TAPPING_TERM
#endif
#define TAPPING_TERM    175

#ifdef TAPPING_TOGGLE
  #undef TAPPING_TOGGLE
#endif
#define TAPPING_TOGGLE 2


enum td_keycodes {
    TD_REND = 0, // right when tapped, end when double tapped
    TD_LOME,     // left when tapped, home when double tapped
    TD_RSFT_CAPS,
    ALT_F2,    // F2 when tapped, LALT when held, LALT+F2 when double tapped
    CTL_F5,    // F5 when tapped, LCTL when held, LCTL+F5 when double tapped
    ALT_F7,    // F7 when tapped, LALT when held, LALT+F7 when double tapped
    DEL_NLCK,  // DEL when tapped, NUMLOCK when double tapped
};


typedef enum { SINGLE_TAP, SINGLE_HOLD, DOUBLE_TAP } td_state_t;
int cur_dance(qk_tap_dance_state_t *state);

void altf2_finished(qk_tap_dance_state_t *state, void *user_data);
void altf2_reset(qk_tap_dance_state_t *state, void *user_data);
void ctlf5_finished(qk_tap_dance_state_t *state, void *user_data);
void ctlf5_reset(qk_tap_dance_state_t *state, void *user_data);
void altf7_finished(qk_tap_dance_state_t *state, void *user_data);
void altf7_reset(qk_tap_dance_state_t *state, void *user_data);
