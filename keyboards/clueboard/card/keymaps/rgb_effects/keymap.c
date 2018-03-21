#include "card.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = KEYMAP(
		RGB_TOG,        RGB_SAI,        RGB_VAI, \
		        RGB_HUD,        RGB_HUI,         \
		RGB_MOD,        RGB_SAD,        RGB_VAD, \
		BL_STEP,                                 \
		KC_NO,   KC_NO,   KC_NO                  \
	)
};

const uint8_t RGBLED_BREATHING_INTERVALS[RGBLED_BREATHING_INTERVAL_COUNT][4] PROGMEM = {{30, 20, 10, 5}};
const uint8_t RGBLED_RAINBOW_MOOD_INTERVALS[RGBLED_RAINBOW_MOOD_INTERVAL_COUNT][3] PROGMEM = {{60, 30, 15}};
const uint8_t RGBLED_RAINBOW_SWIRL_INTERVALS[RGBLED_RAINBOW_SWIRL_INTERVAL_COUNT][3] PROGMEM = {{50, 25, 10}};
const uint8_t RGBLED_SNAKE_INTERVALS[RGBLED_SNAKE_INTERVAL_COUNT][3] PROGMEM = {{255, 170, 85}};
const uint8_t RGBLED_KNIGHT_INTERVALS[RGBLED_KNIGHT_INTERVAL_COUNT][3] PROGMEM = {{255, 170, 85}};

void matrix_init_user(void) {
}

void matrix_scan_user(void) {

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void led_set_user(uint8_t usb_led) {
}
