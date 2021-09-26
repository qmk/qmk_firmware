#include QMK_KEYBOARD_H

enum layers {
	_DVORAK,
	_GAMING,
	_SHIFT,
	_FN,
	_NUMBER,
	_ARROW,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_DVORAK] = LAYOUT_65(
	KC_F15, KC_ESC, KC_CPI_1, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LGUI(KC_BSLASH), LALT(KC_END), GMAIL, \
	KC_F16, KC_TAB, KC_SCOLON, KC_COMMA, KC_DOT, KC_P, KC_Y, 		 		   		KC_F, KC_G, KC_C, KC_R, KC_L, KC_BSLASH, KC_LBRC, KC_RBRC, UCFEMAIL, \
	KC_F17, KC_BSPACE, KC_A, KC_O, KC_E, KC_U, KC_I, 		 						KC_D, KC_H, KC_T, KC_N, KC_S, KC_MINS, KC_ENT, KC_TRNS, \
	KC_F18, MO(_SHIFT), KC_QUOTE, KC_Q, KC_J, KC_K, KC_X, 						KC_B, KC_M, KC_W, KC_V, KC_Z, MO(_SHIFT), KC_UP, \
	TO(_GAMING), KC_LCTRL, KC_LGUI, KC_LALT, MO(_FN), MO(_NUMBER), KC_TRNS,			KC_SPACE, MO(_ARROW), KC_MPLY, KC_VOLD, KC_VOLU, KC_LEFT, KC_DOWN, KC_RIGHT
	),

	[_GAMING] = LAYOUT_65(
	LALT(KC_END), KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, 						 	KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, LALT(KC_END), KC_TRNS, \
	KC_F9, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, 		 		   						KC_F, KC_G, KC_C, KC_R, KC_L, KC_BSLASH, KC_LBRC, KC_RBRC, KC_TRNS, \
	KC_F3, KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, 		 								KC_H, KC_J, KC_K, KC_L, KC_SCOLON, KC_QUOTE, KC_ENT, RGB_TOG, \
	KC_F4, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, 										KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH, KC_RSFT, KC_UP, \
	TO(_DVORAK), KC_LCTRL, KC_LGUI, KC_LALT, KC_2, KC_SPACE, KC_TRNS,					KC_SPACE, KC_SPACE, KC_MPLY, KC_VOLD, KC_VOLU, KC_LEFT, KC_DOWN, KC_RIGHT
	),

	[_SHIFT] = LAYOUT_65(
	KC_TRNS, KC_ESC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 					 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TILD,
	KC_TRNS, LSFT(KC_TAB), KC_COLN, LSFT(KC_COMM), LSFT(KC_DOT), LSFT(KC_P), LSFT(KC_Y), 		 LSFT(KC_F), LSFT(KC_G), LSFT(KC_C), LSFT(KC_R), LSFT(KC_L), LSFT(KC_BSLS), LSFT(KC_LBRC), LSFT(KC_RBRC), KC_GRV,
	KC_TRNS, LCTL(KC_BSPC), LSFT(KC_A), LSFT(KC_O), LSFT(KC_E), LSFT(KC_U), LSFT(KC_I),      LSFT(KC_D), LSFT(KC_H), LSFT(KC_T), LSFT(KC_N), LSFT(KC_S), KC_UNDS, LSFT(KC_ENT), KC_TRNS,
	KC_TRNS, KC_SLASH, KC_DQUO, LSFT(KC_Q), LSFT(KC_J), LSFT(KC_K), LSFT(KC_X), 				 LSFT(KC_B), LSFT(KC_M), LSFT(KC_W), LSFT(KC_V), LSFT(KC_Z), KC_EQL, KC_TRNS,
    TO(_GAMING), KC_LCTRL, KC_LGUI, KC_LALT, MO(_FN), MO(_NUMBER), KC_TRNS,			 		 KC_SPACE, KC_LGUI, KC_MPLY, KC_VOLD, KC_VOLU, KC_LEFT, KC_DOWN, KC_RIGHT
	),

	[_FN] = LAYOUT_65(
	KC_TRNS, KC_ESC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 					 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LALT(KC_END), KC_TRNS,
	KC_TRNS, KC_TRNS, KC_SCOLON, CBRC, SBRC, LALT(KC_F4), LCTL(KC_L), 		 		 		 LCTL(KC_F), KC_PGUP, KC_UP, LCTL(KC_T), LCTL(KC_N), LCTL(LSFT(KC_N)), RGB_TOG, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_BSPC, LCTL(KC_A), LCTL(KC_X), LCTL(KC_C), KC_LSFT, LCTL(KC_V), 				 KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT, LCTL(KC_S), KC_END, LCTL(KC_GRV), KC_TRNS,
	KC_TRNS, KC_LSFT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 						  	 KC_TRNS, KC_PGDN, LCTL(KC_W), LCTL(LSFT(KC_T)), KC_DEL, KC_LGUI, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LALT, KC_TRNS,			 				 KC_LCTRL, KC_LCTRL, KC_TRNS, KC_TRNS, KC_TRNS, LGUI(LCTL(KC_LEFT)), KC_TRNS, LGUI(LCTL(KC_RIGHT))
	),

	[_NUMBER] = LAYOUT_65(
	KC_TRNS, KC_ESC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 					KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_GRV, LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), LSFT(KC_4), LSFT(KC_5), 		 	LSFT(KC_6), LSFT(KC_7), LSFT(KC_8), LSFT(KC_9), LSFT(KC_0), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_BSPC, KC_1, KC_2, KC_3, KC_4, KC_5, 		 								KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_ENTER, KC_TRNS,
	KC_TRNS, LSFT(KC_SLASH), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 					LSFT(KC_LBRC), LSFT(KC_RBRC), KC_LBRC, KC_RBRC, KC_TRNS, LSFT(KC_EQL), KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,			 				KC_SPACE, MO(_ARROW), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
	),

	[_ARROW] = LAYOUT_65(
	KC_TRNS, KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, 							KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, LGUI(LSFT(KC_S)), KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 		 		   		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 		 				LCTL(KC_BTN1), KC_BTN1, KC_BTN2, KC_SCROLLY, KC_SCROLLX, KC_TRNS, LCTL(LALT(KC_O)), KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 						LCTL(KC_BTN1), LCTL(KC_BTN1), KC_TRNS, KC_TRNS, KC_TRNS, KC_LGUI, RGB_TOG,
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_WBAK, KC_WFWD, KC_TRNS,			 			KC_F5, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
	)
};

// Encoder code
bool encoder_update_user(uint8_t index, bool clockwise) {
  // Left Encoder
  if (index == 0) {
      switch(biton32(layer_state))	 {
		case _GAMING:
			if (clockwise)
				tap_code(KC_VOLU);
			else
				tap_code(KC_VOLD);
			break;
		// scroll
		default:
			if (clockwise)
				tap_code(KC_WH_D);
			else
				tap_code(KC_WH_U);
			break;
	  }
  }
  // Right Encoder
  else if (index == 1) {
	  switch(biton32(layer_state)) {
		// Move between windows
		case _FN:
			if (clockwise)
				tap_code16(LGUI(KC_QUOTE));
			else
				tap_code16(C(LGUI(KC_QUOTE)));
			break;
		// Move between tabs
		default:
			if (clockwise)
				tap_code16(C(KC_PGDN));
			else
				tap_code16(C(KC_PGUP));
			break;
	  }
  }
  return true;
}

// layer RGB Lighting
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
	// 0, 0 because I want the rainbow effect to show on the first layer
	{0, 32, RGB_AZURE}
);

const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
	{0, 32, HSV_MAGENTA}
);

const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
	{0, 32, HSV_MAGENTA}
);

const rgblight_segment_t PROGMEM my_layer4_layer[] = RGBLIGHT_LAYER_SEGMENTS(
	{0, 32, HSV_MAGENTA}
);


// create the array of layers so that you can edit the color of each layer. Since I currently have 9 layers above, I make an array of 9
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
	my_layer1_layer,
	my_layer2_layer,
	my_layer3_layer,
	my_layer4_layer
);

//enable the led layers
void keyboard_post_init_user(void) {
	rgblight_layers = my_rgb_layers;
	layer_state_set_user(layer_state);
}

// enable the default layer colors
layer_state_t default_layer_state_set_user(layer_state_t state) {
	rgblight_set_layer_state(0, layer_state_cmp(state, 0));
	return state;
}

// This checks which layer you are in so that it can change the color to match that layer.
layer_state_t layer_state_set_user(layer_state_t state) {
  // Both layers will light up if both kb layers are active
  rgblight_set_layer_state(1, layer_state_cmp(state, 1)); // layer 3 active
  rgblight_set_layer_state(2, layer_state_cmp(state, 3)); // layer 4 active
  rgblight_set_layer_state(3, layer_state_cmp(state, 4)); // layer 5 active
  rgblight_set_layer_state(4, layer_state_cmp(state, 5));
  //rgblight_set_layer_state(6, layer_state_cmp(state, 6));
  //rgblight_set_layer_state(7, layer_state_cmp(state, 7));
  //rgblight_set_layer_state(8, layer_state_cmp(state, 8));

  return state;
}

bool led_update_user(led_t led_state)
{
	return true;
}

void matrix_scan_user(void) {
}
