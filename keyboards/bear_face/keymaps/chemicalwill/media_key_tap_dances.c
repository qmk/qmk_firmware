//define xtap
typedef struct {
	bool is_press_action;
	int state;
} xtap;

//Tap Dance states
enum {
	SINGLE_TAP = 1,
	SINGLE_HOLD = 2,
	DOUBLE_TAP = 3,         //key is tapped twice uninterrupted
	DOUBLE_HOLD = 4,        //key is tapped twice and held
	DOUBLE_SINGLE_TAP = 5,  //key is tapped twice and then interrupted
};
//Tap Dance enums
enum {
	MUTE_F1 = 0,
	VOLD_F2 = 1,
	VOLU_F3 = 2,
	MPRV_F4 = 3,
	MPLY_F5 = 4,
	MNXT_F6 = 5
};

//set up Tap Dance for tap vs. hold
int cur_dance (qk_tap_dance_state_t *state);

//Tap Dance specific functions
void mute_finished (qk_tap_dance_state_t *state, void *user_data);
void mute_reset (qk_tap_dance_state_t *state, void *user_data);

void vold_finished (qk_tap_dance_state_t *state, void *user_data);
void vold_reset (qk_tap_dance_state_t *state, void *user_data);

void volu_finished (qk_tap_dance_state_t *state, void *user_data);
void volu_reset (qk_tap_dance_state_t *state, void *user_data);

void mprv_finished (qk_tap_dance_state_t *state, void *user_data);
void mprv_reset (qk_tap_dance_state_t *state, void *user_data);

void mply_finished (qk_tap_dance_state_t *state, void *user_data);
void mply_reset (qk_tap_dance_state_t *state, void *user_data);

void mnxt_finished (qk_tap_dance_state_t *state, void *user_data);
void mnxt_reset (qk_tap_dance_state_t *state, void *user_data);

//Determine tap state
int cur_dance (qk_tap_dance_state_t *state) {
    if (state->count == 1) {
		//If count = 1, and it has been interrupted - it doesn't matter if it is pressed or not: Send SINGLE_TAP
		if (state->interrupted) {
		//     if (!state->pressed) return SINGLE_TAP;
		//need "permissive hold" here.
		//     else return SINGLE_HOLD;
		//If the interrupting key is released before the tap-dance key, then it is a single HOLD
		//      However, if the tap-dance key is released first, then it is a single TAP
		//      But how to get access to the state of the interrupting key????
			return SINGLE_TAP;
		} else {
			if (!state->pressed)
				return SINGLE_TAP;
			else
				return SINGLE_HOLD;
		}
	}
	//If count = 2, and it has been interrupted - assume that user is trying to type the letter associated
  	//  with single tap.
	else if (state->count == 2) {
		if (state->interrupted)
	  		return DOUBLE_SINGLE_TAP;   //key is tapped twice, but interrupted right after
		else if (state->pressed)
			return DOUBLE_HOLD;
		else
	  		return DOUBLE_TAP;          //key is tapped twice, but is NOT interrupted
	}
	else
		return 6; //return n+1, where n is yoru number of tap dance states
};

//instance 'xtap' for the 'mute/F1' tap dance
static xtap mutetap_state = {
	.is_press_action = true,
	.state = 0
};
void mute_finished (qk_tap_dance_state_t *state, void *user_data) {
	mutetap_state.state = cur_dance(state);
	switch (mutetap_state.state) {
	case SINGLE_TAP:
		register_code(KC_MUTE);
		break;
	case SINGLE_HOLD:
		register_code(KC_F1);
		break;
	}
}
void mute_reset (qk_tap_dance_state_t *state, void *user_data) {
	switch (mutetap_state.state) {
	case SINGLE_TAP:
		unregister_code(KC_MUTE);
		break;
	case SINGLE_HOLD:
		unregister_code(KC_F1);
		break;
	}
	mutetap_state.state = 0;
}

//instance 'xtap' for the 'vold/F2' tap dance
static xtap voldtap_state = {
	.is_press_action = true,
	.state = 0
};
void vold_finished (qk_tap_dance_state_t *state, void *user_data) {
	voldtap_state.state = cur_dance(state);
	switch (voldtap_state.state) {
	case SINGLE_TAP:
		register_code(KC_VOLD);
		break;
	case SINGLE_HOLD:
		register_code(KC_VOLD);
		break;
	case DOUBLE_TAP:
		tap_code(KC_VOLD);
		register_code(KC_VOLD);
		break;
	case DOUBLE_HOLD:
		register_code(KC_F2);
		break;
	}
}
void vold_reset (qk_tap_dance_state_t *state, void *user_data) {
	switch (voldtap_state.state) {
	case SINGLE_TAP:
		unregister_code(KC_VOLD);
		break;
	case SINGLE_HOLD:
		unregister_code(KC_VOLD);
		break;
	case DOUBLE_TAP:
		unregister_code(KC_VOLD);
		break;
	case DOUBLE_HOLD:
		unregister_code(KC_F2);
		break;
	}
	voldtap_state.state = 0;
}

//instance 'xtap' for the 'volu/F3' tap dance
static xtap volutap_state = {
	.is_press_action = true,
	.state = 0
};
void volu_finished (qk_tap_dance_state_t *state, void *user_data) {
	volutap_state.state = cur_dance(state);
	switch (volutap_state.state) {
	case SINGLE_TAP:
		register_code(KC_VOLU);
		break;
	case SINGLE_HOLD:
		register_code(KC_VOLU);
		break;
	case DOUBLE_TAP:
		tap_code(KC_VOLU);
		register_code(KC_VOLU);
		break;
	case DOUBLE_HOLD:
		register_code(KC_F3);
		break;
	}
}
void volu_reset (qk_tap_dance_state_t *state, void *user_data) {
	switch (volutap_state.state) {
	case SINGLE_TAP:
		unregister_code(KC_VOLU);
		break;
	case SINGLE_HOLD:
		unregister_code(KC_VOLU);
		break;
	case DOUBLE_TAP:
		unregister_code(KC_VOLU);
		break;
	case DOUBLE_HOLD:
		unregister_code(KC_F3);
		break;
	}
	volutap_state.state = 0;
}

//instance 'xtap' for the 'mprv/F4' tap dance
static xtap mprvtap_state = {
	.is_press_action = true,
	.state = 0
};
void mprv_finished (qk_tap_dance_state_t *state, void *user_data) {
	mprvtap_state.state = cur_dance(state);
	switch (mprvtap_state.state) {
	case SINGLE_TAP:
		register_code(KC_MPRV);
		break;
	case SINGLE_HOLD:
		register_code(KC_F4);
		break;
	}
}
void mprv_reset (qk_tap_dance_state_t *state, void *user_data) {
	switch (mprvtap_state.state) {
	case SINGLE_TAP:
		unregister_code(KC_MPRV);
		break;
	case SINGLE_HOLD:
		unregister_code(KC_F4);
		break;
	}
	mprvtap_state.state = 0;
}

//instance 'xtap' for the 'mply/F6' tap dance
static xtap mplytap_state = {
	.is_press_action = true,
	.state = 0
};
void mply_finished (qk_tap_dance_state_t *state, void *user_data) {
	mplytap_state.state = cur_dance(state);
	switch (mplytap_state.state) {
	case SINGLE_TAP:
		register_code(KC_MPLY);
		break;
	case SINGLE_HOLD:
		register_code(KC_F5);
		break;
	}
}
void mply_reset (qk_tap_dance_state_t *state, void *user_data) {
	switch (mplytap_state.state) {
	case SINGLE_TAP:
		unregister_code(KC_MPLY);
		break;
	case SINGLE_HOLD:
		unregister_code(KC_F5);
		break;
	}
	mplytap_state.state = 0;
}

//instance 'xtap' for the 'mnxt/F6' tap dance
static xtap mnxttap_state = {
	.is_press_action = true,
	.state = 0
};
void mnxt_finished (qk_tap_dance_state_t *state, void *user_data) {
	mnxttap_state.state = cur_dance(state);
	switch (mnxttap_state.state) {
	case SINGLE_TAP:
		register_code(KC_MNXT);
		break;
	case SINGLE_HOLD:
		register_code(KC_F6);
		break;
	}
}
void mnxt_reset (qk_tap_dance_state_t *state, void *user_data) {
	switch (mnxttap_state.state) {
	case SINGLE_TAP:
		unregister_code(KC_MNXT);
		break;
	case SINGLE_HOLD:
		unregister_code(KC_F6);
		break;
	}
	mnxttap_state.state = 0;
}

//Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
	[MUTE_F1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, mute_finished, mute_reset),
	[VOLD_F2] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, vold_finished, vold_reset),
	[VOLU_F3] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, volu_finished, volu_reset),
	[MPRV_F4] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, mprv_finished, mprv_reset),
	[MPLY_F5] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, mply_finished, mply_reset),
	[MNXT_F6] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, mnxt_finished, mnxt_reset)
};

#define MUTE_F1 TD(MUTE_F1)
#define VOLD_F2 TD(VOLD_F2)
#define VOLU_F3 TD(VOLU_F3)
#define MPRV_F4 TD(MPRV_F4)
#define MPLY_F5 TD(MPLY_F5)
#define MNXT_F6 TD(MNXT_F6)
