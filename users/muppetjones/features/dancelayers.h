/* Copyright 2020 Stephen J. Bush
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
#ifdef TAP_DANCE_ENABLE
#    include QMK_KEYBOARD_H

/*
 * TAP DANCE
 * https://docs.qmk.fm/#/feature_tap_dance
 */

// Define a type for as many tap dance states as you need
typedef enum {
    TD_NONE = 0,
    TD_UNKNOWN,
    TD_1X_TAP,
    TD_1X_HOLD,
    TD_2X_TAP,
    TD_3X_TAP,
    TD_4X_TAP,
} td_state_t;

// Our custom tap dance key; add any other tap dance keys to this enum
enum {
    TD_LAYERS = 0,  // NOTE: Start at 0 as this is also an array index
};
#    define TD_LAYR TD(TD_LAYERS)

typedef struct {
    bool       is_press_action;
    td_state_t state;
} td_tap_t;

// Declare the functions to be used with your tap dance key(s)

/* @brief Determine the current tap dance state
 * @param A tap dance state struct.
 * @return A struct.
 */
td_state_t cur_dance(tap_dance_state_t *state);

// Functions associated with individual tap dances

/* @brief Associate tap actions with layers.
 *
 * NOTE: Weak attribute. Can (and should) be defined in keymap.c
 *
 * @param state Pointer to a tap dance state object.
 * @param user_data Pointer to user data.
 * @return None.
 */
void td_layer_finished(tap_dance_state_t *state, void *user_data);

/* @brief Reset tap dance actions.
 *
 * NOTE: Weak attribute. Can (and should) be defined in keymap.c
 *
 * @param state Pointer to a tap dance state object.
 * @param user_data Pointer to user data.
 * @return None.
 */
void td_layer_reset(tap_dance_state_t *state, void *user_data);

/* Define tap dance actions.
 */
__attribute__((weak))
tap_dance_action_t tap_dance_actions[1] = {[TD_LAYERS] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, td_layer_finished, td_layer_reset, 275)};
#endif
