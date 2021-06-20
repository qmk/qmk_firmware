#include QMK_KEYBOARD_H

#include "bootloader.h"
#ifdef CONSOLE_ENABLE
#include <print.h>
#endif

#ifdef RGBLIGHT_ENABLE
#define RGBLIGHT_LIMIT_VAL 255
#endif

// Backlight timeout feature
#define BACKLIGHT_TIMEOUT 1    // in minutes

#define _______ KC_TRNS

#ifdef RGBLIGHT_ENABLE
static uint16_t idle_timer = 0;
static uint8_t halfmin_counter = 0;
static bool led_on = true;
#endif

// alt key state
static bool alt_tab = false;

enum layer_names {
    _Mac0,
    _Mac1,
    _Mac2,
    _Win0,
    _Win1,
    _Win2,
    _WinALT,
    _CapsColor,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// Mac
	[_Mac0] = LAYOUT_masahide(
			KC_ESC,   KC_1,	   KC_2,    KC_3,	KC_4,	KC_5,		 KC_6,	  KC_7,   KC_8,    KC_9,	KC_0,	 KC_MINS,  KC_EQL,	KC_BSPC,
			KC_TAB,   KC_Q,	   KC_W,    KC_E,	KC_R,	KC_T,		 KC_Y,	  KC_U,   KC_I,    KC_O,	KC_P,	 KC_LBRC,  KC_RBRC, KC_BSLS,
			MO(_Mac1),KC_A,	   KC_S,    KC_D,	KC_F,	KC_G,		 KC_H,	  KC_J,   KC_K,    KC_L,	KC_SCLN, KC_QUOT,  KC_ENT,			 
			KC_LSFT,  KC_Z,	   KC_X,    KC_C,	KC_V,	KC_B,		 KC_N,	  KC_M,   KC_COMM, KC_DOT,	KC_SLSH,           KC_RSFT,
			KC_LCTL,  KC_LALT, KC_LGUI,			LT(_Mac1,KC_SPC),    KC_SPC,          KC_RCTL, KC_RGUI, KC_RALT, KC_LEFT,  KC_DOWN, KC_RGHT),

	[_Mac1] = LAYOUT_masahide(
			KC_GRAVE, KC_F1,   KC_F2,   KC_F3,	KC_F4,	KC_F5,       KC_F6,   KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12,	KC_DEL,
			_______,  _______,KC_MS_U,_______,_______,_______,		 C(S(KC_TAB)),KC_PGDN,KC_PGUP,C(KC_TAB),_______,_______,_______, _______,
			KC_CAPS,  KC_MS_L,KC_MS_D,KC_MS_R,_______,_______,		 KC_LEFT, KC_DOWN,KC_UP,  KC_RGHT,_______,_______,_______,
			_______,  _______,_______,_______,_______,_______,		 KC_BTN1, KC_BTN2,_______,_______,_______,        KC_UP,
			_______,  _______,_______,				  _______,       LT(_Mac2,KC_SPC),_______,_______,_______,_______,_______, _______),

	[_Mac2] = LAYOUT_masahide(
			KC_TILD,  _______,DF(_Win0),_______,_______,_______,       _______, _______,_______,_______,_______, _______, _______, _______,
			_______,  _______,_______,_______,_______,_______,	     _______, _______,_______,_______,_______, _______, _______, _______,
			_______,  _______,_______,_______,_______,_______,	     _______, _______,_______,_______,_______, _______, _______,
			_______,  _______,_______,_______,_______,_______,	     _______, _______,_______,_______,_______,          _______,	
			_______,  _______,_______,				  _______,       _______,         _______,_______,_______, _______,_______, _______),

// Windows
	[_Win0] = LAYOUT_masahide(
			KC_GESC,  KC_1,	   KC_2,     KC_3,	KC_4,	KC_5,		 KC_6,	  KC_7,   KC_8,    KC_9,	KC_0,	 KC_MINS,  KC_EQL,	KC_BSPC,
			KC_TAB,   KC_Q,	   KC_W,     KC_E,	KC_R,	KC_T,		 KC_Y,	  KC_U,   KC_I,    KC_O,	KC_P,	 KC_LBRC,  KC_RBRC, KC_BSLS,
			MO(_Win1),KC_A,	   KC_S,     KC_D,	KC_F,	KC_G,		 KC_H,	  KC_J,   KC_K,    KC_L,	KC_SCLN, KC_QUOT,  KC_ENT,			 
			KC_LSFT,  KC_Z,	   KC_X,     KC_C,	KC_V,	KC_B,		 KC_N,	  KC_M,   KC_COMM, KC_DOT,	KC_SLSH,           KC_RSFT,
			KC_LCTL,  KC_LGUI, MO(_WinALT),	  	LT(_Win1,KC_SPC),    KC_SPC,          KC_RCTL, KC_RALT, KC_RGUI, KC_LEFT,  KC_DOWN, KC_RGHT),

	[_Win1] = LAYOUT_masahide(
			KC_GRAVE, KC_F1,   KC_F2,    KC_F3,	KC_F4,	KC_F5,       KC_F6,   KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11,  KC_F12,	KC_DEL,
			_______,  _______,KC_MS_U,_______,_______,_______,		 C(S(KC_TAB)),KC_PGDN,KC_PGUP,C(KC_TAB),_______,_______,_______, _______,
			KC_CAPS,  KC_MS_L,KC_MS_D,KC_MS_R,_______,_______,		 KC_LEFT, KC_DOWN,KC_UP,  KC_RGHT,_______,_______,_______,
			_______,  _______,_______,_______,_______,_______,		 KC_BTN1, KC_BTN2,_______,_______,_______,        KC_UP,
			_______,  _______, _______,			       _______,      LT(_Win2,KC_SPC),_______, _______,_______,_______,_______, _______),

	[_Win2] = LAYOUT_masahide(
			KC_TILD,  DF(_Mac0),_______,_______,_______,_______,    _______, _______,_______, _______,_______, _______, _______, _______,
			_______,  _______,  _______,_______,_______,_______,	_______, _______,_______, _______,_______, _______, _______, _______,
			_______,  _______,	_______,_______,_______,_______,	_______, _______,_______, _______,_______, _______, _______,
			_______,  _______,	_______,_______,_______,_______,	_______, _______,_______, _______,_______,          _______,	
			_______,  _______,  _______,		 	    _______,    _______,         _______, _______,_______, _______, _______, _______),

	[_WinALT] = LAYOUT_masahide(
			KC_GESC,  A(KC_1), A(KC_2),  A(KC_3),A(KC_4),A(KC_5),   A(KC_6),  A(KC_7),A(KC_8), A(KC_9),	A(KC_0), A(KC_MINS),  A(KC_EQL), A(KC_DEL),
			_______,  A(KC_F4),C(KC_W),  C(KC_E),C(KC_R),C(KC_T),	A(KC_Y),  A(KC_U),A(KC_I), A(KC_O),	A(KC_P), A(KC_LEFT),  A(KC_RGHT),A(KC_BSLS),
			_______,  C(KC_A), C(KC_S),  C(KC_D),C(KC_F),C(KC_G),	A(KC_H),  A(KC_J),A(KC_K), A(KC_L),A(KC_SCLN),A(KC_QUOT), A(KC_ENT),
 			_______,  C(KC_Z), C(KC_X),  C(KC_C),C(KC_V),C(KC_B),   C(KC_N),  A(KC_M),A(KC_COMM),A(KC_DOT),A(KC_SLSH),        A(KC_UP),
			_______,  _______, _______,	    	LT(_Win1,KC_SPC),   KC_SPC,           _______, _______, _______, A(KC_LEFT),  A(KC_DOWN), A(KC_RGHT)),
};



bool check_alt_tab(uint16_t keycode, keyrecord_t *record) {
    //ALT key
    if (keycode == MO(_WinALT) && !record->event.pressed && alt_tab){
        unregister_mods(MOD_LALT);
        alt_tab = false;
        return true;
    }
    if (keycode == KC_TAB && record->event.pressed && layer_state_is(_WinALT) && !alt_tab){
        register_mods(MOD_LALT);
        alt_tab = true;
    }
    return true;

}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // rgb suspend
#ifdef RGBLIGHT_ENABLE
    if (record->event.pressed) {
        if (led_on == false) {
            rgblight_enable_noeeprom();
            led_on = true;
        }
        idle_timer = timer_read();
        halfmin_counter = 0;
    }
#endif

#ifdef CONSOLE_ENABLE
        uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif 

    check_alt_tab(keycode,record);

    return true;
}

void matrix_scan_user(void) {
#ifdef RGBLIGHT_ENABLE
    // idle_timer needs to be set one time
    if (idle_timer == 0) idle_timer = timer_read();
    if (led_on) {
        if ( timer_elapsed(idle_timer) > 30000) {
            halfmin_counter++;
            idle_timer = timer_read();
        }

        if ( halfmin_counter >= BACKLIGHT_TIMEOUT) {
            rgblight_disable_noeeprom();
            led_on = false;
            halfmin_counter = 0;
        }
    }
#endif

}

#ifdef RGBLIGHT_ENABLE
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
const rgblight_segment_t PROGMEM my_6_layer[] = RGBLIGHT_LAYER_SEGMENTS(
	{1, 4, HSV_PURPLE},
	{7, 4, HSV_PURPLE}
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
	my_6_layer,
	my_caps_layer
);


layer_state_t layer_state_set_user(layer_state_t state) {
	rgblight_set_layer_state(_Mac0, layer_state_cmp(state, _Mac0));
	rgblight_set_layer_state(_Mac1, layer_state_cmp(state, _Mac1));
	rgblight_set_layer_state(_Mac2, layer_state_cmp(state, _Mac2));
	rgblight_set_layer_state(_Win0, layer_state_cmp(state, _Win0));
	rgblight_set_layer_state(_Win1, layer_state_cmp(state, _Win1));
	rgblight_set_layer_state(_Win2, layer_state_cmp(state, _Win2));
	rgblight_set_layer_state(_WinALT,layer_state_cmp(state, _WinALT));
    biton32(default_layer_state) == _Win0 ? rgblight_set_layer_state(_Win0, true) : rgblight_set_layer_state(_Mac0, true);
	return state;
};
layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(_Mac0, layer_state_cmp(state, _Mac0));
    return state;
}



bool led_update_user(led_t led_state) {
	rgblight_set_layer_state(_CapsColor, led_state.caps_lock);
	return true;
};

#endif

void keyboard_post_init_user(void) {
#ifdef RGBLIGHT_ENABLE
	// Enable the LED layers
    // RGB setting
	rgblight_layers = my_layers;
	layer_state_set_user(layer_state);
#endif
};

// EEPROM Reset Function
void eeconfig_init_user(void) {
#ifdef RGBLIGHT_ENABLE
	backlight_enable(); // Enable backlight by default
	rgblight_enable(); // Enable RGB by default
	rgblight_sethsv(HSV_RED);	// Set it to orange by default
#endif
}; 
