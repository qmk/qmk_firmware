#include "kbd66.h"

#define _MA 0
#define _GA 1
#define _FL 2
#define _AR 3
#define _LE 4
#define _LO 5
#define _UL 6

#define TRNS KC_TRNS
#define ______ KC_NO
#define trigger_time 400

#define LSHIFT OSM(MOD_LSFT)
#define SPACE LT(_AR, KC_SPC)
#define CAPS LT(_LE, KC_CAPS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// Main Layer
[_MA] = KEYMAP_ANSI(
	KC_GESC,	KC_1, 		KC_2, 		KC_3, 		KC_4, 		KC_5, 		KC_6, 		KC_7, 		KC_8, 		KC_9, 		KC_0, 		KC_MINS,	KC_EQL,		KC_MPLY,	KC_BSPC,	KC_PSCR,
	KC_TAB,		KC_Q, 		KC_W, 		KC_E, 		KC_R, 		KC_T, 		KC_Y, 		KC_U, 		KC_I,  		KC_O,  		KC_P, 		KC_LBRC,	KC_RBRC,	KC_BSLS,				KC_DEL,
	CAPS,		KC_A, 		KC_S,   	KC_D, 		KC_F, 		KC_G, 		KC_H, 		KC_J, 		KC_K,  		KC_L,  		KC_SCLN, 	KC_QUOT,  				KC_ENT,
	LSHIFT, 	TRNS,		KC_Z, 		KC_X,   	KC_C, 		KC_V, 		KC_B, 		KC_N, 		KC_M, 		KC_COMM, 	KC_DOT,		KC_SLSH, 	KC_RSFT,    TRNS,		KC_UP,
	KC_LCTL, 	KC_LGUI, 	KC_LALT,							SPACE,					SPACE,								KC_RALT,	KC_RCTRL, 	MO(_FL),	KC_LEFT, 	KC_DOWN, 	KC_RGHT),

//Function Layer
[_FL] = KEYMAP_ANSI(
	KC_GRV,		KC_F1,		KC_F2,  	KC_F3,  	KC_F4,  	KC_F5,		KC_F6,		KC_F7, 		KC_F8,		KC_F9,		KC_F10,  	KC_F11,		KC_F12,		TRNS,		RESET,		KC_PGUP,
	TRNS, 		KC_BTN1,	KC_MS_U,  	KC_BTN2, 	TRNS, 		TRNS, 		TRNS,		TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS,		TRNS,		TRNS,					KC_PGDN,
	TRNS, 		KC_MS_L,	KC_MS_D, 	KC_MS_R,	TRNS,		TG(_GA),	TRNS,		TRNS,		TRNS,		TRNS,		TRNS,		TRNS,					TRNS,
	TRNS, 		TRNS,		TRNS,		TRNS,		TRNS,	 	TRNS, 		TRNS, 		TRNS,		TRNS,		KC_VOLD,	KC_VOLU,	KC_MUTE,	TRNS,		TRNS,		KC_WH_U,
	TRNS, 		TRNS, 		TRNS,								TRNS,					TRNS,								TRNS,		TRNS,		TRNS,   	KC_WH_L,	KC_WH_D, 	KC_WH_R),

//Arrow keys layer (space bar)
[_AR] = KEYMAP_ANSI(
	KC_GRV,		KC_F1,		KC_F2,  	KC_F3,  	KC_F4,  	KC_F5,		KC_F6,		KC_F7, 		KC_F8,		KC_F9,		KC_F10,  	KC_F11,		KC_F12,		TRNS,		TRNS,		TRNS,
	TRNS,		TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS,  		TRNS,  		TRNS, 		TRNS,		TRNS,		TRNS,					TRNS,
	TRNS,		TRNS, 		TRNS,   	TRNS, 		TRNS, 		TRNS,		TRNS, 		TRNS, 		TRNS, 		TRNS,	  	TRNS, 		TRNS, 	 				TRNS,
	TRNS,		TRNS,		TRNS,		TRNS,		TRNS,		TRNS,	 	TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS,		TRNS, 		TRNS,   	TRNS,		TRNS,
	TRNS, 		TRNS, 		TRNS,								TRNS,					TRNS,								TRNS,		TRNS, 		M(0),		TRNS, 		TRNS, 		TRNS),
//LED control layer (caps)
[_LE] = KEYMAP_ANSI(
	TRNS,		TRNS,		TRNS,  		TRNS,  		TRNS,  		TRNS,		TRNS,		TRNS, 		TRNS,		TRNS,		TRNS,  		TRNS,		TRNS,		TRNS,		TRNS,		TRNS,
	TRNS,		BL_TOGG, 	TRNS, 		TRNS,		TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS,  		TRNS,  		TRNS, 		TRNS,		TRNS,		TRNS,					TRNS,
	TRNS,		BL_INC,		TRNS,   	TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS,  		TRNS,  		TRNS, 		TRNS, 	 				TRNS,
	TRNS,		TRNS,		BL_DEC,		TRNS,		TRNS,		TRNS,	 	TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS,		TRNS, 		TRNS,   	TRNS,		TRNS,
	TRNS, 		TRNS, 		TRNS,								TRNS,					TRNS,								TRNS,		TRNS, 		TRNS,		TRNS, 		TRNS, 		TRNS),

//Game layer (fn + g)
[_GA] = KEYMAP_ANSI(
	TRNS,		TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS,		TRNS,		TRNS,		TRNS,		TRNS,
	TRNS,		TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS,  		TRNS,  		TRNS, 		TRNS,		TRNS,		TRNS,					TRNS,
	KC_CAPS,	TRNS, 		TRNS,   	TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS,  		TRNS,  		TRNS, 		TRNS,  					TRNS,
	KC_LSFT, 	TRNS,		TRNS, 		TRNS,   	TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS,		TRNS, 		TRNS,		TRNS,		TRNS,
	TRNS, 		TRNS, 		TRNS,								KC_SPC,					KC_SPC,								TRNS,		TRNS, 		MO(_FL),	TRNS, 		TRNS, 		TRNS),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    switch (id) {
		case 0:
			if (record->event.pressed) {
				SEND_STRING("AdminF123!");
			}
			break;
	}
    return MACRO_NONE;
};