// Copyright 2022 Cable Car Designs (@westfoxtrot)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

enum custom_layers {
    _MA,
    _F1,
};

const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 1, HSV_GREEN}
);

const rgblight_segment_t PROGMEM my_numlock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {2, 1, HSV_BLUE}
);

const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_RED}
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_capslock_layer,
    my_numlock_layer,
    my_layer1_layer
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    rgblight_set_layer_state(1, led_state.num_lock);
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(2, layer_state_cmp(state, _F1));
    return state;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_MA] = LAYOUT_all( /* Base */
  KC_ESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS, KC_EQL, KC_BSPC, KC_NO, 	 	KC_NUM, KC_PSLS, KC_PAST, KC_PMNS,
  KC_TAB,    RGB_TOG,   RGB_MODE_RGBTEST,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC, KC_RBRC,	    KC_BSLS, 	 	KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
  KC_CAPS,    KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,	KC_QUOT,KC_NO,     KC_ENT,  	 	KC_P4,   KC_P5,   KC_P6,   KC_PEQL,
  KC_LSFT,KC_NO ,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT,  KC_SLSH,        KC_RSFT,        KC_UP,  	KC_P1,   KC_P2,   KC_P3,   KC_PENT,
  KC_LCTL, KC_LGUI,KC_LALT,                    KC_SPC,KC_SPC,KC_SPC,        KC_RALT,KC_RALT,MO(_F1),              KC_LEFT,KC_DOWN,KC_RGHT,    KC_P0,   KC_PDOT, KC_BSPC),

[_F1] = LAYOUT_all( /* Function Layer */
  QK_BOOT,   KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11,  KC_F12, KC_DEL , _______,       _______, _______, _______, _______,
  _______,   BL_TOGG,BL_STEP,BL_ON,BL_OFF,BL_INC,BL_DEC,BL_BRTG,_______,_______,_______,_______, _______,	    _______, 	 	    _______, _______, _______, _______,
  _______,    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,  _______,_______,  _______,  	 	_______, _______, _______, _______,
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______, _______,        _______,       _______, 	_______, _______, _______, _______,
  _______, _______,_______,                    _______,_______,_______,        _______,_______,_______,          _______,_______,_______,    _______, _______, _______),

};
