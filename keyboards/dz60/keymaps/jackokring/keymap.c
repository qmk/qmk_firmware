/* Copyright 2020 Simon Paul Jackson, BEng.
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

#include QMK_KEYBOARD_H

/*
make linux bootloader install via: (or use via if it's firmwared) => CHOICE
	cd qmk_firmware
	sudo make dz60:jackokring:dfu
	^C
	sudo make dz60:via:dfu
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	//ANSI lock mode 0 =================================================================================== ANSI lock mode 0
	// Standard ANSI 60 layout for worldwide ASCII compatibility,
	LAYOUT_60_ansi(
		KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,           KC_BSPC,
		KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
		KC_CAPS,          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
		KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,
		KC_LCTL, KC_LGUI,          KC_LALT,                   KC_SPC,                             KC_RALT, KC_APP,           KC_RCTL, MO(4)),//zero index start

	//Navigation lock mode 1 ============================================================================= Navigation lock mode 1
	// Removed ASCII 47 (/) and right ctrl/win/alt for cursor.
	// VirtualBox host key needs an Fn.
	LAYOUT_60_ansi(
		KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,           KC_BSPC,
		KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
		KC_CAPS,          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
		KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,            KC_RSFT,
		KC_LCTL, KC_LGUI,          KC_LALT,                   KC_SPC,                             KC_LEFT, KC_DOWN,          KC_RIGHT, MO(5)),

	//Numpad lock mode 2 ================================================================================= Numpad lock mode 2
	// A single finger (locking modifiers) number pad, cursor and right hand F1-F24.
	LAYOUT_60_ansi(
		KC_GESC, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_P7,   KC_P8,   KC_P9,   KC_DEL,  KC_PMNS, KC_PPLS,          KC_BSPC,
		KC_TAB,           KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_P4,   KC_P5,   KC_P6,   KC_PAST, KC_LPRN, KC_RPRN, KC_PSLS,
		KC_NLCK,          KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_P1,   KC_P2,   KC_P3,   KC_INS,  KC_CALC, KC_PENT,
		OSM(MOD_LSFT),    KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,  KC_P0,   KC_PCMM, KC_PDOT, KC_UP,            UC(8730),
		OSM(MOD_LCTL),OSM(MOD_LGUI),OSM(MOD_LALT),            OSM(MOD_RALT),                      KC_LEFT, KC_DOWN,          KC_RIGHT, TG(6)),//lock Fn

	//Macro lock mode 3 ================================================================================== Macro lock mode 3
	// A single finger macro launching board producing many modifier and function keys.
	// Can record one macro of 128 steps (backspace start/stop) and play it (space).
	LAYOUT_60_ansi(
		OSM(MOD_LALT|MOD_LSFT),    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           DM_REC1,
		OSM(MOD_LCTL|MOD_LALT),    KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,  ALGR(KC_F24),
		OSM(MOD_LCTL|MOD_LSFT),    ALGR(KC_F1),   ALGR(KC_F2),   ALGR(KC_F3),   ALGR(KC_F4),   ALGR(KC_F5),   ALGR(KC_F6),   ALGR(KC_F7),   ALGR(KC_F8),   ALGR(KC_F9),   ALGR(KC_F10),  ALGR(KC_F11),  ALGR(KC_F12),
		OSM(MOD_LSFT),         	   ALGR(KC_F13),  ALGR(KC_F14),  ALGR(KC_F15),  ALGR(KC_F16),  ALGR(KC_F17),  ALGR(KC_F18),  ALGR(KC_F19),  ALGR(KC_F20),  ALGR(KC_F21),  ALGR(KC_F22),  ALGR(KC_F23),
		OSM(MOD_LCTL),OSM(MOD_LGUI),OSM(MOD_LALT),            DM_PLY1,                            LSA(KC_TAB),OSM(MOD_RGUI), LALT(KC_TAB),  TG(7)),

	//ANSI shift mode 4 ================================================================================== ANSI shift mode 4
	// ISO characters such as £ and control of RGB/backlight and cursor.
	// Fn + P is power switch for shutdown.
	LAYOUT_60_ansi(
		KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_DEL,
		KC_TRNS,          RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_WHOM, KC_PWR,  KC_HOME, KC_END,  KC_INS,
		KC_SLCK,          KC_WSCH, UC(8747),UC(8706),KC_WFAV, UC(8730),KC_VOLD, KC_VOLU, UC(176), UC(163), KC_PAUS, KC_PSCR, KC_TRNS,
		KC_TRNS,          UC(937), KC_MUTE, BL_DEC,  BL_TOGG, BL_INC,  BL_STEP, UC(181), KC_PGUP, KC_PGDN, KC_UP,            KC_TRNS,
		KC_LCTL, DF(3),            DF(1),                     DF(2),                              KC_LEFT, KC_DOWN,          KC_RIGHT, MO(4)),
	
	//Navigation shift mode 5 ============================================================================ Navigation shift mode 5
	// All function keys, so Home and End were sacrificed.
	// Also media player launch and control.
	// No APP menu as / is on the key, as / is ? key.
	LAYOUT_60_ansi(
		KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_DEL,
		KC_TRNS,          KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,  KC_INS,
		KC_SLCK,          KC_WSCH, UC(8747),UC(8706),KC_WFAV, UC(8730),KC_VOLD, KC_VOLU, UC(176), UC(163), KC_PAUS, KC_PSCR, KC_ESC,
		KC_TRNS,          UC(937), KC_MUTE, KC_MPRV, KC_MPLY, KC_MNXT, KC_MSEL, UC(181), KC_PGUP, KC_PGDN, KC_QUES,          KC_TRNS,
		DF(0),   DF(3),            KC_LALT,                   DF(2),                              KC_RALT, KC_SLSH,          KC_RCTL, MO(5)),
	
	//Numpad shift mode 6 ================================================================================ Numpad shift mode 6
	// ANSI text entry with no left ctrl/win/alt.
	LAYOUT_60_ansi(
		KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,           KC_BSPC,
		KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
		KC_CAPS,          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
		KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,
		DF(0),   DF(3),            DF(1),                     KC_SPC,                             KC_RALT, KC_APP,           KC_RCTL, TG(6)),
	
	//Macro shift mode 7 ================================================================================= Macro shift mode 7
	// Same macro layer but different modifier grouping for more hot key combinations.
	LAYOUT_60_ansi(
		OSM(MOD_LGUI|MOD_LALT|MOD_LSFT),    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          OSM(MOD_LCTL|MOD_LALT|MOD_LSFT),
		OSM(MOD_LGUI|MOD_LCTL|MOD_LALT),    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		OSM(MOD_LGUI|MOD_LCTL|MOD_LSFT),    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		OSM(MOD_LGUI|MOD_LSFT),             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
		DF(0),   OSM(KC_LGUI),     DF(1),                     DF(2),                              TG(9),   TG(10),  TG(8),   TG(7)),

	//Extended shift mode 8 ============================================================================== Extended shift mode 8
	// A utility layer for things like the mouse.
	LAYOUT_60_ansi(
		KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_LOCK, KC_PEQL,          KC_BSPC,
		KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_WH_U, KC_WH_D, RESET,
		LSFT(KC_TAB),     KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_BTN4, KC_BTN3, KC_ENT,
		KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_PCMM, KC_BTN1, KC_MS_U,          KC_BTN2,
		KC_LCTL, KC_LGUI,          KC_LALT,                   KC_SPC,                             KC_MS_L, KC_MS_D,          KC_MS_R, TG(8)),
	
	//Special shift mode 9 =============================================================================== Special shift mode 9
	// A utility layer for things not elsewhere, and slow language entry with 0 locking.
	LAYOUT_60_ansi(
		KC_ESC,  KC_P1,   KC_P2,   KC_P3,   KC_P4,   KC_P5,   KC_P6,   KC_P7,   KC_P8,   KC_P9,   KC_P0,   KC_LOCK, KC_HANJ,          KC_DEL,
		KC_TAB,           KC_RO,   KC_KANA, KC_JYEN, KC_HENK, KC_MHEN, KC_INT6, KC_INT7, KC_INT8, KC_INT9, KC_HAEN, KC_HOME, KC_END,  KC_INS,
		KC_NLCK,          KC_WSCH, UC(8747),UC(8706),KC_WFAV, UC(8730),KC_VOLD, KC_VOLU, UC(176), UC(163), KC_PAUS, KC_PSCR, KC_ENT,
		KC_LSFT,          KC_LANG3,KC_LANG4,KC_LANG5,KC_LANG6,KC_LANG7,KC_LANG8,KC_LANG9,KC_ACL0, KC_ACL1, KC_ACL2,          KC_RSFT,
		KC_LCTL, KC_LGUI,          KC_LALT,                   KC_SPC,                             KC_RALT, MOD_RGUI,         KC_RCTL, TG(9)),

	//User shift mode 10 ================================================================================= User shift mode 10
	// Everythings apart from Fn can be defined.
	// KC_A = 04, KC_Z = 29, KC_BSPC = 42, KC_ENT = 40
#define CRYPT_SEED 666
//product line serial number goes above modulo 65536 and serial number recovery is a low
//security option?
//GPL and (C) ME? Negatiate dollar UK effective!
//kring.co.uk and ... I'm not unknown on the index as jackokring.
//Even the open sourced number of 666 might be useful. Consider it free.
//Maybe I demand publication of the source of your variant onder GPL?

//burn your serial, and don't worry we'll know as "I wondered lonly as a clouds" checksum tally!?
	LAYOUT_60_ansi(
		KC_GESC, KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_1,    KC_EQL,  KC_MINS,          KC_BSPC,
		KC_TAB,           KC_U,    KC_A,    KC_R,    KC_E,    KC_H,    KC_O,    KC_T,    KC_N,    KC_U,    KC_E,    KC_RBRC, KC_LBRC, KC_SLSH,
		KC_CAPS,          KC_N,    KC_T,    KC_E,    KC_O,    KC_E,    KC_E,    KC_A,    KC_E,    KC_E,    KC_QUOT, KC_SCLN, KC_ENT,
		KC_LSFT,          KC_I,    KC_T,    KC_O,    KC_E,    KC_E,    KC_D,    KC_E,    KC_DOT,  KC_COMM, KC_BSLS,          KC_RSFT,
		KC_LCTL, KC_LGUI,          KC_LALT,                   KC_SPC,                             KC_RALT, MOD_RGUI,         KC_RCTL, TG(10))	
	
};

const rgblight_segment_t PROGMEM my_caps[] = RGBLIGHT_LAYER_SEGMENTS(
    {8, 1, HSV_GOLD}
);

const rgblight_segment_t PROGMEM my_fn[] = RGBLIGHT_LAYER_SEGMENTS(
    {15, 1, HSV_PINK}
);

const rgblight_segment_t PROGMEM my_lowbit[] = RGBLIGHT_LAYER_SEGMENTS(
    {11, 1, HSV_CHARTREUSE}
);

const rgblight_segment_t PROGMEM my_highbit[] = RGBLIGHT_LAYER_SEGMENTS(
    {12, 1, HSV_SPRINGGREEN}
);

const rgblight_segment_t PROGMEM my_extended[] = RGBLIGHT_LAYER_SEGMENTS(
    {11, 2, HSV_RED}
);

const rgblight_segment_t PROGMEM my_special[] = RGBLIGHT_LAYER_SEGMENTS(
    {11, 2, HSV_BLUE}
);

const rgblight_segment_t PROGMEM my_ivnum[] = RGBLIGHT_LAYER_SEGMENTS(
    {9, 1, HSV_PURPLE}
);

const rgblight_segment_t PROGMEM my_scroll[] = RGBLIGHT_LAYER_SEGMENTS(
    {10, 1, HSV_PURPLE}
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_caps,	// Overrides caps lock layer
	my_fn,		// Overides Fn shifted
    my_lowbit,    
    my_highbit,	// Overrides other layers
	my_extended,// Extended mode
	my_special,	// Special mode
	my_ivnum,	// Inverse num lock indication
	my_scroll	// Scroll lock
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

bool my_state = false;

layer_state_t layer_state_set_user(layer_state_t state) {
    // Layers will light up if kb layers are active
	bool t;
	t = false;
	if(layer_state_cmp(state, 4) || layer_state_cmp(state, 5) ||
		layer_state_cmp(state, 6) || layer_state_cmp(state, 7)) t = true;
	rgblight_set_layer_state(1, t);
	t = false;
	if(layer_state_cmp(state, 1) || layer_state_cmp(state, 3) ||
		layer_state_cmp(state, 5) || layer_state_cmp(state, 7)) t = true;
	rgblight_set_layer_state(2, t);
	t = false;
	if(layer_state_cmp(state, 2) || layer_state_cmp(state, 3) ||
		layer_state_cmp(state, 6) || layer_state_cmp(state, 7)) t = true;
    rgblight_set_layer_state(3, t);
	rgblight_set_layer_state(4, layer_state_cmp(state, 8));
	rgblight_set_layer_state(5, layer_state_cmp(state, 9));
	my_state = false;
	if(layer_state_cmp(state, 10)) {
		rgblight_blink_layer(2, 500);
		rgblight_blink_layer(3, 500);
		my_state = true;
	}
    return state;
}

bool led_update_user(led_t led_state) {
	// Caps lock
    rgblight_set_layer_state(0, led_state.caps_lock);
	rgblight_set_layer_state(6, !led_state.num_lock);
	rgblight_set_layer_state(7, led_state.scroll_lock);
    return true;
}

uint16_t mod = CRYPT_SEED;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	if(!my_state) return true;//not crypt
	if((keycode == KC_BSPC || keycode == KC_ENT) && record->event.pressed) {
		mod = CRYPT_SEED;//reset on BSPC or ENTER
		return true;//and process
	}
	if(keycode < KC_A || keycode > KC_Z)
		return true;//not crypt
	//process simple enigma
	if(record->event.pressed) {
		mod = (mod + keycode) * 27;//first char mixed better (+ b4 *)
		mod = (mod << 4) | (mod >> 12);
		//unregister_code(keycode);
		keycode = mod & 31;//mask
		keycode += KC_A;//apply logical offset
		bool isShiftedL = get_mods() & MOD_BIT(KC_LSFT);
		bool isShiftedR = get_mods() & MOD_BIT(KC_RSFT);
		del_mods(MOD_MASK_SHIFT);
		if(mod & 64) register_code(KC_LSFT);
		if(keycode > KC_Z) {
			keycode -= (KC_Z - KC_J);//wrap and jump
			mod = (mod + keycode) * 17;//mix secondary 26 modulo
		}
		register_code(keycode);
		unregister_code(keycode);
		if (isShiftedL) {
          register_code(KC_LSFT);
        }
		if (isShiftedR) {
          register_code(KC_RSFT);
        }
	}
	return false; // Process keycodes "normally" == NO
}