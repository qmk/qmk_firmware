#include "quantum.h"
#include "action.h"
#include "process_keycode/process_tap_dance.h"
#include "keymap_french.h"


//ref = https://beta.docs.qmk.fm/features/feature_tap_dance
// https://gist.github.com/frederik-h/578524281a0b63ab143de1acd1d30bee

typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  HOLD = 1,
  SINGLE_TAP = 2,
  DOUBLE_TAP = 3,
  TRIPLE_TAP = 4,
  QUAD_TAP = 5
};


enum {
  OPEN = 2,
  CLOSE = 3

};

int cur_dance (qk_tap_dance_state_t *state) {

  if (state->count == 1)
    return SINGLE_TAP;

  if (state->count == 2)
    return DOUBLE_TAP;

  if (state->count == 3)
    return TRIPLE_TAP;

  if (state->count == 4)
    return QUAD_TAP;

   return -1;
}

static tap open_tap_state = {
  .is_press_action = true,
  .state = 0
};


static tap close_tap_state = {
  .is_press_action = true,
  .state = 0
};

void open_finished (qk_tap_dance_state_t *state, void *user_data) {
  open_tap_state.state = cur_dance(state);
  switch (open_tap_state.state) {
  case SINGLE_TAP:
  register_code(FR_V); // V
    break;

  case DOUBLE_TAP:
 unregister_code(FR_V);
  register_code(KC_5); // (
    break;
  case TRIPLE_TAP:
    unregister_code(KC_4);
    register_mods(MOD_BIT(FR_ALGR));
    register_code(KC_5); // [
    break;

  case QUAD_TAP:
    unregister_code(KC_5);
    register_mods(MOD_BIT(FR_ALGR));
    register_code(KC_4); // {
    break;


  }
}



void open_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (open_tap_state.state) {
  case SINGLE_TAP:
    unregister_code(FR_V); // V
    break;
  case DOUBLE_TAP:
    unregister_code(KC_5); // (
    break;
  case TRIPLE_TAP:
    unregister_code(KC_5); // [
   unregister_mods(MOD_BIT(FR_ALGR));

    break;
  case QUAD_TAP:
  unregister_code(KC_4); // {
   unregister_mods(MOD_BIT(FR_ALGR));
    break;


  }
  open_tap_state.state = 0;
}


void close_finished (qk_tap_dance_state_t *state, void *user_data) {
  close_tap_state.state = cur_dance(state);
  switch (close_tap_state.state) {
  case SINGLE_TAP:

    register_code(FR_B);
    break;
  case DOUBLE_TAP:
  unregister_code(FR_B);
    register_code(KC_MINS); // )
    break;
  case TRIPLE_TAP:
    unregister_code(KC_MINS);
    register_mods(MOD_BIT(KC_RALT));
    register_code(KC_MINS); // ]
    break;
  case QUAD_TAP:
    unregister_code(KC_MINS);
register_mods(MOD_BIT(FR_ALGR));
    register_code(KC_EQL); // }
    break;

  }
}

void close_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (close_tap_state.state) {
  case SINGLE_TAP:
    unregister_code(FR_B);
    break;
  case DOUBLE_TAP:
    unregister_code(KC_MINS); // )
    break;
  case TRIPLE_TAP:
    unregister_code(KC_MINS); // ]
     unregister_mods(MOD_BIT(KC_RALT));
    break;
  case QUAD_TAP:
    unregister_code(KC_EQL); // }
    unregister_mods(MOD_BIT(KC_RALT));
    break;

  }
  close_tap_state.state = 0;
}

//ACCENTS

enum {
  TD_A = 4,
  TD_E = 5

};

static tap td_a_tap_state = {
  .is_press_action = true,
  .state = 0
};
static tap td_e_tap_state = {
  .is_press_action = true,
  .state = 0
};
void td_a_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_a_tap_state.state = cur_dance(state);
  switch (td_a_tap_state.state) {
  case SINGLE_TAP:
  register_code(FR_A); // V
    break;

  case DOUBLE_TAP:
 unregister_code(FR_A);
 register_code(FR_ALGR);
  register_code(KC_0); // (
    break;
  case TRIPLE_TAP:
    unregister_code(KC_0);
    unregister_code(FR_ALGR);

    register_code(KC_0); // [
    break;

  case QUAD_TAP:
   unregister_code(KC_0);
    register_code(FR_A); // {
    break;


  }
}



void td_a_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (td_a_tap_state.state) {
  case SINGLE_TAP:
    unregister_code(FR_A); // V
    break;
  case DOUBLE_TAP:
    unregister_code(KC_0);
    unregister_code(FR_ALGR);

    break;
  case TRIPLE_TAP:

   unregister_code(KC_0);


    break;
  case QUAD_TAP:
  unregister_code(FR_A); // {

    break;


  }
  td_a_tap_state.state = 0;
}


void td_e_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_e_tap_state.state = cur_dance(state);
  switch (td_e_tap_state.state) {
  case SINGLE_TAP:

    register_code(FR_E); // e
    break;
  case DOUBLE_TAP:
  unregister_code(FR_E);
    register_code(KC_2); // é
    break;
  case TRIPLE_TAP:
    unregister_code(KC_2);

    register_code(KC_7); // è
    break;
  case QUAD_TAP:
    unregister_code(KC_7);
    register_code(FR_HAT);
    register_code(KC_E); // ê
    break;

  }
}

void td_e_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (td_e_tap_state.state) {
  case SINGLE_TAP:
    unregister_code(FR_E);
    break;
  case DOUBLE_TAP:
    unregister_code(KC_2); // )
    break;
  case TRIPLE_TAP:
    unregister_code(KC_7); // ]
    break;
  case QUAD_TAP:
    unregister_code(KC_E); // }
    unregister_code(FR_HAT);
    break;

  }
  td_e_tap_state.state = 0;
}
