#include "bm16s.h"

enum custom_keycodes {
  BM_HELP = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = KEYMAP(
		KC_BRIU, _______, _______, KC_VOLU, \
		KC_BRID, _______, _______, KC_VOLD, \
		_______, _______, _______, KC_MUTE, \
		KC_MPRV, KC_MPLY, KC_MNXT, MO(1)    \
	),
	[1] = KEYMAP(
		RESET,   _______, _______, _______, \
		BL_TOGG, BL_DEC,  BL_INC,  BL_STEP, \
		RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, \
		RGB_SAI, RGB_SAD, BM_HELP, _______  \
	),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case BM_HELP:
      if (record->event.pressed) {
        // when keycode BM_HELP is pressed
        SEND_STRING("Help is not coming!");
      } else {
        // when keycode BM_HELP is released
      }
      break;
  }
  return true;
}

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
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