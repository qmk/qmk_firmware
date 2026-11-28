/* Copyright 2021 @ Keychron (https://www.keychron.com)
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

// clang-format off

enum layers{
    MAC_BASE,
    WIN_BASE,
    _FN1,
    _FN2,
    _FN3
};

#define KC_TASK LGUI(KC_TAB)
#define KC_FLXP LGUI(KC_E)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Blank
 * ,------------------------------------------------,      ,-------------------------------------------------------,                                  ,------,
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |             |                                  |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------+------|                                  `------'
 * |             |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------+------|                                  ,------,
 * |             |      |      |      |      |      |      |      |      |      |      |      |      |             |                                  |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------+------|             ,------,             |------|
 * |             |      |      |      |      |      |      |      |      |      |      |      |      |      |      |             |      |             |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------+------'      ,------+------+------,      `------'
 * |      |      |      |      |             |      |      |      |             |      |                                  |      |      |      |
 * `--------------      ----------------------------'      `---------------------------'                                  `------+------+------'
 */
[_BLANK] = LAYOUT_ansi_69(
    _______, _______,  _______,  _______, _______, _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______,          _______,
    _______, _______,  _______,  _______, _______, _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______,          _______,
    _______, _______,  _______,  _______, _______, _______,           _______, _______, _______, _______,  _______,  _______,  _______,          _______,
    _______,           _______,  _______, _______, _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______, _______,
    _______, _______,  _______,           _______,          _______,  _______,          _______,           _______,            _______, _______, _______
),

/* Mac Base
 * ,------------------------------------------------,      ,-------------------------------------------------------,                                  ,------,
 * | Esc  |  1   |  2   |  3   |  4   |  5   |  6   |  7   |  8   |  9   |  0   |  -   |  =   | Bspc |             |                                  | Mute |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------+------|                                  `------'
 * | Tab         |  Q   |  W   |  E   |  R   |  T   |  Y   |  U   |  I   |  O   |  P   |  [   |  ]   |  \   |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------+------|                                  ,------,
 * | Caps        |  A   |  S   |  D   |  F   |  G   |  H   |  J   |  K   |  L   |  ;   |  '   | Enter       |                                  | Home |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------+------|             ,------,             |------|
 * | Shift       |  Z   |  X   |  C   |  V   |  B   |  B   |  N   |  M   |  ,   |  .   |  /   | Shift| Up   |             |      |             |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------+------'      ,------+------+------,      `------'
 * | Ctrl | Opt  |      | Cmd  |             |      |      |      |             |      |                                  | LCmd | Left | Down | Rght |
 * `--------------      ----------------------------'      `---------------------------'                                  `------+------+------'
 */
[MAC_BASE] = LAYOUT_ansi_69(
    KC_ESC,  KC_1,     KC_2,     KC_3,    KC_4,    KC_5,    KC_6,     KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,          KC_MUTE,
    KC_TAB,  KC_Q,     KC_W,     KC_E,    KC_R,    KC_T,    KC_Y,     KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,          KC_DEL,
    KC_CAPS, KC_A,     KC_S,     KC_D,    KC_F,    KC_G,              KC_H,    KC_J,    KC_K,    KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,           KC_HOME,
    KC_LSFT,           KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,     KC_B,    KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT, KC_UP,
    KC_LCTL, KC_LOPT,  KC_LCMD,           KC_SPC,           MO(_FN1), MO(_FN3),         KC_SPC,            KC_RCMD,            KC_LEFT, KC_DOWN, KC_RGHT
),

/* Windows Base
 * ,------------------------------------------------,      ,-------------------------------------------------------,                                  ,------,
 * | Esc  |  1   |  2   |  3   |  4   |  5   |  6   |  7   |  8   |  9   |  0   |  -   |  =   | Bspc |             |                                  | Mute |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------+------|                                  `------'
 * | Tab         |  Q   |  W   |  E   |  R   |  T   |  Y   |  U   |  I   |  O   |  P   |  [   |  ]   |  \   |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------+------|                                  ,------,
 * | Caps        |  A   |  S   |  D   |  F   |  G   |  H   |  J   |  K   |  L   |  ;   |  '   | Enter       |                                  | Home |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------+------|             ,------,             |------|
 * | Shift       |  Z   |  X   |  C   |  V   |  B   |  B   |  N   |  M   |  ,   |  .   |  /   | Shift| Up   |             |      |             |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------+------'      ,------+------+------,      `------'
 * | Ctrl | Win  | Alt  |      |             |      |      |      |             |      |                                  | RAlt | Left | Down | Rght |
 * `--------------      ----------------------------'      `---------------------------'                                  `------+------+------'
 */
[WIN_BASE] = LAYOUT_ansi_69(
    KC_ESC,  KC_1,     KC_2,     KC_3,    KC_4,    KC_5,    KC_6,     KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,          KC_MUTE,
    KC_TAB,  KC_Q,     KC_W,     KC_E,    KC_R,    KC_T,    KC_Y,     KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,          KC_DEL,
    KC_CAPS, KC_A,     KC_S,     KC_D,    KC_F,    KC_G,              KC_H,    KC_J,    KC_K,    KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,           KC_HOME,
    KC_LSFT,           KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,     KC_B,    KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT, KC_UP,
    KC_LCTL, KC_LWIN,  KC_LALT,           KC_SPC,           MO(_FN2), MO(_FN3),         KC_SPC,            KC_RALT,            KC_LEFT, KC_DOWN, KC_RGHT
),

/* Mac Function 1
 * ,------------------------------------------------,      ,-------------------------------------------------------,                                  ,------,
 * |  `   | Br-  | Br+  |      |      | RGB- | RGB+ | Prev | Play | Next | Mute | Vol- | Vol+ |      |             |                                  | RGB  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------+------|                                  `------'
 * |             | RGB  | Mode | Hue+ | Sat+ | Spd+ |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------+------|                                  ,------,
 * |             |      | RGB- | Hue- | Sat- | Spd- |      |      |      |      |      |      |      |             |                                  |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------+------|             ,------,             |------|
 * |             |      |      |      |      |      |      |      | NKRO |      |      |      |      |      |      |             |      |             |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------+------'      ,------+------+------,      `------'
 * |      |      |      |      |             |      |      |      |             |      |                                  |      |      |      |
 * `--------------      ----------------------------'      `---------------------------'                                  `------+------+------'
 */
[_FN1] = LAYOUT_ansi_69(
    KC_GRV,  KC_BRID,  KC_BRIU,  KC_NO,   KC_NO,   RGB_VAD, RGB_VAI,  KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,          RGB_TOG,
    RGB_TOG, RGB_MOD,  RGB_VAI,  RGB_HUI, RGB_SAI, RGB_SPI, _______,  _______, _______, _______, _______,  _______,  _______,  _______,          _______,
    _______, RGB_RMOD, RGB_VAD,  RGB_HUD, RGB_SAD, RGB_SPD,           _______, _______, _______, _______,  _______,  _______,  _______,          _______,
    _______,           _______,  _______, _______, _______, _______,  _______, NK_TOGG, _______, _______,  _______,  _______,  _______, _______,
    _______, _______,  _______,           _______,          _______,  _______,          _______,           _______,            _______, _______, _______
),

/* Windows Function 2
 * ,------------------------------------------------,      ,-------------------------------------------------------,                                  ,------,
 * |  `   | Br-  | Br+  | Task | Expl | RGB- | RGB+ | Prev | Play | Next | Mute | Vol- | Vol+ |      |             |                                  | RGB  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------+------|                                  `------'
 * |             | RGB  | Mode | Hue+ | Sat+ | Spd+ |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------+------|                                  ,------,
 * |             |      | RGB- | Hue- | Sat- | Spd- |      |      |      |      |      |      |      |             |                                  |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------+------|             ,------,             |------|
 * |             |      |      |      |      |      |      |      | NKRO |      |      |      |      |      |      |             |      |             |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------+------'      ,------+------+------,      `------'
 * |      |      |      |      |             |      |      |      |             |      |                                  |      |      |      |
 * `--------------      ----------------------------'      `---------------------------'                                  `------+------+------'
 */
[_FN2] = LAYOUT_ansi_69(
    KC_GRV,  KC_BRID,  KC_BRIU,  KC_TASK, KC_FLXP, RGB_VAD, RGB_VAI,  KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,          RGB_TOG,
    RGB_TOG, RGB_MOD,  RGB_VAI,  RGB_HUI, RGB_SAI, RGB_SPI, _______,  _______, _______, _______, _______,  _______,  _______,  _______,          _______,
    _______, RGB_RMOD, RGB_VAD,  RGB_HUD, RGB_SAD, RGB_SPD,           _______, _______, _______, _______,  _______,  _______,  _______,          _______,
    _______,           _______,  _______, _______, _______, _______,  _______, NK_TOGG, _______, _______,  _______,  _______,  _______, _______,
    _______, _______,  _______,           _______,          _______,  _______,          _______,           _______,            _______, _______, _______
),

/* Function 3
 * ,------------------------------------------------,      ,-------------------------------------------------------,                                  ,------,
 * |  ~   |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  | F11  | F12  |      |             |                                  |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------+------|                                  `------'
 * |             | RGB  | Mode | Hue+ | Sat+ | Spd+ |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------+------|                                  ,------,
 * |             |      | RGB- | Hue- | Sat- | Spd- |      |      |      |      |      |      |      |             |                                  |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------+------|             ,------,             |------|
 * |             |      |      |      |      |      |      |      |      |      |      |      |      |      |      |             |      |             |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------+------'      ,------+------+------,      `------'
 * |      |      |      |      |             |      |      |      |             |      |                                  |      |      |      |
 * `--------------      ----------------------------'      `---------------------------'                                  `------+------+------'
 */
[_FN3] = LAYOUT_ansi_69(
    KC_TILD, KC_F1,    KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,    KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,   _______,          _______,
    RGB_TOG, RGB_MOD,  RGB_VAI,  RGB_HUI, RGB_SAI, RGB_SPI, _______,  _______, _______, _______, _______,  _______,  _______,  _______,          _______,
    _______, RGB_RMOD, RGB_VAD,  RGB_HUD, RGB_SAD, RGB_SPD,           _______, _______, _______, _______,  _______,  _______,  _______,          _______,
    _______,           _______,  _______, _______, _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______, _______,
    _______, _______,  _______,           _______,          _______,  _______,          _______,           _______,            _______, _______, _______
)
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [MAC_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [WIN_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_FN1]   = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [_FN2]   = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [_FN3]   = {ENCODER_CCW_CW(_______, _______)}
};
#endif // ENCODER_MAP_ENABLE

const key_override_t dot_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_COMM);
const key_override_t comma_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_EXLM);
const key_override_t ques_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_QUES, KC_SLASH);
const key_override_t slash_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_SLASH, KC_BACKSLASH);
const key_override_t angle_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_LEFT_ANGLE_BRACKET, KC_RIGHT_ANGLE_BRACKET);
const key_override_t curly_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_LEFT_CURLY_BRACE, KC_RIGHT_CURLY_BRACE);
const key_override_t paren_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_LEFT_PAREN, KC_RIGHT_PAREN);
const key_override_t bracket_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_LEFT_BRACKET, KC_RIGHT_BRACKET);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &dot_key_override,
    &comma_key_override,
    &slash_key_override,
    &angle_key_override,
    &curly_key_override,
    &paren_key_override,
    &bracket_key_override,
    &ques_key_override,
    NULL // Null terminate the array of overrides!
};