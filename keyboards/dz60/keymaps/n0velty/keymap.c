#include "dz60.h"
#include "action_layer.h"

#define _______ KC_TRNS //readability

#define _DL 0 //default
#define _F1 1 //function 1
#define _F2 2 //function 2

#define KC_NOPE LALT(KC_F4) //alt+f4

#define RGB_STA RGB_M_P //rgb static
#define RGB_BRE RGB_M_B //rgb breathe
#define RGB_RAI RGB_M_R //rgb rainbow
#define RGB_SWI RGB_M_SW //rgb swirl
#define RGB_SNA RGB_M_SN //rgb snake
#define RGB_KNI RGB_M_K //rgb knight
#define RGB_GRA RGB_M_G //rgb gradient

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_DL] = LAYOUT_true_hhkb( //default Layer
	KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,  \
	KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC, \
	KC_LCTL,          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,           \
	KC_LSPO, XXXXXXX, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSPC, MO(_F1), \
	         MO(_F1),          KC_LALT,                   KC_SPC,                                      MO(_F2),          KC_RGUI),

[_F1] = LAYOUT_true_hhkb( //function Layer 1
	KC_NOPE, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,  KC_GRV,  \
	KC_BSPC,          KC_HOME, KC_UP,   KC_END,  _______, _______, _______, _______, _______, KC_PAUS, KC_PSCR, KC_UP,   KC_HOME, KC_END,  \
	KC_CAPS,          KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLU, _______, _______, _______, _______, KC_PGUP, KC_LEFT, KC_RGHT, _______,          \
	_______, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLD, _______, _______, _______, _______, KC_PGDN, KC_DOWN,          _______, _______, \
		     _______,          KC_MSEL,                   KC_MUTE,                                     _______,          _______),

[_F2] = LAYOUT_true_hhkb( //function Layer 2
	RESET,   RGB_STA, RGB_BRE, RGB_RAI, RGB_SWI, RGB_SNA, RGB_KNI, RGB_GRA, _______, _______, _______, _______, _______, KC_SLEP, KC_PWR,  \
	RGB_TOG,          RGB_HUI, RGB_SAI, RGB_VAI, _______, _______, _______, _______, _______, KC_ACL2, KC_BTN1, KC_MS_U, KC_BTN2, _______, \
	RGB_MOD,          RGB_HUD, RGB_SAD, RGB_VAD, _______, _______, _______, _______, _______, KC_ACL1, KC_MS_L, KC_MS_R, _______,          \
	BL_TOGG, XXXXXXX, BL_STEP, BL_INC,  BL_DEC,  _______, _______, _______, _______, _______, KC_ACL0, KC_MS_D,          _______, _______, \
		     _______,          _______,                   _______,                                     _______,          M(0)),

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    if (record->event.pressed) {
        switch(id) {
            case 0:
                SEND_STRING("https://www.reddit.com/r/MechanicalKeyboards/");
        }
    }
    return MACRO_NONE;
};
