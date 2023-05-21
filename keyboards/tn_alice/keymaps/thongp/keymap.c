// Copyright 2020 QMK / MudkipMao
// SPDX-License-Identifier: GPL-2.0-or-later


#include QMK_KEYBOARD_H
#include "rgblight.h"
#include "color.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT(
		KC_ESC,  KC_GRV,  KC_1, KC_2, KC_3,   KC_4,   KC_5, KC_6, KC_7, KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, 
		KC_PGUP, KC_TAB,  KC_Q, KC_W, KC_E,   KC_R,   KC_T, KC_Y, KC_U, KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, 
		KC_PGDN, KC_CAPS, KC_A, KC_S, KC_D,   KC_F,   KC_G, KC_H, KC_J, KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT, 
		         KC_LSFT, KC_Z, KC_X, KC_C,   KC_V,   KC_B, KC_B, KC_N, KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_UP,   MO(2), 
		         KC_LCTL, KC_LGUI,    KC_LALT,  KC_SPC,  KC_SPC,    MO(1),                        KC_LEFT, KC_DOWN, KC_RGHT
	),

	[1] = LAYOUT(
		KC_TRNS, KC_TRNS, KC_F1,   KC_F2,   KC_F3,    KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_F11,  KC_F12,  QK_BOOT, 
		KC_TRNS, KC_TRNS, RGB_TOG, RGB_MOD, RGB_RMOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD,  KC_PSCR, KC_SCRL, KC_PAUS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_INS,  KC_HOME, KC_TRNS, 
		         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_DEL,  KC_END,  KC_TRNS, KC_TRNS, 
		         KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,                                      KC_TRNS, KC_TRNS, KC_TRNS
	),

	[2] = LAYOUT(
		KC_ESC,  KC_GRV,  KC_1, 	KC_2, 		KC_3,   KC_4,   KC_5, KC_6, KC_7, KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, 
		KC_PGUP, RGB_TOG, RGB_MOD, 	RGB_RMOD, 	RGB_HUI,   RGB_HUD,   RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD,    KC_PSCR,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, 
		KC_PGDN, KC_CAPS, KC_A, 	KC_S, 		KC_D,   KC_F,   KC_G, KC_H, KC_J, KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT, 
		         KC_LSFT, KC_Z, 	KC_X, 		KC_C,   KC_V,   KC_B, KC_B, KC_N, KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_UP,   KC_RSFT, 
		         KC_LCTL, KC_LGUI,    	  		KC_LALT,  KC_SPC,  KC_SPC,    MO(1),                        KC_LEFT, KC_DOWN, KC_RGHT
	),

};

/* LIGHTING LAYERS*/
// Define lighting layers
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 6, HSV_BLACK}	      // Light 6 LEDs, starting with LED 0
);

const rgblight_segment_t PROGMEM layer1[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 6, HSV_RED}	      // Light 6 LEDs, starting with LED 0
);

const rgblight_segment_t PROGMEM layer2[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 6, HSV_ORANGE}	      // Light 6 LEDs, starting with LED 0
);



// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_capslock_layer,
	layer1,
	layer2
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

bool led_update_user(led_t led_state) {
	rgblight_set_layer_state(1, led_state.caps_lock);
    rgblight_set_layer_state(0, !(led_state.caps_lock));
    return true;
}

// layer_state_t default_layer_state_set_user(layer_state_t state) {
//     rgblight_set_layer_state(0, layer_state_cmp(state, 0));
//     return state;
// }

// layer_state_t layer_state_set_user(layer_state_t state) {
// 	switch(get_highest_layer(state)) {
// 		case _LCTRL:
// 		case _LALT:
// 		case _LSHIFT:
// 			rgblight_set_layer_state(2, true);
// 			break;

// 		default:
// 			break;
// 	}
	
//     return state;
// }
