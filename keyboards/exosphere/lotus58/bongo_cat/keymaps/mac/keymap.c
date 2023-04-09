// Copyright 2022 Markus Knutsson (@TweetyDaBird)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "bongo.h"

enum layers {
    _QWERTY,
    _SYM,
};

enum custom_keycodes {
    PR_SCR = SAFE_RANGE,
    CH_LANG,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case PR_SCR:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING(SS_DOWN(X_LSFT) SS_DELAY(10) SS_DOWN(X_LGUI) SS_DELAY(10) SS_TAP(X_4) SS_DELAY(10) SS_UP(X_LGUI) SS_DELAY(10) SS_UP(X_LSFT));
        } else {
            // when keycode QMKBEST is released
        }
        break;
    case CH_LANG:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING(SS_DOWN(X_LCTL) SS_DELAY(10) SS_DOWN(X_LALT) SS_DELAY(10) SS_TAP(X_SPC) SS_DELAY(10) SS_UP(X_LALT) SS_DELAY(10) SS_UP(X_LCTL));
        } else {
            // when keycode QMKBEST is released
        }
        break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT(
      KC_ESC, 	 KC_1, 	    KC_2,      KC_3,	  KC_4,      KC_5,  	KC_KB_MUTE,    KC_NO,      KC_6,  	 KC_7,   	KC_8,      KC_9,      KC_0,      KC_DEL,
      KC_TAB, 	 KC_Q, 	    KC_W,      KC_E,      KC_R,      KC_T,                     		       KC_Y,     KC_U,      KC_I,      KC_O,      KC_P,      KC_BSPC,
      KC_LSFT, 	 KC_A, 	    KC_S,      KC_D,      KC_F,      KC_G,                     			   KC_H, 	 KC_J,      KC_K,      KC_L,      KC_SCLN,   KC_RSFT,
      KC_LCTL,   KC_Z, 	    KC_X,      KC_C,      KC_V,      KC_B,      KC_VOLD,       KC_VOLU,    KC_N,	 KC_M,      KC_COMM,   KC_DOT,    KC_SLSH,   KC_RCTL,
                                       KC_LALT,   MO(_SYM),  KC_LGUI,   KC_ENT,        KC_SPC,     KC_RGUI,  MO(_SYM),  KC_RALT
),

[_SYM] = LAYOUT(
      _______, 	 KC_F2,	    KC_F3,     KC_F4,	  KC_F5,     KC_F6,  	KC_MPLY,       KC_NO,      KC_F7,  	 KC_F8,   	KC_F9,     KC_F10,    KC_F11,    _______,
      _______, 	 KC_F1, 	KC_UP,     KC_GRV,    KC_MINS,   KC_EQL,                   		       KC_LBRC,  KC_RBRC,   KC_QUOT,   KC_MS_U,   KC_F12,    _______,
      _______, 	 KC_LEFT,   KC_DOWN,   KC_RGHT,   S(KC_MINS),S(KC_EQL),                     	   S(KC_LBRC),S(KC_RBRC),KC_MS_L,  KC_MS_D,   KC_MS_R,   _______,
      _______,   KC_NO,     KC_NO,     KC_NO,     KC_NO,     CH_LANG,   KC_MPRV,       KC_MNXT,    PR_SCR,	 KC_BSLS,   KC_BTN1,   KC_BTN3,   KC_BTN2,   _______,
                                       _______,   _______,   _______,   _______,       _______,    _______,  _______,   _______
),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_QWERTY] = { ENCODER_CCW_CW(KC_WH_U, KC_WH_D), ENCODER_CCW_CW(KC_NO, KC_NO) },
    [_SYM] = { ENCODER_CCW_CW(KC_WH_L, KC_WH_R), ENCODER_CCW_CW(KC_NO, KC_NO) }
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
