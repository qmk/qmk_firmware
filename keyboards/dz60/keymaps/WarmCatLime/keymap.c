#include "dz60.h"
#include "action_layer.h"

// Standard layout with split shift and backspace but with HHKB function layer.
#define _DEFAULT 0
#define _FN 1
#define _LIGHTS 2

#define ______ KC_TRNS

bool caps_is_active = false;

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
        switch(id) {
            case 0:
                if (record->event.pressed) {
                    if (caps_is_active) {
                        backlight_level(0);
                        register_code(KC_CAPSLOCK);
                        unregister_code(KC_CAPSLOCK);
                        caps_is_active = false;
                    } else {
                        backlight_level(1);
                        register_code(KC_CAPSLOCK);
                        unregister_code(KC_CAPSLOCK);
                        caps_is_active = true;
                    }
                }
            break;
    }
    return MACRO_NONE;
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_DEFAULT] = KEYMAP(
		KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_BSLS,  KC_GRV,
		KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC, KC_RBRC, KC_BSPC,
		MO(_FN),          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT, KC_ENT,
		KC_LSFT, KC_NO,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,           KC_RSFT, MO(_FN), 
		KC_LCTL, KC_LGUI,  KC_LALT, KC_SPC, KC_SPC,        KC_SPC,                            KC_RALT,  KC_RGUI, KC_NO, M(0),  KC_RCTL),

	[_FN] = KEYMAP(
		RGB_TOG,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,  KC_INS,  KC_DEL, 
		KC_CAPS,          ______,  ______,  ______,  ______,  ______,  ______,  ______,  KC_PSCR, KC_SLCK, KC_PAUS,  KC_UP,   ______,  RESET, 
		MO(_LIGHTS),           KC_VOLD, KC_VOLU, KC_MUTE, ______,  ______,  KC_PAST, KC_PSLS, KC_HOME, KC_PGUP, KC_LEFT,  KC_RGHT, ______,
		______,  ______,  KC_MPRV, KC_MPLY, KC_MNXT, ______,  ______,  KC_PPLS, KC_PMNS, KC_END,  KC_PGDN, KC_DOWN,           ______,  ______, 
		KC_NO,  KC_CAPS,  ______,  ______,  ______,           ______,                              ______,  ______,  ______,  ______,  ______),

	[_LIGHTS] = KEYMAP(
		RGB_TOG, RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, RGB_M_K, RGB_M_X, RGB_M_G, ______, ______, ______, ______, ______, ______, 
		RGB_MOD,          RGB_HUI, RGB_SAI, RGB_VAI,  ______,   ______,  ______,  ______,  ______, ______, ______, ______, ______, ______, 
		______,           RGB_HUD, RGB_SAD, RGB_VAD,  ______,   ______,  ______,  ______,  ______, ______, ______, ______, ______, 
		______,  ______,  BL_DEC,   BL_TOGG,  BL_INC,   ______,   ______,  ______,  ______,  ______, ______, ______,         ______, ______, 
		______,  ______,  ______,  ______,  ______,           ______,                              ______,  ______,  ______,  ______,  ______),

};


