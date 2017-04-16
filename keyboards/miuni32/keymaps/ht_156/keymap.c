#include "miuni32.h"

#define BASE    0
#define NUMBERS 1
#define SYMBOLS 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Level 0: Default Layer
     * ,---------------------------------------------------------------------------------------.
     * |   Q   |   W   |   E   |   R   |   T   |   Y   |   U   |   I   |   O   |   P   |  BSP  |
     * |---------------------------------------------------------------------------------------|
     * |   A   |   S   |   D   |   F   |   G   |   H   |   J   |   K   |   L   |  ENT  |  RSFT |
     * |---------------------------------------------------------------------------------------|
     * |LT(2|Z)|   X   |   C   |   V   |   B   |  SPC  |   N   |   M   |   ,   |LT(1|.)|  RCTL |
     * |---------------------------------------------------------------------------------------|
     */
	[BASE] ={
		{KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC}, 
		{KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_ENT, KC_RSFT}, 
		{LT(2, KC_Z), KC_X, KC_C, KC_V, KC_B, KC_SPC, KC_N, KC_M, KC_COMMA, LT(1, KC_DOT), KC_RCTL}
	},
	/* Level 1: Numbers Layer
     * ,---------------------------------------------------------------------------------------.
     * |  ESC  |   7   |   8   |   9   |   /   |   *   |   .   |   ,   |   (   |   )   |  DEL  |
     * |---------------------------------------------------------------------------------------|
     * |  TAB  |   4   |   5   |   6   |   -   |   +   |  HOME |   UP  |  END  |  INS  |  PGUP |
     * |---------------------------------------------------------------------------------------|
     * |  LATL |   1   |   2   |   3   |   0   |  ENT  |  LEFT |  DOWN |  RGHT | !TRNS!|  PGDN |
     * |---------------------------------------------------------------------------------------|
     */
	[NUMBERS] ={
		{KC_ESC, KC_7, KC_8, KC_9, KC_SLSH, KC_ASTR, KC_DOT, KC_COMM, KC_LPRN, KC_RPRN, KC_DEL}, 
		{KC_TAB, KC_4, KC_5, KC_6, KC_MINS, KC_PLUS, KC_HOME, KC_UP, KC_END, KC_INSERT, KC_PGUP},
		{KC_LALT, KC_1, KC_2, KC_3, KC_0, KC_ENT, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_PGDN}
	},
	/* Level 2: Symbols Layer
     * ,---------------------------------------------------------------------------------------.
     * |   !   |   @   |   #   |   $   |   %   |   ^   |   &   |   *   |   _   |   =   |   ?   |
     * |---------------------------------------------------------------------------------------|
     * | RESET |  LSFT |   ~   |   {   |   }   |   \   |   |   |   ;   |   :   |   `   |   "   |
     * |---------------------------------------------------------------------------------------|
     * | !TRNS!|  LCTL |  TRNS |   [   |   ]   |  TAB  |   <   |   >   |  TRNS |  RCTL |  TRNS |
     * |---------------------------------------------------------------------------------------|
     */
	[SYMBOLS] ={
		{KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_UNDS, KC_EQL, KC_QUES},
		{RESET, KC_LSFT, KC_TILD, KC_LCBR, KC_RCBR, KC_BSLS, KC_PIPE, KC_SCLN, KC_COLN, KC_GRV, KC_DQUO},
		{KC_TRNS, KC_LCTL, KC_TRNS, KC_LBRC, KC_RBRC, KC_TAB, KC_LABK, KC_RABK, KC_TRNS, KC_RCTL, KC_TRNS}
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
