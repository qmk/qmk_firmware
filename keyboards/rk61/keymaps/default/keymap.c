// Copyright 2020 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "common/rgbFunctions.h"
#include "common/layers.h" 

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE_LAYER] = LAYOUT_61(
		KC_ESC,	 KC_1,    KC_2,    KC_3,   KC_4,    KC_5, 	 KC_6, KC_7, KC_8,	  KC_9,     KC_0,      KC_MINS, KC_EQL,   KC_BSPC, 
		KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,    KC_T, 	 KC_Y, KC_U, KC_I, 	  KC_O,     KC_P,      KC_LBRC, KC_RBRC,  KC_BSLS, 
		KC_CAPS, KC_A,    KC_S,    KC_D,   KC_F,    KC_G, 	 KC_H, KC_J, KC_K, 	  KC_L,     KC_SCLN,   KC_QUOT, 	  	  KC_ENT, 
		KC_LSFT, KC_Z,	  KC_X,    KC_C,   KC_V,    KC_B, 	 KC_N, KC_M, KC_COMM, KC_DOT,   KC_SLASH,  KC_RSFT, 
		KC_LCTL, KC_LWIN, KC_LALT, 				    KC_SPC,                       KC_RALT,  KC_APP,    KC_RCTL, 	      MO(FN_LAYER)
	),	

	[BASE_LAYER] = LAYOUT_61(
		KC_ESC,	 KC_1,    KC_2,    KC_3,   KC_4,    KC_5, 	 KC_6, KC_7, KC_8,	  KC_9,     KC_0,      KC_MINS, KC_EQL,   KC_BSPC, 
		KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,    KC_T, 	 KC_Y, KC_U, KC_I, 	  KC_O,     KC_P,      KC_LBRC, KC_RBRC,  KC_BSLS, 
		KC_CAPS, KC_A,    KC_S,    KC_D,   KC_F,    KC_G, 	 KC_H, KC_J, KC_K, 	  KC_L,     KC_SCLN,   KC_QUOT, 	  	  KC_ENT, 
		KC_LSFT, KC_Z,	  KC_X,    KC_C,   KC_V,    KC_B, 	 KC_N, KC_M, KC_COMM, KC_DOT,   KC_SLASH,  KC_RSFT, 
		KC_LCTL, KC_LWIN, KC_LALT, 				    KC_SPC,                       KC_RALT,  KC_APP,    KC_RCTL, 	      MO(FN_LAYER)
	),

	[FN_LAYER] = LAYOUT_61(
		KC_GRV,  	       KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL, 
		TG(MEDIA_LAYER),   _______, _______, _______, _______, _______, KC_PSCR, _______, _______, _______, _______, _______, _______, QK_BOOT, 
		TG(WIN_DIS_LAYER), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		TG(RGB_LAYER), 	   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		TG(FN_LOCK_LAYER), TO(BASE_LAYER),   _______,          	        TG(NAV_LAYER),						_______, _______, _______, _______
	),

	[MEDIA_LAYER] = LAYOUT_61(
		_______, KC_MYCM, KC_WSCH, KC_MAIL, KC_CALC, KC_MSEL, KC_MSTP, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, _______, 
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______
	),

	[NAV_LAYER] = LAYOUT_61(
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
		_______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______,  _______,  _______, _______, _______, 
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______,  _______,
		_______, _______, _______, _______, _______, _______, _______,	 _______, _______, KC_HOME, KC_UP, KC_END,
		_______, _______, _______, _______, 											   KC_LEFT, KC_DOWN, KC_RGHT, _______
	),

	[RGB_LAYER] = LAYOUT_61(
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RM_SPDD, RM_SPDU, _______, 
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RM_VALD, RM_VALU, RM_TOGG, 
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 		   RM_PREV, RM_NEXT, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, 					 _______, 									  _______, _______, _______, _______
	),

	[FN_LOCK_LAYER] = LAYOUT_61(
		_______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, _______, 
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______
	),

	[WIN_DIS_LAYER] = LAYOUT_61(
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, KC_NO,   _______, _______, _______, _______, _______, _______
	)
};

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

	setRgbForCapsLockIndicator();
	setRgbForWinKeyIndicator();
	setRgbForFnLayer();

	setRgbForKeys(MEDIA_LAYER, media_keys, MEDIA_LED_COUNT, (RGB){RGB_YELLOW}); // media layer highlight
	setRgbForKeys(NAV_LAYER, nav_keys, NAV_COUNT, (RGB){RGB_WHITE}); 			// navigation layer highlight
	setRgbForKeys(RGB_LAYER, rgb_keys, RGB_KEYS_COUNT, (RGB){RGB_WHITE});		// navigation layer highlight
	setRgbForKeys(FN_LOCK_LAYER, fn_keys, FN_KEYS_COUNT, (RGB){RGB_RED});		// fn lock layer highlight

    return true;
}

void suspend_power_down_user(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_user(void) {
    rgb_matrix_set_suspend_state(false);
}