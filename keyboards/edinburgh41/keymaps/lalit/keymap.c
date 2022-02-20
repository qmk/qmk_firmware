// Copyright 2022 Lalit Mistry (@schwarzer-geiger)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#ifdef THUMBSTICK_ENABLE
#    include "thumbstick.h"
#endif

enum layer_names {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST
};

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define ADJUST MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_edinburgh41(
    KC_ESC,   KC_Q,     KC_W,     KC_E,     KC_R,      KC_T,               KC_Z,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,
    MT(MOD_LALT, KC_TAB),  KC_A,     KC_S,     KC_D,     KC_F,      KC_G,               KC_H,     KC_J,     KC_K,     KC_L,     KC_QUOTE,  KC_ENTER,
    RALT(KC_TAB),  KC_Y,     KC_X,     KC_C,     KC_V,      KC_B,               KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_SCLN,
                                            KC_LCTL,   KC_LSFT,    KC_NO,   KC_SPC,    LOWER
  ),
  
  [_LOWER] = LAYOUT_edinburgh41(
    _______,  KC_TRNS,  KC_LBRC,    KC_RBRC,  KC_VOLD,    KC_VOLU,            KC_TRNS,  RGUI(KC_E),  KC_MINUS,  KC_KP_PLUS,  KC_TRNS,  RGUI(LSFT(KC_S)),
    _______,  KC_1,  KC_2,  KC_3,  KC_4,   KC_5,            KC_6,  KC_7,  KC_8,    KC_9,  KC_0,   KC_DEL,
    _______,  KC_TRNS,   LSFT(KC_LBRC),  LSFT(KC_RBRC),  KC_TRNS,   KC_TRNS,            KC_TRNS,  KC_EQUAL,   LSFT(KC_SCLN),  KC_TRNS,  KC_TRNS,  KC_TRNS,
                                            KC_LCTL,   KC_LSFT,  RESET,   _______,  KC_RGUI
  ),
  
  [_RAISE] = LAYOUT_edinburgh41(
    _______,  KC_1,     KC_2,     KC_3,     KC_4,      KC_5,               KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_DEL,
    _______,  KC_MINS,  KC_EQL,   KC_LBRC,  KC_RBRC,   KC_BSLS,            KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,
    _______,  KC_ESC,   KC_RGUI,  KC_RALT,  KC_CAPS,   KC_QUOT,            KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,
                                            _______,   _______,  KC_BSPC,  _______,  _______
  ),
  
  [_ADJUST] = LAYOUT_edinburgh41(
    RGB_VAI,   RGB_SAI, RGB_HUI,  RGB_MOD,  XXXXXXX,   RGB_TOG,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    RGB_VAD,   RGB_SAD, RGB_HUD,  RGB_RMOD, XXXXXXX,   XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,   XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,            RESET,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                            _______,   _______,  XXXXXXX,  _______,  _______
  ),
};

// This function controls thumbstick functionality depending on active layer
uint32_t layer_state_set_user(uint32_t state) {
  
  thumbstick_keycodes_t input_keycodes;
  
  switch (biton32(state)) {
    
    // For every layer you want the thumbstick to do something on, add a case. You have three choices for the behaviour on a layer.
    // Mouse behaviour: Copy the content of the case _BASE.
    // Keypress behaviour: Copy the content of the case _RAISE. Set input_keycodes.keycode_up = to the keycode you want to press when moving the thumbstick up etc.
    // Scroll behaviour: Copy the content of the case _LOWER.
    case _BASE:
      thumbstick_mode_set(THUMBSTICK_MODE_MOUSE);
      break;
    
    case _RAISE:
      input_keycodes.keycode_up = KC_UP;
      input_keycodes.keycode_down = KC_DOWN;
      input_keycodes.keycode_left = KC_LEFT;
      input_keycodes.keycode_right = KC_RIGHT;
      thumbstick_mode_set(THUMBSTICK_MODE_KEYPRESS);
      thumbstick_keycodes_set(input_keycodes);
      break;
      
    case _LOWER:
      thumbstick_mode_set(THUMBSTICK_MODE_SCROLL);
      break;
  }
  return state;
}
