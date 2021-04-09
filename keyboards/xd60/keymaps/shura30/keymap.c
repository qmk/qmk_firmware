#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_all(
		KC_GESC,       KC_1,    KC_2,    KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_GRV, KC_BSPC,
		KC_TAB,        KC_Q,    KC_W,    KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_NO,
		LT(1,KC_CAPS), KC_A,    KC_S,    KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,
		KC_LSFT,       KC_NUBS, KC_Z,    KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT,  KC_SLSH, KC_NO,   KC_RSFT, KC_PSCR,
		KC_LCTL,       KC_LGUI, KC_LALT,                   KC_SPC,                    KC_RALT, KC_APP,  KC_NO,   TT(1),   KC_RCTL),
	
	[1] = LAYOUT_all(
		KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6, KC_F7,      KC_F8,       KC_F9,       KC_F10, KC_F11, KC_F12,  KC_NO, KC_DEL,
		KC_TAB,  KC_INS,  KC_DEL,  KC_UP,   KC_PGUP, KC_PGDN, KC_NO, KC_MS_BTN1, KC_MS_UP,    KC_MS_BTN2,  KC_NO,  KC_NO,  KC_NO,   KC_NO,
		KC_TRNS, KC_NO,   KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,   KC_NO, KC_MS_LEFT, KC_MS_DOWN,  KC_MS_RIGHT, KC_NO,  KC_NO,  KC_NO,   KC_ENT,
		KC_LSFT, KC_PSCR, KC_NO,   KC_HOME, KC_END,  KC_NO,   KC_NO, KC_NO,      KC_MS_BTN3,  KC_NO,       KC_NO,  KC_NO,  KC_NO,   KC_RSFT, MO(2),
		KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                                  KC_RALT,     KC_APP, KC_NO,  KC_TRNS, KC_RCTL),
	
	[2] = LAYOUT_all(
		KC_NO, KC_NO,   KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO, RESET,
		KC_NO, BL_TOGG, BL_STEP, BL_ON,    BL_OFF,   BL_INC,   BL_DEC,  BL_BRTG, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,
		KC_NO, RGB_TOG, RGB_MOD, RGB_RMOD, RGB_HUI,  RGB_HUD,  RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, RGB_SPI, RGB_SPD, KC_NO, KC_NO,
		KC_NO, RGB_M_P, RGB_M_B, RGB_M_R,  RGB_M_SW, RGB_M_SN, RGB_M_K, RGB_M_X, RGB_M_G, KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO, KC_TRNS,
		KC_NO, KC_NO,   KC_NO,                                KC_NO,                               KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO)
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
    return state;
};

 bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(3, led_state.caps_lock);
    return true;
};

/* // EEPROM Reset Function
void eeconfig_init_user(void) {
	backlight_enable(); // Enable backlight by default
	rgblight_enable(); // Enable RGB by default
	rgblight_sethsv(HSV_BLUE);  // Set it to orange by default
}; */
