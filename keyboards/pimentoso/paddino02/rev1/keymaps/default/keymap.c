#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	KEYMAP(
		KC_ESC, KC_BTN1, KC_UP, KC_BTN2,
		KC_LSFT, KC_LEFT, KC_DOWN, KC_RGHT,
		MO(1), KC_SPC),

	KEYMAP(
		KC_MY_COMPUTER, KC_MPRV, KC_MPLY, KC_MNXT,
		KC_WWW_HOME, KC_MUTE, KC_VOLD, KC_VOLU,
		KC_TRNS, KC_ENT)

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
	return MACRO_NONE;
}

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	return true;
}

void led_set_user(uint8_t usb_led) {
}
