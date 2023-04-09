// Copyright 2022 Markus Knutsson (@TweetyDaBird)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "bongo.h"

enum layers {
    _QWERTY,
    _GAME,
    _SYM,
};

enum custom_keycodes {
    KC_QWERTY = SAFE_RANGE,
    KC_NUMERIC,
    KC_FUNCTION,
	KC_SYSTEM,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT(
      KC_ESC, 	 KC_1, 	    KC_2,      KC_3,	  KC_4,      KC_5,  	KC_KB_MUTE,    KC_NO,      KC_6,  	 KC_7,   	KC_8,      KC_9,      KC_0,      KC_DEL,
      KC_TAB, 	 KC_Q, 	    KC_W,      KC_E,      KC_R,      KC_T,                     		       KC_Y,     KC_U,      KC_I,      KC_O,      KC_P,      KC_BSPC,
      KC_LSFT, 	 KC_A, 	    KC_S,      KC_D,      KC_F,      KC_G,                     			   KC_H, 	 KC_J,      KC_K,      KC_L,      KC_SCLN,   KC_RSFT,
      KC_LGUI,   KC_Z, 	    KC_X,      KC_C,      KC_V,      KC_B,      KC_VOLD,       KC_VOLU,    KC_N,	 KC_M,      KC_COMM,   KC_DOT,    KC_SLSH,   KC_RGUI,
                                       KC_LALT,   MO(_SYM),  KC_LCTL,   KC_ENT,        KC_SPC,     KC_RCTL,  MO(_SYM),  KC_RALT
),

[_GAME] = LAYOUT(
      KC_ESC, 	 KC_1, 	    KC_2,      KC_3,	  KC_4,      KC_5,  	KC_KB_MUTE,    KC_NO,      KC_6,  	 KC_7,   	KC_8,      KC_9,      KC_0,      KC_DEL,
      KC_TAB, 	 KC_Q, 	    KC_W,      KC_E,      KC_R,      KC_T,                     		       KC_Y,     KC_U,      KC_I,      KC_O,      KC_P,      KC_BSPC,
      KC_LSFT, 	 KC_A, 	    KC_S,      KC_D,      KC_F,      KC_G,                     			   KC_H, 	 KC_J,      KC_K,      KC_L,      KC_SCLN,   KC_RSFT,
      KC_LCTL,   KC_Z, 	    KC_X,      KC_C,      KC_V,      KC_B,      KC_VOLD,       KC_VOLU,    KC_N,	 KC_M,      KC_COMM,   KC_DOT,    KC_SLSH,   KC_RGUI,
                                       KC_LALT,   MO(_SYM),  KC_SPC,    KC_ENT,        KC_SPC,     KC_RCTL,  DF(_QWERTY),KC_RALT
),

[_SYM] = LAYOUT(
      _______, 	 KC_F2,	    KC_F3,     KC_F4,	  KC_F5,     KC_F6,  	KC_MPLY,       KC_NO,      KC_F7,  	 KC_F8,   	KC_F9,     KC_F10,    KC_F11,    _______,
      _______, 	 KC_F1, 	KC_UP,     KC_GRV,    KC_MINS,   KC_EQL,                   		       KC_LBRC,  KC_RBRC,   KC_QUOT,   KC_MS_U,   KC_F12,    _______,
      _______, 	 KC_LEFT,   KC_DOWN,   KC_RGHT,   S(KC_MINS),S(KC_EQL),                     	   S(KC_LBRC),S(KC_RBRC),KC_MS_L,  KC_MS_D,   KC_MS_R,   _______,
      _______,   DF(_GAME), KC_NO,     KC_NO,     KC_NO,     G(KC_SPC), KC_MPRV,       KC_MNXT,    KC_PSCR,	 KC_BSLS,   KC_BTN1,   KC_BTN3,   KC_BTN2,   _______,
                                       _______,   _______,   _______,   _______,       _______,    _______,  _______,   _______
),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_QWERTY] = { ENCODER_CCW_CW(KC_WH_U, KC_WH_D), ENCODER_CCW_CW(KC_NO, KC_NO) },
    [_GAME] = { ENCODER_CCW_CW(KC_NO, KC_NO), ENCODER_CCW_CW(KC_NO, KC_NO) },
    [_SYM] = { ENCODER_CCW_CW(KC_WH_L, KC_WH_R), ENCODER_CCW_CW(KC_NO, KC_NO) },
};
#endif

// This function allows switching to the 'hidden' layer. DO NOT EDIT!
layer_state_t layer_state_set_user(layer_state_t state) {
   return update_tri_layer_state(state, 1, 2, 3);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_left()) {
        return OLED_ROTATION_0;
    } else {
        return OLED_ROTATION_180;
    }
    return rotation;
}

bool oled_task_user(void) {
    draw_bongo();
    return false;
}
