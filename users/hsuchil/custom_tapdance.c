/*
Copyright 2022 Hector Galindo <hi@hsuchil.com>

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

#include QMK_KEYBOARD_H

#include "process_tap_dance.h"

#include "hsuchil.h"

#define TD_FN(FN_NAME) void FN_NAME(qk_tap_dance_state_t *state, void *user_data)
#define TD_ON_EACH_TAP_FN_N(T) T##_on_each_tap
#define TD_ON_EACH_TAP_FN(T) TD_FN(TD_ON_EACH_TAP_FN_N(T))
#define TD_ON_DANCE_FINISHED_FN_N(T) T##_on_dance_finished
#define TD_ON_DANCE_FINISHED_FN(T) TD_FN(TD_ON_DANCE_FINISHED_FN_N(T))
#define TD_ON_DANCE_RESET_FN_N(T) T##_on_dance_reset
#define TD_ON_DANCE_RESET_FN(T) TD_FN(TD_ON_DANCE_RESET_FN_N(T))

#define ACTION_TD_DEF(T,E,F,R) [T] = ACTION_TAP_DANCE_FN_ADVANCED(E,F,R)
#define ACTION_TD_DEF_FULL(T) ACTION_TD_DEF(T, TD_ON_EACH_TAP_FN_N(T), TD_ON_DANCE_FINISHED_FN_N(T), TD_ON_DANCE_RESET_FN_N(T))
#define ACTION_TD_DEF_NO_EACH(T) ACTION_TD_DEF(T, NULL, TD_ON_DANCE_FINISHED_FN_N(T), TD_ON_DANCE_RESET_FN_N(T))
#define ACTION_TD_DEF_NO_FINISHED(T) ACTION_TD_DEF(T, TD_ON_EACH_TAP_FN_N(T), NULL, TD_ON_DANCE_RESET_FN_N(T))
#define ACTION_TD_DEF_NO_RESET(T) ACTION_TD_DEF(T, TD_ON_EACH_TAP_FN_N(T), TD_ON_DANCE_FINISHED_FN_N(T), NULL)
#define ACTION_TD_DEF_ONLY_EACH(T) ACTION_TD_DEF(T, TD_ON_EACH_TAP_FN_N(T), NULL, NULL)
#define ACTION_TD_DEF_ONLY_FINISHED(T) ACTION_TD_DEF(T, NULL, TD_ON_DANCE_FINISHED_FN_N(T), NULL)
#define ACTION_TD_DEF_ONLY_RESET(T) ACTION_TD_DEF(T, NULL, NULL, TD_ON_DANCE_RESET_FN_N(T))

#define SIMPLE_DANCE_STATE cur_dance_simple(state)
#define DANCE_STATE cur_dance(state)

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_TAP,
    TD_HOLD,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD
} td_state_t;

td_state_t cur_dance_simple(qk_tap_dance_state_t *state) {
    if (!state->pressed) return TD_TAP;
    return TD_HOLD;
}

td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        return TD_SINGLE_HOLD;
    }

    if (state->count == 2) {
        if (!state->pressed) return TD_DOUBLE_TAP;
        return TD_DOUBLE_HOLD;
    }

    return TD_UNKNOWN;
}

static td_state_t rshift_up_state;

TD_ON_DANCE_FINISHED_FN(_TD_RSHIFT_UP) {
    rshift_up_state = SIMPLE_DANCE_STATE;
    if (rshift_up_state == TD_HOLD) {
        register_mods(MOD_BIT(KC_RSFT));
    } else {
        register_code16(KC_UP);
    }
}

TD_ON_DANCE_RESET_FN(_TD_RSHIFT_UP) {
    if (rshift_up_state == TD_HOLD) {
        unregister_mods(MOD_BIT(KC_RSFT));
    } else {
        unregister_code16(KC_UP);
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    ACTION_TD_DEF_NO_EACH(_TD_RSHIFT_UP),
};
