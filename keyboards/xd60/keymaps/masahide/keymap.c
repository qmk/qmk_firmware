#include QMK_KEYBOARD_H

#include "bootloader.h"

enum custom_keycodes {
    CMD_R = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// Mac
	[0] = LAYOUT_masahide(
			KC_GESC, KC_1,	  KC_2,    KC_3,	KC_4,	KC_5,		 KC_6,	      KC_7,   KC_8,    KC_9,	KC_0,	 KC_MINS,  KC_EQL,	KC_BSPC,
			KC_TAB,  KC_Q,	  KC_W,    KC_E,	KC_R,	KC_T,		 KC_Y,	      KC_U,   KC_I,    KC_O,	KC_P,	 KC_LBRC,  KC_RBRC, KC_BSLS,
			MO(1),	 KC_A,	  KC_S,    KC_D,	KC_F,	KC_G,		 KC_H,	      KC_J,   KC_K,    KC_L,	KC_SCLN, KC_QUOT,  KC_ENT,			 
			KC_LSFT, KC_Z,	  KC_X,    KC_C,	KC_V,	KC_B,		 KC_N,	      KC_M,   KC_COMM, KC_DOT,	KC_SLSH,           KC_RSFT,
			KC_LCTL, KC_LALT, KC_LGUI,					LT(1,KC_SPC),KC_SPC,              KC_RCTL, KC_RGUI, KC_RALT, KC_LEFT,  KC_DOWN, KC_RGHT),

	[1] = LAYOUT_masahide(
			KC_TILD, KC_F1,   KC_F2,   KC_F3,	KC_F4,	KC_F5,       KC_F6,       KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,	KC_DEL,
			KC_TAB,  KC_Q,	  KC_W,    KC_E,	KC_R,	KC_T,		 KC_Y,	      KC_U,   KC_I,    KC_O,	KC_P,	 KC_LBRC,  KC_RBRC, KC_BSLS,
			KC_CAPS, KC_A,	  KC_S,    KC_D,	KC_F,	KC_G,		 KC_LEFT,	  KC_DOWN,KC_UP,   KC_RGHT,	KC_P,	 KC_QUOT,  KC_ENT,
			KC_TRNS, KC_Z,	  KC_X,    KC_C,	KC_V,	KC_B,		 KC_N,	      KC_M,   KC_COMM, KC_DOT,	KC_SLSH,           KC_UP,
			KC_TRNS, KC_TRNS, KC_TRNS,					KC_TRNS,     LT(2,KC_SPC),        KC_RGUI, KC_APP,	KC_TRNS, KC_TRNS,  KC_DOWN, KC_RGHT),

	[2] = LAYOUT_masahide(
			KC_TILD, KC_F1,   DF(3),   KC_F3,	KC_F4,	KC_F5,       KC_F6,       KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,	KC_DEL,
			KC_TAB,  KC_Q,	  KC_W,    KC_E,	KC_R,	KC_T,		 KC_Y,	      KC_U,   KC_I,    KC_O,	KC_P,	 KC_LBRC,  KC_RBRC, KC_BSLS,
			KC_CAPS, KC_A,	  KC_S,    KC_D,	KC_F,	KC_G,		 KC_LEFT,	  KC_DOWN,KC_UP,   KC_RGHT,	KC_P,	 KC_QUOT,  KC_ENT,
			KC_TRNS, KC_Z,	  KC_X,    KC_C,	KC_V,	KC_B,		 KC_N,	      KC_M,   KC_COMM, KC_DOT,	KC_SLSH,           KC_UP,	
			KC_TRNS, KC_TRNS, KC_TRNS,					KC_TRNS,     KC_TRNS,             KC_TRNS, KC_TRNS,	KC_TRNS, KC_TRNS,  KC_DOWN, KC_RGHT),

// Windows
	[3] = LAYOUT_masahide(
			KC_GESC, KC_1,	  KC_2,    KC_3,	KC_4,	KC_5,		 KC_6,	      KC_7,   KC_8,    KC_9,	KC_0,	 KC_MINS,  KC_EQL,	KC_BSPC,
			KC_TAB,  KC_Q,	  KC_W,    KC_E,	KC_R,	KC_T,		 KC_Y,	      KC_U,   KC_I,    KC_O,	KC_P,	 KC_LBRC,  KC_RBRC, KC_BSLS,
			MO(1),	 KC_A,	  KC_S,    KC_D,	KC_F,	KC_G,		 KC_H,	      KC_J,   KC_K,    KC_L,	KC_SCLN, KC_QUOT,  KC_ENT,			 
			KC_LSFT, KC_Z,	  KC_X,    KC_C,	KC_V,	KC_B,		 KC_N,	      KC_M,   KC_COMM, KC_DOT,	KC_SLSH,           KC_RSFT,
			KC_LCTL, KC_LGUI, KC_LALT,					LT(4,KC_SPC),KC_SPC,              KC_RCTL, KC_RGUI, KC_RALT, KC_LEFT,  KC_DOWN, KC_RGHT),

	[4] = LAYOUT_masahide(
			KC_TILD, KC_F1,   KC_F2,   KC_F3,	KC_F4,	KC_F5,       KC_F6,       KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,	KC_DEL,
			KC_TAB,  KC_Q,	  KC_W,    KC_E,	KC_R,	KC_T,		 KC_Y,	      KC_U,   KC_I,    KC_O,	KC_P,	 KC_LBRC,  KC_RBRC, KC_BSLS,
			KC_CAPS, KC_A,	  KC_S,    KC_D,	KC_F,	KC_G,		 KC_LEFT,	  KC_DOWN,KC_UP,   KC_RGHT,	KC_P,	 KC_QUOT,  KC_ENT,
			KC_TRNS, KC_Z,	  KC_X,    KC_C,	KC_V,	KC_B,		 KC_N,	      KC_M,   KC_COMM, KC_DOT,	KC_SLSH,           KC_UP,
			KC_TRNS, KC_TRNS, KC_TRNS,					KC_TRNS,     LT(5,KC_SPC),        KC_RGUI, KC_APP,	KC_TRNS, KC_TRNS,  KC_DOWN, KC_RGHT),

	[5] = LAYOUT_masahide(
			KC_TILD, DF(0),   KC_F2,   KC_F3,	KC_F4,	KC_F5,       KC_F6,       KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,	KC_DEL,
			KC_TAB,  KC_Q,	  KC_W,    KC_E,	KC_R,	KC_T,		 KC_Y,	      KC_U,   KC_I,    KC_O,	KC_P,	 KC_LBRC,  KC_RBRC, KC_BSLS,
			KC_CAPS, KC_A,	  KC_S,    KC_D,	KC_F,	KC_G,		 KC_LEFT,	  KC_DOWN,KC_UP,   KC_RGHT,	KC_P,	 KC_QUOT,  KC_ENT,
			KC_TRNS, KC_Z,	  KC_X,    KC_C,	KC_V,	KC_B,		 KC_N,	      KC_M,   KC_COMM, KC_DOT,	KC_SLSH,           KC_UP,	
			KC_TRNS, KC_TRNS, KC_TRNS,					KC_TRNS,     KC_TRNS,             KC_TRNS, KC_TRNS,	KC_TRNS, KC_TRNS,  KC_DOWN, KC_RGHT),
};


const rgblight_segment_t PROGMEM my_0_layer[] = RGBLIGHT_LAYER_SEGMENTS(
	{0, 6, HSV_CYAN},
	{6, 6, HSV_BLUE}
);

const rgblight_segment_t PROGMEM my_1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
	{1, 4, HSV_GREEN},
	{7, 4, HSV_GREEN}
);
const rgblight_segment_t PROGMEM my_2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
	{1, 4, HSV_PURPLE},
	{7, 4, HSV_PURPLE}
);

const rgblight_segment_t PROGMEM my_3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
	{0, 6, HSV_WHITE},
	{6, 6, HSV_WHITE}
);

const rgblight_segment_t PROGMEM my_4_layer[] = RGBLIGHT_LAYER_SEGMENTS(
	{1, 4, HSV_GREEN},
	{7, 4, HSV_GREEN}
);
const rgblight_segment_t PROGMEM my_5_layer[] = RGBLIGHT_LAYER_SEGMENTS(
	{1, 4, HSV_WHITE},
	{7, 4, HSV_WHITE}
);


const rgblight_segment_t PROGMEM my_caps_layer[] = RGBLIGHT_LAYER_SEGMENTS(
	{0, 1, HSV_RED},
	{5, 1, HSV_RED},
	{6, 1, HSV_RED},
	{11, 1, HSV_RED}
);
	
// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_layers[] = RGBLIGHT_LAYERS_LIST(
	my_0_layer,
	my_1_layer,
	my_2_layer,
	my_3_layer,
	my_4_layer,
	my_5_layer,
	my_caps_layer
);

void keyboard_post_init_user(void) {
	// Enable the LED layers
	rgblight_layers = my_layers;
	layer_state_set_user(layer_state);
};

layer_state_t layer_state_set_user(layer_state_t state) {
	rgblight_set_layer_state(0, layer_state_cmp(state, 0));
	rgblight_set_layer_state(1, layer_state_cmp(state, 1));
	rgblight_set_layer_state(2, layer_state_cmp(state, 2));
	rgblight_set_layer_state(3, layer_state_cmp(state, 3));
	rgblight_set_layer_state(4, layer_state_cmp(state, 4));
	rgblight_set_layer_state(5, layer_state_cmp(state, 5));
	return state;
};

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, 0));
    rgblight_set_layer_state(3, layer_state_cmp(state, 3));
    return state;
}


bool led_update_user(led_t led_state) {
	rgblight_set_layer_state(6, led_state.caps_lock);
	return true;
};


// EEPROM Reset Function
void eeconfig_init_user(void) {
	backlight_enable(); // Enable backlight by default
	rgblight_enable(); // Enable RGB by default
	rgblight_sethsv(HSV_BLUE);	// Set it to orange by default
}; 
