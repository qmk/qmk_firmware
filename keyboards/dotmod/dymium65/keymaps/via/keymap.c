// Copyright 2023 <felix@fjlaboratories.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
  _BASE,
  _FN,
  _LN,
  _MT
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
    KC_ESC,                            
                   KC_1,        KC_2,        KC_3,  KC_4,  KC_5,  KC_6,      KC_7,  KC_8,  KC_9,         KC_0,         KC_MINUS,        KC_EQUAL,         KC_BACKSPACE,      
    KC_TAB,        KC_Q,        KC_W,        KC_E,  KC_R,  KC_T,  KC_Y,      KC_U,  KC_I,  KC_O,         KC_P,         KC_LEFT_BRACKET, KC_RIGHT_BRACKET, KC_BACKSLASH,            
    KC_CAPS_LOCK,  KC_A,        KC_S,        KC_D,  KC_F,  KC_G,  KC_H,      KC_J,  KC_K,  KC_L,         KC_SEMICOLON, KC_QUOTE,                          KC_ENTER,       KC_PAGE_UP,     KC_PAGE_DOWN,
    KC_LEFT_SHIFT,              KC_Z,        KC_X,  KC_C,  KC_V,  KC_B,      KC_N,  KC_M,  KC_COMMA,     KC_DOT,       KC_SLASH,                          KC_RIGHT_SHIFT, KC_UP,          KC_AUDIO_MUTE,
    KC_LEFT_CTRL,  KC_LEFT_GUI, KC_LEFT_ALT,                      KC_SPACE,                KC_RIGHT_ALT, MO(_FN),                       KC_RIGHT_CTRL,    KC_LEFT,        KC_DOWN,        KC_RIGHT
    ),
    [_FN] = LAYOUT(
    KC_GRAVE,                            
                   KC_F1,       KC_F2,       KC_F3, KC_F4, KC_F5, KC_F6,     KC_F7, KC_F8, KC_F9,        KC_F10,       KC_F11,          KC_F12,           KC_BACKSPACE,
    RGB_TOG,       KC_Q,        KC_W,        KC_E,  KC_R,  KC_T,  KC_Y,      KC_U,  KC_I,  KC_O,         KC_P,         RGB_HUI,         RGB_HUD,          KC_BACKSLASH,            
    KC_CAPS_LOCK,  KC_A,        KC_S,        KC_D,  KC_F,  KC_G,  KC_H,      KC_J,  KC_K,  KC_L,         RGB_SAD,      RGB_SAI,                           KC_ENTER,       KC_PAGE_UP,     KC_PAGE_DOWN,
    KC_LEFT_SHIFT,              KC_Z,        KC_X,  KC_C,  KC_V,  KC_B,      KC_N,  KC_M,  KC_COMMA,     MO(_LN),      KC_SLASH,                          KC_RIGHT_SHIFT, RGB_VAI,        KC_AUDIO_MUTE,
    KC_LEFT_CTRL,  KC_LEFT_GUI, KC_LEFT_ALT,                      KC_SPACE,                RGB_MOD,      _______,                       KC_RIGHT_CTRL,    RGB_SPD,        RGB_VAD,        RGB_SPI
    ),                                                                                                                      
    [_LN] = LAYOUT(
    KC_ESC,                            
                   KC_1,        KC_2,        KC_3,  KC_4,  KC_5,  KC_6,      KC_7,  KC_8,  KC_9,         KC_0,         KC_MINUS,        KC_EQUAL,         KC_BACKSPACE,
    KC_TAB,        KC_Q,        KC_W,        KC_E,  KC_R,  KC_T,  KC_Y,      KC_U,  KC_I,  KC_O,         KC_P,         KC_LEFT_BRACKET, KC_RIGHT_BRACKET, KC_BACKSLASH,            
    KC_CAPS_LOCK,  KC_A,        KC_S,        KC_D,  KC_F,  KC_G,  KC_H,      KC_J,  KC_K,  KC_L,         KC_SEMICOLON, KC_QUOTE,                          KC_ENTER,       KC_PAGE_UP,     KC_PAGE_DOWN,
    KC_LEFT_SHIFT,              KC_Z,        KC_X,  KC_C,  KC_V,  KC_B,      KC_N,  KC_M,  MO(_MT),      _______,      KC_SLASH,                          KC_RIGHT_SHIFT, KC_UP,          KC_AUDIO_MUTE,
    KC_LEFT_CTRL,  KC_LEFT_GUI, KC_LEFT_ALT,                      KC_SPACE,                KC_RIGHT_ALT, _______,                       KC_RIGHT_CTRL,    KC_LEFT,        KC_DOWN,        KC_RIGHT
    ),
    [_MT] = LAYOUT(
    KC_ESC,                            
                   KC_1,        KC_2,        KC_3,  KC_4,  KC_5,  KC_6,      KC_7,  KC_8,  KC_9,         KC_0,         KC_MINUS,        KC_EQUAL,         KC_BACKSPACE,
    KC_TAB,        KC_Q,        KC_W,        KC_E,  KC_R,  KC_T,  KC_Y,      KC_U,  KC_I,  KC_O,         KC_P,         KC_LEFT_BRACKET, KC_RIGHT_BRACKET, KC_BACKSLASH,            
    KC_CAPS_LOCK,  KC_A,        KC_S,        KC_D,  KC_F,  KC_G,  KC_H,      KC_J,  KC_K,  KC_L,         KC_SEMICOLON, KC_QUOTE,                          KC_ENTER,       KC_PAGE_UP,     KC_PAGE_DOWN,
    KC_LEFT_SHIFT,              KC_Z,        KC_X,  KC_C,  KC_V,  KC_B,      KC_N,  KC_M,  _______,      _______,      KC_SLASH,                          KC_RIGHT_SHIFT, KC_UP,          KC_AUDIO_MUTE,
    KC_LEFT_CTRL,  KC_LEFT_GUI, KC_LEFT_ALT,                      KC_SPACE,                KC_RIGHT_ALT, _______,                       KC_RIGHT_CTRL,    KC_LEFT,        KC_DOWN,        KC_RIGHT
    )
};

bool rgb_matrix_indicators_user(void) {
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(LED_CAP_LOCK_INDEX, RGB_WHITE);
    }
    return false;
}

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_BASE] =   { ENCODER_CCW_CW(KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP) },
    [_FN] =     { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
    [_LN] =     { ENCODER_CCW_CW(RGB_SAD, RGB_SAI) },
    [_MT] =     { ENCODER_CCW_CW(RGB_SPD, RGB_SPI) },
};
#endif
