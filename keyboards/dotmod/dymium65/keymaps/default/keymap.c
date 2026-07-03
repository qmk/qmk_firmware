/* Copyright 2023 Finalkey
 * Copyright 2023 LiWenLiu <https://github.com/LiuLiuQMK>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

// Layer names
enum ats_layers{
  // - Base layer:
  _BASE,
  // - Symbols, numbers, and functions:
  _FN,
  // - Alternate Function layer:
  _LN,
  // - Alternate Function layer:
  _MT
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
    KC_ESC,        KC_1,        KC_2,        KC_3,  KC_4,  KC_5,  KC_6,      KC_7,  KC_8,  KC_9,         KC_0,         KC_MINUS,        KC_EQUAL,         KC_BACKSPACE,   KC_AUDIO_MUTE,
    KC_TAB,        KC_Q,        KC_W,        KC_E,  KC_R,  KC_T,  KC_Y,      KC_U,  KC_I,  KC_O,         KC_P,         KC_LEFT_BRACKET, KC_RIGHT_BRACKET, KC_BACKSLASH,   KC_PAGE_UP,
    KC_CAPS_LOCK,  KC_A,        KC_S,        KC_D,  KC_F,  KC_G,  KC_H,      KC_J,  KC_K,  KC_L,         KC_SEMICOLON, KC_QUOTE,                          KC_ENTER,       KC_PAGE_DOWN,
    KC_LEFT_SHIFT,              KC_Z,        KC_X,  KC_C,  KC_V,  KC_B,      KC_N,  KC_M,  KC_COMMA,     KC_DOT,       KC_SLASH,                          KC_RIGHT_SHIFT, KC_UP,
    KC_LEFT_CTRL,  KC_LEFT_GUI, KC_LEFT_ALT,                      KC_SPACE,                KC_RIGHT_ALT, MO(_FN),                       KC_RIGHT_CTRL,    KC_LEFT,        KC_DOWN,        KC_RIGHT
    ),
    [_FN] = LAYOUT(
    KC_GRAVE,      KC_F1,       KC_F2,       KC_F3, KC_F4, KC_F5, KC_F6,     KC_F7, KC_F8, KC_F9,        KC_F10,       KC_F11,          KC_F12,           KC_BACKSPACE,   KC_TRNS,
    RM_TOGG,       KC_Q,        KC_W,        KC_E,  KC_R,  KC_T,  KC_Y,      KC_U,  KC_I,  KC_O,         KC_P,         RM_HUEU,         RM_HUED,          KC_BACKSLASH,   KC_TRNS,
    KC_CAPS_LOCK,  KC_A,        KC_S,        KC_D,  KC_F,  KC_G,  KC_H,      KC_J,  KC_K,  KC_L,         RM_SATD,      RM_SATU,                           KC_ENTER,       KC_TRNS,
    KC_LEFT_SHIFT,              KC_Z,        KC_X,  KC_C,  KC_V,  KC_B,      KC_N,  KC_M,  KC_COMMA,     MO(_LN),      KC_SLASH,                          KC_RIGHT_SHIFT, RM_VALU,
    KC_LEFT_CTRL,  KC_LEFT_GUI, KC_LEFT_ALT,                      KC_SPACE,                RM_NEXT,      _______,                       KC_RIGHT_CTRL,    RM_SPDD,        RM_VALD,        RM_SPDU
    ),
    [_LN] = LAYOUT(
    KC_ESC,        KC_1,        KC_2,        KC_3,  KC_4,  KC_5,  KC_6,      KC_7,  KC_8,  KC_9,         KC_0,         KC_MINUS,        KC_EQUAL,         KC_BACKSPACE,   KC_TRNS,
    KC_TAB,        KC_Q,        KC_W,        KC_E,  KC_R,  KC_T,  KC_Y,      KC_U,  KC_I,  KC_O,         KC_P,         KC_LEFT_BRACKET, KC_RIGHT_BRACKET, KC_BACKSLASH,   KC_TRNS,
    KC_CAPS_LOCK,  KC_A,        KC_S,        KC_D,  KC_F,  KC_G,  KC_H,      KC_J,  KC_K,  KC_L,         KC_SEMICOLON, KC_QUOTE,                          KC_ENTER,       KC_TRNS,
    KC_LEFT_SHIFT,              KC_Z,        KC_X,  KC_C,  KC_V,  KC_B,      KC_N,  KC_M,  MO(_MT),      _______,      KC_SLASH,                          KC_RIGHT_SHIFT, KC_UP,
    KC_LEFT_CTRL,  KC_LEFT_GUI, KC_LEFT_ALT,                      KC_SPACE,                KC_RIGHT_ALT, _______,                       KC_RIGHT_CTRL,    KC_LEFT,        KC_DOWN,        KC_RIGHT
    ),
    [_MT] = LAYOUT(
    KC_ESC,        KC_1,        KC_2,        KC_3,  KC_4,  KC_5,  KC_6,      KC_7,  KC_8,  KC_9,         KC_0,         KC_MINUS,        KC_EQUAL,         KC_BACKSPACE,   KC_TRNS,
    KC_TAB,        KC_Q,        KC_W,        KC_E,  KC_R,  KC_T,  KC_Y,      KC_U,  KC_I,  KC_O,         KC_P,         KC_LEFT_BRACKET, KC_RIGHT_BRACKET, KC_BACKSLASH,   KC_TRNS,
    KC_CAPS_LOCK,  KC_A,        KC_S,        KC_D,  KC_F,  KC_G,  KC_H,      KC_J,  KC_K,  KC_L,         KC_SEMICOLON, KC_QUOTE,                          KC_ENTER,       KC_TRNS,
    KC_LEFT_SHIFT,              KC_Z,        KC_X,  KC_C,  KC_V,  KC_B,      KC_N,  KC_M,  _______,      _______,      KC_SLASH,                          KC_RIGHT_SHIFT, KC_UP,
    KC_LEFT_CTRL,  KC_LEFT_GUI, KC_LEFT_ALT,                      KC_SPACE,                KC_RIGHT_ALT, _______,                       KC_RIGHT_CTRL,    KC_LEFT,        KC_DOWN,        KC_RIGHT
    )
};


#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] =   { ENCODER_CCW_CW(KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP) },
    [_FN] =     { ENCODER_CCW_CW(RM_VALD, RM_VALU) },
    [_LN] =     { ENCODER_CCW_CW(RM_SATD, RM_SATU) },
    [_MT] =     { ENCODER_CCW_CW(RM_SPDD, RM_SPDU) },
};
#endif
