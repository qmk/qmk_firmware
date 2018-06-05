#include QMK_KEYBOARD_H

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  DYNAMIC_MACRO_RANGE,
};

#include "dynamic_macro.h"

#define _______ KC_TRNS
#define KC_REC DYN_REC_START1
#define KC_DONE DYN_REC_STOP
#define KC_PLAY DYN_MACRO_PLAY1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	LAYOUT(
    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_HOME, KC_END,  KC_PGUP, KC_PGDN, KC_DEL,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_BSPC, KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_P7,   KC_P8,   KC_P9,   KC_PMNS,
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,                    KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
    KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_P1,   KC_P2,   KC_P3,   KC_PENT,
    KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             MO(1),   KC_RALT, KC_RCTL,   KC_LEFT, KC_DOWN, KC_RGHT, KC_P0,   KC_PDOT, KC_PENT),

	LAYOUT(
    RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, RGB_TOG, _______, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, _______, _______,          _______, _______, _______, _______,
    BL_TOGG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______,
    _______, _______, _______, _______, BL_DEC,  BL_TOGG, BL_INC,  _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______,
    _______, _______, _______,                            KC_PLAY,                            _______, KC_REC,  KC_DONE, _______, _______, _______, _______, _______, _______),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
	return MACRO_NONE;
}

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_dynamic_macro(keycode, record)) {
        return false;
    }
	return true;
}

void led_set_user(uint8_t usb_led) {

	if (usb_led & (1 << USB_LED_NUM_LOCK)) {
		DDRC |= (1 << 6); PORTC &= ~(1 << 6);
	} else {
		DDRC &= ~(1 << 6); PORTC &= ~(1 << 6);
	}

	if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
		DDRC |= (1 << 7); PORTC &= ~(1 << 7);
	} else {
		DDRC &= ~(1 << 7); PORTC &= ~(1 << 7);
	}

	if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {
		DDRB |= (1 << 5); PORTB &= ~(1 << 5);
	} else {
		DDRB &= ~(1 << 5); PORTB &= ~(1 << 5);
	}

	if (usb_led & (1 << USB_LED_COMPOSE)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_KANA)) {

	} else {

	}

}
