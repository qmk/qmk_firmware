// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include QMK_KEYBOARD_H
#include "quantum.h"

#ifdef CONSOLE_ENABLE
#include <print.h>
#endif

//////////////////////////////////////////////////////////////////////////////

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    KC_ESC   , KC_1     , KC_2     , KC_3     , KC_4     , KC_5     ,                                  KC_6     , KC_7     , KC_8     , KC_9     , KC_0     , KC_MINS  ,
	KC_TAB   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                  KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_LBRC  ,
	KC_LCTL  , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                                  KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , KC_QUOTE ,
    MO(1)    , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     , KC_RBRC  ,              KC_NUHS, KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , KC_INT1  ,
	KC_LALT  , KC_LGUI  ,                  LT(1,KC_LNG2) ,LT(2,KC_SPC),                                KC_BSPC  , KC_ENT   ,                       KC_EQL   , KC_INT3  ,
                          TG(2)    ,            KC_ENT   ,       LT(3,KC_LNG1) ,             KC_LGUI            , KC_ESC   ,            KC_ENT   ,
					                                                   G(KC_C) ,             G(KC_V) ,
    LT(1,KC_LNG2),        LT(2,KC_SPC),         LT(3,KC_LNG1)       ,                                             KC_LGUI  ,            KC_BSPC  ,            KC_ENT
  ),

  [1] = LAYOUT(
    S(KC_ESC), S(KC_1)  , S(KC_2)  , S(KC_3)  , S(KC_4)  , S(KC_5)  ,                                  S(KC_6)  , S(KC_7)  , S(KC_8)  , S(KC_9)  , S(KC_0)  , S(KC_MINS),
    S(KC_TAB), S(KC_Q)  , S(KC_W)  , S(KC_E)  , S(KC_R)  , S(KC_T)  ,                                  S(KC_Y)  , S(KC_U)  , S(KC_I)  , S(KC_O)  , S(KC_P)  , S(KC_LBRC),
    S(KC_LCTL),S(KC_A)  , S(KC_S)  , S(KC_D)  , S(KC_F)  , S(KC_G)  ,                                  S(KC_H)  , S(KC_J)  , S(KC_K)  , S(KC_L)  ,S(KC_SCLN), S(KC_QUOTE),
    _______  , S(KC_Z)  , S(KC_X)  , S(KC_C)  , S(KC_V)  , S(KC_B)  ,S(KC_RBRC),           S(KC_NUHS), S(KC_N)  , S(KC_M)  ,S(KC_COMM), S(KC_DOT),S(KC_SLSH), LALT(KC_INT3),
    S(KC_LALT),S(KC_LGUI),                      _______  , _______  ,                                  _______  , _______  ,                      S(KC_EQL) , S(KC_INT3),
                          _______  ,            _______  ,             _______ ,             _______ ,            _______  ,             _______ ,
                                                                       _______ ,             _______ ,
    _______  ,            _______  ,            _______  ,                                                        _______  ,             _______ ,            _______
  ),

  [2] = LAYOUT(
    _______  , KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    ,                                  KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , KC_F11   ,
    _______  , _______  , KC_7     , KC_8     , KC_9     , _______  ,                                  _______  , KC_PGUP  , KC_UP    , KC_PGDN  , _______  , KC_F12   ,
    _______  , _______  , KC_4     , KC_5     , KC_6     ,S(KC_SCLN),                                  KC_HOME  , KC_LEFT  , KC_DOWN  , KC_RGHT  , KC_END   , _______  ,
    _______  , _______  , KC_1     , KC_2     , KC_3     ,S(KC_MINS), S(KC_8)  ,             KC_BTN4 , KC_BTN5  , KC_BTN1  , KC_BTN2  , KC_BTN3  , _______  , _______  ,
    _______  , _______                        , _______  , _______  ,                                  _______  , _______                        , _______  , _______  ,
	                      _______             , _______  ,             _______ ,             _______            , _______             , _______ ,
                                                                       _______ ,             _______ ,
    _______  ,            _______  ,            _______  ,                                                        _______  ,            _______ ,             _______
  ),

  [3] = LAYOUT(
    RGB_TOG  , _______  , _______  , _______  , _______  , _______  ,                                  RGB_M_P  , RGB_M_B  , RGB_M_R  , RGB_M_SW , RGB_M_SN , RGB_M_K  ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , _______  , _______  ,                                  RGB_M_X  , RGB_M_G  , RGB_M_T  , RGB_M_TW , _______  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , SCRL_MO  , SCRL_TO  ,                                  CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , KBC_LOAD , KBC_SAVE ,
	AM_TG    , AM_TOUT_DEC , AM_TOUT_INC ,
	                                 SCRL_INV , SCRL_DVD , SCRL_DVI , EE_CLR   ,             EE_CLR  , _______  , _______  , _______  , _______  , _______  , _______  ,
	QK_BOOT  , _______ ,                        _______  , _______  ,                                  _______  , _______  ,                       _______  , QK_BOOT  ,
                          _______  ,            _______  ,             _______ ,             _______ ,            _______  ,             _______ ,
                                                                       _______ ,             _______ ,
    _______  ,            _______  ,            _______  ,                                                        _______  ,             _______ ,            _______
  ),

  [4] = LAYOUT(
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , _______  , _______  , _______  , _______ , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , _______  , _______  , _______  , _______ , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , _______  , _______  , _______  , _______ , _______  ,
	_______  , _______  , _______  , _______  , _______  , _______  ,  _______ ,             _______ , _______  , _______  , _______  , _______  , _______ , _______  ,
	_______  , _______  ,                       _______  , _______  ,                                  _______  , _______  ,                       _______ , _______  ,
                          _______  ,            _______  ,             _______ ,             _______ ,            _______  ,             _______ ,
                                                                       _______ ,             _______ ,
    _______  ,            _______  ,            _______  ,                                                        _______  ,             _______ ,            _______
  ),

  [5] = LAYOUT(
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , _______  , _______  , _______  , _______ , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , _______  , _______  , _______  , _______ , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , _______  , _______  , _______  , _______ , _______  ,
	_______  , _______  , _______  , _______  , _______  , _______  ,  _______ ,             _______ , _______  , _______  , _______  , _______  , _______ , _______  ,
	_______  , _______  ,                       _______  , _______  ,                                  _______  , _______  ,                       _______ , _______  ,
                          _______  ,            _______  ,             _______ ,             _______ ,            _______  ,             _______ ,
                                                                       _______ ,             _______ ,
    _______  ,            _______  ,            _______  ,                                                        _______  ,             _______ ,            _______
  ),

  [6] = LAYOUT(
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , _______  , _______  , _______  , _______ , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , _______  , _______  , _______  , _______ , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , _______  , _______  , _______  , _______ , _______  ,
	_______  , _______  , _______  , _______  , _______  , _______  ,  _______ ,             _______ , _______  , _______  , _______  , _______  , _______ , _______  ,
	_______  , _______  ,                       _______  , _______  ,                                  _______  , _______  ,                       _______ , _______  ,
                          _______  ,            _______  ,             _______ ,             _______ ,            _______  ,             _______ ,
                                                                       _______ ,             _______ ,
    _______  ,            _______  ,            _______  ,                                                        _______  ,             _______ ,            _______
  ),

  [7] = LAYOUT(
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , _______  , _______  , _______  , _______ , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , _______  , _______  , _______  , _______ , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , _______  , _______  , _______  , _______ , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,  _______ ,             KC_BTN4 , KC_BTN5  , KC_BTN1  , KC_BTN2  , KC_BTN3  , _______ , _______  ,
	_______  , _______  ,                       _______  , _______  ,                                  _______  , _______  ,                       _______ , _______  ,
                          _______  ,            _______  ,             _______ ,             _______ ,            _______  ,             _______ ,
                                                                       _______ ,             _______ ,
    _______  ,            _______  ,            _______  ,                                                        _______  ,             _______ ,            _______
  ),

};
// clang-format on

// encoder logic
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = {ENCODER_CCW_CW(KC_LEFT  , KC_RGHT) , ENCODER_CCW_CW(KC_UP   , KC_DOWN  ), ENCODER_CCW_CW(KC_LEFT  , KC_RGHT) , ENCODER_CCW_CW(KC_UP   , KC_DOWN  )},
    [1] = {ENCODER_CCW_CW(S(KC_TAB), KC_TAB)  , ENCODER_CCW_CW(KC_PGUP , KC_PGDN  ), ENCODER_CCW_CW(S(KC_TAB), KC_TAB)  , ENCODER_CCW_CW(KC_PGUP , KC_PGDN  )},
    [2] = {ENCODER_CCW_CW(KC_VOLU  , KC_VOLD) , ENCODER_CCW_CW(CPI_I100, CPI_D100 ), ENCODER_CCW_CW(KC_VOLU  , KC_VOLD) , ENCODER_CCW_CW(CPI_I100, CPI_D100 )},
    [3] = {ENCODER_CCW_CW(RGB_MOD  , RGB_RMOD), ENCODER_CCW_CW(RGB_HUI , RGB_HUD  ), ENCODER_CCW_CW(RGB_MOD  , RGB_RMOD), ENCODER_CCW_CW(RGB_HUI , RGB_HUD  )},
    [4] = {ENCODER_CCW_CW(KC_LEFT  , KC_RGHT) , ENCODER_CCW_CW(KC_UP   , KC_DOWN  ), ENCODER_CCW_CW(KC_LEFT  , KC_RGHT) , ENCODER_CCW_CW(KC_UP   , KC_DOWN  )},
    [5] = {ENCODER_CCW_CW(KC_LEFT  , KC_RGHT) , ENCODER_CCW_CW(KC_UP   , KC_DOWN  ), ENCODER_CCW_CW(KC_LEFT  , KC_RGHT) , ENCODER_CCW_CW(KC_UP   , KC_DOWN  )},
    [6] = {ENCODER_CCW_CW(KC_LEFT  , KC_RGHT) , ENCODER_CCW_CW(KC_UP   , KC_DOWN  ), ENCODER_CCW_CW(KC_LEFT  , KC_RGHT) , ENCODER_CCW_CW(KC_UP   , KC_DOWN  )},
    [7] = {ENCODER_CCW_CW(KC_LEFT  , KC_RGHT) , ENCODER_CCW_CW(KC_UP   , KC_DOWN  ), ENCODER_CCW_CW(KC_LEFT  , KC_RGHT) , ENCODER_CCW_CW(KC_UP   , KC_DOWN  )},
};
#endif

#ifdef CONSOLE_ENABLE
void matrix_init_kb(void)
{
	debug_enable = true;
	debug_matrix = true;
}
#endif

#ifdef RGBLIGHT_LAYERS
const rgblight_segment_t PROGMEM rgb_layer_0[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_BLACK},
    {7, 1, HSV_BLACK}
);
const rgblight_segment_t PROGMEM rgb_layer_1[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_GREEN},
    {7, 1, HSV_GREEN}
);
const rgblight_segment_t PROGMEM rgb_layer_2[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_ORANGE},
    {7, 1, HSV_ORANGE}
);
const rgblight_segment_t PROGMEM rgb_layer_3[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_PURPLE},
    {7, 1, HSV_PURPLE}
);
const rgblight_segment_t PROGMEM rgb_layer_4[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_MAGENTA},
    {7, 1, HSV_MAGENTA}
);
const rgblight_segment_t PROGMEM rgb_layer_5[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_RED},
    {7, 1, HSV_RED}
);
const rgblight_segment_t PROGMEM rgb_layer_6[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_BLUE},
    {7, 1, HSV_BLUE}
);
const rgblight_segment_t PROGMEM rgb_layer_7[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_YELLOW},
    {7, 1, HSV_YELLOW}
);
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    rgb_layer_0,
    rgb_layer_1,
    rgb_layer_2,
    rgb_layer_3,
    rgb_layer_4,
    rgb_layer_5,
    rgb_layer_6,
    rgb_layer_7
);

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, 0));
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, layer_state_cmp(state, 3));
    rgblight_set_layer_state(4, layer_state_cmp(state, 4));
    rgblight_set_layer_state(5, layer_state_cmp(state, 5));
    rgblight_set_layer_state(6, layer_state_cmp(state, 6));
    rgblight_set_layer_state(7, layer_state_cmp(state, 7));
    return state;
}
#endif

void keyboard_post_init_user(void)
{
#if defined(CONSOLE_ENABLE)
	debug_enable = true;
#endif
#ifdef RGBLIGHT_LAYERS
	 rgblight_layers = my_rgb_layers;
#endif
}
