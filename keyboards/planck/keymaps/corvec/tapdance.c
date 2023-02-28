/**
 * Tap Dance config and functions
 **/
/* Copyright 2018 Corey Kump
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

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD = 2,
    DOUBLE_TAP = 3,
    DOUBLE_SINGLE_TAP = 4,
    UNKNOWN_TAPS = 5
};

typedef struct {
  bool is_press_action;
  int state;
} tap;

int cur_dance (tap_dance_state_t *state) {
    if (state->count == 1) {
      if (state->interrupted || !state->pressed) {
        return SINGLE_TAP;
      } else {
        return SINGLE_HOLD;
      }
    }
    if (state->count == 2) {
      if (state->interrupted) {
        return DOUBLE_SINGLE_TAP;
      } else if (!state->pressed) {
        return DOUBLE_TAP;
      }
    }
    return UNKNOWN_TAPS;
}

/**
 * quote
 **/

static tap quote_state = {
  .is_press_action = true,
  .state = 0
};

void quote_finished(tap_dance_state_t *state, void *user_data) {
    quote_state.state = cur_dance(state);
    switch(quote_state.state) {
      case SINGLE_TAP: register_code(KC_QUOT); break;
      case SINGLE_HOLD: layer_on(_LEANDOWN); break;
      case DOUBLE_TAP: register_code(KC_MINS); break;
      case DOUBLE_SINGLE_TAP: register_code(KC_QUOT); unregister_code(KC_QUOT); register_code(KC_QUOT); break;
    }
}
void quote_reset(tap_dance_state_t *state, void *user_data) {
    switch(quote_state.state) {
      case SINGLE_TAP: unregister_code(KC_QUOT); break;
      case SINGLE_HOLD: layer_off(_LEANDOWN); break;
      case DOUBLE_TAP: unregister_code(KC_MINS); break;
      case DOUBLE_SINGLE_TAP: unregister_code(KC_QUOT); break;
    }
    quote_state.state = 0;
}

/**
 * ralt / left bracket / left curly brace
 **/

static tap ralt_state = {
  .is_press_action = true,
  .state = 0
};

void ralt_finished(tap_dance_state_t *state, void *user_data) {
    ralt_state.state = cur_dance(state);
    switch(ralt_state.state) {
      case SINGLE_TAP: register_code(KC_LBRC); break;
      case SINGLE_HOLD: register_code(KC_RALT); break;
      case DOUBLE_TAP: register_code(KC_LSFT); register_code(KC_LBRC); break;
      // fallback to alt because it's the primary purpose of this key
      case DOUBLE_SINGLE_TAP: register_code(KC_RALT); break;
    }
}
void ralt_reset(tap_dance_state_t *state, void *user_data) {
    switch(ralt_state.state) {
      case SINGLE_TAP: unregister_code(KC_LBRC); break;
      case SINGLE_HOLD: unregister_code(KC_RALT); break;
      case DOUBLE_TAP: unregister_code(KC_LBRC); unregister_code(KC_LSFT); break;
      case DOUBLE_SINGLE_TAP: unregister_code(KC_RALT); break;
    }
    ralt_state.state = 0;
}

/**
 * rgui / right bracket / right curly brace
 **/

static tap rgui_state = {
  .is_press_action = true,
  .state = 0
};

void rgui_finished(tap_dance_state_t *state, void *user_data) {
    rgui_state.state = cur_dance(state);
    switch(rgui_state.state) {
      case SINGLE_TAP: register_code(KC_RBRC); break;
      case SINGLE_HOLD: register_code(KC_RGUI); break;
      case DOUBLE_TAP: register_code(KC_LSFT); register_code(KC_RBRC); break;
      // fallback to alt because it's the primary purpose of this key
      case DOUBLE_SINGLE_TAP: register_code(KC_RGUI); break;
    }
}
void rgui_reset(tap_dance_state_t *state, void *user_data) {
    switch(rgui_state.state) {
      case SINGLE_TAP: unregister_code(KC_RBRC); break;
      case SINGLE_HOLD: unregister_code(KC_RGUI); break;
      case DOUBLE_TAP: unregister_code(KC_RBRC); unregister_code(KC_LSFT); break;
      case DOUBLE_SINGLE_TAP: unregister_code(KC_RGUI); break;
    }
    rgui_state.state = 0;
}

/**
 * Define the available tap dance keys
 **/

enum {
  TD_ALT_SHIFT = 0,
  TD_LQUT_MINS,
  TD_QUOT_LEAN_MINS,
  TD_LBRC_RALT_LCBR,
  TD_RBRC_RGUI_RCBR
};

tap_dance_action_t tap_dance_actions[] = {
  // Tap once for Alt, twice for Shift
  [TD_ALT_SHIFT] = ACTION_TAP_DANCE_DOUBLE(KC_RALT, KC_RSFT),
  [TD_QUOT_LEAN_MINS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, quote_finished, quote_reset),
  [TD_LBRC_RALT_LCBR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ralt_finished, ralt_reset),
  [TD_RBRC_RGUI_RCBR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rgui_finished, rgui_reset)
};

