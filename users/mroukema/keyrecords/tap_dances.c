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

#include "tap_dances.h"

/*
 * TAP DANCE LOGIC
 */
static tap dance_state[TAP_CODES_COUNT];

uint8_t dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed)
            return SINGLE_TAP;
        else
            return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted)
            return DOUBLE_SINGLE_TAP;
        else if (state->pressed)
            return DOUBLE_HOLD;
        else
            return DOUBLE_TAP;
    }
    if (state->pressed) {
        return MORE_HOLDS;
    }
    return MORE_TAPS;
}

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    [TD_ARW_UP] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_up, dance_up_finished, dance_up_reset),
    [TD_ARW_LEFT] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_left, dance_left_finished, dance_left_reset),
    [TD_ARW_DOWN] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_down, dance_down_finished, dance_down_reset),
    [TD_ARW_RIGHT] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_right, dance_right_finished, dance_right_reset),
    [CAPS_LOCK] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_nothing, dance_capslock_finished, dance_capslock_reset)
};

void on_dance_up(tap_dance_state_t *state, void *user_data) {
    if (state->count == 3) {
        tap_code16(KC_UP);
        tap_code16(KC_UP);
        tap_code16(KC_UP);
    }
    if (state->count > 3) {
        tap_code16(KC_UP);
    }
}

void dance_up_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[TD_ARW_UP].step = dance_step(state);
    switch (dance_state[TD_ARW_UP].step) {
        case SINGLE_TAP:
            register_code16(KC_UP);
            break;
        case SINGLE_HOLD:
            register_code16(LALT(KC_UP));
            break;
        case DOUBLE_TAP:
            register_code16(KC_UP);
            register_code16(KC_UP);
            break;
        case DOUBLE_SINGLE_TAP:
            tap_code16(KC_UP);
            register_code16(KC_UP);
            break;
        case DOUBLE_HOLD:
            tap_code16(KC_UP);
            register_code16(LALT(KC_UP));
            break;
        case MORE_HOLDS:
            register_code16(LALT(KC_UP));
            break;
    }
}

void dance_up_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[TD_ARW_UP].step) {
        case SINGLE_TAP:
            unregister_code16(KC_UP);
            break;
        case SINGLE_HOLD:
            unregister_code16(LALT(KC_UP));
            break;
        case DOUBLE_TAP:
            unregister_code16(KC_UP);
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code16(KC_UP);
            break;
        case DOUBLE_HOLD:
            unregister_code16(LALT(KC_UP));
            break;
        case MORE_HOLDS:
            unregister_code16(LALT(KC_UP));
            break;
    }
    dance_state[TD_ARW_UP].step = 0;
}

void on_dance_left(tap_dance_state_t *state, void *user_data) {
    if (state->count == 3) {
        tap_code16(KC_LEFT);
        tap_code16(KC_LEFT);
        tap_code16(KC_LEFT);
    }
    if (state->count > 3) {
        tap_code16(KC_LEFT);
    }
}

void dance_left_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[TD_ARW_LEFT].step = dance_step(state);
    switch (dance_state[TD_ARW_LEFT].step) {
        case SINGLE_TAP:
            register_code16(KC_LEFT);
            break;
        case SINGLE_HOLD:
            register_code16(LALT(KC_LEFT));
            break;
        case DOUBLE_TAP:
            register_code16(KC_LEFT);
            register_code16(KC_LEFT);
            break;
        case DOUBLE_SINGLE_TAP:
            tap_code16(KC_LEFT);
            register_code16(KC_LEFT);
            break;
        case DOUBLE_HOLD:
            tap_code16(KC_LEFT);
            register_code16(LALT(KC_LEFT));
            break;
        case MORE_HOLDS:
            register_code16(LALT(KC_LEFT));
            break;
    }
}

void dance_left_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[TD_ARW_LEFT].step) {
        case SINGLE_TAP:
            unregister_code16(KC_LEFT);
            break;
        case SINGLE_HOLD:
            unregister_code16(LALT(KC_LEFT));
            break;
        case DOUBLE_TAP:
            unregister_code16(KC_LEFT);
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code16(KC_LEFT);
            break;
        case DOUBLE_HOLD:
            unregister_code16(LALT(KC_LEFT));
            break;
        case MORE_HOLDS:
            unregister_code16(LALT(KC_LEFT));
            break;
    }
    dance_state[TD_ARW_LEFT].step = 0;
}

void on_dance_down(tap_dance_state_t *state, void *user_data) {
    if (state->count == 3) {
        tap_code16(KC_DOWN);
        tap_code16(KC_DOWN);
        tap_code16(KC_DOWN);
    }
    if (state->count > 3) {
        tap_code16(KC_DOWN);
    }
}

void dance_down_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[TD_ARW_DOWN].step = dance_step(state);
    switch (dance_state[TD_ARW_DOWN].step) {
        case SINGLE_TAP:
            register_code16(KC_DOWN);
            break;
        case SINGLE_HOLD:
            register_code16(LALT(KC_DOWN));
            break;
        case DOUBLE_TAP:
            register_code16(KC_DOWN);
            register_code16(KC_DOWN);
            break;
        case DOUBLE_SINGLE_TAP:
            tap_code16(KC_DOWN);
            register_code16(KC_DOWN);
            break;
        case DOUBLE_HOLD:
            tap_code16(KC_DOWN);
            register_code16(LALT(KC_DOWN));
            break;
        case MORE_HOLDS:
            register_code16(LALT(KC_DOWN));
            break;
    }
}

void dance_down_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[TD_ARW_DOWN].step) {
        case SINGLE_TAP:
            unregister_code16(KC_DOWN);
            break;
        case SINGLE_HOLD:
            unregister_code16(LALT(KC_DOWN));
            break;
        case DOUBLE_TAP:
            unregister_code16(KC_DOWN);
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code16(KC_DOWN);
            break;
        case DOUBLE_HOLD:
            unregister_code16(LALT(KC_DOWN));
            break;
        case MORE_HOLDS:
            unregister_code16(LALT(KC_DOWN));
            break;
    }
    dance_state[TD_ARW_DOWN].step = 0;
}

void on_dance_right(tap_dance_state_t *state, void *user_data) {
    if (state->count == 3) {
        tap_code16(KC_RIGHT);
        tap_code16(KC_RIGHT);
        tap_code16(KC_RIGHT);
    }
    if (state->count > 3) {
        tap_code16(KC_RIGHT);
    }
}

void dance_right_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[TD_ARW_RIGHT].step = dance_step(state);
    switch (dance_state[TD_ARW_RIGHT].step) {
        case SINGLE_TAP:
            register_code16(KC_RIGHT);
            break;
        case SINGLE_HOLD:
            register_code16(LALT(KC_RIGHT));
            break;
        case DOUBLE_TAP:
            register_code16(KC_RIGHT);
            register_code16(KC_RIGHT);
            break;
        case DOUBLE_SINGLE_TAP:
            tap_code16(KC_RIGHT);
            register_code16(KC_RIGHT);
            break;
        case DOUBLE_HOLD:
            tap_code16(KC_RIGHT);
            register_code16(LALT(KC_RIGHT));
            break;
        case MORE_HOLDS:
            register_code16(LALT(KC_RIGHT));
            break;
    }
}

void dance_right_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[TD_ARW_RIGHT].step) {
        case SINGLE_TAP:
            unregister_code16(KC_RIGHT);
            break;
        case SINGLE_HOLD:
            unregister_code16(LALT(KC_RIGHT));
            break;
        case DOUBLE_TAP:
            unregister_code16(KC_RIGHT);
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code16(KC_RIGHT);
            break;
        case DOUBLE_HOLD:
            unregister_code16(LALT(KC_RIGHT));
            break;
        case MORE_HOLDS:
            unregister_code16(LALT(KC_RIGHT));
            break;
    }
    dance_state[TD_ARW_RIGHT].step = 0;
}

void on_dance_nothing(tap_dance_state_t *state, void *user_data) {}

void dance_capslock_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[CAPS_LOCK].step = dance_step(state);
    switch (dance_state[CAPS_LOCK].step) {
        case DOUBLE_HOLD:
            register_code16(KC_CAPS_LOCK);
            break;
    }
}

void dance_capslock_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[CAPS_LOCK].step) {
        case DOUBLE_HOLD:
            unregister_code16(KC_CAPS_LOCK);
            break;
    }
    dance_state[CAPS_LOCK].step = 0;
}
