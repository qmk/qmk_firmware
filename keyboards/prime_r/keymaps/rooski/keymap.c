// Prime_R Rev 1.0

#include "prime_r.h"
#include "action_layer.h"
#include "backlight.h"

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

//Custom Keys
enum custom_keycodes{
	AR_TOG = SAFE_RANGE, //Toggle Arrow Keys
	AR_LT,	//Num0 or Left Arrow
	AR_RT,	//NumEnt or Right Arrow
	AR_DN,	//NumDot or Down Arrow
	AR_UP,	//Num2 or Up Arrow
};
		
// Tap/Hold Space Layer
#define SPC_LT LT(1, KC_SPC)

//Arrow Cluster Toggle
static bool arrow_toggle = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* (Base Layer) Default Layer
   * ,---------------------------------------------------------------.
   * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|BSP|DEL|HOM|END|
   * |---------------------------------------------------------------|
   * |Grv|  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  7|  8|  9|
   * |---------------------------------------------------------------|
   * |Tab |  A|  S|  D|  F|  G|  H|  J|  K|  L|  '|Return|  4|  5|  6|
   * |---------------------------------------------------------------|
   * |Shift|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  ?|Shift|  1|  2|  3|
   * |---------------------------------------------------------------|
   * |Ctrl|Gui |Alt|TO1| 1/SP |  1/SP  |TO3|App|Alt|Ctrl |  0|  .|Ret|
   * `---------------------------------------------------------------'
   */
  // 0: Base Layer
	KEYMAP(
		KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   KC_6,    KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_BSPC, KC_DEL,  KC_HOME, KC_END,   \
		KC_GRV,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_P7,   KC_P8,   KC_P9,    \
		KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   KC_H,    KC_J,   KC_K,    KC_L,    KC_QUOT,          KC_ENT,  KC_P4,   KC_P5,   KC_P6,    \
		KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,    KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_LSFT, KC_P1,   AR_UP,   KC_P3,    \
		KC_LCTL,          KC_LGUI, KC_LALT, TO(1),   SPC_LT,          SPC_LT,          AR_TOG,  KC_APP,  KC_RALT, KC_RCTL, AR_LT,   AR_DN,   AR_RT),   \

  /* (Base Layer) Default Layer
   * ,---------------------------------------------------------------.
   * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9| F0|  =|BSP|HOM|END|DEL|
   * |---------------------------------------------------------------|
   * |Grv|  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  \|  7|  8|  9|
   * |---------------------------------------------------------------|
   * |Tab |  A|  S|  D|  F|  G|  H|  J|  K|  L|  '|Return|  4|  5|  6|
   * |---------------------------------------------------------------|
   * |Shift|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  ?|Shift|  1| UP|  3|
   * |---------------------------------------------------------------|
   * |Ctrl|Gui |Alt|TO0| 1/SP |  1/SP  |ART|App|Alt|Ctrl |LFT|DWN| RT|
   * `---------------------------------------------------------------'
   */
  // 1: Function Layer

	KEYMAP(
		_______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_EQL,  _______, KC_PAST, KC_PMNS, KC_PPLS, 
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BSLS, _______, _______, _______, 
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_SCLN,          _______, _______, _______, _______, 
		_______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
		_______,          _______, _______, TO(0),   _______,          _______,          _______, _______, _______, _______, _______, _______, _______),	
		
  // 2: Extra
	KEYMAP(
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, 
		_______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
		_______,          _______, _______, _______, _______,          _______,          _______, _______, _______, _______, _______, _______, _______),

};

void matrix_init_user(void) {
	if (get_backlight_level() != 0){
		backlight_toggle();
	}
};

void matrix_scan_user(void) {
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch(keycode) {
		case AR_TOG:
			if(record->event.pressed){
				arrow_toggle = !arrow_toggle;
				backlight_toggle();				
			}
			break;
		case AR_UP:
			if(record->event.pressed){
				if(arrow_toggle == 1){
//					SEND_STRING(SS_TAP(X_UP));
					register_code(KC_UP);
					unregister_code(KC_UP);
				} else {
//					SEND_STRING(SS_TAP(X_KP_2));
					register_code(KC_P2);
					unregister_code(KC_P2);					
				}
				break;
			}
		case AR_DN:
			if(record->event.pressed){
				if(arrow_toggle == 1){
					SEND_STRING(SS_TAP(X_DOWN));
				} else {
					SEND_STRING(SS_TAP(X_KP_DOT));
				}
				break;
			}
		case AR_LT:
			if(record->event.pressed){
				if(arrow_toggle == 1){
					SEND_STRING(SS_TAP(X_LEFT));
				} else {
					SEND_STRING(SS_TAP(X_KP_0));
				}
				break;
			}
		case AR_RT:
			if(record->event.pressed){
				if(arrow_toggle == 1){
					SEND_STRING(SS_TAP(X_RIGHT));
				} else {
					SEND_STRING(SS_TAP(X_KP_ENTER));
				}
				break;
			}
	}		
	return true;
};

void led_set_kb(uint8_t usb_led) {
};