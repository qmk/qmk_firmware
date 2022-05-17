/* 
 * Customización teclado YMD40 por Santiago Intxausti <intxausti@gmail.com>
 */

#include QMK_KEYBOARD_H


// FUNCION PARA ACTIVAR EL NUMLOCK DE LA CAPA _NUM_PAD
void led_set_user(uint8_t usb_led) {
  if (!(usb_led & (1<<USB_LED_NUM_LOCK))) {
    tap_code(KC_NLCK);
  }
}


// FUNCIONES TAP DANCE

// Define a type for as many tap dance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// Declare the functions to be used with your tap dance key(s)

// Function associated with all tap dances
td_state_t cur_dance(qk_tap_dance_state_t *state);

// Functions associated with individual tap dances
void ql_finished(qk_tap_dance_state_t *state, void *user_data);
void ql_reset(qk_tap_dance_state_t *state, void *user_data);


void dance_cln_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(KC_N);
    } else {
        SEND_STRING(SS_DOWN(X_RALT) SS_TAP(X_N));
        clear_keyboard();
    }
}


void dance_cln_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(KC_N);
    }
}


void dance_exclam_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(KC_EXLM);
    } else {
        SEND_STRING(SS_DOWN(X_RALT) SS_TAP(X_1));
        clear_keyboard();
    }
}

void dance_exclam_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(KC_EXLM);
    }
}

void dance_interrog_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(KC_SLSH);
    } else {
        SEND_STRING(SS_DOWN(X_RALT) SS_TAP(X_SLSH));
        clear_keyboard();
    }
}

void dance_interrog_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(KC_SLSH);
    }
}


//NOMBRES TAP DANCE
enum {
    TD_ENE,
    TD_SIFT_CAPSLOCK,
    TD_RHAND_LAYER,
    TD_WIN_MENU,
    TD_EXCLAM,
    TD_INTERROG

};

// Tap Dance DEFINICIONES
qk_tap_dance_action_t tap_dance_actions[] = {
    // 1 TOQUE PARA OPC 1 DOS PARA OPC 2
    [TD_ENE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_cln_finished, dance_cln_reset),
    [TD_SIFT_CAPSLOCK]  = ACTION_TAP_DANCE_DOUBLE(KC_LEFT_SHIFT, KC_CAPS_LOCK),
    [TD_RHAND_LAYER] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, ql_finished, ql_reset, 275),
    [TD_WIN_MENU]  = ACTION_TAP_DANCE_DOUBLE(KC_LGUI, KC_APP),
    [TD_EXCLAM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_exclam_finished, dance_exclam_reset),
    [TD_INTERROG] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_interrog_finished, dance_interrog_reset),

};



enum layer_names {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
  _MOV,
  _ONE_HAND,
  _RIGHT_NUM_PAD,
  _RIGHT_NUM_PAD2,
  _LEFT_NUM_PAD,
  _QWERTY2,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_QWERTY]=LAYOUT_ortho_4x12(
		TD(TD_RHAND_LAYER),		KC_Q,			KC_W,			KC_E,			KC_R,					KC_T,					KC_Y,					KC_U,				KC_I,				KC_O,		KC_P,				KC_BSPC,
		LT(_MOV,KC_ESC),		KC_A,			KC_S,			KC_D,			KC_F,					KC_G,					KC_H,					KC_J,				KC_K,				KC_L,		KC_SCLN,			KC_QUOT,
		TD(TD_SIFT_CAPSLOCK),	KC_Z,			KC_X,			KC_C,			KC_V,					KC_B,					TD(TD_ENE),				KC_M,				KC_COMM,			KC_DOT,		TD(TD_INTERROG),	KC_SFTENT,
		OSM(MOD_LCTL),			OSM(MOD_LALT),	OSM(MOD_RALT),	OSM(MOD_LGUI),	LT(_LOWER,KC_BSPC),		LT(_ONE_HAND,KC_SPACE),	LT(_ONE_HAND,KC_SPACE),	LT(_RAISE,KC_ENT),	TD(TD_WIN_MENU),	KC_RALT,	KC_RCTL,			KC_LEAD
	),

    [_RAISE] = LAYOUT_ortho_4x12(
        KC_TILD,	TD(TD_EXCLAM),	KC_AT,		KC_HASH,	KC_DLR,			KC_PERC,	KC_CIRC,	KC_AMPR,	KC_ASTR,	KC_LPRN,	KC_RPRN,	KC_BSPC,
        KC_F1,		KC_F2,			KC_F3,		KC_F4,		KC_F5,			KC_F6,		KC_PIPE,	KC_UNDS,	KC_PLUS,	KC_LCBR,	KC_RCBR,	KC_PIPE,
        KC_F7,		KC_F8,			KC_F9,		KC_F10,		KC_F11,			KC_F12,		KC_NO,		KC_MUTE,	KC_NO,		KC_LBRC,	KC_RBRC,	KC_VOLU,
        KC_TRNS,	KC_TRNS,		KC_TRNS,	KC_TRNS,	MO(_ADJUST),	KC_SPC,		KC_SPC,		KC_TRNS,	KC_MRWD,	KC_MPLY,	KC_MFFD,	KC_VOLD
    ),

    [_LOWER] = LAYOUT_ortho_4x12(
		KC_GRV,		KC_1,		KC_2,		KC_3,		KC_4,		KC_5,	KC_6,		KC_7,		KC_8,		KC_9,			KC_0,			KC_BSPC,
		KC_F13,		KC_F14,		KC_F15,		KC_F16,		KC_F17,		KC_F18,	KC_BSLS,	KC_MINS,	KC_EQL,		KC_LBRC,		KC_RBRC,		KC_BSLS,
    	KC_F19,		KC_F20,		KC_F21,		KC_F22,		KC_F23,		KC_F24,	KC_NO,		KC_MUTE,	KC_NO,		RALT(KC_LBRC),	RALT(KC_RBRC),	KC_VOLU,
		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_SPC,	KC_SPC,		KC_TRNS,	KC_MPRV,	KC_MPLY,		KC_MNXT,		KC_VOLD
    ),
    
    [_ADJUST] = LAYOUT_ortho_4x12(
		RESET,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		TO(_LEFT_NUM_PAD),	KC_NO,		DEBUG,
		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		LAG_NRM,	LAG_SWP,	KC_NO,		KC_NO,		KC_NO,				KC_NO,		KC_NO,
		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		DM_REC1,	DM_REC2,	DM_RSTP,			DM_RSTP,	DM_RSTP,
		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,			KC_TRNS,	KC_TRNS
    ),

    [_MOV] = LAYOUT_ortho_4x12(
		KC_TAB,		KC_NO,	KC_NO,		DM_PLY1,	DM_PLY2,			KC_NO,		KC_NO,		KC_PGUP,	KC_INS,	KC_PSCR,	KC_SLCK,		KC_PAUS,
		KC_TRNS,	KC_NO,	KC_LCTL,	KC_LALT,	KC_LSFT,			KC_HOME,	KC_LEFT,	KC_DOWN,	KC_UP,	KC_RGHT,	KC_NO,			KC_NO,
		KC_NO,		KC_NO,	KC_DEL,		KC_NO,		LCTL(KC_LEFT_GUI),	KC_END,		KC_END,		KC_PGDN,	KC_NO,	KC_NO,		KC_NO,			KC_NO,
		KC_NO,		KC_NO,	KC_NO,		KC_NO,		KC_BSPC,			KC_TRNS,	KC_TRNS,	KC_ENT,		KC_NO,	KC_NO,		C(G(KC_LEFT)),	C(G(KC_RIGHT))
    ),

    [_ONE_HAND] = LAYOUT_ortho_4x12(
		KC_BSPC,	KC_P,		KC_O,	KC_I,		KC_U,	KC_Y,		KC_T,		KC_R,	KC_E,	KC_W,	KC_Q,	KC_TAB,
		KC_QUOT,	KC_SCLN,	KC_L,	KC_K,		KC_J,	KC_H,		KC_G,		KC_F,	KC_D,	KC_S,	KC_A,	KC_ESC,
		KC_SFTENT,	KC_SLSH,	KC_DOT,	KC_COMM,	KC_M,	TD(TD_ENE),	KC_B,		KC_V,	KC_C,	KC_X,	KC_Z,	TD(TD_SIFT_CAPSLOCK),
		KC_LEAD,	KC_NO,		KC_NO,	KC_NO,		KC_NO,	KC_TRNS,	KC_TRNS,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO
    ),    

    [_RIGHT_NUM_PAD] = LAYOUT_ortho_4x12(
        KC_TRNS,	KC_PAST, 	KC_P7,		KC_P8,	KC_P9, 	KC_ESC,		                    KC_ESC, 	                    KC_P7,	KC_P8,	KC_P9,		KC_PAST,	KC_NO,
        KC_NO,		KC_PPLS, 	KC_P4, 		KC_P5, 	KC_P6,	KC_BSPC,	                    KC_BSPC, 	                    KC_P4, 	KC_P5, 	KC_P6, 		KC_PPLS,	KC_NO,
        KC_NO, 		KC_PMNS, 	KC_P1,		KC_P2, 	KC_P3, 	KC_DEL, 		                KC_DEL, 	                    KC_P1,	KC_P2, 	KC_P3,		KC_PMNS,	KC_NO,
        KC_NO,		KC_PSLS, 	KC_PDOT,	KC_P0, 	KC_P0, 	LT(_RIGHT_NUM_PAD2,KC_ENT),		LT(_RIGHT_NUM_PAD2,KC_ENT), 	KC_P0,	KC_P0, 	KC_PDOT, 	KC_PSLS,	KC_NO
    ),
    
    [_RIGHT_NUM_PAD2] = LAYOUT_ortho_4x12(
        KC_TRNS,	C(KC_L), 	KC_PERC,	KC_AT, 		KC_R, 		KC_NO,		KC_NO,      KC_R, 		KC_AT, 		KC_PERC,	C(KC_L),    KC_NO,
        KC_NO,		KC_PAST, 	KC_NO, 		KC_NO, 		KC_NO,		KC_NO,	    KC_NO,  	KC_NO, 		KC_NO, 		KC_NO,		KC_PAST,    KC_NO,
        KC_NO, 		C(KC_R), 	C(KC_Q), 	C(KC_P),   	C(KC_M), 	KC_NO, 		KC_NO,      C(KC_M),    C(KC_P), 	C(KC_Q),    C(KC_R),    KC_NO,
        KC_NO,		KC_TRNS, 	KC_TRNS,  	KC_TRNS, 	KC_NO, 		KC_TRNS, 	KC_TRNS, 	KC_NO,	    KC_NO, 	    KC_NO,      KC_NO,	    KC_NO
    ),
    
    [_LEFT_NUM_PAD] = LAYOUT_ortho_4x12(
        LM(_QWERTY2, MOD_LALT),	KC_BSPC, 	KC_7, 		KC_8,	KC_9, 	KC_NO,		KC_NO, 		KC_NO,	KC_NO,	KC_TRNS,	KC_NO,		TO(_QWERTY),
        LM(_QWERTY2, MOD_LALT),	KC_BSPC, 	KC_4, 		KC_5, 	KC_6,	KC_NO,		KC_NO, 		KC_NO, 	KC_NO, 	KC_NO, 		KC_NO,		KC_NO,
        LM(_QWERTY2, MOD_LCTL), KC_BSPC, 	KC_1, 		KC_2, 	KC_3, 	KC_NO, 		KC_NO, 		KC_NO,	KC_NO, 	KC_NO,		KC_NO,		KC_NO,
        LM(_QWERTY2, MOD_LCTL),	KC_0, 		KC_0,  		KC_0, 	KC_0, 	A(KC_TAB), 	A(KC_TAB), 	KC_NO,	KC_NO, 	KC_NO, 		KC_TRNS,	KC_TRNS
    ),
    
	[_QWERTY2]=LAYOUT_ortho_4x12(
		KC_TRNS,	KC_Q,		KC_W,		KC_E,		KC_R,		KC_T,		KC_Y,		KC_U,		KC_I,		KC_O,		KC_P,		KC_TRNS,
		KC_TRNS,	KC_A,		KC_S,		KC_D,		KC_F,		KC_G,		KC_H,		KC_J,		KC_K,		KC_L,		KC_SCLN,	KC_TRNS,
		KC_TRNS,	KC_Z,		KC_X,		KC_C,		KC_V,		KC_B,		KC_N,		KC_M,		KC_COMM,	KC_DOT,		KC_SLSH,	KC_TRNS,
		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS
	),
    
	[_MOUSE]=LAYOUT_ortho_4x12(
		KC_TRNS,	KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_BTN1,		KC_MS_UP,		KC_MS_BTN2,		KC_NO,	    KC_MS_ACCEL0,
		KC_TRNS,	KKC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_MS_LEFT,		KC_MS_DOWN,		KC_MS_RIGHT,	KC_NO,	    KC_MS_ACCEL1,
		KC_TRNS,	KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		    KC_MS_BTN3,	    KC_NO,          KC_NO,	    KC_MS_ACCEL2,
		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	    KC_TRNS,	    KC_TRNS,	    KC_TRNS,	KC_TRNS
	)


};

/*

  	layer_state_t layer_state_set_user(layer_state_t state) {
  	return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
	}

*/

// FUNCION TECLA LEADER
LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();
    
    SEQ_ONE_KEY(KC_H) {
		SEND_STRING(SS_LALT(SS_TAP(X_HOME)));
	}

     SEQ_ONE_KEY(KC_V) {
    	SEND_STRING(SS_LCTRL(SS_LCTL(SS_LALT(SS_TAP(X_V)))));
    }

     SEQ_ONE_KEY(KC_K) {
    	SEND_STRING(SS_LCTRL(SS_LCTL(SS_LALT(SS_TAP(X_C)))));
    }
   
    SEQ_THREE_KEYS(KC_C, KC_A, KC_D) {
    	SEND_STRING(SS_LCTRL(SS_LALT(SS_TAP(X_DELETE))));
    }

  }
}

// Determine the current tap dance state
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;	
    } else if (state->count == 2) return TD_DOUBLE_TAP;
    else return TD_UNKNOWN;
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
            tap_code(KC_TAB);
            break;
        case TD_SINGLE_HOLD:
            layer_on(_RIGHT_NUM_PAD);
            break;
        case TD_DOUBLE_TAP:
            // Check to see if the layer is already set
            if (layer_state_is(_RIGHT_NUM_PAD)) {
                // If already set, then switch it off
                layer_off(_RIGHT_NUM_PAD);
            } else {
                // If not already set, then switch the layer on
                layer_on(_RIGHT_NUM_PAD);
            }
            break;
        default:
            break;
    }
}

void ql_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (ql_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(_RIGHT_NUM_PAD);
    }
    ql_tap_state.state = TD_NONE;
}


