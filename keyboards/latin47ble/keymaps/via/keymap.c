#include QMK_KEYBOARD_H

enum layers {
    _QWERTY,
    _FN1,
    _FN2,
};

#define KC_X0 LT(_FN2, KC_CAPS)
#define KC_X1 MO(_FN1)
#define KC_X2 MO(_FN2)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_47( 
	KC_ESC,  KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,  KC_Y,  KC_U,  KC_I,  KC_O,    KC_P,    KC_BSPC,
	KC_X0,   KC_A,  KC_S,  KC_D,  KC_F,  KC_G,  KC_H,  KC_J,  KC_K,  KC_L,    KC_SCLN, KC_ENT,
	KC_LSFT, KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,  KC_N,  KC_M, KC_COMM, KC_DOT, KC_X2, KC_DEL,
	KC_LCTL, KC_LGUI, KC_LALT,    KC_PGUP, KC_PGDOWN,      KC_SPC,       KC_X1, KC_1,  KC_2,  KC_3,  KC_4,XXX),	
    [1] = LAYOUT_47( 
	OUT_AUTO,  KC_1,  KC_2,  KC_3,  KC_4,  KC_5,  KC_6,  KC_7,  KC_8,  KC_9,    KC_0,    KC_EQL,
	KC_X0,   KC_A,  KC_S,  KC_D,  KC_F,  KC_G,  KC_H,  KC_J,  KC_K,  KC_L,    KC_SCLN, KC_ENT,
	KC_LSFT, KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,  KC_N,  KC_M, KC_COMM, KC_DOT, RGB_TOG, KC_DEL,
	KC_LCTL, KC_LGUI, KC_LALT,    KC_PGUP, KC_PGDOWN,      KC_SPC,       KC_X1, RGB_TOG, RGB_MOD,  KC_MY_COMPUTER,KC_CALCULATOR,XXX),	
    [2] = LAYOUT_47( 
	KC_NUMLOCK,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,    KC_F10,    KC_BSPC,
	KC_X0,   KC_A,  KC_S,  KC_D,  KC_F,  KC_G,  KC_H,  KC_J,  KC_K,  KC_L,    KC_SCLN, KC_ENT,
	KC_LSFT, KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,  KC_N,  KC_M, KC_COMM, KC_DOT, RGB_TOG, KC_DEL,
	KC_LCTL, KC_LGUI, KC_LALT,    KC_PGUP, KC_PGDOWN,      KC_SPC,       KC_X1, RGB_TOG, RGB_MOD,  KC_MY_COMPUTER,KC_CALCULATOR,XXX),	
};
