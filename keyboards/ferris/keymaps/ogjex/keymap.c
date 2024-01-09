#include "action.h"
#include "action_code.h"
#include "keycodes.h"
#include QMK_KEYBOARD_H

#include "features/tapdance.h"
#include "definitions/keycodes.h"

// Define our tap dance states
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    td_state_t state;
    bool       recording;
} td_tap_t;

typedef struct {
  bool is_press_action;
  int state;
} tap;

// define alttap state for oneshot functions
static tap alttap_state = {
  .is_press_action = true,
  .state = 0
};

// declare variables to be used
static td_tap_t tap_state = {.state = TD_NONE};


 //Our custom tap dance keys; add any other tap dance keys to this enum
enum {
    TD_RESET,
    TD_DELETE,
    TD_BSPACE,
    TD_AE_ENTER,
    TD_TEST_STRING,
    TD_AA_DK,
    TD_OE_DK,
    TD_APP_TAB,
    TD_HOME_P,
    TD_END_N,
    TD_ESC_TM,
    TD_NEXT_T,
    TD_PREV_T,
    ALT_OSL1,
    TD_OSM_SCAW,
    TD_LEFT_SKIP

};

uint16_t key_timer;

// define the various layers
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
    // Base key input layer--------------------                         -----------------------------------------------
    KC_Q, KC_W, KC_E, KC_R, KC_T,                                       KC_Y, KC_U, KC_I, TD(TD_OE_DK), KC_P,
    //-----------------------------------------                         -----------------------------------------------
    TD(TD_AA_DK), KC_S, KC_D, KC_F, KC_G,                               KC_H, KC_J, KC_K, KC_L, TD(TD_AE_ENTER),
    //-----------------------------------------                         -----------------------------------------------
    KC_Z, KC_X , KC_C, KC_V, TD(TD_DELETE),                             KC_B, KC_N, KC_M, KC_COMM, KC_DOT,
    //-----------------------------------------                         -----------------------------------------------
                        OSM(MOD_LSFT), KC_SPC,                          OSL(1), TD(TD_OSM_SCAW)
    ),

    [1] = LAYOUT(
    // Signs and symbols layer, from layer 0---                         ----------------------------------------------
    TD(TD_ESC_TM), KC_AT, KC_HASH, KC_DLR, KC_PERC,                     KC_AMPR, KC_PSLS, KC_PIPE, KC_PMNS, KC_QUES,
    // ----------------------------------------                         ----------------------------------------------
    TD(TD_APP_TAB), KC_CIRC, KC_AT, KC_QUOT, KC_PIPE,                   KC_EXLM, KC_ASTR, KC_LPRN, KC_QUES, KC_ENT,
    // ----------------------------------------                         ----------------------------------------------
    KC_LT, KC_GT, KC_TILD, KC_GRV, KC_TRNS,                             KC_LBRC, KC_LCBR, KC_RCBR, KC_RBRC, TO(3),
    // ----------------------------------------                         ----------------------------------------------
                            TO(0), KC_TRNS,                             TO(2), KC_TRNS
    ),

    [2] = LAYOUT(
    // Numpad layer, from layer 1--------------                         ---------------------------------------------
    KC_TRNS, KC_TRNS, KC_PSLS, KC_PAST, KC_PMNS,                        KC_PEQL, KC_7, KC_8, KC_9, TD(TD_BSPACE),
    // ----------------------------------------                         ---------------------------------------------
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_PPLS,                              KC_PERC, KC_4, KC_5, KC_6, KC_ENT,
    // ----------------------------------------                         ---------------------------------------------
    KC_LSFT, KC_LCTL, KC_LGUI, KC_LALT, KC_TRNS,                        KC_0, KC_1, KC_2, KC_3, KC_PEQL,
    // ----------------------------------------                         ---------------------------------------------
                                TO(0), KC_TRNS,                         TO(4), KC_TRNS
    ),


    [3] = LAYOUT(
    // Navigation layer, from base layer 0-----                         --------------------------------------------
    TD(TD_ESC_TM), KC_WH_L, KC_MS_U, KC_WH_R, KC_WH_U,                  TD(TD_HOME_P), TD(TD_PREV_T), TD(TD_NEXT_T), TD(TD_END_N), TD(TD_BSPACE),
    // ----------------------------------------                         --------------------------------------------
    TD(TD_APP_TAB), KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D,                 TD(TD_LEFT_SKIP), KC_DOWN, KC_UP, KC_RIGHT, KC_ENT,
    // ----------------------------------------                         --------------------------------------------
    KC_BTN2, LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), TD(TD_DELETE),         KC_ACL0, KC_ACL1, KC_ACL2, KC_PGDN, KC_PGUP,
    // ----------------------------------------                         --------------------------------------------
                            TO(0), KC_LSFT,                             KC_BTN1, TD(TD_OSM_SCAW)
    ),

    [4] = LAYOUT(
    // Reset layer, from layer 3---------------                         --------------------------------------------
    QK_BOOTLOADER, KC_Q, KC_NO, KC_NO, KC_NO,                            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    // ----------------------------------------                         ---------------------------------------------
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    // ----------------------------------------                         ---------------------------------------------
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    // ----------------------------------------                         ---------------------------------------------
                                TO(0), KC_NO,                           KC_NO, KC_NO

    ),
};

// -------------------------------------------------------------------------------------
// TAP DANCE INITIALISATION
// -------------------------------------------------------------------------------------
// initiate handlers to define the types of taps

// declare functions to be defined later

td_state_t dance_state(tap_dance_state_t *state);
void alt_finished (tap_dance_state_t *state, void *user_data);
void alt_reset (tap_dance_state_t *state, void *user_data);

td_state_t dance_state(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else
            return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted)
            return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed)
            return TD_DOUBLE_HOLD;
        else
            return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed)
            return TD_TRIPLE_TAP;
        else
            return TD_TRIPLE_HOLD;
    } else
        return TD_UNKNOWN;
}

// example of a full tap dance function structure
void td_send_success_strings(tap_dance_state_t *state, void *user_data) {
    tap_state.state = dance_state(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            SEND_STRING("key tapped once");
            break;
        case TD_DOUBLE_TAP:
            SEND_STRING("key tapped twice");
            break;
        case TD_SINGLE_HOLD:
            SEND_STRING("key held once");
            break;
        case TD_DOUBLE_HOLD:
            SEND_STRING("key held twice");
            break;
        case TD_TRIPLE_TAP:
            SEND_STRING("key tapped thrice");
            break;
        case TD_TRIPLE_HOLD:
            SEND_STRING("key held thrice");
            break;
        default:
            break;
    }
}

// defining DK å
void td_aa(tap_dance_state_t *state, void *user_data) {
    tap_state.state = dance_state(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_A);
            break;
        case TD_SINGLE_HOLD:
            tap_code(KC_LBRC);
            break;
        default:
            break;
    }
}

// defining temporary ø
void td_oe(tap_dance_state_t *state, void *user_data) {
    tap_state.state = dance_state(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_O);
            break;
        case TD_SINGLE_HOLD:
            tap_code(KC_QUOT);
            break;
        default:
            break;
    }
}

// defining right arrow tapdance
void td_right_skip(tap_dance_state_t *state, void *user_data) {
    tap_state.state = dance_state(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_RIGHT);
            break;
        default:
            break;
    }
}

// defining delete key macro
void td_delete(tap_dance_state_t *state, void *user_data) {
    tap_state.state = dance_state(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_DEL);

            break;
        case TD_SINGLE_HOLD:
            SEND_STRING(SS_DOWN(X_LCTL) SS_TAP(X_DEL) SS_UP(X_LCTL));

            break;
        case TD_DOUBLE_HOLD:
            SEND_STRING(SS_DOWN(X_LSFT) SS_DOWN(X_END) SS_TAP(X_DEL) SS_UP(X_LSFT) SS_UP(X_END));

            break;
        default:
            break;
    }
}

// defining backspace key macro
void td_bspace(tap_dance_state_t *state, void *user_data) {
    tap_state.state = dance_state(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_BSPC);
            break;
        case TD_DOUBLE_TAP:
            tap_code(KC_BSPC);
            tap_code(KC_BSPC);
            break;
        case TD_TRIPLE_TAP:
            tap_code(KC_BSPC);
            tap_code(KC_BSPC);
            tap_code(KC_BSPC);
            break;
        case TD_SINGLE_HOLD:
            SEND_STRING(SS_DOWN(X_LCTL) SS_TAP(X_BSPC) SS_UP(X_LCTL));
            break;
        case TD_DOUBLE_HOLD:
            SEND_STRING(SS_DOWN(X_LSFT) SS_DOWN(X_HOME) SS_TAP(X_BSPC) SS_UP(X_LSFT) SS_UP(X_HOME));

            break;
        default:
            break;
    }
}

// enable keyboard reset key
void safe_reset(tap_dance_state_t *state, void *user_data) {
    tap_state.state = dance_state(state);
    switch (tap_state.state) {
        case TD_SINGLE_HOLD:
            SEND_STRING("keyboard should be reset now");
            reset_keyboard();
            break;
        default:
            break;
    }
}

// defining app and tab switcher tapdance key
void td_apptab_switch(tap_dance_state_t *state, void *user_data) {
    tap_state.state = dance_state(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_TAB);
            break;
        case TD_DOUBLE_TAP:
            tap_code(KC_TAB);
            tap_code(KC_TAB);
            break;
        case TD_TRIPLE_TAP:
            tap_code(KC_TAB);
            tap_code(KC_TAB);
            tap_code(KC_TAB);
            break;
        case TD_SINGLE_HOLD:
            SEND_STRING(SS_DOWN(X_LALT) SS_DOWN(X_LCTL) SS_TAP(X_TAB) SS_UP(X_LALT) SS_UP(X_LCTL) );
            break;
        case TD_DOUBLE_HOLD:
            SEND_STRING(SS_DOWN(X_LCTL) SS_TAP(X_TAB) SS_UP(X_LCTL));
        break;
        case TD_TRIPLE_HOLD:
            SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_TAB) SS_UP(X_LGUI));
        default:
            break;
    }
}

// defining esc and task manager tapdance key
    void td_esc_tm(tap_dance_state_t *state, void *user_data) {
    tap_state.state = dance_state(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_ESCAPE);
            break;
        case TD_DOUBLE_HOLD:
            SEND_STRING(SS_DOWN(X_LCTL) SS_DOWN(X_LALT) SS_TAP(X_DEL) SS_UP(X_LCTL) SS_UP(X_LALT));
            break;
        default:
            break;
    }
}

// defining ae and enter tapdance
void td_ae_enter(tap_dance_state_t *state, void *user_data) {
    tap_state.state = dance_state(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_SCLN);
            break;
        case TD_DOUBLE_TAP:
            tap_code(KC_ENT);
            break;
        default:
            reset_tap_dance(state);
            break;
    }
}

// defining previous tab tapdance key
void td_prev_tab(tap_dance_state_t *state, void *user_data) {
    tap_state.state = dance_state(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            SEND_STRING(SS_DOWN(X_LCTL) SS_DOWN(X_LSFT) SS_TAP(X_TAB) SS_UP(X_LCTL) SS_UP(X_LSFT));
            break;
        default:
            break;
    }
}

// defining next tab tapdance key
void td_next_tab(tap_dance_state_t *state, void *user_data) {
    tap_state.state = dance_state(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            SEND_STRING(SS_DOWN(X_LCTL) SS_TAP(X_TAB) SS_UP(X_LCTL));
            break;
        default:
            break;
    }
}

// defining home and previous desktop tapdance key
void td_home_prev(tap_dance_state_t *state, void *user_data) {
    tap_state.state = dance_state(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_HOME);
            break;
        case TD_DOUBLE_TAP:
            SEND_STRING(SS_DOWN(X_LCTL) SS_DOWN(X_LALT) SS_TAP(X_LEFT) SS_UP(X_LALT) SS_UP(X_LCTL));
            break;
        case TD_SINGLE_HOLD:
            SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_LEFT) SS_UP(X_LALT));
            break;
        default:
            break;
    }
}

// defining end and next desktop tapdance key
void td_end_next(tap_dance_state_t *state, void *user_data) {
    tap_state.state = dance_state(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_END);
            break;
        case TD_DOUBLE_TAP:
            SEND_STRING(SS_DOWN(X_LCTL) SS_DOWN(X_LALT) SS_TAP(X_RIGHT) SS_UP(X_LALT) SS_UP(X_LCTL));
            break;
        case TD_SINGLE_HOLD:
            SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_RIGHT) SS_UP(X_LALT));
        default:
            break;
    }
}


// defining one shot mod shift-ctrl-alt and next desktop tapdance key
void td_osm_sft_ctl_alt(tap_dance_state_t *state, void *user_data) {
    tap_state.state = dance_state(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            set_oneshot_mods(MOD_LSFT);
            break;
        case TD_DOUBLE_TAP:
            set_oneshot_mods(MOD_LCTL);
            break;
        case TD_TRIPLE_TAP:
            set_oneshot_mods(MOD_LALT);
            break;
        case TD_SINGLE_HOLD:
            set_oneshot_mods(MOD_LGUI);
            break;
        case TD_DOUBLE_HOLD:
            tap_code(KC_LGUI);
            break;

        default:
            break;
    }
}

void td_left_skip(tap_dance_state_t *state, void *user_data) {
    tap_state.state = dance_state(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_LEFT);
            break;
        case TD_SINGLE_HOLD:
            SEND_STRING(SS_DOWN(X_LCTL) SS_TAP(X_LEFT) SS_UP(X_LCTL));

            break;

        default:
            break;
    }
}

// Defining oneshot layer functions

void alt_finished (tap_dance_state_t *state, void *user_data) {
  alttap_state.state = dance_state(state);
  switch (alttap_state.state) {
    case TD_SINGLE_TAP: set_oneshot_layer(0, ONESHOT_START); clear_oneshot_layer_state(ONESHOT_PRESSED); break;
    case TD_SINGLE_HOLD: register_code(KC_LALT); break;
    case TD_DOUBLE_TAP: set_oneshot_layer(0, ONESHOT_START); set_oneshot_layer(0, ONESHOT_PRESSED); break;
    case TD_DOUBLE_HOLD: register_code(KC_LALT); layer_on(0); break;
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void alt_reset (tap_dance_state_t *state, void *user_data) {
  switch (alttap_state.state) {
    case TD_SINGLE_TAP: break;
    case TD_SINGLE_HOLD: unregister_code(KC_LALT); break;
    case TD_DOUBLE_TAP: break;
    case TD_DOUBLE_HOLD: layer_off(0); unregister_code(KC_LALT); break;
  }
  alttap_state.state = 0;

}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_TRNS:
    case KC_NO:
      /* Always cancel one-shot layer when another key gets pressed */
      if (record->event.pressed && is_oneshot_layer_active()){
      clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
      return true;
      }
    case QK_BOOTLOADER:
      /* Don't allow reset from oneshot layer state */
      if (record->event.pressed && is_oneshot_layer_active()){
        clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
        return false;
      }
      return true;
    default:
      return true;
  }
  return true;
}

// define per key tapping term
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case TD(TD_OSM_SCAW):
      return 150;
    case TD(TD_BSPACE):
      return 50;
    case TD(TD_DELETE):
      return 50;
    default:
      return TAPPING_TERM;
  }
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(TD_LEFT_SKIP):
            return QUICK_TAP_TERM - 20;
        default:
            return QUICK_TAP_TERM;
    }
}

//Associate our tap dance key with its functionality
tap_dance_action_t tap_dance_actions[] = {
    [TD_RESET] = ACTION_TAP_DANCE_FN(safe_reset),
    [TD_DELETE] = ACTION_TAP_DANCE_FN(td_delete),
    [TD_BSPACE] = ACTION_TAP_DANCE_FN(td_bspace),
    [TD_AE_ENTER] = ACTION_TAP_DANCE_FN(td_ae_enter),
    [TD_TEST_STRING] = ACTION_TAP_DANCE_FN(td_send_success_strings),
    [TD_AA_DK] = ACTION_TAP_DANCE_FN(td_aa),
    [TD_OE_DK] = ACTION_TAP_DANCE_FN(td_oe),
    [TD_APP_TAB] = ACTION_TAP_DANCE_FN(td_apptab_switch),
    [TD_HOME_P] = ACTION_TAP_DANCE_FN(td_home_prev),
    [TD_END_N] = ACTION_TAP_DANCE_FN(td_end_next),
    [TD_ESC_TM] = ACTION_TAP_DANCE_FN(td_esc_tm),
    [TD_NEXT_T] = ACTION_TAP_DANCE_FN(td_next_tab),
    [TD_PREV_T] = ACTION_TAP_DANCE_FN(td_prev_tab),
    [ALT_OSL1]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL,alt_finished, alt_reset),
    [TD_OSM_SCAW] = ACTION_TAP_DANCE_FN(td_osm_sft_ctl_alt),
    [TD_LEFT_SKIP] = ACTION_TAP_DANCE_FN(td_left_skip)
};

// old code from here

// -------------------------------------------------------------------------------------
// ONESHOT MOD INITIALISATION
// -------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------
// MACRO INITIALISATION
// -------------------------------------------------------------------------------------

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {

};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
