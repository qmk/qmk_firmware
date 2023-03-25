#include QMK_KEYBOARD_H
enum custom_keycodes{
  M1 = SAFE_RANGE,
  SumaPos,
  SumaNeg,
};
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case M1:
        if (record->event.pressed) {
            // when keycode M1 is pressed
            SEND_STRING(SS_TAP(X_LALT) SS_DELAY(45) SS_TAP(X_O) SS_DELAY(45) SS_TAP(X_V) SS_DELAY(45) SS_TAP(X_V));
            } else {
            // when keycode M1 is released
        }
        break;
    case SumaPos:
        if (record->event.pressed) {
            // when keycode SumaPos is pressed
            SEND_STRING("=suma(");
            } else {
            // when keycode SumaPos is released
        }
        break;
    case SumaNeg:
        if (record->event.pressed) {
            // when keycode SumaNeg is pressed
            SEND_STRING("-suma(");
            } else {
            // when keycode SumaNeg is released
        }
        break;
    }
    return true; //macro pegar como valor
};
uint32_t layer_state_set_user(uint32_t state) {
  switch (biton32(state)) {
    case 0:
      backlight_set(0);
      break;
    case 1:
      backlight_set(1);
      break;
    case 2:
      backlight_set(2);
      break;
  }
  return state;  //estados de backlight vs layer
};

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_TRIPLE_TAP,
    TD_TEN_TAP
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

enum {
    TAPDANCEKEY, // Our custom tap dance key; add any other tap dance keys to this enum 
};

// Declare the functions to be used with your tap dance key(s)

// Function associated with all tap dances
td_state_t cur_dance(qk_tap_dance_state_t *state);

// Functions associated with individual tap dances
void ql_finished(qk_tap_dance_state_t *state, void *user_data);
void ql_reset(qk_tap_dance_state_t *state, void *user_data);


//LAYERS DEL TECLADO
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    LSFT(LGUI(KC_S)), LCTL(LALT(KC_F11)), MO(2),      LCTL(KC_S), \
    LCTL(KC_N),       SumaNeg,            SumaPos,    LCTL(KC_N), \
    LCTL(KC_K),       LCTL(KC_X),         LCTL(KC_V), LCTL(KC_K), \
    LCTL(KC_P),       LCTL(KC_C),         M1,         KC_PENT, \
    LSFT(LGUI(KC_S)), LCTL(LALT(KC_F11)), TD(TAPDANCEKEY),      KC_NO \
  ),

  [1] = LAYOUT(
    KC_TRNS, KC_TRNS, KC_PSLS, KC_PAST, \
    KC_P7,   KC_P8,   KC_P9,   KC_PMNS, \
    KC_P4,   KC_P5,   KC_P6,   KC_PPLS, \
    KC_P1,   KC_P2,   KC_P3,   KC_PENT, \
    KC_P0,   KC_PDOT, KC_TRNS, KC_NO \
  ),

  [2] = LAYOUT(
    RESET,     KC_NO,     KC_TRNS,    KC_NLCK, \
    KC_NO,     KC_NO,     KC_NO,      KC_NO, \
    KC_NO,     KC_NO,     KC_NO,      KC_NO, \
    KC_NO,     KC_NO,     KC_NO,      KC_NO, \
    KC_NO,     KC_NO,     KC_TRNS,    KC_NO \
  ),
};


// Determine the current tap dance state
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 3) {;
        if (!state->pressed) return TD_TRIPLE_TAP;
        else return TD_UNKNOWN;
    } else if (state->count == 10) {;
        if (!state->pressed) return TD_TEN_TAP;
        else return TD_UNKNOWN;
    }else return TD_UNKNOWN;
}

// Initialize tap structure associated with example tap dance key
static td_tap_t ql_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void ql_finished(qk_tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            //tap_code(KC_A);
            break;
        case TD_SINGLE_HOLD:
            if (layer_state_is(0)) {
                layer_on(1);
            } else if (layer_state_is(1)) {
                layer_off(1);
            }
            break;
        case TD_TRIPLE_TAP:
            // Check to see if the layer is already set
            if (layer_state_is(1)) {
                // If already set, then switch it off
                layer_off(1);
            } else {
                // If not already set, then switch the layer on
                layer_on(1);
            }
            break;
        case TD_TEN_TAP:
            // Check to see if the layer is already set
            if (layer_state_is(2)) {
                // If already set, then switch it off
                layer_off(2);
            } else {
                // If not already set, then switch the layer on
                layer_on(2);
            }
            break;
        default:
            break;
    }
}

void ql_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (ql_tap_state.state == TD_SINGLE_HOLD) {
        if (layer_state_is(1)) {
            layer_off(1);
        } else if (layer_state_is(0)) {
            layer_on(1);  
        }
        
    }
    ql_tap_state.state = TD_NONE;
}

// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    [TAPDANCEKEY] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, ql_finished, ql_reset, 275)
};
