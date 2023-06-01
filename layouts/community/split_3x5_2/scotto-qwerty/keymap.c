/*
Copyright 2023 Joe Scotto

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "scotto.h"

// Tap dance declarations
enum {
    TD_ESC_LALT_LCTL_SPOTLIGHT_EMOJI,
    TD_ESC_LCTL_LALT_WINDOWS_EMOJI
};

// Custom tapping term for multi function keys
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(TD_ESC_LALT_LCTL_SPOTLIGHT_EMOJI) :
        case TD(TD_ESC_LCTL_LALT_WINDOWS_EMOJI) :
        case LGUI_T(KC_SPC) :
        case LT(1, KC_SPC) :
        case LT(1, KC_TAB) :
        case LT(2, KC_ENT) :
      return 200;
    default:
      return TAPPING_TERM;
  }
};

// Begin quad TD
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_HOLD,
    TD_DOUBLE_HOLD,
    TD_TRIPLE_HOLD,
    TD_SINGLE_TAP,
    TD_DOUBLE_TAP,
    TD_TRIPLE_TAP
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// Create an instance of 'td_tap_t' for the 'x' tap dance.
static td_tap_t xtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) {
            return TD_SINGLE_TAP;
        } else {
            return TD_SINGLE_HOLD;
        }
    } else if (state->count == 2) {
        if (state->interrupted || !state->pressed) {
            return TD_DOUBLE_TAP;
        } else {
            return TD_DOUBLE_HOLD;
        }
    } else if (state->count == 3) {
        if (state->interrupted || !state->pressed) {
        return TD_TRIPLE_TAP;
        } else {
            return TD_TRIPLE_HOLD;
        }
    }   

    return TD_UNKNOWN;
}

void td_esc_lalt_lctl_spotlight_emoji_finished(tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: tap_code(KC_ESC); break;
        case TD_SINGLE_HOLD: register_code(KC_LALT); break;
        case TD_DOUBLE_HOLD: register_code(KC_LCTL); break;
        case TD_DOUBLE_TAP: tap_code16(G(KC_SPC)); break;
        case TD_TRIPLE_TAP: tap_code16(C(G(KC_SPC))); break;
        default: break;
    }
}

void td_esc_lalt_lctl_spotlight_emoji_reset(tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_ESC); break;
        case TD_SINGLE_HOLD: unregister_code(KC_LALT); break;
        case TD_DOUBLE_HOLD: unregister_code(KC_LCTL); break;
        default: break;
    }
    xtap_state.state = TD_NONE;
}

void td_esc_lctl_lalt_windows_emoji_finished(tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: tap_code16(KC_ESC); break;
        case TD_SINGLE_HOLD: register_code(KC_LCTL); break;
        case TD_DOUBLE_HOLD: register_code(KC_LALT); break;
        case TD_DOUBLE_TAP: tap_code(KC_LGUI); break;
        case TD_TRIPLE_TAP: tap_code16(G(KC_DOT)); break;
        default: break;
    }
}

void td_esc_lctl_lalt_windows_emoji_reset(tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_ESC); break;
        case TD_SINGLE_HOLD: unregister_code(KC_LCTL); break;
        case TD_DOUBLE_HOLD: unregister_code(KC_LALT); break;
        default: break;
    }
    xtap_state.state = TD_NONE;
}

 // Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    [TD_ESC_LALT_LCTL_SPOTLIGHT_EMOJI] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_esc_lalt_lctl_spotlight_emoji_finished, td_esc_lalt_lctl_spotlight_emoji_reset),
    [TD_ESC_LCTL_LALT_WINDOWS_EMOJI] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_esc_lctl_lalt_windows_emoji_finished, td_esc_lctl_lalt_windows_emoji_reset)
};

// For the x tap dance. Put it here so it can be used in any keymap
void x_finished(tap_dance_state_t *state, void *user_data);
void x_reset(tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x5_2(
        _________________QWERTY1__________________,
        _________________QWERTY2__________________,
        _________________QWERTY3a_________________,
        _______THUMB4_1_______
    ),
    [1] = LAYOUT_split_3x5_2(
        ______________SYM_MEDIA_NAV1______________,
        ______________SYM_MEDIA_NAV2______________,
        ______________SYM_MEDIA_NAV3______________,
        _____THUMB4_TRNS______
    ),
    [2] = LAYOUT_split_3x5_2(
        _________________NUM_SYM1_________________,
        _________________NUM_SYM2_________________,
        _________________NUM_SYM3a________________,
        _____THUMB4_TRNS______
    ),
    [3] = LAYOUT_split_3x5_2(
        ________________FUNC_SYS1a________________, 
        ________________FUNC_SYS2_________________,
        ________________FUNC_SYS3_________________,
        _____THUMB4_TRNS______
    ),
    [4] = LAYOUT_split_3x5_2(
        _________________QWERTY1__________________,
        _________________QWERTY2__________________,
        _________________QWERTY3a_________________,
        _______THUMB4_4_______
    ),
    [5] = LAYOUT_split_3x5_2(
        _________________QWERTY1__________________,
        _________________QWERTY2__________________,
        _________________QWERTY3b_________________,
        _______THUMB4_5_______
    ),
    [6] = LAYOUT_split_3x5_2(
        ______________SYM_MEDIA_NAV1______________,
        ______________SYM_MEDIA_NAV2______________,
        ______________SYM_MEDIA_NAV3______________,
        _____THUMB4_TRNS______
    ),
    [7] = LAYOUT_split_3x5_2(
        _________________NUM_SYM1_________________,
        _________________NUM_SYM2_________________,
        _________________NUM_SYM3b________________,
        _____THUMB4_TRNS______
    ),
    [8] = LAYOUT_split_3x5_2(
        ________________FUNC_SYS1b________________, 
        ________________FUNC_SYS2_________________,
        ________________FUNC_SYS3_________________,
        _____THUMB4_TRNS______
    )
};
