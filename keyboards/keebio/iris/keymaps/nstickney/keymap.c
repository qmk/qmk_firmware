#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Layers
#define BASE 0 // Base layer
#define SYMB 1 // Symbols
#define SYSH 2 // Symbols, shifted
#define NUMP 3 // Numpad
#define FCTN 4 // Functions

// Tap Dancing
void dance_lock (qk_tap_dance_state_t *state, void *user_data) {
	switch (state->count){
		case 1: // Press once for LGUI
			tap_code(KC_LGUI);
			break;
		case 2: // Press twice for NUMLOCK
			tap_code(KC_NLCK);
			break;
		case 3: // Press thrice for CAPSLOCK
			tap_code(KC_CAPS);
			break;
		case 4: // Press four times for SCROLLOCK
			tap_code(KC_SLCK);
			break;
		default:
			break;
	}
};

void dance_layer (qk_tap_dance_state_t *state, void *user_data) {
	switch (state -> count) {
		case 1: // Press once for MENU
			tap_code(KC_APP);
			break;
		case 2: // Press twice for NUMPAD
			layer_invert(NUMP);
			break;
		case 3: // Press thrice for SYMBOLS
			layer_invert(SYMB);
			break;
		case 4: // Press four times for SYMBOLS, SHIFTED
			layer_invert(SYSH);
			break;
		default:
			break;
	}
};

enum tap_dances {LOCKS = 0, LAYERS = 1};
qk_tap_dance_action_t tap_dance_actions[] = {
	[LOCKS] = ACTION_TAP_DANCE_FN(dance_lock),
	[LAYERS] = ACTION_TAP_DANCE_FN(dance_layer)
};

// Make layering more clear
#define CC_ESC LCTL_T(KC_ESC)
#define CC_QUOT RCTL_T(KC_QUOT)
#define AC_SLSH LALT_T(KC_SLSH)
#define AC_EQL RALT_T(KC_EQL)
#define FC_BSLS LT(FCTN, KC_BSLS)
#define FC_MINS LT(FCTN, KC_MINS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[BASE] = LAYOUT(
// ┌──────────┬──────────┬──────────┬──────────┬──────────┬──────────┐                              ┌──────────┬──────────┬──────────┬──────────┬──────────┬──────────┐
	KC_GRV,    KC_1,      KC_2,      KC_3,      KC_4,      KC_5,                                     KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      KC_BSPC,
// ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤                              ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
	KC_TAB,    KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,                                     KC_Y,      KC_U,      KC_I,      KC_O,      KC_P,      KC_DEL,
// ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤                              ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
	CC_ESC,    KC_A,      KC_S,      KC_D,      KC_F,      KC_G,                                     KC_H,      KC_J,      KC_K,      KC_L,      KC_SCLN,   CC_QUOT,
// ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┐        ┌──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
	KC_LSPO,   KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,      TD(LOCKS),          TD(LAYERS),KC_N,      KC_M,      KC_COMM,   KC_DOT,    KC_SLSH,   KC_RSPC,
// └──────────┴──────────┴──────────┴────┬─────┴────┬─────┴────┬─────┴────┬─────┘        └────┬─────┴────┬─────┴────┬─────┴────┬─────┴──────────┴──────────┴──────────┘
	                                                 AC_SLSH,   FC_BSLS,   KC_SPC,                        KC_ENT,    FC_MINS,   AC_EQL
//                                                  └──────────┴──────────┴──────────┘                   └──────────┴──────────┴──────────┘
	),

	[SYMB] = LAYOUT(
// ┌──────────┬──────────┬──────────┬──────────┬──────────┬──────────┐                              ┌──────────┬──────────┬──────────┬──────────┬──────────┬──────────┐
	UC(0x00EF),UC(0x00A1),UC(0x00B2),UC(0x00B3),UC(0x00A4),UC(0x20AC),                               UC(0x00BC),UC(0x00BD),UC(0x00BE),UC(0x2018),UC(0x2019),_______,  
// ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤                              ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
	_______,   UC(0x00E4),UC(0x00E5),UC(0x00E9),UC(0x00AE),UC(0x00FE),                               UC(0x00FC),UC(0x00FA),UC(0x00ED),UC(0x00F3),UC(0x00F6),_______,  
// ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤                              ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
	_______,   UC(0x00E1),UC(0x00DF),UC(0x00F0),UC(0x00EC),UC(0x00ED),                               UC(0x00EE),UC(0x00E0),UC(0x00E2),UC(0x00F8),UC(0x00B6),UC(0x00B4),
// ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┐        ┌──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
	_______,   UC(0x00E6),UC(0x00E8),UC(0x00A9),UC(0x00EA),UC(0x00EB),_______,            _______,   UC(0x00F1),UC(0x00FD),UC(0x00E7),UC(0x00F4),UC(0x00BF),_______,  
// └──────────┴──────────┴──────────┴────┬─────┴────┬─────┴────┬─────┴────┬─────┘        └────┬─────┴────┬─────┴────┬─────┴────┬─────┴──────────┴──────────┴──────────┘
	                                      UC(0x00BF),UC(0x00AC),_______,                       _______,   UC(0x00B1),UC(0x00D7)
//                                       └──────────┴──────────┴──────────┘                   └──────────┴──────────┴──────────┘
	),

	[SYSH] = LAYOUT(
// ┌──────────┬──────────┬──────────┬──────────┬──────────┬──────────┐                              ┌──────────┬──────────┬──────────┬──────────┬──────────┬──────────┐
	UC(0x00CF),UC(0x00B9),UC(0x2200),UC(0x2201),UC(0x00A3),UC(0x00A5),                               UC(0x00B5),UC(0x00AB),UC(0x00BB),UC(0x201C),UC(0x201D),_______,  
// ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤                              ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
	_______,   UC(0x00C4),UC(0x00C5),UC(0x00C9),UC(0x2122),UC(0x00DE),                               UC(0x00DC),UC(0x00DA),UC(0x00CD),UC(0x00D3),UC(0x00D6),_______,  
// ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤                              ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
	_______,   UC(0x00C1),UC(0x00A7),UC(0x00D0),UC(0x00CC),UC(0x00CD),                               UC(0x00CE),UC(0x00C1),UC(0x00C2),UC(0x00D8),UC(0x00B0),UC(0x00A8),
// ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┐        ┌──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
	_______,   UC(0x00C6),UC(0x00C8),UC(0x00A2),UC(0x00CA),UC(0x00CB),_______,            _______,   UC(0x00D1),UC(0x00DD),UC(0x00C7),UC(0x00D4),UC(0x203D),_______,  
// └──────────┴──────────┴──────────┴────┬─────┴────┬─────┴────┬─────┴────┬─────┘        └────┬─────┴────┬─────┴────┬─────┴────┬─────┴──────────┴──────────┴──────────┘
										  UC(0x203D),UC(0x00A6),_______,                       _______,   UC(0x00AA),UC(0x00F7)
//                                       └──────────┴──────────┴──────────┘                   └──────────┴──────────┴──────────┘
	),

	[NUMP] = LAYOUT(
// ┌──────────┬──────────┬──────────┬──────────┬──────────┬──────────┐                              ┌──────────┬──────────┬──────────┬──────────┬──────────┬──────────┐
	_______,   _______,   KC_P7,     KC_P8,     KC_P9,     KC_PSLS,                                  _______,   KC_P7,     KC_P8,     KC_P9,     KC_PSLS,   _______,  
// ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤                              ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
	_______,   _______,   KC_P4,     KC_P5,     KC_P6,     KC_PAST,                                  _______,   KC_P4,     KC_P5,     KC_P6,     KC_PAST,   _______,  
// ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤                              ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
	_______,   _______,   KC_P1,     KC_P2,     KC_P3,     KC_PMNS,                                  _______,   KC_P1,     KC_P2,     KC_P3,     KC_PMNS,   _______,  
// ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┐        ┌──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
	_______,   _______,   KC_P0,     KC_PCMM,   KC_PDOT,   KC_PPLS,   _______,            _______,   _______,   KC_P0,     KC_PCMM,   KC_PDOT,   KC_PPLS,   _______,  
// └──────────┴──────────┴──────────┴────┬─────┴────┬─────┴────┬─────┴────┬─────┘        └────┬─────┴────┬─────┴────┬─────┴────┬─────┴──────────┴──────────┴──────────┘
										  _______,   _______,   _______,                       KC_PENT,   _______,   _______
//                                       └──────────┴──────────┴──────────┘                   └──────────┴──────────┴──────────┘
	),

	[FCTN] = LAYOUT(
// ┌──────────┬──────────┬──────────┬──────────┬──────────┬──────────┐                              ┌──────────┬──────────┬──────────┬──────────┬──────────┬──────────┐
	KC_ESC,    KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,                                    KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_SYSREQ,
// ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤                              ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
	KC_PSCR,   UC_MOD,    KC_HOME,   KC_UP,     KC_END,    KC_PGUP,                                  UC(0x2014),KC_LBRC,   KC_RBRC,   S(KC_LBRC),S(KC_RBRC),KC_INS,
// ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤                              ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
	KC_PAUS,   RGB_TOG,   KC_LEFT,   KC_DOWN,   KC_RGHT,   KC_PGDN,                                  KC_LEFT,   KC_DOWN,   KC_UP,     KC_RGHT,   KC_BRIU,   KC_CLR,
// ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┐        ┌──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
	_______,   KC_MPRV,   KC_MRWD,   KC_MPLY,   KC_MFFD,   KC_MNXT,   KC_F11,             KC_F12,    KC_MSTP,   KC_MUTE,   KC_VOLD,   KC_VOLU,   KC_BRID,   _______,  
// └──────────┴──────────┴──────────┴────┬─────┴────┬─────┴────┬─────┴────┬─────┘        └────┬─────┴────┬─────┴────┬─────┴────┬─────┴──────────┴──────────┴──────────┘
										  _______,   _______,   _______,                       _______,   _______,   _______
//                                       └──────────┴──────────┴──────────┘                   └──────────┴──────────┴──────────┘
	)
};

// Initialize rgblight
void keyboard_post_init_user(void) {
	rgblight_enable_noeeprom();
	rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
	layer_state_set_user(layer_state);
	uint16_t user_hue = rgblight_get_hue();
	for (uint16_t i = 0; i < 360; ++i) {
		rgblight_sethsv_noeeprom( (i + user_hue) % 360, 255, 255);
		wait_ms(4);
	}
	layer_state_set_user(layer_state);
};

// Turn on RGB underglow according to active layer
uint32_t layer_state_set_user(uint32_t state) {
	switch (biton32(state)) {
		case FCTN:
			rgblight_sethsv_noeeprom(136, 255, 255);
			break;
		case NUMP:
			rgblight_sethsv_noeeprom(228, 255, 255);
			break;
		case SYMB:
		case SYSH:
			rgblight_sethsv_noeeprom(320, 255, 255);
			break;
		default: //  for any other layers, or the default layer
			rgblight_sethsv_noeeprom(19, 255, 255);
			break;
	}
	return state;
};
