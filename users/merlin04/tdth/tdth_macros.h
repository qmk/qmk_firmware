/* Tap dance tap hold
 * This is a separate file so that the tap dance macros can be used
 * before tdth.c is included. This is necessary because the macros
 * set up various variables that tdth.c expects to be defined.
 *
 * Copyright 2021 Benjamin Smith (@Merlin04)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

typedef struct {
    uint8_t count;
    uint8_t type;
} td_tap_result;

enum {
    TD_TAP,
    TD_HOLD
};

#define TD_STATE(name) [name] = {\
    .count = 0,\
    .type = 0\
}

#define DEFINE_TD_STATES(...) static td_tap_result td_states[TD_TH_COUNT] = {\
     __VA_ARGS__ \
};

typedef struct {
    uint16_t tap_kc[TD_TH_MAX_TAP];
    uint16_t hold_kc[TD_TH_MAX_TAP];
} td_th;

#define ARRAY_LITERAL(...) __VA_ARGS__

#define TD_DEF(name, tap, hold) [name] = {\
    .tap_kc = tap,\
    .hold_kc = hold\
}

#define DEFINE_TD_KEYCODES(...) const static td_th td_th_defs[TD_TH_COUNT] = {\
    __VA_ARGS__\
};

#define TD_ACTION(name) [name] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_finished, td_reset)

#define DEFINE_TD_ACTIONS(...) qk_tap_dance_action_t tap_dance_actions[] = {\
    __VA_ARGS__\
};
