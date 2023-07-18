/*
Copyright 2023 @mroukema

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#include USERSPACE_H

// Tap Dance declarations

enum tap_dance_codes {
    TD_ARW_UP = 0,
    TD_ARW_LEFT,
    TD_ARW_DOWN,
    TD_ARW_RIGHT,
    CAPS_LOCK,
    TAP_CODES_COUNT
};

extern tap_dance_action_t tap_dance_actions[];
extern uint8_t dance_step(tap_dance_state_t *state);

/*
 * TAP DANCE LOGIC
 */

typedef struct {
    bool    is_press_action;
    uint8_t step;
} tap;

enum { SINGLE_TAP = 1, SINGLE_HOLD, DOUBLE_TAP, DOUBLE_HOLD, DOUBLE_SINGLE_TAP, MORE_TAPS, MORE_HOLDS };

uint8_t dance_step(tap_dance_state_t *state);

void on_dance_up(tap_dance_state_t *state, void *user_data);
void dance_up_finished(tap_dance_state_t *state, void *user_data);
void dance_up_reset(tap_dance_state_t *state, void *user_data);

void on_dance_left(tap_dance_state_t *state, void *user_data);
void dance_left_finished(tap_dance_state_t *state, void *user_data);
void dance_left_reset(tap_dance_state_t *state, void *user_data);

void on_dance_down(tap_dance_state_t *state, void *user_data);
void dance_down_finished(tap_dance_state_t *state, void *user_data);
void dance_down_reset(tap_dance_state_t *state, void *user_data);

void on_dance_right(tap_dance_state_t *state, void *user_data);
void dance_right_finished(tap_dance_state_t *state, void *user_data);
void dance_right_reset(tap_dance_state_t *state, void *user_data);

void on_dance_nothing(tap_dance_state_t *state, void *user_data);

void dance_capslock_finished(tap_dance_state_t *state, void *user_data);
void dance_capslock_reset(tap_dance_state_t *state, void *user_data);
