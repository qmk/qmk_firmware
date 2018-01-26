#include "miuni32.h"
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Level 0: BEAKL
     * ,---------------------------------------------------------------------------------------.
     * |   J   |   H   |   O   |   U   |   K   | LOWER |   G   |   C   |   R   |   F   |  Z    |
     * |---------------------------------------------------------------------------------------|
     * |   Q   |   I   |   E   |   A   |   Y   | RAISE |   D   |   S   |   T   |  N    |  B    |
     * |---------------------------------------------------------------------------------------|
     * |   /   |   ,   |   '   |   .   |   X   |  SPC  |   W   |   M   |   L   |  P   |    V   |
     * |---------------------------------------------------------------------------------------|
     */
	[_BEAKL] ={
		{KC_J,    KC_H,    KC_O,    KC_U,   KC_K, KC_NO,   KC_G, KC_C, KC_R, KC_F, KC_Z},
		{KC_Q,    KC_I,    KC_E,    KC_A,   KC_Y, RAISE,   KC_D, KC_S, KC_T, KC_N, KC_B},
		{KC_SLSH, KC_COMM, KC_QUOT, KC_DOT, KC_X, SPC_SHF, KC_W, KC_M, KC_L, KC_P, KC_V}
	},
	/* Level 1: Numbers Layer
     * ,---------------------------------------------------------------------------------------.
     * |  Tab  |   {   |   _   |   }   |   &   |       |  Gui  |   [   |       |   ]   | Bkspc |
     * |---------------------------------------------------------------------------------------|
     * |   \   |   (   |   1   |   )   |   #   |       |   $   |   <   |   0   |   >   |   |   |
     * |---------------------------------------------------------------------------------------|
     * |   5   |   4   |   3   |   2   |  Ctl  |       |  Alt  |   9   |   8   |   7   |   6   |
     * |---------------------------------------------------------------------------------------|
     */
	[_LOWER] ={
		{KC_TAB,  KC_LCBR, KC_UNDS, KC_RBRC, KC_AMPR, _______, KC_RGUI, KC_LBRC, KC_LPRN, KC_RBRC, KC_BSPC},
		{KC_BSLS, KC_LPRN, KC_1,    KC_RPRN, KC_HASH, _______, KC_DLR,  KC_LT,   KC_0,    KC_GT,   KC_PIPE},
		{KC_5,    KC_4,    KC_3,    KC_2,    KC_LCTL, _______, KC_RALT, KC_9,    KC_8,    KC_7,    KC_6}
	},
	/* Level 2: Symbols Layer
     * ,---------------------------------------------------------------------------------------.
     * |       |       |       |       |       |       |       |       |       |       |  Del  |
     * |---------------------------------------------------------------------------------------|
     * |       |       |   !   |   -   |   +   |       |   =   |   ;   |   )   |   `   |   ?   |
     * |------------------------------- -------------------------------------------------------|
     * |   %   |   $   |   #   |   @   |       |       |       |   (   |   *   |   &   |   ^   |
     * |---------------------------------------------------------------------------------------|
     */
	[_RAISE] ={
		{_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL},
		{_______, _______, KC_EXLM, KC_MINS, KC_PLUS, _______, KC_EQL,  KC_SCLN, KC_RPRN, KC_GRV,  KC_QUES},
		{KC_PERC, KC_DLR,  KC_HASH, KC_AT,   _______, _______, _______, KC_LPRN, KC_ASTR, KC_AMPR, KC_CIRC}
	},
	/* Level 3: RGB Layer
     * ,---------------------------------------------------------------------------------------.
     * | RESET |  TRNS |  TRNS |  TRNS |  TRNS |   F1  |   F2  |   F3  |   F4  |   F5  |   F6  |
     * |---------------------------------------------------------------------------------------|
     * |RGB_TOG|RGB_MOD|RGB_HUI|RGB_HUD|   NO  |RGB_SAI|RGB_SAD|RGB_VAI|RGB_VAD|  TRNS |  TRNS |
     * |---------------------------------------------------------------------------------------|
     * |  TRNS |  TRNS |  TRNS |  TRNS |   NO  |   F7  |   F8  |   F9  |  F10  |  F11  |  F12  |
     * |---------------------------------------------------------------------------------------|
     */
	[_UNION] ={
		{RESET, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6},
		{RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, KC_NO, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_TRNS, KC_TRNS},
		{KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,  KC_F12}
	}
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
          } else {
            unregister_code(KC_RSFT);
          }
        break;
      }
    return MACRO_NONE;
};

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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
