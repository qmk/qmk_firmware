#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_planck_grid( /* Native */
      KC_ESC,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    DF(1), 
      KC_BSPC,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
     KC_TAB,     KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
      KC_DEL,     KC_LCTL, KC_NO,   KC_LSFT, KC_LALT, KC_SPC,        KC_NO,   KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT
),	  
    [1] = LAYOUT_planck_grid( /* QWERTY->PHOTOSHOP */
      KC_DELETE,  KC_0,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    DF(0),
      KC_O,       KC_G,    KC_S,    KC_U,    KC_T,    C(KC_R),  KC_F21,  KC_F10,  KC_F11,  KC_F7,   KC_F8,   KC_F9,
      KC_TAB,     C(S(A(KC_F9))), C(S(KC_I)),  S(KC_M),  KC_F1,   A(KC_BSPC),  KC_F18,  KC_F19,  KC_F23,  KC_F20,  KC_F22,  C(S(A(KC_F12))),
      KC_COMM,    KC_DOT,  KC_R, C(KC_H), MO(2),    KC_SPC,        C(KC_S), KC_F2,   C(S(A(KC_X))),  KC_F3,   KC_F14
	  ),
    [2] = LAYOUT_planck_grid( /* PHOTOSHOP */
      KC_ESC,    C(KC_Z), C(KC_Y),   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
      KC_NO,      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   C(S(A(KC_F7))), C(S(A(KC_F8))), C(S(KC_X)), 
      KC_C,       KC_NO,  S(KC_MINS),  C(S(KC_I)),   KC_NO,   C(S(KC_BSPC)), KC_NO,   KC_NO,   KC_NO,   KC_NO,   C(S(KC_F5)), KC_NO,
      C(KC_F2),    C(S(KC_F2)), C(KC_0), C(S(KC_H)), MO(2),     KC_SPC,        C(S(KC_S)), KC_NO,   KC_NO,   KC_F24,  KC_NO
	  )
};
