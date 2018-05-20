#include QMK_KEYBOARD_H
#include "action_layer.h"

enum miuni32_layers {
  _BEAKL,
  _LOWER,
  _RAISE,
  _UNION
};

enum miuni32_keycodes {
  BEAKL = SAFE_RANGE,
  LOWER,
  RAISE
};

#define SPC_SHF SFT_T(KC_SPC)

// Set the custom keymap
// 33 keys, ortho 3x11 layout
#ifdef LAYOUT
#undef LAYOUT
#endif

#define LAYOUT_ortho_3x11( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A ) { \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A } \
}

#define LAYOUT LAYOUT_ortho_3x11

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Level 0: BEAKL
     * ,---------------------------------------------------------------------------------------.
     * |   J   |   H   |   O   |   U   |   K   | LOWER |   G   |   C   |   R   |   F   |   Z   |
     * |---------------------------------------------------------------------------------------|
     * |   Q   |   I   |   E   |   A   |   Y   | RAISE |   D   |   S   |   T   |   N   |   B   |
     * |---------------------------------------------------------------------------------------|
     * |   /   |   ,   |   '   |   .   |   X   |SPC\SHF|   W   |   M   |   L   |   P   |   V   |
     * |---------------------------------------------------------------------------------------|
     */
	[_BEAKL] = LAYOUT(
		KC_J,    KC_H,    KC_O,    KC_U,   KC_K, KC_NO,   KC_G, KC_C, KC_R, KC_F, KC_Z, \
		KC_Q,    KC_I,    KC_E,    KC_A,   KC_Y, RAISE,   KC_D, KC_S, KC_T, KC_N, KC_B, \
		KC_SLSH, KC_COMM, KC_QUOT, KC_DOT, KC_X, SPC_SHF, KC_W, KC_M, KC_L, KC_P, KC_V
	),
	/* Lower
     * ,---------------------------------------------------------------------------------------.
     * |  Tab  |   {   |   _   |   }   |   &   |       |  Gui  |   [   |   %   |   ]   | Bkspc |
     * |---------------------------------------------------------------------------------------|
     * |   \   |   (   |   1   |   )   |   #   |       |   $   |   <   |   0   |   >   |   |   |
     * |---------------------------------------------------------------------------------------|
     * |   5   |   4   |   3   |   2   |  Ctl  |       |  Alt  |   9   |   8   |   7   |   6   |
     * |---------------------------------------------------------------------------------------|
     */
	[_LOWER] = LAYOUT(
		KC_TAB,  KC_LCBR, KC_UNDS, KC_RBRC, KC_AMPR, _______, KC_RGUI, KC_LBRC, KC_PERC, KC_RBRC, KC_BSPC, \
		KC_BSLS, KC_LPRN, KC_1,    KC_RPRN, KC_HASH, _______, KC_DLR,  KC_LT,   KC_0,    KC_GT,   KC_PIPE, \
		KC_5,    KC_4,    KC_3,    KC_2,    KC_LCTL, _______, KC_RALT, KC_9,    KC_8,    KC_7,    KC_6
	),
	/* Raise
     * ,---------------------------------------------------------------------------------------.
     * |   F1  |   F2  |   F3  |   F4  |   F5  |       |   F6  |   F7  |   F8  |   F9  |  F10  |
     * |---------------------------------------------------------------------------------------|
     * |  F11  |  F12  |   !   |   -   |   +   |       |   =   |   ;   |   )   |   `   |   ?   |
     * |------------------------------- -------------------------------------------------------|
     * |   %   |   $   |   #   |   @   |       |       |       |   (   |   *   |   &   |   ^   |
     * |---------------------------------------------------------------------------------------|
     */
	[_RAISE] = LAYOUT(
		KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  \
		KC_F11,  KC_F12,  KC_EXLM, KC_MINS, KC_PLUS, _______, KC_EQL,  KC_SCLN, KC_RPRN, KC_GRV,  KC_QUES, \
		KC_PERC, KC_DLR,  KC_HASH, KC_AT,   _______, _______, _______, KC_LPRN, KC_ASTR, KC_AMPR, KC_CIRC
	),
	/* Union
     * ,---------------------------------------------------------------------------------------.
     * | RESET |       |       |       |       |       |       |       |       |       |  Del  |
     * |---------------------------------------------------------------------------------------|
     * |       |       |       |       |       |       |       |       |       |       |       |
     * |---------------------------------------------------------------------------------------|
     * |       |       |       |       |       |       |       |       |       |       |       |
     * |---------------------------------------------------------------------------------------|
     */
	[_UNION] = LAYOUT(
		RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,  \
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
	)
};

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

//planck like tri layer
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case BEAKL:
    if (record->event.pressed) {
      set_single_persistent_default_layer(_BEAKL);
    }
    return false;
    break;
  case LOWER:
    if (record->event.pressed) {
      layer_on(_LOWER);
      update_tri_layer(_LOWER, _RAISE, _UNION);
    } else {
      layer_off(_LOWER);
      update_tri_layer(_LOWER, _RAISE, _UNION);
    }
    return false;
    break;
  case RAISE:
    if (record->event.pressed) {
      layer_on(_RAISE);
      update_tri_layer(_LOWER, _RAISE, _UNION);
    } else {
      layer_off(_RAISE);
      update_tri_layer(_LOWER, _RAISE, _UNION);
    }
    return false;
    break;
  }
	return true;
}

void led_set_user(uint8_t usb_led) {

	if (usb_led & (1 << USB_LED_NUM_LOCK)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_CAPS_LOCK)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_COMPOSE)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_KANA)) {

	} else {

	}

}
