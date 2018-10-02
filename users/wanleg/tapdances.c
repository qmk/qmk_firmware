//Tap Dance Settings
#include "wanleg.h"

///// QUAD FUNCTION TAP DANCE GENERAL SETUP SECTION START /////
///// (no need to edit this section) /////
//Enums used to clearly convey the state of the tap dance
enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send SINGLE_TAP twice - NOT DOUBLE_TAP
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7,
  TRIPLE_SINGLE_TAP = 8
  // Add more enums here if you want for triple, quadruple, etc.
};

typedef struct {
  bool is_press_action;
  int state;
} tap;

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    //If count = 1, and it has been interrupted - it doesn't matter if it is pressed or not: Send SINGLE_TAP
    if (state->interrupted || !state->pressed) return SINGLE_TAP;
    if (state->interrupted) return SINGLE_TAP;
    else return SINGLE_HOLD;
  }
  //If count = 2, and it has been interrupted - assume that user is trying to type the letter associated
  //with single tap.
  else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  
  //If count = 3, and it has been interrupted - assume that user is trying to type the letter associated
  //with double tap.
  else if (state->count == 3) {
    if (state->interrupted) return TRIPLE_SINGLE_TAP;
    else if (state->pressed) return TRIPLE_HOLD;
    else return TRIPLE_TAP;
  }
  else return 9; //magic number. At some point this method will expand to work for more presses
}
///// QUAD FUNCTION TAP DANCE GENERAL SETUP SECTION END /////
///// QUAD FUNCTION TAP DANCE PERSONALIZATION SECTION START /////
//instantiate 'tap' for the 'CAD' tap dance.
static tap CADtap_state = {
  .is_press_action = true,
  .state = 0
};

void CAD_finished (qk_tap_dance_state_t *state, void *user_data) {
  CADtap_state.state = cur_dance(state);
  switch (CADtap_state.state) {
    case SINGLE_TAP: 
		//register_code(KC_SPC); 
		SEND_STRING(SS_LGUI("l"));
		#ifdef BACKLIGHT_ENABLE
		backlight_set(3);
		#endif
		break;
    case SINGLE_HOLD: 
		//register_code(KC_NO);
		//take a screenshot of a single window, open Paint and paste
		SEND_STRING(SS_LALT(SS_TAP(X_PSCREEN)) SS_LGUI("r"));
        _delay_ms(500);
        SEND_STRING("mspaint" SS_TAP(X_ENTER));
        _delay_ms(700);
        SEND_STRING(SS_LCTRL("v"));
		break; //register this keycode when button is held
    case DOUBLE_TAP: 
		//register_code(KC_ENT); 
		SEND_STRING(SS_LCTRL(SS_LALT(SS_TAP(X_DELETE))));
		#ifdef BACKLIGHT_ENABLE
		backlight_set(0);
		#endif
		break;
    //case DOUBLE_HOLD: register_code(KC_NO); break; //register this keycode when button is tapped and then held
	case DOUBLE_HOLD: 
		reset_keyboard(); 
		break; //register this keycode when button is tapped and then held
	case TRIPLE_TAP:
		SEND_STRING("wanleg@github.com");
		break;
	case TRIPLE_HOLD: set_single_persistent_default_layer(1); break;
  }
}

void CAD_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (CADtap_state.state) {
//nothing to do
  }
  CADtap_state.state = 0;
}  
  
//instantiate 'tap' for the 'RST' tap dance.
static tap RSTtap_state = {
  .is_press_action = true,
  .state = 0
};

void RST_finished (qk_tap_dance_state_t *state, void *user_data) {
  RSTtap_state.state = cur_dance(state);
  switch (RSTtap_state.state) {
	case SINGLE_TAP: register_code(KC_LCTL); break;
	case SINGLE_HOLD: register_code(KC_LCTL); break;
	case DOUBLE_TAP: reset_keyboard(); break;
	case DOUBLE_SINGLE_TAP: register_code(KC_LCTL); unregister_code(KC_LCTL); register_code(KC_LCTL); break;
  }
}		

void RST_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (RSTtap_state.state) {
	case SINGLE_TAP: unregister_code(KC_LCTL); break;
	case SINGLE_HOLD: unregister_code(KC_LCTL); break;
    case DOUBLE_SINGLE_TAP: unregister_code(KC_LCTL); break;
  }
  RSTtap_state.state = 0;
}	

//instantiate 'tap' for the 'LYR' tap dance.
static tap LYRtap_state = {
  .is_press_action = true,
  .state = 0
};

void LYR_finished (qk_tap_dance_state_t *state, void *user_data) {
  LYRtap_state.state = cur_dance(state);
  switch (LYRtap_state.state) {
	case SINGLE_TAP: register_code(KC_PSLS); break;
	case DOUBLE_TAP: set_single_persistent_default_layer(_GK); break;
    case DOUBLE_SINGLE_TAP: register_code(KC_PSLS); unregister_code(KC_PSLS); register_code(KC_PSLS);
  }
}		

void LYR_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (LYRtap_state.state) {
    case SINGLE_TAP: unregister_code(KC_PSLS); break;
    case DOUBLE_TAP: set_single_persistent_default_layer(_GK); break;
    case DOUBLE_SINGLE_TAP: unregister_code(KC_PSLS);
  }
  LYRtap_state.state = 0;
}	

//instantiate 'tap' for the 'BSW' tap dance.
static tap BSWtap_state = {
  .is_press_action = true,
  .state = 0
};

void BSW_finished (qk_tap_dance_state_t *state, void *user_data) {
  BSWtap_state.state = cur_dance(state);
  switch (BSWtap_state.state) {
    case SINGLE_TAP: register_code(KC_A); break;
    case SINGLE_HOLD: set_single_persistent_default_layer(0); break;
    case DOUBLE_TAP: register_code(KC_B); break;
	case DOUBLE_HOLD: 
		reset_keyboard(); 
		break; //register this keycode when button is tapped and then held
  }
}

void BSW_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (BSWtap_state.state) {
    case SINGLE_TAP: unregister_code(KC_A); break;
    case DOUBLE_TAP: unregister_code(KC_B); break; 
  }
  BSWtap_state.state = 0;
}  

///// QUAD FUNCTION TAP DANCE PERSONALIZATION SECTION END /////

//Tap Dance Definitions
//THIS SECTION HAS TO BE AT THE END OF THE TAP DANCE SECTION
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_SFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS)
// Other declarations would go here, separated by commas, if you have them
 ,[TD_Q_ESC]  = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_ESC)
 ,[RST_TAP_DANCE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, RST_finished, RST_reset)
 ,[CAD_TD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, CAD_finished, CAD_reset)
 ,[LYR_TAP_DANCE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, LYR_finished, LYR_reset)
 ,[BSW_TAP_DANCE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, BSW_finished, BSW_reset)
};

//In Layer declaration, add tap dance item in place of a key code
//TD(TD_SFT_CAPS)
