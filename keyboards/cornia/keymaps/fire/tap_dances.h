/* Copyright 2024 Vaarai
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

/* Tap dances definitions */
enum tap_dances {
  TD_SFT_CAPSW,
  TD_NAV_ACCENT,
  TD_NUM_ACCENT,
  TAP_DANCE_ACTIONS_COUNT /* Utility to get TD_xxx count */
};

/* Accented letters */
typedef enum {
  ACCENT_NONE,
  ACCENT_LEFT,
  ACCENT_RIGHT
} accent_state_t;

extern accent_state_t accent_state;

extern tap_dance_action_t tap_dance_actions[TAP_DANCE_ACTIONS_COUNT];

void dance_shift_capsword_finished (tap_dance_state_t *state, void *user_data);
void dance_shift_capsword_reset (tap_dance_state_t *state, void *user_data);

void dance_nav_accent_finished (tap_dance_state_t *state, void *user_data);
void dance_nav_accent_reset (tap_dance_state_t *state, void *user_data);

void dance_num_accent_finished (tap_dance_state_t *state, void *user_data);
void dance_num_accent_reset (tap_dance_state_t *state, void *user_data);
