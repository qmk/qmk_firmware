#include QMK_KEYBOARD_H
// the two lines below this are needed to use alt tab with encoders
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

enum layers {
    _DVORAK,
	_CAMILA,
    _NUMBER,
	_NUMPAD,
    _FN1,
    _GAMING,
    _LSHIFT,
    _RSHIFT,
	_ARROW,
};

enum unicode_names {
  SE_AA_HIGH,
  SE_AE_HIGH,
  SE_OE_HIGH,
  SE_AA_LOW,
  SE_AE_LOW,
  SE_OE_LOW,
};

const uint32_t PROGMEM unicode_map[] = {
  [SE_AA_HIGH] = 0x00C5,
  [SE_AE_HIGH] = 0x00C4,
  [SE_OE_HIGH] = 0x00D6,
  [SE_AA_LOW]  = 0x00E5,
  [SE_AE_LOW]  = 0x00E4,
  [SE_OE_LOW]  = 0x00F6,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_DVORAK] = LAYOUT_4Bar(
		KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_TRNS, LALT(KC_N), LALT(KC_END), 
		KC_TAB, KC_SCLN, KC_COMM, KC_DOT, KC_P, KC_Y, KC_F, KC_G, KC_C, KC_R, KC_L,	KC_BSLS, KC_MUTE, KC_S, 
		KC_BSPC, KC_A, KC_O, KC_E, KC_U, KC_I, KC_D, KC_H, KC_T, KC_N, KC_S, KC_MINS, KC_ENT,
		MO(_LSHIFT), KC_QUOT, KC_Q, KC_J, KC_K, KC_X, KC_B, KC_M, KC_W, KC_V, KC_Z, MO(_RSHIFT), 
		KC_LCTL, KC_LGUI, KC_LALT, MO(_FN1), MO(_NUMBER), KC_SPC, MO(_FN1), KC_MPLY, KC_VOLD, KC_VOLU, MO(_ARROW)
	),
	
	[_CAMILA] = LAYOUT_4Bar(
		KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_TRNS, KC_TRNS, LALT(KC_END), 
		KC_TAB, KC_QUOT, KC_COMM, KC_DOT, KC_P, KC_Y, KC_F, KC_G, KC_C, KC_R, KC_L, KC_SLSH, KC_EQL, KC_BSLS, 
		KC_BSPC, KC_A, KC_O, KC_E, KC_U, KC_I, KC_D, KC_H, KC_T, KC_N, KC_S, KC_MINS, KC_ENT, 
		KC_LSFT, KC_SCLN, KC_Q, KC_J, KC_K, KC_X, KC_B, KC_M, KC_W, KC_V, KC_Z, KC_RSFT, 
		KC_LCTL, KC_LGUI, KC_LALT, MO(_FN1), MO(_NUMBER), KC_SPC, MO(_FN1), KC_MPLY, KC_VOLD, KC_VOLU, MO(_ARROW)
	),
    
    [_NUMBER] = LAYOUT_4Bar(
		KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_TRNS, KC_TRNS, LALT(KC_END), 
		KC_GRV, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_BSPC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_ENT, 
		KC_QUES, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PLUS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_SPC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
	),
	
	[_NUMPAD] = LAYOUT_4Bar(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MINS, KC_ASTR, KC_PLUS, KC_CIRC, KC_LPRN, KC_RPRN, KC_BSPC,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_7, KC_8, KC_9, KC_LBRC, KC_RBRC, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_4, KC_5, KC_6, KC_COLN, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_1, KC_2, KC_3, KC_SLSH, KC_COMM, LGUI(LSFT(KC_S)),
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_0, KC_DOT, KC_TRNS, LCTL(KC_C), LCTL(KC_V), TO(_DVORAK)
	),

    [_FN1] = LAYOUT_4Bar(
		KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_TRNS, KC_TRNS, LALT(KC_END), 
		KC_TAB, KC_TRNS, KC_TRNS, KC_TRNS, LALT(KC_F4), KC_TRNS,KC_TRNS, KC_PGUP, KC_UP, LCTL(KC_T), LCTL(KC_N), LCTL(LSFT(KC_N)), KC_TRNS, KC_TRNS, 
		KC_BSPC, LCTL(KC_A), LCTL(KC_X), LCTL(KC_C), KC_LSFT, LCTL(KC_V), KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT, LCTL(KC_S), KC_END, LSFT(KC_ENT), 
		KC_LSFT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGDN, LCTL(KC_W), LCTL(LSFT(KC_T)), KC_DEL, KC_RSFT,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LCTRL, KC_RCTL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS

	),
	
	[_GAMING] = LAYOUT_4Bar(
		KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_TRNS, KC_TRNS, LCTL(KC_END),
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_BSPC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, 
		KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_QUES, KC_RSFT, 
		KC_LCTRL, KC_LGUI, KC_LALT, KC_1, KC_SPC, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLD, KC_VOLU, TO(_DVORAK) 
	),
	
	[_LSHIFT] = LAYOUT_4Bar(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TILD, KC_COLN, LSFT(KC_COMM), LSFT(KC_DOT), LSFT(KC_P), LSFT(KC_Y), LSFT(KC_F), LSFT(KC_G), LSFT(KC_C), LSFT(KC_R), LSFT(KC_L), LSFT(KC_BSLS), KC_TRNS, KC_TRNS, 
		LCTL(KC_BSPC), LSFT(KC_A), LSFT(KC_O), LSFT(KC_E), LSFT(KC_U), LSFT(KC_I), LSFT(KC_D), LSFT(KC_H), LSFT(KC_T), LSFT(KC_N), LSFT(KC_S), KC_UNDS, LSFT(KC_ENT), 
		KC_TRNS, KC_DQUO, LSFT(KC_Q), LSFT(KC_J), LSFT(KC_K), LSFT(KC_X), LSFT(KC_B), LSFT(KC_M), LSFT(KC_W), LSFT(KC_V), LSFT(KC_Z), KC_EQL, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_LBRC, KC_RBRC, KC_SPC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
	),
	
	
	[_RSHIFT] = LAYOUT_4Bar(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TILD, KC_COLN, LSFT(KC_COMM), LSFT(KC_DOT), LSFT(KC_P), LSFT(KC_Y), LSFT(KC_F), LSFT(KC_G), LSFT(KC_C), LSFT(KC_R), LSFT(KC_L), LSFT(KC_BSLS), KC_TRNS, KC_TRNS, 
		LCTL(KC_BSPC), LSFT(KC_A), LSFT(KC_O), LSFT(KC_E), LSFT(KC_U), LSFT(KC_I), LSFT(KC_D), LSFT(KC_H), LSFT(KC_T), LSFT(KC_N), LSFT(KC_S), KC_UNDS, LSFT(KC_ENT), 
		KC_SLSH, KC_DQUO, LSFT(KC_Q), LSFT(KC_J), LSFT(KC_K), LSFT(KC_X), LSFT(KC_B), LSFT(KC_M), LSFT(KC_W), LSFT(KC_V), LSFT(KC_Z), KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, LSFT(KC_LBRC), LSFT(KC_RBRC), KC_SPC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
	),
	
	[_ARROW] = LAYOUT_4Bar(
		KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LGUI(LSFT(KC_S)), 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_UP, KC_TRNS,
		RESET, KC_TRNS, KC_TRNS, TO(_GAMING), TO(_NUMPAD), TO(_CAMILA), TO(_DVORAK), KC_LEFT, KC_DOWN, KC_RIGHT, KC_TRNS

	)
};

// layer RGB Lighting
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
	{1, 2, HSV_CYAN},
	{3, 4, HSV_CYAN},
	{5, 6, HSV_CYAN},
	{7, 8, HSV_CYAN},
	{9, 10, HSV_CYAN}
);

const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
	{1, 2, HSV_PINK},
	{3, 4, HSV_PINK},
	{5, 6, HSV_PINK},
	{7, 8, HSV_PINK},
	{9, 10, HSV_PINK}
);

const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
	{1, 2, HSV_PINK},
	{3, 4, HSV_PINK},
	{5, 6, HSV_PINK},
	{7, 8, HSV_PINK},
	{9, 10, HSV_PINK}
);

const rgblight_segment_t PROGMEM my_layer4_layer[] = RGBLIGHT_LAYER_SEGMENTS(
	{1, 2, HSV_GREEN},
	{3, 4, HSV_GREEN},
	{5, 6, HSV_GREEN},
	{7, 8, HSV_GREEN},
	{9, 10, HSV_GREEN}
);

const rgblight_segment_t PROGMEM my_layer5_layer[] = RGBLIGHT_LAYER_SEGMENTS(
	{1, 2, HSV_WHITE},
	{3, 4, HSV_WHITE},
	{5, 6, HSV_WHITE},
	{7, 8, HSV_WHITE},
	{9, 10, HSV_WHITE}
);

const rgblight_segment_t PROGMEM my_layer6_layer[] = RGBLIGHT_LAYER_SEGMENTS(
	{1, 2, HSV_RED},
	{3, 4, HSV_RED},
	{5, 6, HSV_RED},
	{7, 8, HSV_RED},
	{9, 10, HSV_RED}
);

const rgblight_segment_t PROGMEM my_layer7_layer[] = RGBLIGHT_LAYER_SEGMENTS(
	{1, 2, HSV_PINK},
	{3, 4, HSV_PINK},
	{5, 6, HSV_PINK},
	{7, 8, HSV_PINK},
	{9, 10, HSV_PINK}
);

// define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
	my_layer1_layer,
	my_layer2_layer,
	my_layer3_layer,
	my_layer4_layer,
	my_layer5_layer,
	my_layer6_layer,
	my_layer7_layer
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

// other layers
layer_state_t layer_state_set_user(layer_state_t state) {
  // Both layers will light up if both kb layers are active
  rgblight_set_layer_state(1, layer_state_cmp(state, 1));
  rgblight_set_layer_state(2, layer_state_cmp(state, 2));
  rgblight_set_layer_state(3, layer_state_cmp(state, 3));
  rgblight_set_layer_state(4, layer_state_cmp(state, 4));
  return state;
}

// idek
bool led_update_user(led_t led_state)
{
	return true;
}

// Encoder
void encoder_update_user(uint8_t index, bool clockwise) {
  // first Encoder top left
  if (index == 0) {
      switch(biton32(layer_state))	 {
		  // scroll left and right while holding the bottom right FN key
		  case _ARROW: 
			if (clockwise)
				tap_code(KC_RIGHT); 
			else
				tap_code(KC_LEFT);
			break;
		// scroll left and right by default until I find something better
		 default: 
			// it will work as alt tab by default
			if (clockwise) {
				if (!is_alt_tab_active) {
					is_alt_tab_active = true;
					register_code(KC_LALT);
				}
				alt_tab_timer = timer_read();
				tap_code16(KC_TAB);
			} else {
				alt_tab_timer = timer_read();
				tap_code16(S(KC_TAB));
			}
			break;
	  }
  }
  // second encoder right
  else if (index == 1) {
	  switch(biton32(layer_state)) {
		  // I want it to work as left and right arrow key in numpad layer
		case _NUMPAD:
			if (clockwise) {
				tap_code(KC_RIGHT);
			} else {
				tap_code(KC_LEFT);
			}
			break;
		// in my coding fn layer it can work as ctrl Z and ctrl Y
		case _FN1:
			if (clockwise)
				tap_code16(C(KC_Y));
			else
				tap_code16(C(KC_Z));
		// the number layer being held down will allow it to maximize
		case _NUMBER:
			if (clockwise)
				tap_code16(C(KC_EQL));
			else
				tap_code16(C(KC_MINS));
			break;
		// volume control by default
		default: 
			if (clockwise)
				tap_code(KC_VOLU);
			else
				tap_code(KC_VOLD);
			break;
	  }
  }
}

// This sets the is_alt_tab_active back to false after 1250 ms which can be changed
void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1250) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}

void econfig_init_user(void) {
  set_unicode_input_mode(UC_LNX);
}
