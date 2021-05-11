#include "BOP.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	KEYMAP(
	/*			For build guide: go to https://github.com/blewis308/BOP-Keyboard
	*	,-----------------------------------------------------------------------------------------------------------------------.
	*	| F1  | F5  | F9  |  ~  |  !  |  @  |  #  |  $  |  %  |  ^  |  &  |  *  |  (  |  )  |  _  |  +  | del |  {  |  }  |  |  |
	*	|-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
	*	| F2  | F6  | F10 | esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |bkspc| home| end |pg up|
	*	|-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
	*	| F3  | F7  | F11 | tab |  q  |  w  |  e  |  r  |  t  |  y  |  u  |  i  |  o  |  p  |  [  |  ]  |  \  |  :  |  "  |pg dn|
	*	|-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
	*	| F4  | F8  | F12 |caplk|  a  |  s  |  d  |  f  |  g  |  h  |  j  |  k  |  l  |  ;  |  '  |enter|     |  7  |  8  |  9  |
	*	|-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|  0  |-----+-----+-----|
	*	|ptscr|scrlk|psbrk|shift|  z  |  x  |  c  |  v  |  b  |  n  |  m  |  <  |  >  |  ?  |shift| up  |     |  4  |  5  |  6  |
	*	|-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
	*	| cut | copy|paste|Lctrl|L gui|L alt|   space   | n/a |   space   |  ,  |  .  |  /  | left| down|right|  1  |  2  |  3  |
	*	`-----------------------------------------------------------------------------------------------------------------------'
	*
	*	Notes: spaces and numpad 0 can be 1u instead of 2u also, this is already reflected in the keymap below
	*/
	
	
		KC_F1, 		KC_F5, 		KC_F9, 	    KC_TILD, KC_EXLM,   KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN,  KC_RPRN, 	KC_UNDS, KC_PLUS, KC_DEL, KC_LCBR, KC_RCBR, KC_PIPE, 
		KC_F2, 		KC_F6, 		KC_F10, 	KC_ESC,  KC_1, 		KC_2, 	KC_3, 	KC_4, 	KC_5, 	KC_6, 		KC_7, 	KC_8, 	KC_9, 		KC_0, 	KC_MINS, KC_EQL, KC_BSPC, KC_HOME, KC_END, KC_PGUP, 
		KC_F3, 		KC_F7, 		KC_F11, 	KC_TAB,  KC_Q, 		KC_W, 	KC_E, 	KC_R, 	KC_T, 	KC_Y, 		KC_U, 	KC_I, 	KC_O, 		KC_P, 	KC_LBRC, KC_RBRC, KC_BSLS, KC_COLN, KC_DQUO, KC_PGDN, 
		KC_F4,      KC_F8, 		KC_F12, 	KC_CAPS, KC_A, 		KC_S, 	KC_D, 	KC_F, 	KC_G, 	KC_H, 		KC_J, 	KC_K, 	KC_L, 		KC_SCLN, KC_QUOT, KC_ENT, KC_0,		KC_7, 	KC_8,   KC_9, 
		KC_PSCR,    KC_SLCK, 	KC_PAUS, 	KC_LSFT, KC_Z, 		KC_X, 	KC_C, 	KC_V, 	KC_B, 	KC_N, 		KC_M, 	KC_LABK, KC_RABK, 	KC_QUES, KC_RSFT, KC_UP,  KC_0, 	KC_4, 	KC_5,   KC_6, 
		LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), KC_LCTL, KC_LGUI,	KC_LALT, KC_SPC, KC_SPC, KC_NO, KC_SPC,   KC_SPC, 	KC_COMM, KC_DOT,   KC_SLSH,  KC_LEFT, KC_DOWN, KC_RGHT, KC_1, 	KC_2, 	KC_3 )
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