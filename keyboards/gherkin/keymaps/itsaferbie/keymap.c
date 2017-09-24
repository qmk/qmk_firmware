#include "gherkin.h"
#include "action_layer.h"

extern rgblight_config_t rgblight_config;
extern keymap_config_t keymap_config;

#define _PS 0 // This is the Photoshop Layer
#define _AI 1 // This is the Illustrator Layer
#define _PR 2 // This is the Premier Layer

enum custom_keycodes {
	PS = SAFE_RANGE,
	AI,
	PR,
};

#define PS TO(0)
#define AI TO(1)
#define PR TO(2)

// Mix of Photoshop, Illustrator, and Premiere shortcuts.
#define SAVE  LCTL(KC_S)
#define OPEN  LCTL(KC_O)
#define COPY  LCTL(KC_C)
#define PAST  LCTL(KC_V)
#define CUNDO LCTL(LALT(KC_Z))
#define INVERT LCTL(LSFT(KC_I))
#define NLAYER LSFT(LCTL(KC_N))
#define UNDO LCTL(KC_Z)
#define TRANS LCTL(KC_T)
#define ALIGNL LCTL(LSFT(KC_L))
#define ALIGNC LCTL(LSFT(KC_C))
#define ALIGNR LCTL(LSFT(KC_R))
#define BRINGF LCTL(KC_RBRC)
#define BRINGB LCTL(KC_LBRC)

// Some illustrator only shortcuts.
#define SHAPE LSFT(KC_M)
#define RULER LCTL(LALT(KC_R))

// Premiere only shortcuts.
#define REDO LCTL(LSFT(KC_Z))
#define EXPORT LCTL(KC_M)
#define IMPORT LCTL(KC_I)
#define PCOPY LCTL(KC_V)
#define PPASTE LCTL(LSFT(KC_V))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	// Photoshop layer.
	[_PS] = KEYMAP(
		SAVE,    KC_W, KC_E, KC_T,  KC_U,   KC_I,   KC_P,   INVERT, CUNDO,    NLAYER,
		UNDO,    KC_H, KC_L, TRANS, ALIGNL, ALIGNC, ALIGNR, BRINGB,  BRINGF,  OPEN,
		KC_LSFT, COPY, PAST, KC_Z,  KC_C,   KC_V,   KC_B,   KC_LBRC, KC_RBRC, AI),

	[_AI] = KEYMAP(
		KC_TRNS, M(0),    RULER,   KC_TRNS, KC_G,    KC_TRNS, KC_TRNS, KC_Q,  KC_MINS, KC_PLUS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_E,    KC_TRNS, KC_TRNS, KC_TRNS, SHAPE, KC_O,    OPEN,  
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_M,  KC_SLSH, PR),

	[_PR] = KEYMAP(
		KC_TRNS, KC_Q,  KC_W,   KC_I,   KC_O, KC_P, IMPORT, EXPORT,  KC_MINS,  KC_EQL,
		KC_TRNS, REDO,  KC_D,   KC_F,   KC_H, KC_M, KC_ENT, KC_LBRC, KC_RBRC,  OPEN,  
		KC_TRNS, PCOPY, PPASTE, KC_SPC, KC_Z, KC_C, KC_V,   KC_LEFT, KC_RIGHT, PS),

};

void persistent_default_layer_set(uint16_t default_layer) {
	eeconfig_update_default_layer(default_layer);
	default_layer_set(default_layer);
}

void matrix_init_user(void) {
	rgblight_enable();
}

void matrix_scan_user(void) {
	#ifdef RGBLIGHT_ENABLE

	static uint8_t old_layer = 255;
	uint8_t new_layer = biton32(layer_state);

	// Color of the Icons.
	if (old_layer != new_layer) {
		switch (new_layer) {
			case _PS:
			  rgblight_setrgb(49, 197, 240);
			break;
			case _AI:
			  rgblight_setrgb(255, 128, 17);
			break;
			case _PR:
			  rgblight_setrgb(231, 136, 255);
			break;
		}
		old_layer = new_layer;
	}
	#endif
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
	keyevent_t event = record->event;
    (void)event;

	switch (id) {
		case 0:
			// Save for Web Macro.
			return MACRO(D(LSFT), D(LALT), D(LCTL), T(S), U(LCTL), U(LALT), U(LSFT), END);
	}
	return MACRO_NONE;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
	}
	return true;
}
