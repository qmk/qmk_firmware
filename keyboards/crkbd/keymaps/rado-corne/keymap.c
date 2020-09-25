#include QMK_KEYBOARD_H
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef SSD1306OLED
#include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _NUMBER 1
#define _SYMBOL 2
#define _I3 3
#define _SYMBOL_SHIFT 4
#define _NUM_PAD 5
#define _PROGRAMMING 6
#define _GAMMING 7

enum custom_keycodes {
		QWERTY = SAFE_RANGE,
		LOWER,
		RAISE,
		ADJUST,
		SYMBOL_SHIFT,
		NUM_PAD,
		PROGRAMMING
};

enum unicode_names {
		ch,
		bch,
		sh,
		bsh,
		zh,
		bzh
};

const uint32_t PROGMEM unicode_map[] = {
		[ch]  = 0x010D,
		[bch]  = 0x010C,
		[sh]  = 0x0161,
		[bsh]  = 0x0160,
		[zh]  = 0x017E,
		[bzh]  = 0x017D
};

enum macro_keycodes {
		KC_SAMPLEMACRO,
};

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_LOWER LOWER
#define KC_RAISE RAISE
#define KC_RST   RESET
#define KC_LRST  RGBRST
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LMOD  RGB_MOD
#define KC_GUIEI GUI_T(KC_LANG2)
#define KC_ALTKN ALT_T(KC_LANG1)


// Tap Dance declarations
enum {
		TD_ESC_CAPS,
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
		// Tap once for Escape, twice for Caps Lock
		[TD_ESC_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_A, KC_B),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
		[_QWERTY] = LAYOUT_split_3x6_3(
						KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, 						KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, 
						LCTL_T(KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, 				KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, 
						KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, 						KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, 
						KC_LGUI, MO(1), KC_SPC, 									KC_ENT, MO(2), KC_RALT
						),
		[_NUMBER] = LAYOUT_split_3x6_3(
						KC_TAB, KC_1, KC_2, KC_3, KC_4, KC_5, 						KC_6, KC_7, KC_8, KC_9, KC_0, KC_DEL, 
						LCTL_T(KC_ESC), KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, 	KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO, KC_NO, 
						KC_LSFT, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, 				KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_RSFT, 
						KC_LGUI, KC_TRNS, KC_SPC, 									KC_ENT, MO(3), KC_RALT
						),
		[_SYMBOL] = LAYOUT_split_3x6_3(
						KC_TAB, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, 			KC_CIRC, KC_AMPR, KC_ASTR, KC_MINS, KC_EQL, KC_BSPC, 
						LCTL_T(KC_ESC), KC_NO, X(sh), KC_NO, KC_NO, KC_NO, 			KC_LPRN, KC_RPRN, KC_SCLN, KC_QUOT, KC_BSLS, KC_GRV, 
						MO(4), X(zh), KC_NO, X(ch), KC_NO, KC_NO, 					KC_LBRC, KC_RBRC, KC_COMM, KC_DOT, KC_SLSH, KC_TILD, 
						KC_LGUI, MO(3), KC_SPC, 									KC_ENT, KC_TRNS, KC_RALT
						),
		[_I3] = LAYOUT_split_3x6_3(
						LGUI(KC_TAB), LGUI(KC_1), LGUI(KC_2), LGUI(KC_3), LGUI(KC_4), LGUI(KC_5), 		LGUI(KC_6), LGUI(KC_7), LGUI(KC_8), LGUI(KC_9), LGUI(KC_0), KC_BSPC, 
						KC_LCTRL, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 									LGUI(KC_H), LGUI(KC_J), LGUI(KC_K), LGUI(KC_L), LGUI(KC_MINS), KC_LCTRL, 
						KC_LSFT, TG(5), TG(6), TG(7), KC_NO, KC_NO, 									KC_NO, KC_NO, KC_NO, KC_NO, KC_INS, KC_RSFT, 
						KC_LALT, KC_TRNS, KC_SPC, 														KC_ENT, KC_TRNS, KC_RALT
						),
		[_SYMBOL_SHIFT] = LAYOUT_split_3x6_3(
						KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 					KC_NO, KC_NO, KC_NO, KC_UNDS, KC_PLUS, KC_BSPC, 
						KC_NO, KC_NO, X(bsh), KC_NO, KC_NO, KC_NO, 					KC_LCBR, KC_RCBR, KC_COLN, KC_DQUO, KC_PIPE, KC_NO, 
						KC_TRNS, X(bzh), KC_NO, X(bch), KC_NO, KC_NO, 				KC_LT, KC_GT, KC_LT, KC_GT, KC_QUES, KC_NO, 
						KC_LGUI, KC_NO, KC_SPC, 									KC_ENT, KC_NO, KC_RALT
						),
		[_NUM_PAD] = LAYOUT_split_3x6_3(
						KC_TAB,KC_F1,KC_F2,KC_F3,KC_F4,KC_F5,						KC_1,KC_2,KC_3,KC_SLSH,KC_ASTR,KC_BSPC,
						LCTL_T(KC_ESC),KC_F6,KC_F7,KC_F8,KC_F9,KC_F10,				KC_4,KC_5,KC_6,KC_PLUS,KC_MINS,KC_NO,
						KC_LSFT,KC_F11,KC_F12,KC_NO,KC_NO,KC_NO,					KC_7,KC_8,KC_9,KC_0,KC_PDOT,KC_RSFT,
						KC_LGUI,TG(5),KC_SPC,										KC_ENT,TG(5),KC_RALT
						),
		[_PROGRAMMING] = LAYOUT_split_3x6_3(
						KC_TAB, LALT(KC_INS), LCA(KC_M), KC_NO, KC_NO, KC_NO, 				KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
						LCTL_T(KC_ESC), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 					KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
						KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 						KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TAB, 
						KC_LGUI, TG(6), KC_NO, 												KC_NO, TG(6), KC_RALT),
		[_GAMMING] = LAYOUT_split_3x6_3(
						KC_TAB, KC_Q, KC_W, KC_R, KC_E, KC_T, 			KC_F5, KC_F9, KC_NO, KC_NO, KC_NO, KC_NO, 
						LCTL_T(KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G,	KC_1, KC_2, KC_3, KC_4, KC_5, KC_NO, 
						KC_LSFT, KC_Z, KC_X, KC_TRNS, KC_V, KC_B, 		KC_6, KC_7, KC_8, KC_9, KC_0, KC_NO, 
						KC_LGUI, TG(7), KC_SPC, 						KC_ENT, TG(7), KC_RALT
						)

};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
		eeconfig_update_default_layer(default_layer);
		default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
		if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
				layer_on(layer3);
		} else {
				layer_off(layer3);
		}
}

void matrix_init_user(void) {
		//SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED
		iota_gfx_init(!has_usb());   // turns on the display
#endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
		iota_gfx_task();
}
void matrix_render_user(struct CharacterMatrix *matrix) {
		if (is_master) {
				// If you want to change the display of OLED, you need to change here
				matrix_write_ln(matrix, read_layer_state());
				matrix_write_ln(matrix, read_keylog());
				matrix_write_ln(matrix, read_keylogs());
				//matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
				//matrix_write_ln(matrix, read_host_led_state());
				//matrix_write_ln(matrix, read_timelog());
		} else {
				matrix_write(matrix, read_logo());
		}
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
		if (memcmp(dest->display, source->display, sizeof(dest->display))) {
				memcpy(dest->display, source->display, sizeof(dest->display));
				dest->dirty = true;
		}
}

void iota_gfx_task_user(void) {
		struct CharacterMatrix matrix;
		matrix_clear(&matrix);
		matrix_render_user(&matrix);
		matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
		if (record->event.pressed) {
#ifdef SSD1306OLED
				set_keylog(keycode, record);
#endif
				// set_timelog();
		}

		switch (keycode) {
				case QWERTY:
						if (record->event.pressed) {
								persistent_default_layer_set(1UL<<_QWERTY);
						}
						return false;
				case LOWER:
						if (record->event.pressed) {
								layer_on(_NUMBER);
								update_tri_layer_RGB(_NUMBER, _SYMBOL, _I3);
						} else {
								layer_off(_NUMBER);
								update_tri_layer_RGB(_NUMBER, _SYMBOL, _I3);
						}
						return false;
				case RAISE:
						if (record->event.pressed) {
								layer_on(_SYMBOL);
								update_tri_layer_RGB(_NUMBER, _SYMBOL, _I3);
						} else {
								layer_off(_SYMBOL);
								update_tri_layer_RGB(_NUMBER, _SYMBOL, _I3);
						}
						return false;
				case ADJUST:
						if (record->event.pressed) {
								layer_on(_I3);
						} else {
								layer_off(_I3);
						}
						return false;
				case SYMBOL_SHIFT:
						if (record->event.pressed) {
								layer_on(_SYMBOL_SHIFT);
						} else {
								layer_off(_SYMBOL_SHIFT);
						}
						return false;
		}
		return true;
}

// Light LEDs 9 & 10 in cyan when keyboard layer 1 is active
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
				{9, 2, HSV_CYAN}
				);
// Light LEDs 11 & 12 in purple when keyboard layer 2 is active
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
				{9, 2, HSV_YELLOW}
				);
// Light LEDs 6 to 9 and 12 to 15 red when caps lock is active. Hard to ignore!
const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
				{9, 2, HSV_MAGENTA}
				);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
				my_layer1_layer,    // Overrides caps lock layer
				my_layer2_layer,     // Overrides other layers
				my_layer3_layer
				);

extern rgblight_config_t rgblight_config;
void keyboard_post_init_user(void) {
		rgblight_config.hue    = 8;
		rgblight_config.sat    = 2;
		rgblight_config.val    = 103;
		// Enable the LED layers
		rgblight_layers = my_rgb_layers;
}
layer_state_t layer_state_set_user(layer_state_t state) {
		// Both layers will light up if both kb layers are active
		rgblight_set_layer_state(0, layer_state_cmp(state, _NUM_PAD));
		rgblight_set_layer_state(1, layer_state_cmp(state, _PROGRAMMING));
		rgblight_set_layer_state(2, layer_state_cmp(state, _GAMMING));
		return state;
}

