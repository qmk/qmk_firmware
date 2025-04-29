#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif

typedef struct {
  bool is_press_action;
  int state;
} tap;

//Define a type for as many tap dance states as you need
enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3
};

enum {
  CAPS_LAYER = 0     //Our custom tap dance key; add any other tap dance keys to this enum 
};

// Having to implement Space Cadet manually, since () are on layers
enum custom_keycodes {
    SPC_LSPO = SAFE_RANGE,
    SPC_RSPC,
};


//Declare the functions to be used with your tap dance key(s)

//Function associated with all tap dances
int cur_dance (tap_dance_state_t *state);

//Functions associated with individual tap dances
void ql_finished (tap_dance_state_t *state, void *user_data);
void ql_reset (tap_dance_state_t *state, void *user_data);

//Determine the current tap dance state
int cur_dance (tap_dance_state_t *state) {
  if (state->count == 1) {
    if (!state->pressed) {
      return SINGLE_TAP;
    } else {
      return SINGLE_HOLD;
    }
  } else if (state->count == 2) {
    return DOUBLE_TAP;
  }
  else return 8;
}

//Initialize tap structure associated with example tap dance key
static tap ql_tap_state = {
  .is_press_action = true,
  .state = 0
};

//Functions that control what our tap dance key does
void ql_finished (tap_dance_state_t *state, void *user_data) {
  ql_tap_state.state = cur_dance(state);
  switch (ql_tap_state.state) {
    case SINGLE_TAP: 
      break;
    case SINGLE_HOLD: 
      layer_on(1); 
      break;
    case DOUBLE_TAP: 
      tap_code(KC_CAPS);
      break;
  }
}

void ql_reset (tap_dance_state_t *state, void *user_data) {
  //if the key was held down and now is released then switch off the layer
  if (ql_tap_state.state==SINGLE_HOLD) {
    layer_off(1);
  }
  ql_tap_state.state = 0;
}

//Associate our tap dance key with its functionality
tap_dance_action_t tap_dance_actions[] = {
  [CAPS_LAYER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ql_finished, ql_reset)
};

// Manually implementing Space Cadet since my parens are on layers and can't be sent with native keycodes
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SPC_LSPO:
            if (record->event.pressed) {
                register_mods(MOD_BIT(KC_LSFT));
            } else {
                unregister_mods(MOD_BIT(KC_LSFT));
                if (record->tap.count && !record->tap.interrupted) {
                    // Send ( by temporarily enabling Layer 2 and pressing KC_O
                    layer_on(2);
                    tap_code(KC_O);
                    layer_off(2);
                }
            }
            return false;

        case SPC_RSPC:
            if (record->event.pressed) {
                register_mods(MOD_BIT(KC_RSFT));
            } else {
                unregister_mods(MOD_BIT(KC_RSFT));
                if (record->tap.count && !record->tap.interrupted) {
                    // Send ) by temporarily enabling Layer 2 and pressing KC_P
                    layer_on(2);
                    tap_code(KC_P);
                    layer_off(2);
                }
            }
            return false;
    }
    return true;
}




const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, TD(CAPS_LAYER), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_ENT, SC_LSPO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, SC_RSPC, KC_LCTL, KC_LGUI, KC_LALT, LT(2,KC_SPC), KC_SPC, MO(3), MO(4), KC_RCTL),
  [1] = LAYOUT(KC_NO, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC, KC_NO, KC_GRV, KC_BSLS, KC_NO, KC_NO, KC_NO, KC_EQL, KC_NO, KC_SCLN, KC_QUOT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MINS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),
  [2] = LAYOUT(KC_NO, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, KC_NO, KC_TILD, KC_PIPE, KC_LBRC, KC_RBRC, KC_NO, KC_PLUS, KC_NO, KC_COLN, KC_DQUO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LCBR, KC_RCBR, KC_UNDS, KC_NO, KC_NO, KC_NO, KC_SLSH, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_UP, KC_DOWN, KC_LEFT, KC_RGHT),
  [3] = LAYOUT(KC_ESC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_UP, KC_NO, KC_NO, KC_NO, KC_DEL, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_QUES, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),
  [4] = LAYOUT(KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_PSCR, KC_NO, KC_F11, KC_F12, KC_NO, KC_NO, KC_INS, KC_HOME, KC_PGUP, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_DEL, KC_END, KC_PGDN, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO)
};



#ifdef OTHER_KEYMAP_C
#    include OTHER_KEYMAP_C
#endif // OTHER_KEYMAP_C