#include QMK_KEYBOARD_H
#include "tominabox1.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_BASE] = LAYOUT_wrapper(
		__________________BASE1____________________,
		__________________BASE2____________________,
		__________________BASE3L___________________,__________________BASE3R___________________,
		__________________BASE4____________________
	),

	[_LOWER] = LAYOUT_wrapper(
		_________________LOWER_1___________________,
		_________________LOWER_2___________________,
		_________________LOWER_3___________________,
		_________________LOWER_4___________________
	),

	[_RAISE] = LAYOUT_wrapper(
		___________________NAV1____________________,
		___________________NAV2____________________,
		___________________NAV3____________________,
		___________________NAV4____________________

	),


	[_ADJUST] = LAYOUT_wrapper(
		___________________ADJST1__________________,
		___________________ADJST2__________________,
		___________________ADJST3__________________,
		___________________ADJST4__________________

	),


	[_FKEY] = LAYOUT_wrapper(
		___________________FKEY1___________________,
		___________________FKEY2___________________,
		___________________FKEY3___________________,
		___________________FKEY4___________________
	),

	[_GAMER] = LAYOUT_wrapper(
		___________________GAMER1__________________,
		___________________GAMER2__________________,
		___________________GAMER3__________________,
		___________________GAMER4__________________
	),
};

void keyboard_post_init_user(void) {
		rgblight_sethsv_at(0, 0, 0, 24);
		rgblight_set();
		writePinHigh(E6);
}

bool led_update_kb(led_t led_state){
  if(led_state.caps_lock){
      rgblight_setrgb_at(145, 255, 0, 24);
      rgblight_mode_noeeprom(0);
  } else{
      rgblight_sethsv_at(0, 0, 0, 24);
  }
    return true;
}
