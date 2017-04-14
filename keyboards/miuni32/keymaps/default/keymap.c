#include "miuni32.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] ={
			{KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC}, 
			{KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_ENT, LT(1, KC_COMMA)}, 
			{LT(3, KC_Z), KC_X, KC_C, KC_V, KC_NO, KC_SPC, KC_B, KC_N, KC_M, KC_RSFT, LT(2, KC_DOT)}
	},
	[1] ={
			{KC_ESC, KC_7, KC_8, KC_9, KC_SLSH, KC_ASTR, KC_DOT, KC_COMM, KC_LPRN, KC_RPRN, KC_BSPC}, 
			{KC_TAB, KC_4, KC_5, KC_6, KC_MINS, KC_PLUS, KC_EQL, KC_UP, KC_HOME, KC_PGUP, KC_TRNS},
			{KC_LALT, KC_1, KC_2, KC_3, KC_0, KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_RALT}
	},
	[2] ={
			{KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_MINS, KC_PLUS, KC_EQL},
			{KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, KC_TRNS, KC_TRNS, KC_BSLS, KC_SCLN, KC_COLN, KC_GRV, KC_QUES},
			{KC_TRNS, KC_LCTL, KC_L, KC_T, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_RCTL, KC_TRNS}
	},
	[3] ={
			{RESET, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS}, 
			{RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, KC_NO, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_TRNS, KC_TRNS},
			{KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS}
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
