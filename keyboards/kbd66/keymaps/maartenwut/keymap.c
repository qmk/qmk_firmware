#include QMK_KEYBOARD_H

#define _MA 0
#define _GA 1
#define _FL 2
#define _AR 3

#define TRNS KC_TRNS
#define ______ KC_NO
#define trigger_time 400

#define LSHIFT OSM(MOD_LSFT)
#define SPACE LT(_AR, KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// Main Layer
[_MA] = LAYOUT_all(
	KC_GESC,	KC_1, 		KC_2, 		KC_3, 		KC_4, 		KC_5, 		KC_6, 		KC_7, 		KC_8, 		KC_9, 		KC_0, 		KC_MINS,	KC_EQL,		______,		KC_BSPC,	KC_MPLY,
	KC_TAB,		KC_Q, 		KC_W, 		KC_E, 		KC_R, 		KC_T, 		KC_Y, 		KC_U, 		KC_I,  		KC_O,  		KC_P, 		KC_LBRC,	KC_RBRC,	KC_BSLS,				KC_DEL,
	KC_CAPS,	KC_A, 		KC_S,   	KC_D, 		KC_F, 		KC_G, 		KC_H, 		KC_J, 		KC_K,  		KC_L,  		KC_SCLN, 	KC_QUOT,  				KC_ENT,
	LSHIFT, 	TRNS,		KC_Z, 		KC_X,   	KC_C, 		KC_V, 		KC_B, 		KC_N, 		KC_M, 		KC_COMM, 	KC_DOT,		KC_SLSH, 	KC_RSFT,    TRNS,		KC_UP,
	KC_LCTL, 	KC_LGUI, 	KC_LALT,							SPACE,					SPACE,								KC_RALT,	KC_RCTRL, 	MO(_FL),	KC_LEFT, 	KC_DOWN, 	KC_RGHT),

//Function Layer
[_FL] = LAYOUT_all(
	KC_GRV,		KC_F1,		KC_F2,  	KC_F3,  	KC_F4,  	KC_F5,		KC_F6,		KC_F7, 		KC_F8,		KC_F9,		KC_F10,  	KC_F11,		KC_F12,		TRNS,		RESET,		KC_PSCR,
	TRNS, 		______,		______,  	______, 	TRNS, 		TRNS, 		TRNS,		TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS,		TRNS,		TRNS,					______,
	TRNS, 		______,		______, 	______,		TRNS,		TG(_GA),	TRNS,		TRNS,		TRNS,		TRNS,		TRNS,		TRNS,					TRNS,
	TRNS, 		TRNS,		TRNS,		TRNS,		TRNS,	 	TRNS, 		TRNS, 		TRNS,		TRNS,		KC_VOLD,	KC_VOLU,	KC_MUTE,	TRNS,		TRNS,		KC_PGUP,
	TRNS, 		TRNS, 		TRNS,								TRNS,					TRNS,								TRNS,		TRNS,		TRNS,   	______,		KC_PGDN, 	______),

//Arrow keys layer (space bar)
[_AR] = LAYOUT_all(
	KC_GRV,		KC_F1,		KC_F2,  	KC_F3,  	KC_F4,  	KC_F5,		KC_F6,		KC_F7, 		KC_F8,		KC_F9,		KC_F10,  	KC_F11,		KC_F12,		TRNS,		TRNS,		TRNS,
	TRNS,		TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS,  		TRNS,  		TRNS, 		TRNS,		TRNS,		TRNS,					TRNS,
	TRNS,		TRNS, 		TRNS,   	TRNS, 		TRNS, 		TRNS,		TRNS, 		TRNS, 		TRNS, 		TRNS,	  	TRNS, 		TRNS, 	 				TRNS,
	TRNS,		TRNS,		TRNS,		TRNS,		TRNS,		TRNS,	 	TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS,		TRNS, 		TRNS,   	TRNS,		TRNS,
	TRNS, 		TRNS, 		TRNS,								TRNS,					TRNS,								TRNS,		TRNS, 		TRNS,		TRNS, 		TRNS, 		TRNS),

//Game layer (fn + g)
[_GA] = LAYOUT_all(
	TRNS,		TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS,		TRNS,		TRNS,		TRNS,		TRNS,
	TRNS,		TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS,  		TRNS,  		TRNS, 		TRNS,		TRNS,		TRNS,					TRNS,
	TRNS,		TRNS, 		TRNS,   	TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS,  		TRNS,  		TRNS, 		TRNS,  					TRNS,
	KC_LSFT, 	TRNS,		TRNS, 		TRNS,   	TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS,		TRNS, 		TRNS,		TRNS,		TRNS,
	TRNS, 		TRNS, 		TRNS,								KC_SPC,					KC_SPC,								TRNS,		TRNS, 		MO(_FL),	TRNS, 		TRNS, 		TRNS),
};

void matrix_init_user() {
	//Set led port to output
	DDRB |= (1<<2);
}

void led_set_user(uint8_t usb_led) {
	if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
		// Turn capslock on
		PORTB &= ~(1<<2);
	} else {
		// Turn capslock off
		PORTB |= (1<<2);
	}
}
