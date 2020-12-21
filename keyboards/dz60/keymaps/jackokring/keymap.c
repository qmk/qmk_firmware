#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	//ANSI lock mode 0 =================================================================================== ANSI lock mode 0
	LAYOUT_60_ansi(
		KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,           KC_BSPC,
		KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
		KC_CAPS,          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
		KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,
		KC_LCTL, KC_LGUI,          KC_LALT,                   KC_SPC,                             KC_RALT, KC_APP,           KC_RCTL, MO(4)),//zero index start

	//Navigation lock mode 1 ============================================================================= Navigation lock mode 1
	LAYOUT_60_ansi(
		KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,           KC_BSPC,
		KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
		KC_CAPS,          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
		KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,            KC_RSFT,
		KC_LCTL, KC_LGUI,          KC_LALT,                   KC_SPC,                             KC_LEFT, KC_DOWN,          KC_RIGHT, MO(5)),

	//Numpad lock mode 2 ================================================================================= Numpad lock mode 2
	LAYOUT_60_ansi(
		KC_GESC, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_P7,   KC_P8,   KC_P9,   KC_DEL,  KC_PMNS, KC_PPLS,          KC_BSPC,
		KC_TAB,           KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_P4,   KC_P5,   KC_P6,   KC_PAST, KC_LPRN, KC_RPRN, KC_PSLS,
		KC_NLCK,          KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_P1,   KC_P2,   KC_P3,   KC_INS,  KC_CALC, KC_PENT,
		OSM(MOD_LSFT),    KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,  KC_P0,   KC_COMM, KC_PDOT, KC_UP,            MOD_RSFT,
		OSM(MOD_LCTL),OSM(MOD_LGUI),        OSM(MOD_LALT),                  KC_SPC,                             KC_LEFT, KC_DOWN,          KC_RIGHT, TG(6)),//lock Fn

	//Macro lock mode 3 ================================================================================== Macro lock mode 3
	LAYOUT_60_ansi(
		OSM(MOD_LALT|MOD_LSFT),    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           DM_REC1,
		OSM(MOD_LCTL|MOD_LALT),    KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,  ALGR(KC_F24),
		OSM(MOD_LCTL|MOD_LSFT),    ALGR(KC_F1),   ALGR(KC_F2),   ALGR(KC_F3),   ALGR(KC_F4),   ALGR(KC_F5),   ALGR(KC_F6),   ALGR(KC_F7),   ALGR(KC_F8),   ALGR(KC_F9),   ALGR(KC_F10),  ALGR(KC_F11),  ALGR(KC_F12),
		OSM(MOD_LSFT),         	   ALGR(KC_F13),  ALGR(KC_F14),  ALGR(KC_F15),  ALGR(KC_F16),  ALGR(KC_F17),  ALGR(KC_F18),  ALGR(KC_F19),  ALGR(KC_F20),  ALGR(KC_F21),  ALGR(KC_F22),  ALGR(KC_F23),
		OSM(MOD_LCTL),OSM(MOD_LGUI),        OSM(MOD_LALT),                  DM_PLY1,                            OSM(MOD_RALT),OSM(MOD_RGUI),         OSM(MOD_RCTL), TG(7)),

	//ANSI shift mode 4 ================================================================================== ANSI shift mode 4
	LAYOUT_60_ansi(
		KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_DEL,
		KC_TRNS,          RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_WHOM, KC_PWR,  KC_HOME, KC_END,  KC_INS,
		KC_SLCK,          KC_WSCH, UC(8747),UC(8706),KC_WFAV, UC(8730),KC_VOLD, KC_VOLU, UC(176), UC(163), KC_PAUS, KC_PSCR, KC_TRNS,
		KC_TRNS,          UC(937), KC_MUTE, BL_DEC,  BL_TOGG, BL_INC,  BL_STEP, UC(181), KC_PGUP, KC_PGDN, KC_UP,            KC_TRNS,
		KC_LCTL, DF(3),            DF(1),                     DF(2),                              KC_LEFT, KC_DOWN,          KC_RIGHT, KC_TRNS),
	
	//Navigation shift mode 5 ============================================================================ Navigation shift mode 5
	LAYOUT_60_ansi(
		KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_DEL,
		KC_TRNS,          KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,  KC_INS,
		KC_SLCK,          KC_WSCH, UC(8747),UC(8706),KC_WFAV, UC(8730),KC_VOLD, KC_VOLU, UC(176), UC(163), KC_PAUS, KC_PSCR, KC_ESC,
		KC_TRNS,          UC(937), KC_MUTE, KC_MPRV, KC_MPLY, KC_MNXT, KC_MSEL, UC(181), KC_PGUP, KC_PGDN, KC_QUES,          KC_TRNS,
		DF(0),   DF(3),            KC_LALT,                   DF(2),                              KC_RALT, KC_SLSH,          KC_RCTL, KC_TRNS),
	
	//Numpad shift mode 6 ================================================================================ Numpad shift mode 6
	LAYOUT_60_ansi(
		KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,           KC_BSPC,
		KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
		KC_CAPS,          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
		KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,
		DF(0),   DF(3),            DF(1),                     KC_SPC,                             KC_RALT, KC_APP,           KC_RCTL, KC_TRNS),
	
	//Macro shift mode 7 ================================================================================= Macro shift mode 7
	LAYOUT_60_ansi(
		OSM(MOD_LGUI|MOD_LALT|MOD_LSFT),    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          OSM(MOD_LCTL|MOD_LALT|MOD_LSFT),
		OSM(MOD_LGUI|MOD_LCTL|MOD_LALT),    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		OSM(MOD_LGUI|MOD_LCTL|MOD_LSFT),    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		OSM(MOD_LGUI|MOD_LSFT),             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
		DF(0),   KC_LGUI,          DF(1),                     DF(2),                              LSA(KC_TAB),OSM(MOD_RGUI), LALT(KC_TAB),KC_TRNS)
};

const rgblight_segment_t PROGMEM my_caps[] = RGBLIGHT_LAYER_SEGMENTS(
    {8, 1, HSV_CYAN}
);

const rgblight_segment_t PROGMEM my_fn[] = RGBLIGHT_LAYER_SEGMENTS(
    {15, 1, HSV_CYAN}
);

const rgblight_segment_t PROGMEM my_lowbit[] = RGBLIGHT_LAYER_SEGMENTS(
    {11, 1, HSV_CYAN}
);

const rgblight_segment_t PROGMEM my_highbit[] = RGBLIGHT_LAYER_SEGMENTS(
    {12, 1, HSV_CYAN}
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_caps,	// Overrides caps lock layer
	my_fn,		// Overides Fn shifted
    my_lowbit,    
    my_highbit	// Overrides other layers
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

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
    return state;
}

bool led_update_user(led_t led_state) {
	// Caps lock
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}