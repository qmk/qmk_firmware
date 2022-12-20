#include QMK_KEYBOARD_H

// Helpful defines
#define _L0 0
#define _L1 1
#define _L2 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	 
  [_L0] = LAYOUT_60_ansi(
			QK_GESC,   KC_1,    KC_2,   KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,    KC_EQL,    KC_BSPC, 
			KC_TAB,     KC_Q,    KC_W,   KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,    KC_RBRC,   KC_BSLS, 
			KC_CAPS,     KC_A,    KC_S,   KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,    KC_ENT, 
			SC_LSPO,      KC_Z,    KC_X,   KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SC_RSPC, 
			KC_LCTL,   KC_LGUI,   KC_LALT,                       KC_SPC,                                 TT(2),   KC_RALT,    MO(1),    KC_RCTL),
	
  [_L1] = LAYOUT_60_ansi(
			KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,     KC_F6,     KC_F7,     KC_F8,    KC_F9,    KC_F10,    KC_F11,    KC_F12,    KC_DEL, 
			KC_NO,     KC_NO,    KC_UP,    KC_NO,    KC_NO,    KC_NO,     KC_NO,     KC_NO,     KC_NO,    KC_NO,    KC_NO,     KC_NO,     KC_NO,     KC_PGUP, 
			KC_NO,      KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_NO,    KC_NO,     KC_NO,     KC_NO,     KC_NO,    KC_NO,    KC_NO,     KC_NO,     KC_PGDN, 
			KC_NO,       KC_MRWD,  KC_MFFD,  KC_NO,    KC_NO,    KC_NO,     KC_NO,     KC_NO,     KC_NO,    KC_NO,    KC_NO,     KC_NO, 
			KC_MSTP,   KC_VOLD,    KC_VOLU,                            KC_MPLY,                             KC_VOLD, KC_VOLU, KC_TRNS, KC_NO),
	
  [_L2] = LAYOUT_60_ansi(    
			KC_ESC, RGB_M_P,  RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, RGB_M_K, RGB_M_X, RGB_M_G, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
			KC_NO,   RGB_HUD,  RGB_HUI,  KC_NO,   KC_NO,    KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
            KC_NO,    RGB_SAD,  RGB_SAI,  KC_NO,   KC_NO,    KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, 
            KC_NO,     RGB_VAD,  RGB_VAI,  KC_NO,   KC_NO,    KC_NO,    KC_NO,   KC_NO,   KC_NO,   RGB_SPD, RGB_SPI, KC_NO, 
            KC_NO,    KC_NO,    KC_NO,                             RGB_TOG,                           KC_TRNS, KC_NO, KC_NO, DB_TOGG)
};




