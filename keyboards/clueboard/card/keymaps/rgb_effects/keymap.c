#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(
		RGB_TOG,        RGB_SAI,        RGB_VAI, \
		        RGB_HUD,        RGB_HUI,         \
		RGB_MOD,        RGB_SAD,        RGB_VAD, \
		BL_STEP,                                 \
		KC_NO,  KC_NO,  KC_NO                    \
	)
};

const uint8_t RGBLED_SNAKE_INTERVALS[] PROGMEM = {255, 170, 85};
const uint8_t RGBLED_KNIGHT_INTERVALS[] PROGMEM = {255, 170, 85};

void matrix_init_user(void) {
}

void matrix_scan_user(void) {

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void led_set_user(uint8_t usb_led) {
}
