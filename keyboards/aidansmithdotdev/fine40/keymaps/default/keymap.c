// Copyright 2022 Aidan Smith (@Aidan-OS)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

enum keyboard_layers {
	_MAIN,
	_RIGHT,
	_LEFT,
	_TAB,
};

#define LT3_TAB LT(_TAB, KC_TAB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_MAIN] = LAYOUT_2u_single_space(
    KC_ESC  , KC_Q    , KC_W    , KC_E    , KC_R      , KC_T   , KC_Y       , KC_U    , KC_I    , KC_O   , KC_P     , KC_BSPC ,
    LT3_TAB , KC_A    , KC_S    , KC_D    , KC_F      , KC_G   , KC_H       , KC_J    , KC_K    , KC_L   , KC_SCLN  , KC_QUOT ,
    KC_LSFT , KC_Z    , KC_X    , KC_C    , KC_V      , KC_B   , KC_N       , KC_M    , KC_COMM , KC_DOT , KC_SLSH  , KC_ENT  ,
    KC_LCTL , KC_RALT , KC_LGUI , KC_BSLS , MO(_LEFT) , KC_SPC , MO(_RIGHT) , KC_LEFT , KC_DOWN , KC_UP  , KC_RIGHT , KC_MPLY
),

[_LEFT] = LAYOUT_2u_single_space( /* LEFT */
  KC_GRV  , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , KC_6    , KC_7          , KC_8    , KC_9                , KC_0                 , KC_DELETE ,
  _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_UNDERSCORE , KC_PLUS , KC_LEFT_CURLY_BRACE , KC_RIGHT_CURLY_BRACE , _______   ,
  _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______       , _______ , _______             , _______              , _______   ,
  _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_HOME       , KC_PGDN , KC_PGUP             , KC_END               , _______
),

[_RIGHT] = LAYOUT_2u_single_space( /* RIGHT */
  KC_TILDE , KC_EXCLAIM , KC_AT   , KC_HASH , KC_DOLLAR , KC_PERCENT , KC_CIRCUMFLEX , KC_AMPERSAND , KC_ASTERISK , KC_LEFT_PAREN , KC_RIGHT_PAREN , KC_DELETE ,
  _______  , _______    , _______ , _______ , _______   , _______    , _______       , KC_MINS      , KC_EQL      , KC_LBRC       , KC_RBRC        , _______   ,
  _______  , _______    , _______ , _______ , _______   , _______    , _______       , _______      , KC_LT       , KC_GT         , _______        , _______   ,
  _______  , _______    , _______ , _______ , _______   , _______    , _______       , KC_MUTE      , KC_VOLD     , KC_VOLU       , KC_MPLY        , _______
),

[_TAB] = LAYOUT_2u_single_space( /* Tab */
  KC_ESC  , QK_BOOT, _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
  _______ , KC_F11  , KC_F12  , KC_F13  , KC_F14  , KC_F15  , KC_F16  , KC_F17  , KC_F18  , KC_F19  , KC_F20  , _______ ,
  _______ , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10  , _______ ,
  _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_MS_L , KC_MS_D , KC_MS_U , KC_MS_R , _______
),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_MAIN] =  { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_LEFT] =  { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_RIGHT] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_TAB] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
};
#endif