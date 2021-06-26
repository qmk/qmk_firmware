#include QMK_KEYBOARD_H

enum my_keycodes {
  RGBWHITE = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT_denial75_ansi(
	KC_ESC,   KC_F1,   KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,  KC_INS,   KC_DEL,  
    	KC_GRV,   KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS, KC_EQL,            KC_BSPC,  KC_HOME, 
    	KC_TAB,            KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,  KC_BSLS,  KC_PGUP, 
    	KC_CAPS,  	   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,             KC_PGDN, 
   		  KC_LSFT, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,  KC_UP,    KC_END,  
    	KC_LCTL,  KC_LGUI, 	   KC_LALT,                KC_SPC,                          KC_RALT, MO(1),   KC_RCTL, KC_LEFT,  KC_DOWN,  KC_RGHT
	), 
	
	[1] = LAYOUT_denial75_ansi(
	KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO,   KC_NO,   RGBWHITE,   KC_MUTE,  KC_AUDIO_VOL_UP, KC_AUDIO_VOL_DOWN,  
    	KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,             KC_NO,    KC_BRIU, 
    	KC_NO,            KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,    KC_BRID, 
    	KC_NO,  	  KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,              RGB_VAI, 
   		 KC_NO,   KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO,   KC_NO,            KC_NO,    KC_BRIU,  RGB_VAD,  
    	KC_NO,   KC_NO, 	   KC_NO,                  KC_NO,                           KC_NO,   MO(1),   RGB_TOG, RGB_SAD,  KC_BRID,  RGB_SAI
	)
}; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case RGBWHITE:
      if (record->event.pressed) {
        rgblight_setrgb(RGB_WHITE);
      } else {
        // Do something else when release
      }
      return false; // Skip all further processing of this key
    default:
      return true; // Process all other keycodes normally
  }
}
