#include "kb.h"
#include "keymap_swedish.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // COLEMAK
	KEYMAP(
		KC_TAB,  SE_Q,          SE_W,    SE_F,    SE_P,    SE_G,  SE_J,   SE_L,  SE_U,    SE_Y,    SE_ODIA,       SE_ARNG,
		KC_BSPC, SE_A,          SE_R,    SE_S,    SE_T,    SE_D,  SE_H,   SE_N,  SE_E,    SE_I,    SE_O,          SE_ADIA,
		KC_LSFT, SE_Z,          SE_X,    SE_C,    SE_V,    SE_B,  SE_K,   SE_M,  SE_COMM, SE_DOT,  SE_MINS,       KC_LSFT,
		KC_LCTL, LCTL(KC_LSFT), KC_LGUI, KC_LALT, MO(1),      KC_SPC,     MO(2), KC_ENT, KC_LGUI, LCTL(KC_LSFT), KC_LCTL),

    // LOWER
	KEYMAP(
		KC_ESC,  SE_1,    SE_2,     SE_3,    SE_4,    SE_5,     SE_6,    SE_7,    SE_8,    SE_9,    SE_0,    SE_PLUS,
		KC_TRNS, KC_TRNS, KC_LEFT , KC_UP,   KC_DOWN, KC_RIGHT, KC_HOME, KC_END,  KC_PGDN, KC_PGUP, KC_TRNS, KC_F12,
		KC_TRNS, KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_F5,    KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
		KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,     KC_TRNS,       MO(3),   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    // RAISE
	KEYMAP(
		KC_DEL,  SE_EXLM, SE_AT,   SE_DLR,  SE_TILD, SE_CIRC, SE_LCBR, SE_LBRC, SE_RBRC, SE_RCBR, SE_LABK, KC_TRNS,
		KC_TRNS, KC_TRNS, SE_DQUO, SE_HASH, SE_PERC, SE_QUOT, SE_SLSH, SE_LPRN, SE_RPRN, SE_EQL,  SE_RABK, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, SE_ASTR, SE_BSLS, SE_GRV,  KC_TRNS, KC_TRNS, KC_TRNS, SE_AMPR,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,     KC_TRNS, KC_TRNS, KC_VOLD, KC_VOLU, SE_PIPE),

    // EXTRAS
	KEYMAP(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		RESET,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
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
