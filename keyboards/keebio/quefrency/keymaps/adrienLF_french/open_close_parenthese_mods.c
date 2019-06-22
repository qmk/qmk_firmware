#include "quantum.h"
#include "action.h"
#include "process_keycode/process_tap_dance.h"

//ref = https://beta.docs.qmk.fm/features/feature_tap_dance
// https://gist.github.com/frederik-h/578524281a0b63ab143de1acd1d30bee


enum {
SHIFT_PAR_O=6,
  CTRL_BRACK_O,
  ALT_CURL_O,
  SHIFT_PAR_C,
  CTRL_BRACK_C,
  ALT_CURL_C,

};


//SHIFT
static tap shift_o_tap_state = {
  .is_press_action = true,
  .state = 0
};

void shift_o_finished (qk_tap_dance_state_t *state, void *user_data) {
  shift_o_tap_state.state = cur_dance(state);
  switch (shift_o_tap_state.state) {
  case SINGLE_TAP:
  register_code(KC_LSHIFT);
    break;

  case DOUBLE_TAP:
 unregister_code(KC_LSHIFT);
 register_code(KC_5);

    break;


  }
}



void shift_o_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (shift_o_tap_state.state) {
  case SINGLE_TAP:
    unregister_code(KC_LSHIFT);
    break;
  case DOUBLE_TAP:
    unregister_code(KC_5);
    break;
  }
  shift_o_tap_state.state = 0;
}

//CTRL
static tap ctrl_o_o_tap_state = {
  .is_press_action = true,
  .state = 0
};

void ctrl_o_o_finished (qk_tap_dance_state_t *state, void *user_data) {
  ctrl_o_o_tap_state.state = cur_dance(state);
  switch (ctrl_o_o_tap_state.state) {
  case SINGLE_TAP:

    register_code(KC_LCTL); // e
    break;
  case DOUBLE_TAP:
  unregister_code(KC_LCTL);
 register_mods(MOD_BIT(FR_ALGR));
    register_code(KC_5); // [
    break;

  }
}


void ctrl_o_o_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (ctrl_o_o_tap_state.state) {
  case SINGLE_TAP:
      unregister_code(KC_LCTL);
    break;
  case DOUBLE_TAP:
    unregister_mods(MOD_BIT(FR_ALGR));
    unregister_code(KC_5); // [

    break;

  }
  ctrl_o_o_tap_state.state = 0;
}

//ALT
static tap alt_o_tap_state = {
  .is_press_action = true,
  .state = 0
};
void alt_o_finished (qk_tap_dance_state_t *state, void *user_data) {
  alt_o_tap_state.state = cur_dance(state);
  switch (alt_o_tap_state.state) {
  case SINGLE_TAP:

    register_code(KC_LALT); // e
    break;
  case DOUBLE_TAP:
  unregister_code(KC_LALT);
    register_mods(MOD_BIT(FR_ALGR));
    register_code(KC_4); // {
    break;

  }
}

void alt_o_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (alt_o_tap_state.state) {
  case SINGLE_TAP:
  unregister_code(KC_LALT);

    break;
  case DOUBLE_TAP:
  unregister_code(KC_4); // {
    unregister_mods(MOD_BIT(FR_ALGR));

    break;

  }
  alt_o_tap_state.state = 0;
}



////////////////////////////////////////////CLOSE



//SHIFT
static tap shift_c_tap_state = {
  .is_press_action = true,
  .state = 0
};


void shift_c_finished (qk_tap_dance_state_t *state, void *user_data) {
  shift_c_tap_state.state = cur_dance(state);
  switch (shift_c_tap_state.state) {
  case SINGLE_TAP:
  register_code(KC_RSHIFT);
    break;

  case DOUBLE_TAP:
 unregister_code(KC_RSHIFT);
     register_code(KC_MINS); // )
    break;


  }
}



void shift_c_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (shift_c_tap_state.state) {
  case SINGLE_TAP:
    unregister_code(KC_RSHIFT);
    break;
  case DOUBLE_TAP:
    unregister_code(KC_MINS); // )
    break;
  }

  shift_c_tap_state.state = 0;
}

//CTRL
static tap ctrl_c_c_tap_state = {
  .is_press_action = true,
  .state = 0
};

void ctrl_c_c_finished (qk_tap_dance_state_t *state, void *user_data) {
  ctrl_c_c_tap_state.state = cur_dance(state);
  switch (ctrl_c_c_tap_state.state) {
  case SINGLE_TAP:

    register_code(KC_RCTL); // e
    break;
  case DOUBLE_TAP:
  unregister_code(KC_RCTL);
    register_mods(MOD_BIT(KC_RALT));
    register_code(KC_MINS); // ]
    break;

  }
}


void ctrl_c_c_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (ctrl_c_c_tap_state.state) {
  case SINGLE_TAP:
  unregister_code(KC_RCTL);

    break;
  case DOUBLE_TAP:

    unregister_code(KC_MINS); // ]
    unregister_mods(MOD_BIT(KC_RALT));
    break;

  }
  ctrl_c_c_tap_state.state = 0;
}

//ALT
static tap alt_c_tap_state = {
  .is_press_action = true,
  .state = 0
};
void alt_c_finished (qk_tap_dance_state_t *state, void *user_data) {
  alt_c_tap_state.state = cur_dance(state);
  switch (alt_c_tap_state.state) {
  case SINGLE_TAP:

    register_code(KC_RALT); // e
    break;
  case DOUBLE_TAP:
  register_mods(MOD_BIT(KC_RALT));
    register_code(KC_EQL); // }
    break;

  }
}

void alt_c_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (alt_c_tap_state.state) {
  case SINGLE_TAP:
    unregister_code(KC_RALT);
    break;
  case DOUBLE_TAP:

    unregister_code(KC_EQL); // }
    unregister_mods(MOD_BIT(KC_RALT));
    break;

  }
  alt_o_tap_state.state = 0;
}
