
#include QMK_KEYBOARD_H
enum layers {
    /* _M_XYZ = Mac Os, _W_XYZ S= Win/Linux */
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT( 
		KC_Q,        KC_W,    KC_E,    KC_R,   KC_T,       KC_Y,       KC_U,    KC_I,    KC_O,   KC_P, 
		LSFT_T(KC_A),KC_S,    KC_D,    KC_F,   KC_G,       KC_H,       KC_J,    KC_K,    KC_L,   RSFT_T(KC_SCLN), 
		KC_Z,        KC_X,    KC_C,    KC_V,   KC_B,       KC_N,       KC_M,    KC_COMM, KC_DOT, KC_SLSH, 
		_______,     KC_LGUI, KC_LALT, KC_LCTL,KC_SPC,     KC_ENT,     KC_RCTL, KC_LBRC, KC_RBRC,_______,
		_______,     KC_U,    KC_I,    KC_O,   MO(_LOWER), MO(_RAISE), KC_H,    KC_J, 	 KC_K,	 _______
	),
    [_LOWER] = LAYOUT(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5, KC_F6,   KC_F7,  KC_F8,  KC_F9,  KC_F10, 
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,  KC_X,    KC_Y, 	KC_Z, 	KC_Q, 	KC_PSLS,
    KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC, KC_CIRC, KC_KP_4, KC_KP_5, KC_KP_6, KC_PAST,
    KC_EQL, KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR, KC_LBRC, KC_KP_1, KC_KP_2, KC_KP_3, KC_PMNS,
    _______, _______, _______, _______, _______, _______, _______, KC_KP_0, KC_DOT,  KC_PPLS

	),
	[_RAISE] = LAYOUT(
    _______, _______, _______, _______, _______,_______, _______,DB_TOGG, _______,_______,
    KC_INS, KC_PSCR, KC_APP , _______, _______, KC_PGUP, _______,   KC_UP, _______, _______,
    KC_LALT, KC_LCTL, KC_LSFT, _______, KC_CAPS, KC_PGDN,  KC_LEFT,KC_DOWN, KC_RGHT,  KC_DEL,
    KC_UNDO, KC_CUT,  KC_COPY, KC_PASTE,_______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

	[_ADJUST] = LAYOUT(
        XXXXXXX,  XXXXXXX, _______, _______, _______, _______, XXXXXXX, _______, _______, _______,  
        QK_BOOT,  XXXXXXX, _______, _______, _______, _______, XXXXXXX, _______, _______, _______,  
        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______,
        QK_REBOOT,XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        XXXXXXX,  XXXXXXX, _______, _______, _______, _______, _______, _______, _______, _______
	)
};

