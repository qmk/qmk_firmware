#include QMK_KEYBOARD_H
#include "led.h"
#include <print.h>

#ifdef RGBLIGHT_ENABLE
#include "rgblight.h"
#endif

#define _______ KC_TRNS

// Each layer gets a name for readability, which is then used in the keymap matrix below.
enum cospad_layers {
	_QWERTY_LAYER,
	_QWERTZ_LAYER,
	_COLEMA_LAYER,
	_DVORAK_LAYER,
	_QWERTY_LOWER_LAYER,
	_QWERTZ_LOWER_LAYER,
	_COLEMA_LOWER_LAYER,
	_DVORAK_LOWER_LAYER,
	_RAISE_LAYER,
	_ALTER_LAYER,
};

// To switch the default layer used for the layout, there are special keycodes.
// Which onces detected below serve to switch it.
enum cospad_keycodes {
	QWERTY = SAFE_RANGE,
	QWERTZ,
	COLEMAK,
	DVORAK
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	/* Keymap _QWERTY_LAYER: Default layer
	 * ,-----------------------.
	 * |  T  |  G  |  B  | Alt |
	 * |-----|-----|-----|-----|
	 * |  R  |  F  |  V  | LOW |
	 * |-----|-----|-----|-----|
	 * |  E  |  D  |  C  |     |
	 * |-----|-----|-----| Spc |
	 * |  W  |  S  |  X  |     |
	 * |-----|-----|-----|-----|
	 * |  Q  |  A  |  Z  | RAI |
	 * |-----|-----|-----|-----|
	 * | Esc | Tab | Sft | Ctl |
	 * `-----------------------'
	 *
	 *   And it's LOWER layer
	 * ,-----------------------.
	 * |  P  |  ;  |  /  | Alt |
	 * |-----|-----|-----|-----|
	 * |  O  |  L  |  .  | LOW |
	 * |-----|-----|-----|-----|
	 * |  I  |  K  |  ,  |     |
	 * |-----|-----|-----| Ent |
	 * |  U  |  J  |  M  |     |
	 * |-----|-----|-----|-----|
	 * |  Y  |  H  |  N  | RAI |
	 * |-----|-----|-----|-----|
	 * | Esc | Tab | Sft | Ctl |
	 * `-----------------------'
	 */
	[_QWERTY_LAYER] = LAYOUT_gamepad_6x4(
			KC_T,    KC_G,    KC_B,    KC_LALT,  \
			KC_R,    KC_F,    KC_V,    MO(_QWERTY_LOWER_LAYER),\
			KC_E,    KC_D,    KC_C,              \
			KC_W,    KC_S,    KC_X,    KC_SPACE, \
			KC_Q,    KC_A,    KC_Z,    MO(_RAISE_LAYER),\
			KC_GESC, KC_TAB,  KC_LSFT, KC_LCTRL),
	[_QWERTY_LOWER_LAYER] = LAYOUT_gamepad_6x4(
			KC_P,    KC_SCLN, KC_SLSH, KC_LALT,  \
			KC_O,    KC_L,    KC_DOT,  _______,  \
			KC_I,    KC_K,    KC_COMM,           \
			KC_U,    KC_J,    KC_M,    KC_ENTER, \
			KC_Y,    KC_H,    KC_N,    _______,  \
			_______, _______,  _______, _______),



	/* Keymap _QWERTZ_LAYER: Alternate default layer
	 * ,-----------------------.
	 * |  T  |  G  |  B  | Alt |
	 * |-----|-----|-----|-----|
	 * |  R  |  F  |  V  | LOW |
	 * |-----|-----|-----|-----|
	 * |  E  |  D  |  C  |     |
	 * |-----|-----|-----| Spc |
	 * |  W  |  S  |  X  |     |
	 * |-----|-----|-----|-----|
	 * |  Q  |  A  |  Y  | RAI |
	 * |-----|-----|-----|-----|
	 * | Esc | Tab | Sft | Ctl |
	 * `-----------------------'
	 *
	 *   And it's LOWER layer
	 * ,-----------------------.
	 * |  P  |  ;  |  /  | Alt |
	 * |-----|-----|-----|-----|
	 * |  O  |  L  |  >  | LOW |
	 * |-----|-----|-----|-----|
	 * |  I  |  K  |  <  |     |
	 * |-----|-----|-----| Ent |
	 * |  U  |  J  |  M  |     |
	 * |-----|-----|-----|-----|
	 * |  Z  |  H  |  N  | RAI |
	 * |-----|-----|-----|-----|
	 * | Esc | Tab | Sft | Ctl |
	 * `-----------------------'
	 */
	[_QWERTZ_LAYER] = LAYOUT_gamepad_6x4(
			KC_T,    KC_G,    KC_B,    KC_LALT,  \
			KC_R,    KC_F,    KC_V,    MO(_QWERTZ_LOWER_LAYER),\
			KC_E,    KC_D,    KC_C,              \
			KC_W,    KC_S,    KC_X,    KC_SPACE, \
			KC_Q,    KC_A,    KC_Y,    MO(_RAISE_LAYER),\
			KC_GESC, KC_TAB,  KC_LSFT, KC_LCTRL),
	[_QWERTZ_LOWER_LAYER] = LAYOUT_gamepad_6x4(
			KC_P,    KC_SCLN, KC_SLSH, KC_LALT,  \
			KC_O,    KC_L,    KC_DOT,  _______,  \
			KC_I,    KC_K,    KC_COMM,           \
			KC_U,    KC_J,    KC_M,    KC_ENTER, \
			KC_Z,    KC_H,    KC_N,    _______,  \
			_______, _______, _______, _______),



	/* Keymap _COLEMA_LAYER: Alternate default layer
	 * ,-----------------------.
	 * |  G  |  D  |  B  | Alt |
	 * |-----|-----|-----|-----|
	 * |  P  |  T  |  V  | LOW |
	 * |-----|-----|-----|-----|
	 * |  F  |  S  |  C  |     |
	 * |-----|-----|-----| Spc |
	 * |  W  |  R  |  X  |     |
	 * |-----|-----|-----|-----|
	 * |  Q  |  A  |  Z  | RAI |
	 * |-----|-----|-----|-----|
	 * | Esc | Tab | Sft | Ctl |
	 * `-----------------------'
	 *
	 *   And it's LOWER layer
	 * ,-----------------------.
	 * |  ;  |  O  |  /  | Alt |
	 * |-----|-----|-----|-----|
	 * |  Y  |  I  |  .  | LOW |
	 * |-----|-----|-----|-----|
	 * |  U  |  E  |  ,  |     |
	 * |-----|-----|-----| Ent |
	 * |  L  |  N  |  M  |     |
	 * |-----|-----|-----|-----|
	 * |  J  |  H  |  K  | RAI |
	 * |-----|-----|-----|-----|
	 * | Esc | Tab | Sft | Ctl |
	 * `-----------------------'
	 */
	[_COLEMA_LAYER] = LAYOUT_gamepad_6x4(
			KC_T,    KC_D,     KC_B,    KC_LALT,  \
			KC_R,    KC_T,     KC_V,    MO(_COLEMA_LOWER_LAYER),\
			KC_E,    KC_S,     KC_C,              \
			KC_W,    KC_R,     KC_X,    KC_SPACE, \
			KC_Q,    KC_A,     KC_Z,    MO(_RAISE_LAYER),\
			KC_GESC, KC_TAB,   KC_LSFT, KC_LCTRL),
	[_COLEMA_LOWER_LAYER] = LAYOUT_gamepad_6x4(
			KC_SCLN, KC_O,     KC_SLSH, _______,  \
			KC_Y,    KC_I,     KC_DOT,  _______,  \
			KC_U,    KC_E,     KC_COMM,           \
			KC_L,    KC_N,     KC_M,    KC_ENTER, \
			KC_J,    KC_H,     KC_K,    _______,  \
			KC_F,    KC_G,     _______, _______),



	/* Keymap _DVORAK_LAYER: Alternate default layer
	 * ,-----------------------.
	 * |  Y  |  I  |  X  | Alt |
	 * |-----|-----|-----|-----|
	 * |  P  |  U  |  K  | LOW |
	 * |-----|-----|-----|-----|
	 * |  .  |  E  |  J  |     |
	 * |-----|-----|-----| Spc |
	 * |  ,  |  O  |  Q  |     |
	 * |-----|-----|-----|-----|
	 * |  '  |  A  |  ;  | RAI |
	 * |-----|-----|-----|-----|
	 * | Esc | Tab | Sft | Ctl |
	 * `-----------------------'
	 *
	 *   And it's LOWER layer
	 * ,-----------------------.
	 * |  L  |  S  |  Z  | Alt |
	 * |-----|-----|-----|-----|
	 * |  R  |  N  |  V  | LOW |
	 * |-----|-----|-----|-----|
	 * |  C  |  T  |  W  |     |
	 * |-----|-----|-----| Ent |
	 * |  G  |  H  |  M  |     |
	 * |-----|-----|-----|-----|
	 * |  F  |  D  |  B  | RAI |
	 * |-----|-----|-----|-----|
	 * | Esc | Tab | Sft | Ctl |
	 * `-----------------------'
	 */
	[_DVORAK_LAYER] = LAYOUT_gamepad_6x4(
			KC_Y,    KC_I,    KC_X,    KC_LALT,   \
			KC_P,    KC_U,    KC_K,    MO(_DVORAK_LOWER_LAYER),\
			KC_DOT,  KC_E,    KC_J,               \
			KC_COMM, KC_O,    KC_A,    KC_SPACE,  \
			KC_QUOT, KC_A,    KC_SCLN, MO(_RAISE_LAYER),\
			KC_GESC, KC_TAB,  KC_LSFT, KC_LCTRL),
	[_DVORAK_LOWER_LAYER] = LAYOUT_gamepad_6x4(
			KC_L,    KC_S,    KC_Z,    KC_LALT, \
			KC_R,    KC_N,    KC_V,    _______, \
			KC_C,    KC_T,    KC_W,             \
			KC_G,    KC_H,    KC_M,    KC_ENTER,\
			KC_F,    KC_D,    KC_B,    _______, \
			_______, _______, _______, _______),



	/* Keymap _RAISE_LAYER: Additional layer to access more
	 * ,-----------------------.
	 * |  5  |  0  | del | Alt |
	 * |-----|-----|-----|-----|
	 * |  4  |  9  | ->  | LOW |
	 * |-----|-----|-----|-----|
	 * |  3  |  8  |  <- |     |
	 * |-----|-----|-----| Spc |
	 * |  2  |  7  | ->  |     |
	 * |-----|-----|-----|-----|
	 * |  1  |  6  |  <- | RAI |
	 * |-----|-----|-----|-----|
	 * | Esc | Tab | Sft | Ctl |
	 * `-----------------------'
	 */
	[_RAISE_LAYER] = LAYOUT_gamepad_6x4(
			KC_5,    KC_0,   KC_BSPC,  _______, \
			KC_4,    KC_9,   KC_RIGHT, _______, \
			KC_3,    KC_8,   KC_UP,             \
			KC_2,    KC_7,   KC_DOWN,  _______, \
			KC_1,    KC_6,   KC_LEFT,  _______, \
			_______, _______, _______, _______),



	/* Keymap _ALTER_LAYER: Function layer used to control the Leds
	 *                     and use media buttons
	 * ,----------------------------------------.
	 * | Val Dec | Bl Toggle  | Qwertz  | Super |
	 * |---------|------------|---------|-------|
	 * | Val Inc |   Bl Off   | Qwerty  |       |
	 * |---------|------------|---------|-------|
	 * | Sat Dec |   Bl On    | Colemak |       |
	 * |---------|------------|---------|       |
	 * | Sat Inc | RGB Toggle | Dvorak  |       |
	 * |---------|------------|---------|-------|
	 * | Hue Dec |  RGB Next  | Vol Dwn |       |
	 * |---------|------------|---------|-------|
	 * | Hue Inc |  RGB Prev  | Vol Up  | Reset |
	 * `----------------------------------------'
	 */
	[_ALTER_LAYER] = LAYOUT_gamepad_6x4(
			RGB_VAD, BL_TOGG,  QWERTZ,  KC_LGUI, \
			RGB_VAI, BL_OFF,   QWERTY,  _______, \
			RGB_SAD, BL_ON,    COLEMAK,          \
			RGB_SAI, RGB_TOG,  DVORAK,  _______, \
			RGB_HUD, RGB_MOD,  KC_VOLD, _______, \
			RGB_HUI, RGB_RMOD, KC_VOLU, RESET),
};

// Makes sure to update the good tri-layer if a layer changes
uint32_t layer_state_set_user(uint32_t state) {
	switch (biton32(default_layer_state)) {
		case _QWERTY_LAYER:
			state = update_tri_layer_state(state, _RAISE_LAYER, _QWERTY_LOWER_LAYER, _ALTER_LAYER);
			break;
		case _QWERTZ_LAYER:
			state = update_tri_layer_state(state, _RAISE_LAYER, _QWERTZ_LOWER_LAYER, _ALTER_LAYER);
			break;
		case _COLEMA_LAYER:
			state = update_tri_layer_state(state, _RAISE_LAYER, _COLEMA_LOWER_LAYER, _ALTER_LAYER);
			break;
		case _DVORAK_LAYER:
			state = update_tri_layer_state(state, _RAISE_LAYER, _DVORAK_LOWER_LAYER, _ALTER_LAYER);
			break;
	}
	return state;
}

// Makes the tri-layer
uint32_t default_layer_state_set_kb(uint32_t state) {
	switch (biton32(state)) {
		case _QWERTY_LAYER:
			state = update_tri_layer_state(state, _RAISE_LAYER, _QWERTZ_LOWER_LAYER, _ALTER_LAYER);
			state = update_tri_layer_state(state, _RAISE_LAYER, _COLEMA_LOWER_LAYER, _ALTER_LAYER);
			state = update_tri_layer_state(state, _RAISE_LAYER, _DVORAK_LOWER_LAYER, _ALTER_LAYER);
			layer_move(_QWERTY_LAYER);
			break;
		case _QWERTZ_LAYER:
			state = update_tri_layer_state(state, _RAISE_LAYER, _QWERTY_LOWER_LAYER, _ALTER_LAYER);
			state = update_tri_layer_state(state, _RAISE_LAYER, _COLEMA_LOWER_LAYER, _ALTER_LAYER);
			state = update_tri_layer_state(state, _RAISE_LAYER, _DVORAK_LOWER_LAYER, _ALTER_LAYER);
			layer_move(_QWERTZ_LAYER);
			break;
		case _COLEMA_LAYER:
			state = update_tri_layer_state(state, _RAISE_LAYER, _QWERTY_LOWER_LAYER, _ALTER_LAYER);
			state = update_tri_layer_state(state, _RAISE_LAYER, _QWERTZ_LOWER_LAYER, _ALTER_LAYER);
			state = update_tri_layer_state(state, _RAISE_LAYER, _DVORAK_LOWER_LAYER, _ALTER_LAYER);
			layer_move(_COLEMA_LAYER);
			break;
		case _DVORAK_LAYER:
			state = update_tri_layer_state(state, _RAISE_LAYER, _QWERTY_LOWER_LAYER, _ALTER_LAYER);
			state = update_tri_layer_state(state, _RAISE_LAYER, _QWERTZ_LOWER_LAYER, _ALTER_LAYER);
			state = update_tri_layer_state(state, _RAISE_LAYER, _COLEMA_LOWER_LAYER, _ALTER_LAYER);
			layer_move(_DVORAK_LAYER);
			break;
	}
	return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case BL_TOGG:
			if (record->event.pressed) {
				cospad_bl_led_togg();
			}
			return false;
		case BL_ON:
			if (record->event.pressed) {
				cospad_bl_led_on();
			}
			return false;
		case BL_OFF:
			if (record->event.pressed) {
				cospad_bl_led_off();
			}
			return false;
		case QWERTY:
			if (record->event.pressed) {
				set_single_persistent_default_layer(_QWERTY_LAYER);
				print("switched to QWERTY layout\n");
			}
			return false;
			break;
		case QWERTZ:
			if (record->event.pressed) {
				set_single_persistent_default_layer(_QWERTZ_LAYER);
			}
			return false;
			break;
		case COLEMAK:
			if (record->event.pressed) {
				set_single_persistent_default_layer(_COLEMA_LAYER);
			}
			return false;
			break;
		case DVORAK:
			if (record->event.pressed) {
				set_single_persistent_default_layer(_DVORAK_LAYER);
			}
			return false;
			break;
		default:
			return true;
	}
}
