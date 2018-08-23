#include QMK_KEYBOARD_H
#include "rgblight.h"

//Layer definitions
#define _BL 0
#define _DL 1
#define _UL 2
#define _GL 3
#define _BK 4


//other variables
int mCalled = 0;
bool blockToggle = false;
bool lRGB = true;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BL] = LAYOUT(
  KC_Q,     KC_W,     KC_E,     KC_R,    KC_T,     KC_Y,           KC_U,           KC_I,    KC_O,    KC_P,    KC_BSPC, \
  KC_A,     KC_S,     KC_D,     KC_F,    KC_G,     KC_H,           KC_J,           KC_K,    KC_L,    KC_SCLN, TG(_GL), \
  KC_LSFT,  KC_Z,     KC_X,     KC_C,    KC_V,     KC_B,           KC_N,           KC_M,    KC_QUOT, KC_SLSH, KC_ENT,  \
  KC_TAB,   KC_ESC,   KC_LCTL,  KC_LALT, KC_COMMA, LT(_DL,KC_SPC), LT(_UL,KC_SPC),          KC_DOT,  KC_LGUI),

[_DL] = LAYOUT(
  KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,  KC_F12,\
  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,    KC_TRNS,\
  KC_TRNS,  KC_PSCR,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  \
  KC_TRNS,  KC_F1,    KC_TRNS,  RESET,    KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS),

[_UL] = LAYOUT(
  KC_LBRC,  KC_RBRC,  KC_LCBR,  KC_RCBR,  KC_PIPE,  KC_BSLS,  KC_PLUS,  KC_UNDS,  KC_MINS,  KC_EQL,  KC_DEL,\
  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN, KC_TRNS, \
  KC_TRNS,  KC_FN0,   RGB_TOG,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  RGB_SAD,  RGB_VAD,  KC_TRNS,  KC_TRNS,  \
  KC_TRNS,  KC_GRV,   KC_TRNS,  RGB_MOD,  RGB_HUI,  KC_TRNS,  KC_TRNS,            RGB_SAI,  RGB_VAI),

[_GL] = LAYOUT(
  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_UP,    KC_TRNS,  KC_TRNS, \
  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_TRNS, \
  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  \
  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_SPC,   KC_SPC,             KC_TRNS,  KC_TRNS),

[_BK] = LAYOUT(
  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,\
  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,\
  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_NO,    KC_NO,    KC_TRNS,  KC_TRNS,  \
  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_NO,    KC_NO,    KC_TRNS,  KC_FN1,  KC_NO,    KC_NO),

};


//KC_MPLY,  KC_VOLU,  KC_VOLD,  KC_TRNS,  KC_TRNS,            KC_MNXT,  KC_MPRV
//function to toggle the interactive rgb variable
bool toggleLayerRGB(void){
	if(lRGB == true){
	return false;
	}
	else{
	return true;
	}
}

void matrix_init_user(void){
	rgblight_enable();
  	rgblight_mode(1);
	rgblight_sethsv(0,10,255);
}

//check for layer and if there was a keypress change underglow lighting
void matrix_scan_kb(void){
	if(lRGB == true)
	{



		//base layer
		if(layer_state == 0x00000000 && mCalled == 1 ){
			rgblight_sethsv(0,10,255);
			mCalled = 0;
		}

		//down layer
		else if(layer_state == 0x00000002 && mCalled == 1){
			rgblight_sethsv(160,255,255);
			mCalled = 0;
		}


		//up layer with rgb access blocked
		else if(layer_state == 0x00000004 && mCalled == 1 && lRGB == true){
			//blockToggle = true;
			layer_state = 0x00000014;
			rgblight_sethsv(180,255,255);
			mCalled = 0;
		}

		//arrow cluster layer
		else if(layer_state == 0x00000008 && mCalled == 1){
			rgblight_sethsv(0,180,255);
			mCalled = 0;
		}

		//if on blocked layer and the spacebar has been released reset to baselayer and set colours to white
		else if(layer_state == 0x00000014 && blockToggle == true )
		{
			blockToggle = false;
			layer_state = 0x00000000;
			rgblight_sethsv(0,10,255);
		}

	}
}

//set mCalled to 1 when a button is pressed to make sure the leds aren't continuesly updated.
bool process_record_user (uint16_t keycode, keyrecord_t *record) {
  mCalled = 1;

  //uncommenting the line below causes the lights to flicker when typing on the keyboard.
  //rgblight_sethsv(0,255,0);

	if(keycode == KC_FN0 && record->event.pressed){
		//set the toggle and make sure to set the colour back to white
		lRGB = toggleLayerRGB();
		rgblight_enable();
  		rgblight_mode(1);
		rgblight_sethsv(0,255,255);
		layer_state =0x00000000;

		return false;
	}

	//check if spacebar is released when on a different layer
	if(keycode == KC_FN1){
		if(record ->event.pressed){
		}else{
		blockToggle = true;
		}
	}

  return true;
}
