#include QMK_KEYBOARD_H


enum custom_keycodes {
  UP_URL = SAFE_RANGE
};

#define _BASE 0
#define _MY_LAYER 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_ortho_3x4
  (
    KC_MNXT, KC_UP, KC_LSFT,
    KC_LEFT, KC_DOWN, KC_UP,
    KC_P, KC_PASTE,  TG(_MY_LAYER),
    KC_NO, TG(_MY_LAYER), KC_NO
  ),
    [_MY_LAYER] = LAYOUT_ortho_3x4
  (
    KC_1, KC_2, KC_3,
    KC_MY_COMPUTER, KC_WWW_BACK, KC_WWW_FORWARD,
    KC_CALCULATOR, UP_URL, KC_TRANSPARENT,
    KC_NO, KC_NO, KC_NO
  )
};





bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
     case UP_URL:
      if (record->event.pressed) {
        SEND_STRING("Rami ");
		
      }	  
	   else
	   case KC_P:
      if (record->event.pressed) {
       SEND_STRING(SS_LCTRL(SS_LSFT("t")));;
	         return false;
      break;
      }
	  
	  else
      return false;
      break;
  }
  return true;
}
