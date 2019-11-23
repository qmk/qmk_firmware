#include QMK_KEYBOARD_H

enum layer_names {
    _BASE,
    _MACRO,
    _MOD
};

enum custom_keycodes {
    M801 = SAFE_RANGE,
    M802,
    M803,
    M804,
    M805,
    M806,
    MAIL_C
};

// tapdance keycodes
enum td_keycodes {
    LAY  // Our example key: `LALT` when held, `(` when tapped. Add additional keycodes for each tapdance.
};

// define a type containing as many tapdance states as you need
typedef enum {
  SINGLE_TAP,
  SINGLE_HOLD,
} td_state_t;

// create a global instance of the tapdance state type
static td_state_t td_state;

// declare your tapdance functions:

// function to determine the current tapdance state
int cur_dance (qk_tap_dance_state_t *state);

// `finished` and `reset` functions for each tapdance keycode
void altlp_finished (qk_tap_dance_state_t *state, void *user_data);
void altlp_reset (qk_tap_dance_state_t *state, void *user_data);

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case M801:
      if (record->event.pressed) {
        SEND_STRING("M801" SS_TAP(X_ENTER));
      }
      break;
    case M802:
      if (record->event.pressed) {
          SEND_STRING("M802" SS_TAP(X_ENTER));
      }
      break;
    case M803:
      if (record->event.pressed) {
          SEND_STRING("M803" SS_TAP(X_ENTER));
      }
      break;
     case M804:
      if (record->event.pressed) {
          SEND_STRING("M804" SS_TAP(X_ENTER));
      }
      break; 
    case M805:
      if (record->event.pressed) {
          SEND_STRING("M805" SS_TAP(X_ENTER));
      }
      break;
    case M806:
      if (record->event.pressed) {
          SEND_STRING("M806" SS_TAP(X_ENTER));
      }
      break;
    case MAIL_C:
      if (record->event.pressed) {
          SEND_STRING(SS_TAP(X_ENTER) SS_TAP(X_DOWN) SS_TAP(X_DOWN) SS_TAP(X_ENTER));
      }
      break;
  }

  return true;
};

#define EX_ARR LCTL(LSFT(KC_ENTER))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
    // ┌────────┬────────┬────────┐
         KC_MUTE, KC_UP,  TD(LAY),
    // ├────────┼────────┼────────┤
         KC_LEFT, KC_DOWN, KC_RGHT,
    // ├────────┼────────┼────────┤
         KC_NO,   KC_NO,   KC_NO
    // └────────┴────────┴────────┘
        ),
    [_MACRO] = LAYOUT(
    // ┌────────┬────────┬────────┐
        _______,  KC_SPC, TG(_MACRO),
    // ├────────┼────────┼────────┤
          M801,    M802,    M803,
    // ├────────┼────────┼────────┤
         MAIL_C,  KC_NO,   EX_ARR
    // └────────┴────────┴────────┘
        ),
    [_MOD] = LAYOUT(
    // ┌────────┬────────┬────────┐
        _______,  BL_STEP,TG(_MOD),
    // ├────────┼────────┼────────┤
         KC_NO,  RGB_MOD,  KC_NO,
    // ├────────┼────────┼────────┤
         KC_NO,   KC_NO,   KC_NO
    // └────────┴────────┴────────┘
        )
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLD);
        } else {
            tap_code(KC_VOLU);
        }
    }
}

// determine the tapdance state to return
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) { return SINGLE_TAP; }
    else { return SINGLE_HOLD; }
  } else { return 3; } // any number higher than the maximum state value you return above
}

// handle the possible states for each tapdance keycode you define:

void altlp_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case SINGLE_TAP:
      layer_on(_MACRO);
      break;
    case SINGLE_HOLD:
      layer_on(_MOD);
      break;
  }
}

void altlp_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case SINGLE_TAP:
      break;
    case SINGLE_HOLD:
      layer_off(_MOD);
      break;
  }
}

// define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
qk_tap_dance_action_t tap_dance_actions[] = {
  [LAY] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, altlp_finished, altlp_reset)
};
