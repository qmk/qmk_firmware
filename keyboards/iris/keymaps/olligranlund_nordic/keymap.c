#include QMK_KEYBOARD_H
#include "keymap_swedish.h"

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
	QWERTY = SAFE_RANGE,
	LOWER,
	RAISE,
	ADJUST
};

#define KC_ KC_TRNS

#define KC_LOWER LOWER
#define KC_RAISE RAISE
#define KC_ADJ ADJUST
#define KC_RST RESET

#define KC_AA NO_AA
#define KC_AE NO_AE
#define KC_OE NO_OSLH

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_QWERTY] = LAYOUT(
	//┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
	 	KC_ESC,  KC_1, 	  KC_2, 	 KC_3, 	 KC_4, 	  KC_5,                				  KC_6,    KC_7,    KC_8, 	 KC_9,     KC_0,  KC_MINS,
	//├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
LT(_LOWER, KC_TAB),KC_Q,  KC_W, 	KC_E, 	 KC_R, 	  KC_T,                				  KC_Y,    KC_U, 	KC_I, 	 KC_O, 	  KC_P,   KC_AA,
	//├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
	 	KC_LSFT,  KC_A, 	KC_S, 	 KC_D, 	 KC_F, 	  KC_G,         					  KC_H, 	KC_J, 	KC_K, 	  KC_L,  KC_OE,   KC_AE,
	//├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 	KC_LCTL,   KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,   RAISE,           KC_BSPC,  KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_MINS,
	//└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
	                   				   KC_LGUI, KC_LALT, KC_SPC,         			 KC_ENT,  ADJUST, KC_RALT
								  // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
	),

	[_LOWER] = LAYOUT(
	//┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
	   NO_TILD,  KC_EXLM, NO_AT,   KC_HASH, NO_DLR, KC_PERC,                     		NO_CIRC,  NO_AMPR, NO_ASTR, NO_SLSH, NO_LPRN, NO_RPRN,
	//├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
	   KC_TRNS,  KC_MPRV, KC_MPLY, KC_MNXT, KC_TRNS, KC_TRNS,                     		KC_TRNS,  KC_PGUP, KC_UP, KC_PGDOWN, NO_LCBR, NO_RCBR,
	//├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
	  KC_TRNS,  KC_VOLD, KC_MUTE, KC_VOLU, KC_TRNS, NO_BSLS,                     		KC_TRNS, KC_LEFT,  KC_DOWN, KC_RGHT, NO_LBRC,  NO_RBRC,
	//├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	   KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_DEL, KC_TRNS, KC_GRAVE, KC_CIRC, KC_QUOTE, NO_LESS, NO_GRTR,
	//└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
	                               	   KC_TRNS, KC_TRNS, KC_TRNS,         		    KC_TRNS, KC_TRNS, KC_TRNS
								  // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
	),

	[_RAISE] = LAYOUT(
	//┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
	 	KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     		 KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
	//├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
	 	NO_GRV, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                     		 KC_TRNS,  KC_7,    KC_8,    KC_9,  NO_MINS, NO_ASTR,
	//├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
	 	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                     		KC_TRNS,  KC_4,    KC_5,    KC_6,  NO_PLUS, NO_SLSH,
	//├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,  KC_1,   KC_2,     KC_3,   KC_0,   KC_TRNS,
	//└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
	                               	   KC_TRNS, KC_TRNS, KC_TRNS,         			KC_TRNS, KC_TRNS, KC_TRNS
								  // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
	),

	[_ADJUST] = LAYOUT(
	//┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
	   BL_TOGG, BL_STEP, BL_BRTG, RGB_TOG, RGB_RMOD, RGB_MOD,                            _______, _______, _______, _______, _______, _______,
	//├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
	   BL_DEC, _______,   BL_INC, RGB_VAD, RGB_SAI, RGB_VAI,                            _______, _______, _______, _______, _______, _______,
	//├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
	   _______, _______, _______, RGB_HUD, RGB_SAD, RGB_HUI,                            _______, _______, _______, _______, _______, _______,
	//├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	   _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
	//└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
									  _______, _______, _______,                   _______, _______, _______
								  // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
	)
};

void persistent_default_layer_set(uint16_t default_layer) {
	eeconfig_update_default_layer(default_layer);
	default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
	case QWERTY:
		if (record->event.pressed) {
			set_single_persistent_default_layer(_QWERTY);
		}
		return false;
		break;
	case LOWER:
		if (record->event.pressed) {
			layer_on(_LOWER);
			update_tri_layer(_LOWER, _RAISE, _ADJUST);
		} else {
			layer_off(_LOWER);
			update_tri_layer(_LOWER, _RAISE, _ADJUST);
		}
		return false;
		break;
	case RAISE:
		if (record->event.pressed) {
			layer_on(_RAISE);
			update_tri_layer(_LOWER, _RAISE, _ADJUST);
		} else {
			layer_off(_RAISE);
			update_tri_layer(_LOWER, _RAISE, _ADJUST);
		}
		return false;
		break;
	case ADJUST:
		if (record->event.pressed) {
			layer_on(_ADJUST);
		} else {
			layer_off(_ADJUST);
		}
		return false;
		break;
	}
	return true;
}
