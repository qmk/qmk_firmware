#include QMK_KEYBOARD_H

#include "bootloader.h"

enum custom_keycodes {
    CMD_R = SAFE_RANGE,
};

#define RGBLIGHT_LIMIT_VAL 255

// Backlight timeout feature
#define BACKLIGHT_TIMEOUT 1    // in minutes

#define _______ KC_TRNS
static uint16_t idle_timer = 0;
static uint8_t halfmin_counter = 0;
static bool led_on = true;

// alt key state
static bool alt_pressed = false;
static uint8_t ex_alt_layer_pressed = 0;


typedef struct {   
    uint16_t from_key; 
    uint16_t to_mod; 
    uint16_t to_key; 
}key_swapmap_t;


enum layer_names {
    _Mac0,
    _Mac1,
    _Mac2,
    _Win0,
    _Win1,
    _Win2,
    _CapsColor,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// Mac
	[_Mac0] = LAYOUT_masahide(
			KC_ESC,   KC_1,	   KC_2,    KC_3,	KC_4,	KC_5,		 KC_6,	      KC_7,   KC_8,    KC_9,	KC_0,	 KC_MINS,  KC_EQL,	KC_BSPC,
			KC_TAB,   KC_Q,	   KC_W,    KC_E,	KC_R,	KC_T,		 KC_Y,	      KC_U,   KC_I,    KC_O,	KC_P,	 KC_LBRC,  KC_RBRC, KC_BSLS,
			MO(_Mac1),KC_A,	   KC_S,    KC_D,	KC_F,	KC_G,		 KC_H,	      KC_J,   KC_K,    KC_L,	KC_SCLN, KC_QUOT,  KC_ENT,			 
			KC_LSFT,  KC_Z,	   KC_X,    KC_C,	KC_V,	KC_B,		 KC_N,	      KC_M,   KC_COMM, KC_DOT,	KC_SLSH,           KC_RSFT,
			KC_LCTL,  KC_LALT, KC_LGUI,				LT(_Mac1,KC_SPC),KC_SPC,              KC_RCTL, KC_RGUI, KC_RALT, KC_LEFT,  KC_DOWN, KC_RGHT),

	[_Mac1] = LAYOUT_masahide(
			KC_TILD,  KC_F1,   KC_F2,   KC_F3,	KC_F4,	KC_F5,       KC_F6,       KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,	KC_DEL,
			KC_TAB,   KC_Q,	   KC_W,    KC_E,	KC_R,	KC_T,		 KC_Y,	      KC_U,   KC_I,    KC_O,	KC_P,	 KC_LBRC,  KC_RBRC, KC_BSLS,
			KC_CAPS,  KC_A,	   KC_S,    KC_D,	KC_F,	KC_G,		 KC_LEFT,	  KC_DOWN,KC_UP,   KC_RGHT,	KC_P,	 KC_QUOT,  KC_ENT,
			_______,  KC_Z,	   KC_X,    KC_C,	KC_V,	KC_B,		 KC_N,	      KC_M,   KC_COMM, KC_DOT,	KC_SLSH,           KC_UP,
			_______,  _______, _______,				_______,         LT(_Mac2,KC_SPC),    _______, _______,	_______, _______,  KC_DOWN, KC_RGHT),

	[_Mac2] = LAYOUT_masahide(
			KC_TILD,  KC_F1,   DF(_Win0),KC_F3,	KC_F4,	KC_F5,       KC_F6,       KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,	KC_DEL,
			KC_TAB,   KC_Q,	   KC_W,     KC_E,	KC_R,	KC_T,		 KC_Y,	      KC_U,   KC_I,    KC_O,	KC_P,	 KC_LBRC,  KC_RBRC, KC_BSLS,
			KC_CAPS,  KC_A,	   KC_S,     KC_D,	KC_F,	KC_G,		 KC_LEFT,	  KC_DOWN,KC_UP,   KC_RGHT,	KC_P,	 KC_QUOT,  KC_ENT,
			_______,  KC_Z,	   KC_X,     KC_C,	KC_V,	KC_B,		 KC_N,	      KC_M,   KC_COMM, KC_DOT,	KC_SLSH,           KC_UP,	
			_______,  _______, _______,					_______,     _______,             _______, _______,	_______, _______,  KC_DOWN, KC_RGHT),

// Windows
	[_Win0] = LAYOUT_masahide(
			KC_GESC,  KC_1,	   KC_2,     KC_3,	KC_4,	KC_5,		 KC_6,	      KC_7,   KC_8,    KC_9,	KC_0,	 KC_MINS,  KC_EQL,	KC_BSPC,
			KC_TAB,   KC_Q,	   KC_W,     KC_E,	KC_R,	KC_T,		 KC_Y,	      KC_U,   KC_I,    KC_O,	KC_P,	 KC_LBRC,  KC_RBRC, KC_BSLS,
			MO(1),	  KC_A,	   KC_S,     KC_D,	KC_F,	KC_G,		 KC_H,	      KC_J,   KC_K,    KC_L,	KC_SCLN, KC_QUOT,  KC_ENT,			 
			KC_LSFT,  KC_Z,	   KC_X,     KC_C,	KC_V,	KC_B,		 KC_N,	      KC_M,   KC_COMM, KC_DOT,	KC_SLSH,           KC_RSFT,
			KC_LCTL,  KC_LGUI, KC_LALT,		    	LT(_Win1,KC_SPC),KC_SPC,              KC_RCTL, KC_RGUI, KC_RALT, KC_LEFT,  KC_DOWN, KC_RGHT),

	[_Win1] = LAYOUT_masahide(
			KC_TILD,  KC_F1,   KC_F2,    KC_F3,	KC_F4,	KC_F5,       KC_F6,       KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,	KC_DEL,
			KC_TAB,   KC_Q,	   KC_W,     KC_E,	KC_R,	KC_T,		 KC_Y,	      KC_U,   KC_I,    KC_O,	KC_P,	 KC_LBRC,  KC_RBRC, KC_BSLS,
			KC_CAPS,  KC_A,	   KC_S,     KC_D,	KC_F,	KC_G,		 KC_LEFT,	  KC_DOWN,KC_UP,   KC_RGHT,	KC_P,	 KC_QUOT,  KC_ENT,
			_______,  KC_Z,	   KC_X,     KC_C,	KC_V,	KC_B,		 KC_N,	      KC_M,   KC_COMM, KC_DOT,	KC_SLSH,           KC_UP,
			_______,  _______, _______,					_______,     LT(_Win2,KC_SPC),    _______, _______,	_______, _______,  KC_DOWN, KC_RGHT),

	[_Win2] = LAYOUT_masahide(
			KC_TILD,  DF(_Mac0),KC_F2,   KC_F3,	KC_F4,	KC_F5,       KC_F6,       KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,	KC_DEL,
			KC_TAB,   KC_Q,	    KC_W,    KC_E,	KC_R,	KC_T,		 KC_Y,	      KC_U,   KC_I,    KC_O,	KC_P,	 KC_LBRC,  KC_RBRC, KC_BSLS,
			KC_CAPS,  KC_A,	    KC_S,    KC_D,	KC_F,	KC_G,		 KC_LEFT,	  KC_DOWN,KC_UP,   KC_RGHT,	KC_P,	 KC_QUOT,  KC_ENT,
			_______,  KC_Z,	    KC_X,    KC_C,	KC_V,	KC_B,		 KC_N,	      KC_M,   KC_COMM, KC_DOT,	KC_SLSH,           KC_UP,	

	[_WinALT] = LAYOUT_masahide(
			KC_GESC,  KC_1,	   KC_2,     KC_3,	 KC_4,	KC_5,		 KC_6,	      KC_7,   KC_8,    KC_9,	KC_0,	 KC_MINS,  KC_EQL,	KC_BSPC,
			KC_TAB,   A(KC_F4),C(KC_W),  C(KC_E),C(KC_R),C(KC_T),	 KC_Y,	      KC_U,   KC_I,    KC_O,	KC_P,	 KC_LBRC,  KC_RBRC, KC_BSLS,
			MO(1),	  C(KC_A), C(KC_S),  C(KC_D),C(KC_F),C(KC_G),	 KC_H,	      KC_J,   KC_K,    KC_L,	KC_SCLN, KC_QUOT,  KC_ENT,			 
 			KC_LSFT,  C(KC_Z), C(KC_X),  C(KC_C),C(KC_V),C(KC_B),  C(KC_N),	      KC_M,   KC_COMM, KC_DOT,	KC_SLSH,           KC_RSFT,
			KC_LCTL,  KC_LGUI, KC_LALT,		    	LT(_Win1,KC_SPC),KC_SPC,              KC_RCTL, KC_RGUI, KC_RALT, KC_LEFT,  KC_DOWN, KC_RGHT),
};

static key_swapmap_t  alt_swap_map[] = {
    { KC_A,    MOD_LCTL, KC_A },
    { KC_W,    MOD_LCTL, KC_W },
    { KC_E,    MOD_LCTL, KC_E },
    { KC_S,    MOD_LCTL, KC_S },
    { KC_V,    MOD_LCTL, KC_V },
    { KC_C,    MOD_LCTL, KC_C },
    { KC_X,    MOD_LCTL, KC_X },
    { KC_N,    MOD_LCTL, KC_N },
    { KC_Z,    MOD_LCTL, KC_Z },
    { KC_F,    MOD_LCTL, KC_F },
    { KC_RBRC, MOD_LCTL, KC_TAB},
    { KC_LBRC, MOD_LCTL|MOD_LSFT, KC_TAB},
    { KC_Q,    MOD_LALT, KC_F4}
};

bool check_alt_sk(uint16_t keycode, keyrecord_t *record, key_swapmap_t *map) {
    if (keycode != map->from_key) {
        return true;
    }
    if (record->event.pressed) {
        unregister_code(KC_LALT);
         register_mods(map->to_mod);
        register_code(map->to_key);
        ex_alt_layer_pressed++;
        return false;
    }

    unregister_code(map->to_key);
    unregister_mods(map->to_mod);
    if(alt_pressed){
        register_code(KC_LALT);
    }
    if (ex_alt_layer_pressed>0) {
        ex_alt_layer_pressed--;
    }
    return false;

}



// rgb suspend
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        if (led_on == false) {
            rgblight_enable_noeeprom();
            led_on = true;
        }
        idle_timer = timer_read();
        halfmin_counter = 0;
    }

    // ALT key
    if (biton32(default_layer_state) < _Win0) {
        return true;
    }
    if (keycode == KC_LALT){
        alt_pressed =  record->event.pressed;
        return true;
    }
    int i;
    if (alt_pressed || (ex_alt_layer_pressed >0)){
        for (i=0;i<sizeof(alt_swap_map);i++) {
            if (!check_alt_sk( keycode, record, &alt_swap_map[i])) {
                return false;
            }
        }
    }
    return true;
}

void matrix_scan_user(void) {
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

}


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

// RGB setting
void keyboard_post_init_user(void) {
	// Enable the LED layers
	rgblight_layers = my_layers;
	layer_state_set_user(layer_state);
};

layer_state_t layer_state_set_user(layer_state_t state) {
	rgblight_set_layer_state(_Mac0, layer_state_cmp(state, _Mac0));
	rgblight_set_layer_state(_Mac1, layer_state_cmp(state, _Mac1));
	rgblight_set_layer_state(_Mac2, layer_state_cmp(state, _Mac2));
	rgblight_set_layer_state(_Win0, layer_state_cmp(state, _Win0));
	rgblight_set_layer_state(_Win1, layer_state_cmp(state, _Win1));
	rgblight_set_layer_state(_Win2, layer_state_cmp(state, _Win2));
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


// EEPROM Reset Function
void eeconfig_init_user(void) {
	backlight_enable(); // Enable backlight by default
	rgblight_enable(); // Enable RGB by default
	rgblight_sethsv(HSV_RED);	// Set it to orange by default
}; 
