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
#include "tap_dances.h"

uint8_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TRIPLE_TAP;
        else return TRIPLE_HOLD;
    } else return 8;
}

static tap tap_state = {
    .is_press_action = true,
    .state = 0
};

#ifdef TAP_DANCE_LALT_GIT
void lalt_finished(qk_tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LALT));
            break;
        case DOUBLE_SINGLE_TAP:
        case DOUBLE_TAP:
            set_oneshot_layer(_GIT, ONESHOT_START);
            break;
    }
}

void lalt_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (tap_state.state) {
        case SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LALT));
            break;
        case DOUBLE_SINGLE_TAP:
        case DOUBLE_TAP:
            clear_oneshot_layer_state(ONESHOT_PRESSED);
            break;
    }
    tap_state.state = 0;
}
#endif

#ifdef TAP_DANCE_LSFT_CAPS
#    ifdef LAYERS_PROGRAMMER
void pg_lsft_finished(qk_tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LSFT));
            layer_on(_PROGRAMMER_SHIFTED);
            break;
        case DOUBLE_SINGLE_TAP:
        case DOUBLE_TAP:
            tap_code(KC_CAPS);
            layer_on(_PROGRAMMER_SHIFTED);
            break;
    }
}

void pg_lsft_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (tap_state.state) {
        case SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LSFT));
            layer_off(_PROGRAMMER_SHIFTED);
            break;
    }
    tap_state.state = 0;
}
#    endif
#endif

qk_tap_dance_action_t tap_dance_actions[] = {
#ifdef TAP_DANCE_LALT_GIT
    [TD_LALT_GIT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lalt_finished, lalt_reset),
#endif
#ifdef TAP_DANCE_LSFT_CAPS
    [TD_LSFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
#    ifdef LAYERS_PROGRAMMER
    [TD_PG_LSFT_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, pg_lsft_finished, pg_lsft_reset),
#    endif
#endif
};
