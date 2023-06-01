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
    TD_LCTL_ESC_SPOTLIGHT_EMOJI,
    TD_LALT_ESC_WINDOWS_EMOJI
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(TD_LCTL_ESC_SPOTLIGHT_EMOJI) :
        case TD(TD_LALT_ESC_WINDOWS_EMOJI) :
        case LGUI_T(KC_SPC) :
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
        return TD_DOUBLE_TAP;
    } else if (state->count == 3) {
        return TD_TRIPLE_TAP;
    }   

    return TD_UNKNOWN;
}

void td_lctl_esc_spotlight_emoji_finished(tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_ESC); break;
        case TD_SINGLE_HOLD: register_code(KC_LCTL); break;
        case TD_DOUBLE_TAP: tap_code16(G(KC_SPC)); break;
        case TD_TRIPLE_TAP: tap_code16(C(G(KC_SPC))); break;
        default: break;
    }
}

void td_lctl_esc_spotlight_emoji_reset(tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_ESC); break;
        case TD_SINGLE_HOLD: unregister_code(KC_LCTL); break;
        default: break;
    }
    xtap_state.state = TD_NONE;
}

void td_lalt_esc_windowr_emoji_finished(tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_ESC); break;
        case TD_SINGLE_HOLD: register_code(KC_LALT); break;
        case TD_DOUBLE_TAP: tap_code(KC_LGUI); break;
        case TD_TRIPLE_TAP: tap_code16(G(KC_DOT)); break;
        default: break;
    }
}

void td_lalt_esc_windowr_emoji_reset(tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_ESC); break;
        case TD_SINGLE_HOLD: unregister_code(KC_LALT); break;
        default: break;
    }
    xtap_state.state = TD_NONE;
}

 // Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    [TD_LCTL_ESC_SPOTLIGHT_EMOJI] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_lctl_esc_spotlight_emoji_finished, td_lctl_esc_spotlight_emoji_reset),
    [TD_LALT_ESC_WINDOWS_EMOJI] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_lalt_esc_windowr_emoji_finished, td_lalt_esc_windowr_emoji_reset),
};

// For the x tap dance. Put it here so it can be used in any keymap
void x_finished(tap_dance_state_t *state, void *user_data);
void x_reset(tap_dance_state_t *state, void *user_data);


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x5_3(
        _________________COLEMAK1_________________,
        _________________COLEMAK2_________________,
        _________________COLEMAK3a________________,
        _______THUMB6_1_______
    ),
    [1] = LAYOUT_split_3x5_3(
        ______________SYM_MEDIA_NAV1______________,
        ______________SYM_MEDIA_NAV2______________,
        ______________SYM_MEDIA_NAV3______________,
        _____THUMB6_TRNS______
    ),
    [2] = LAYOUT_split_3x5_3(
        _________________NUM_SYM1_________________,
        _________________NUM_SYM2_________________,
        _________________NUM_SYM3a________________,
        _____THUMB6_TRNS______
    ),
    [3] = LAYOUT_split_3x5_3(
        ________________FUNC_SYS1a________________,
        ________________FUNC_SYS2_________________,
        ________________FUNC_SYS3_________________,
        _____THUMB6_TRNS______
    ),
    [4] = LAYOUT_split_3x5_3(
        _________________COLEMAK1_________________,
        _________________COLEMAK2_________________,
        _________________COLEMAK3a________________,
        _______THUMB6_4_______
    ),
    [5] = LAYOUT_split_3x5_3(
        _________________COLEMAK1_________________,
        _________________COLEMAK2_________________,
        _________________COLEMAK3b________________,
        _______THUMB6_5_______
    ),
    [6] = LAYOUT_split_3x5_3(
        ______________SYM_MEDIA_NAV1______________,
        ______________SYM_MEDIA_NAV2______________,
        ______________SYM_MEDIA_NAV3______________,
        _____THUMB6_TRNS______
    ),
    [7] = LAYOUT_split_3x5_3(
        _________________NUM_SYM1_________________,
        _________________NUM_SYM2_________________,
        _________________NUM_SYM3b________________,
        _____THUMB6_TRNS______
    ),
    [8] = LAYOUT_split_3x5_3(
        ________________FUNC_SYS1b________________,
        ________________FUNC_SYS2_________________,
        ________________FUNC_SYS3_________________,
        _____THUMB6_TRNS______
    )
};
