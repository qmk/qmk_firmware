/* Copyright 2020 Dane Evans
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 2 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */

// CRKBD

#include QMK_KEYBOARD_H


char layer_state_str[24];


  enum userspace_layers {
    _DEFAULTS = 0,
	_COLEMAK = 0,
	_COLEMAKDH,
    _QWERTY,
    _NUM,
    _SYM,
    _COMMAND,
    _NUMPAD,
	_SWITCH,
    _MOVE,

};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

		// colemak
	[_COLEMAK] = LAYOUT(
	//,-----------------------------------------------------.                    ,-----------------------------------------------------.
	    LT(_NUMPAD,KC_TAB), 	KC_Q, 	 KC_W, 	  KC_F,    KC_P,    KC_G, 		 LT(_SWITCH,KC_J),    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_BSPC,
	//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
	    KC_LSFT,    KC_A,    KC_R,    KC_S,    KC_T,    KC_D, 						  KC_H,    KC_N,    KC_E,    KC_I,LT(_NUMPAD,KC_O),KC_QUOT,
	//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
		KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, 						  KC_K,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
	//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
										 KC_LGUI,   MO(_NUM),  KC_SPC, 	KC_ENT,    MO(_SYM), KC_LALT
										//`--------------------------'  `--------------------------'
	),

			// colemak DH
	[_COLEMAKDH] = LAYOUT(
	//,-----------------------------------------------------.                    ,-----------------------------------------------------.
	    LT(_NUMPAD,KC_TAB), 	KC_Q, 	 KC_W, 	  KC_F,    KC_P,    KC_B, 					LT(_SWITCH,KC_J),    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_BSPC,
	//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
	    KC_LSFT,    KC_A,    KC_R,    KC_S,    KC_T,    KC_G, 						  KC_M,    KC_N,    KC_E,    KC_I,LT(_NUMPAD,KC_O),KC_QUOT,
	//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
		KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V, 						  KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
	//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
										 KC_LGUI,   MO(_NUM),  KC_SPC, 	KC_ENT,    MO(_SYM), KC_LALT
										//`--------------------------'  `--------------------------'
	),

	// qwerty
	[_QWERTY] = LAYOUT(
	//,-----------------------------------------------------.                    ,-----------------------------------------------------.
	KC_TRNS, 	KC_Q, 	KC_W, 	KC_E, 	KC_R, 	KC_T, 							LT(_SWITCH,KC_Y), KC_U, 	KC_I, 	 KC_O, 	 KC_P, 	KC_TRNS,
	//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
	KC_TRNS, 		KC_A, 	KC_S, 	KC_D, 	KC_F, 	KC_G, 							KC_H, 	  KC_J, 	KC_K, 	 KC_L, LT(_NUMPAD,KC_SCLN), KC_TRNS,
	//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
	KC_TRNS, 		KC_Z, 	KC_X, 	KC_C, 	KC_V, 	KC_B, 							KC_N, 	  KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_TRNS,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
										 KC_TRNS,   KC_TRNS,  KC_TRNS, 	KC_TRNS,    KC_TRNS, KC_TRNS
									   //`--------------------------'  `--------------------------'
	),



	// numbers  - L thumb
	[_NUM] = LAYOUT(
	//,-----------------------------------------------------.                    ,-----------------------------------------------------.
	     KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5, 					      KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
	//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
	    KC_TRNS,   KC_NO,   KC_NO,   KC_NO,   KC_WH_U,   KC_PGUP, 				   KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,   KC_NO,  KC_DEL,
	//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
		KC_TRNS,   KC_NO,   KC_NO,   KC_NO,   KC_WH_D,   KC_PGDN,					     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
	//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
											KC_TRNS, KC_TRNS,  KC_TRNS,     KC_TRNS,   MO(_COMMAND), KC_TRNS
										//`--------------------------'  `--------------------------'
	),

	// symbols  - R thumb
	[_SYM] = LAYOUT(
	//,-----------------------------------------------------.                    ,-----------------------------------------------------.
	     KC_ESC, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC, 					   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
	    KC_TRNS,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, 					   KC_MINS,  KC_EQL, KC_LCBR, KC_RCBR, KC_PIPE, KC_GRV,
	//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
		KC_TRNS,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, 					   KC_UNDS, KC_PLUS, KC_LBRC, KC_RBRC, KC_BSLS, KC_TILD,
	//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
											KC_TRNS,   MO(_COMMAND),  KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS
										//`--------------------------'  `--------------------------'
	),

	// commands - both thumbs
	[_COMMAND] = LAYOUT(
	//,-----------------------------------------------------.                    ,-----------------------------------------------------.
	      QK_BOOT, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5, 						 KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_NO,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
	    RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI,   DF(1),   DF(0), 					 C(G(KC_LEFT)),   KC_NO,   KC_NO,   C(G(KC_RGHT)),   KC_NO,   KC_NO,
	//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
		RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD,   KC_NO,   DF(2), 					     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
	//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
										    KC_TRNS, KC_TRNS,  KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS
										//`--------------------------'  `--------------------------'
	),

	// numpad
	[_NUMPAD] = LAYOUT(
	//,-----------------------------------------------------.                    ,-----------------------------------------------------.
	LT(0,KC_NO),   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO, 					   KC_CIRC,   KC_P7,   KC_P8,   KC_P9, KC_ASTR, KC_BSPC,
	//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
	      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, 					   KC_MINS,   KC_P4,   KC_P5,   KC_P6,  KC_EQL,  KC_DEL,
	//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
		  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, 					   KC_PLUS,   KC_P1,   KC_P2,   KC_P3, KC_SLSH,   KC_NO,
	//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
									   OSM(MOD_MEH),   KC_NO,   KC_TRNS,     KC_ENT,   KC_P0,  KC_PDOT
										//`--------------------------'  `--------------------------'
	),

	// layer switcher
	[_SWITCH] = LAYOUT(
	//,-----------------------------------------------------.                    ,-----------------------------------------------------.
	      TO(0),   TO(1),   TO(2),   TO(3),   TO(4),   TO(5), 					     KC_NO,   TO(7),   KC_NO,   KC_NO,   KC_NO,   QK_BOOT,
	//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
	      KC_NO,   KC_NO, KC_BRIU,   KC_NO,   KC_NO,   KC_NO, 						 KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, EEP_RST,
	//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
		KC_SYSTEM_SLEEP,   KC_NO, KC_BRID,   KC_NO,   KC_NO,   KC_NO, 						 KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
	//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
											  KC_NO,   KC_NO,   KC_NO,      KC_NO,   KC_NO,   KC_NO
										//`--------------------------'  `--------------------------'

	),

	// amovement
	[_MOVE] = LAYOUT(
	//,-----------------------------------------------------.                    ,-----------------------------------------------------.
	LT(0,KC_NO),   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, 					   KC_HOME,  KC_UP,  KC_PGUP,   KC_NO,   KC_NO,   KC_NO,
	//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
	      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, 					   KC_LEFT,  KC_ENT, KC_RGHT,   KC_NO,   KC_NO,   KC_NO,
	//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
		 KC_APP,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, 						KC_END, KC_DOWN, KC_PGDN,  KC_DEL,   KC_NO,   KC_NO,
	//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
		                                      KC_NO,   KC_NO,   KC_NO,    KC_TRNS,   KC_NO,   KC_NO
										//`--------------------------'  `--------------------------'
	)

};


// it appears that these are different to the board numbering.
// when you specify n here, it lightss up n+1 on the board diagram - actually may be an entirely different pattern

// _QWERTY,
// Light on inner column and underglow
const rgblight_segment_t PROGMEM layer_qwerty_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 10, HSV_AZURE}
);

// _COLEMAKDH,
// Light on inner column and underglow
const rgblight_segment_t PROGMEM layer_colemakdh_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 10, HSV_RED}
);

// _NUM,
// Light on inner column and underglow
const rgblight_segment_t PROGMEM layer_num_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 10, HSV_TEAL}
);
// _SYMBOL,
// Light on inner column and underglow
const rgblight_segment_t PROGMEM layer_symbol_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 10, HSV_BLUE}
);
// _COMMAND,
// Light on inner column and underglow
const rgblight_segment_t PROGMEM layer_command_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 10, HSV_PURPLE}
);


//_NUMPAD
//havent worked out how to do each side individually either
const rgblight_segment_t PROGMEM layer_numpad_lights[] = RGBLIGHT_LAYER_SEGMENTS(
{0, 10, HSV_ORANGE}
);
const rgblight_segment_t PROGMEM layer_numpad_rh_lights[] = RGBLIGHT_LAYER_SEGMENTS(
	{0, 10, HSV_ORANGE},
	{10, 5, HSV_BLUE},
    {15, 3, HSV_BLUE},
	{18, 3, HSV_BLUE}
);

// _MOVE,
// Light on inner column and underglow
const rgblight_segment_t PROGMEM layer_move_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 10, HSV_PINK}
);

// _SWITCHER   // light up top row
const rgblight_segment_t PROGMEM layer_switcher_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 6, HSV_GREEN},
	{9, 2, HSV_GREEN},
	{17, 2, HSV_GREEN},
	{23, 2, HSV_GREEN}
);


// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    layer_qwerty_lights,
	layer_colemakdh_lights,
	layer_num_lights,// overrides layer 1
	layer_symbol_lights,
    layer_command_lights,
	layer_numpad_lights,
	layer_numpad_rh_lights,
	layer_move_lights,
	layer_switcher_lights  // Overrides other layers
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
	rgblight_mode(10);// haven't found a way to set this in a more useful way

}


layer_state_t layer_state_set_user(layer_state_t state) {
	rgblight_set_layer_state(0, layer_state_cmp(state, _DEFAULTS) && layer_state_cmp(default_layer_state,_QWERTY));
	rgblight_set_layer_state(1, layer_state_cmp(state, _DEFAULTS) && layer_state_cmp(default_layer_state,_QWERTY));

	rgblight_set_layer_state(2, layer_state_cmp(state, _NUM));
	rgblight_set_layer_state(3, layer_state_cmp(state, _SYM));
	rgblight_set_layer_state(4, layer_state_cmp(state, _COMMAND));
	rgblight_set_layer_state(5, layer_state_cmp(state, _NUMPAD));
	if (!is_keyboard_master())
		rgblight_set_layer_state(6, layer_state_cmp(state, _NUMPAD));
	rgblight_set_layer_state(7, layer_state_cmp(state, _MOVE));
	rgblight_set_layer_state(8, layer_state_cmp(state, _SWITCH));
    return state;
}

/*
bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}
*/

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}
// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);


const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);


void oled_render_layer_state(void) {
  char string [24];
  switch (get_highest_layer(default_layer_state|layer_state))
  {
      case _QWERTY:
        oled_write_ln_P(PSTR("Layer: QWERTY"),false);
        break;
      case _COLEMAK:
        oled_write_ln_P(PSTR("Layer: COLEMAK"),false);
        break;
      case _COLEMAKDH:
        oled_write_ln_P(PSTR("Layer: COLEMAKDH"),false);
        break;
      case _NUM:
        oled_write_ln_P(PSTR("Layer: Numbers"),false);
        break;
      case _SYM:
        oled_write_ln_P(PSTR("Layer: Symbols"),false);
        break;
      case _COMMAND:
        oled_write_ln_P(PSTR("Layer: Command"),false);
        break;
      case _NUMPAD:
        oled_write_ln_P(PSTR("Layer: Numpad"),false);
        break;
      case _MOVE:
        oled_write_ln_P(PSTR("Layer: Movement"),false);
        break;
      case _SWITCH:
        oled_write_ln_P(PSTR("Layer: Layer Switch"),false);
        break;
      default:
#if defined (LAYER_STATE_32BIT)
        snprintf(string, sizeof(string), "%ld",layer_state);
#else
        snprintf(string, sizeof(string), "%d",layer_state);
#endif
        oled_write_P(PSTR("Layer: Undef-"),false);
        oled_write_ln(string, false);
    }
}

char keylog_str[24] = {};
const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }
  return true;
}
#endif // OLED_ENABLE
