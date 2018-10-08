#include "viterbi.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

enum my_layers {
	LAYER_HOME = 0,
	LAYER_TENKEY,
	LAYER_UTIL,
	LAYER_COUNT
};

enum my_keycodes {
	LOWER = SAFE_RANGE,
	RAISE,
	BL_MODE
};

enum {
	TD_LSFT_CAPS = 0,
	TD_RSFT_CAPS
};

qk_tap_dance_action_t tap_dance_actions[] = {
	[TD_LSFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
	[TD_RSFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_RSFT, KC_CAPS)
};

const uint16_t PROGMEM keymaps[LAYER_COUNT][MATRIX_ROWS][MATRIX_COLS] = {
	[LAYER_HOME] = LAYOUT( \
			KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,           ALT_T(KC_ESC),     ALT_T(KC_ESC),     KC_6,           KC_7,        KC_8,     KC_9,     KC_0,     KC_EQL,   \
			KC_PGUP,  KC_QUOT,  KC_COMM,  KC_DOT,   KC_P,     KC_Y,           KC_BSPC,           KC_DEL,            KC_F,           KC_G,        KC_C,     KC_R,     KC_L,     KC_SLSH,  \
			KC_TAB,   KC_A,     KC_O,     KC_E,     KC_U,     KC_I,           TD(TD_LSFT_CAPS),  TD(TD_RSFT_CAPS),  KC_D,           KC_H,        KC_T,     KC_N,     KC_S,     KC_MINS,  \
			KC_PGDN,  KC_SCLN,  KC_Q,     KC_J,     KC_K,     KC_X,           CTL_T(KC_ENT),     CTL_T(KC_ENT),     KC_B,           KC_M,        KC_W,     KC_V,     KC_Z,     KC_BSLS,  \
			KC_HOME,  KC_LEFT,  KC_UP,    KC_DOWN,  KC_RGHT,  GUI_T(KC_SPC),  LOWER,             RAISE,             GUI_T(KC_SPC),  RCTL(KC_A),  KC_HYPR,  KC_LBRC,  KC_RBRC,  KC_END \
			),
	[LAYER_TENKEY] = LAYOUT( \
			KC_GRV,   KC_F1,    KC_F2,   KC_F3,    KC_F4,    KC_F5,          ALT_T(KC_ESC),     ALT_T(KC_ESC),     KC_PAUSE,       KC_PSCR,        KC_WH_U,     KC_SLCK,         BL_MODE,     RGB_TOG,   \
			KC_PGUP,  KC_F6,    KC_F7,   KC_F8,    KC_F9,    KC_F10,         KC_BSPC,           KC_DEL,            KC_VOLU,        LALT(KC_LEFT),  KC_MS_UP,    LALT(KC_RIGHT),  KC_MS_BTN3,  RGB_VAI,   \
			KC_TAB,   KC_F11,   KC_F12,  KC_F13,   KC_F14,   KC_F15,         TD(TD_LSFT_CAPS),  TD(TD_RSFT_CAPS),  KC_MUTE,        KC_MS_LEFT,     KC_MS_DOWN,  KC_MS_RIGHT,     KC_MS_BTN1,  RGB_VAD,   \
			KC_PGDN,  KC_F16,   KC_F17,  KC_F18,   KC_F19,   KC_F20,         CTL_T(KC_ENT),     CTL_T(KC_ENT),     KC_VOLD,        KC_WH_L,        KC_WH_D,     KC_WH_R,         RGB_HUI,     RGB_SAI,   \
			KC_HOME,  KC_LEFT,  KC_UP,   KC_DOWN,  KC_RGHT,  GUI_T(KC_SPC),  LOWER,             RAISE,             GUI_T(KC_SPC),  RCTL(KC_A),     KC_HYPR,     KC_SYSREQ,       RGB_HUD,     RGB_SAD \
			),
	[LAYER_UTIL] = LAYOUT( \
			KC_GRV,    KC_1,   KC_2,   KC_3,   KC_4,   KC_5,           ALT_T(KC_ESC),     ALT_T(KC_ESC),     KC_NO,          KC_NO,  KC_PSLS,  KC_PAST,  KC_PMNS,  KC_NO,    \
			KC_TAB,    KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,           KC_BSPC,           KC_DEL,            KC_NO,          KC_P7,  KC_P8,    KC_P9,    KC_PPLS,  KC_NO,    \
			KC_CAPS,   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,           TD(TD_LSFT_CAPS),  TD(TD_RSFT_CAPS),  KC_TAB,         KC_P4,  KC_P5,    KC_P6,    KC_PENT,  KC_NO,    \
			MOD_LSFT,  KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,           CTL_T(KC_ENT),     CTL_T(KC_ENT),     KC_NO,          KC_P1,  KC_P2,    KC_P3,    KC_PENT,  KC_NO,    \
			MOD_LCTL,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  GUI_T(KC_SPC),  LOWER,             RAISE,             GUI_T(KC_SPC),  KC_P0,  KC_HYPR,  KC_PDOT,  KC_PCMM,  KC_END \
			)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	static uint8_t layer = 0;
	static uint8_t mode = 1;

	switch (keycode) {
		case LOWER:
			if (record->event.pressed) {
				if (layer > 0) layer_move(--layer);
			}	
			return false;
		case RAISE:
			if (record->event.pressed) {
				if(layer < LAYER_COUNT - 1) layer_move(++layer);
			}
			return false;
		case BL_MODE:
			if (record->event.pressed) {
				switch(mode) {
					case 1:
						mode = 8;
						break;
					case 8:
						mode = 14;
						break;
					default:
						mode = 1;
						break;
				}
				rgblight_mode(mode);
			}
			return false;
		default:
			return true;
	}
}
