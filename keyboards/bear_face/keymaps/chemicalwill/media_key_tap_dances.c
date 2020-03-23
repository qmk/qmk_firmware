//define xtap
typedef struct {
  bool is_press_action;
  int state;
} xtap;

//Tap Dance states
enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
};

//Tap Dance enums
enum {
  F1_MUTE = 0,
  F2_VOLD = 1,
  F3_VOLU = 2,
  F4_MPRV = 3,
  F5_MPLY = 4,
  F6_MNXT = 5
};

//set up Tap Dance for tap vs. hold
int cur_dance (qk_tap_dance_state_t *state);

//Tap Dance specific functions
void f1_finished (qk_tap_dance_state_t *state, void *user_data);
void f1_reset (qk_tap_dance_state_t *state, void *user_data);

void f2_finished (qk_tap_dance_state_t *state, void *user_data);
void f2_reset (qk_tap_dance_state_t *state, void *user_data);

void f3_finished (qk_tap_dance_state_t *state, void *user_data);
void f3_reset (qk_tap_dance_state_t *state, void *user_data);

void f4_finished (qk_tap_dance_state_t *state, void *user_data);
void f4_reset (qk_tap_dance_state_t *state, void *user_data);

void f5_finished (qk_tap_dance_state_t *state, void *user_data);
void f5_reset (qk_tap_dance_state_t *state, void *user_data);

void f6_finished (qk_tap_dance_state_t *state, void *user_data);
void f6_reset (qk_tap_dance_state_t *state, void *user_data);

//determine Tap Dance state
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->interrupted || !state->pressed) {
    return SINGLE_TAP;
  } else {
    //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'
    return SINGLE_HOLD;
  }
};

//instance 'xtap' for the 'F1/mute' tap dance
static xtap f1tap_state = {
  .is_press_action = true,
  .state = 0
};
void f1_finished (qk_tap_dance_state_t *state, void *user_data) {
  f1tap_state.state = cur_dance(state);
  switch (f1tap_state.state) {
    case SINGLE_TAP:
      register_code(KC_MUTE);
      break;
    case SINGLE_HOLD:
      register_code(KC_F1);
      break;
  }
}
void f1_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (f1tap_state.state) {
    case SINGLE_TAP:
      unregister_code(KC_MUTE);
      break;
    case SINGLE_HOLD:
      unregister_code(KC_F1);
      break;
  }
  f1tap_state.state = 0;
}

//instance 'xtap' for the 'F2/volume down' tap dance
static xtap f2tap_state = {
  .is_press_action = true,
  .state = 0
};
void f2_finished (qk_tap_dance_state_t *state, void *user_data) {
  f2tap_state.state = cur_dance(state);
  switch (f2tap_state.state) {
    case SINGLE_TAP:
      register_code(KC_VOLD);
      break;
    case SINGLE_HOLD:
      register_code(KC_F2);
      break;
  }
}
void f2_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (f2tap_state.state) {
    case SINGLE_TAP:
      unregister_code(KC_VOLD);
      break;
    case SINGLE_HOLD:
      unregister_code(KC_F2);
      break;
  }
  f2tap_state.state = 0;
}

//instance 'xtap' for the 'F3/volume up' tap dance
static xtap f3tap_state = {
  .is_press_action = true,
  .state = 0
};
void f3_finished (qk_tap_dance_state_t *state, void *user_data) {
  f3tap_state.state = cur_dance(state);
  switch (f3tap_state.state) {
    case SINGLE_TAP:
      register_code(KC_VOLU);
      break;
    case SINGLE_HOLD:
      register_code(KC_F3);
      break;
  }
}
void f3_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (f3tap_state.state) {
    case SINGLE_TAP:
      unregister_code(KC_VOLU);
      break;
    case SINGLE_HOLD:
      unregister_code(KC_F3);
      break;
  }
  f3tap_state.state = 0;
}

//instance 'xtap' for the 'F4/previous' tap dance
static xtap f4tap_state = {
  .is_press_action = true,
  .state = 0
};
void f4_finished (qk_tap_dance_state_t *state, void *user_data) {
  f4tap_state.state = cur_dance(state);
  switch (f4tap_state.state) {
    case SINGLE_TAP:
      register_code(KC_MPRV);
      break;
    case SINGLE_HOLD:
      register_code(KC_F4);
      break;
  }
}
void f4_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (f4tap_state.state) {
    case SINGLE_TAP:
      unregister_code(KC_MPRV);
      break;
    case SINGLE_HOLD:
      unregister_code(KC_F4);
      break;
  }
  f4tap_state.state = 0;
}

//instance 'xtap' for the 'F5/play+pause' tap dance
static xtap f5tap_state = {
  .is_press_action = true,
  .state = 0
};
void f5_finished (qk_tap_dance_state_t *state, void *user_data) {
  f5tap_state.state = cur_dance(state);
  switch (f5tap_state.state) {
    case SINGLE_TAP:
      register_code(KC_MPLY);
      break;
    case SINGLE_HOLD:
      register_code(KC_F5);
      break;
  }
}
void f5_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (f5tap_state.state) {
    case SINGLE_TAP:
      unregister_code(KC_MPLY);
      break;
    case SINGLE_HOLD:
      unregister_code(KC_F5);
      break;
  }
  f5tap_state.state = 0;
}

//instance 'xtap' for the 'F6/next' tap dance
static xtap f6tap_state = {
  .is_press_action = true,
  .state = 0
};
void f6_finished (qk_tap_dance_state_t *state, void *user_data) {
  f6tap_state.state = cur_dance(state);
  switch (f6tap_state.state) {
    case SINGLE_TAP:
      register_code(KC_MNXT);
      break;
    case SINGLE_HOLD:
      register_code(KC_F6);
      break;
  }
}
void f6_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (f6tap_state.state) {
    case SINGLE_TAP:
      unregister_code(KC_MNXT);
      break;
    case SINGLE_HOLD:
      unregister_code(KC_F6);
      break;
  }
  f6tap_state.state = 0;
}

//Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [F1_MUTE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, f1_finished, f1_reset),
  [F2_VOLD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, f2_finished, f2_reset),
  [F3_VOLU] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, f3_finished, f3_reset),
  [F4_MPRV] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, f4_finished, f4_reset),
  [F5_MPLY] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, f5_finished, f5_reset),
  [F6_MNXT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, f6_finished, f6_reset)
};

//Tap Dance declarations
#define F1_MUTE TD(F1_MUTE)
#define F2_VOLD TD(F2_VOLD)
#define F3_VOLU TD(F3_VOLU)
#define F4_MPRV TD(F4_MPRV)
#define F5_MPLY TD(F5_MPLY)
#define F6_MNXT TD(F6_MNXT)