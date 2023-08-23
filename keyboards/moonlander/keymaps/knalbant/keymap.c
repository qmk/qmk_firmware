/* Copyright 2020 ZSA Technology Labs, Inc <@zsa>
 * Copyright 2020 Jack Humbert <jack.humb@gmail.com>
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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
#include "version.h"

// Layers ----------------------------------------------------------------------

enum KeyboardLayers {
  STANDARD,
  BASE,
  SYMBOLS,
  NUMERIC,
  MOVEMENT,
  FUNCTION,

  // Aliases
  STD = STANDARD,
  SYM = SYMBOLS,
  NUM = NUMERIC,
  MOV = MOVEMENT,
  FN = FUNCTION
};

// The main design elements are:
// * Modifiers on the home row keys.
// * Left-hand layer access, with the right hand accessing keys.

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*
   * Well aligned comment and layout instances, ready for copy-pasting.
     ,-----------------------------------------.     ,------------------------------------------.
     |     |     |     |     |     |     |     |     |      |     |     |     |     |     |     |
     |-----+-----+-----+-----+-----+-----------|     |------+-----+-----+-----+-----+-----+-----|
     |     |     |     |     |     |     |     |     |      |     |     |     |     |     |     |
     |-----+-----+-----+-----+-----+-----|-----|     |------|-----+-----+-----+-----+-----+-----|
     |     |     |     |     |     |     |     |     |      |     |     |     |     |     |     |
     |-----+-----+-----+-----+-----+-----|-----'     `------|-----+-----+-----+-----+-----+-----|
     |     |     |     |     |     |     |                  |     |     |     |     |     |     |
     `------------------------------------                  ------------------------------------|
     |     |     |     |     |     |                              |     |     |     |     |     |
     `-----------------------------'                              `-----------------------------'
                                   ,-----------.     ,------------.
                                   |           |     |            |
                             ,-----+-----------|     |------------+-----.
                             |     |     |     |     |      |     |     |
                             |     |     |     |     |      |     |     |
                             |     |     |     |     |      |     |     |
                             `-----------------'     `------------------'

    [NONE] = LAYOUT_moonlander(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,        KC_NO,     KC_NO,        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                    KC_NO, KC_NO, KC_NO,     KC_NO, KC_NO, KC_NO
    ),

    [TRANSPARENT] = LAYOUT_moonlander(
        _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,              _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,          _______,     _______,          _______, _______, _______, _______, _______,
                                            _______, _______, _______,     _______, _______, _______
    ),
   */

  /* Standard layer
   *
   * Standard keycodes.
   * This layer is intended to define the location of standard keycodes. It does
   * not have any special keycodes, except for a toggle to the normal layer. It
   * is intended as a rarely used layer, when custom functions (e.g. home row
   * modifiers) should not get in the way.
   *
   * TODO: Add standard locations for ctrl and shift ?
   *
   * ,-----------------------------------------.     ,------------------------------------------.
   * | Esc |  1  |  2  |  3  |  4  |  5  |     |     |      |  6  |  7  |  8  |  9  |  0  |  =  |
   * |-----+-----+-----+-----+-----+-----------|     |------+-----+-----+-----+-----+-----+-----|
   * |     |  Q  |  W  |  E  |  R  |  T  | Tab |     | Tab  |  Y  |  U  |  I  |  O  |  P  |     |
   * |-----+-----+-----+-----+-----+-----|-----|     |------|-----+-----+-----+-----+-----+-----|
   * |  '  |  A  |  S  |  D  |  F  |  G  | Del |     |Bspace|  H  |  J  |  K  |  L  |  ;  |  -  |
   * |-----+-----+-----+-----+-----+-----|-----'     `------|-----+-----+-----+-----+-----+-----|
   * |     |  Z  |  X  |  C  |  V  |  B  |                  |  N  |  M  |  ,  |  .  |  /  |  _  |
   * `-----------------------------------'                  `-----------------------------------|
   * | DF1 |     |     |     | Alt |                              | Alt |     |     |     |     |
   * `-----------------------------'                              `-----------------------------'
   *                               ,-----------.     ,------------.
   *                               |           |     |            |
   *                         ,-----+-----------|     |------------+-----.
   *                         |     |     |     |     |      |     |     |
   *                         |Space|Enter|     |     |      |Enter|Space|
   *                         |     |     |     |     |      |     |     |
   *                         `-----------------'     `------------------'
   */
  [STANDARD] = LAYOUT_moonlander(
      KC_ESC , KC_1 , KC_2 , KC_3 , KC_4   , KC_5  , KC_NO , /*|*/ KC_NO  , KC_6  , KC_7   , KC_8   , KC_9  , KC_0   , KC_EQL ,
      KC_NO  , KC_Q , KC_W , KC_E , KC_R   , KC_T  , KC_TAB, /*|*/ KC_TAB , KC_Y  , KC_U   , KC_I   , KC_O  , KC_P   , KC_NO  ,
      KC_QUOT, KC_A , KC_S , KC_D , KC_F   , KC_G  , KC_DEL, /*|*/ KC_BSPC, KC_H  , KC_J   , KC_K   , KC_L  , KC_SCLN, KC_MINS,
      KC_NO  , KC_Z , KC_X , KC_C , KC_V   , KC_B  ,         /*|*/          KC_N  , KC_M   , KC_COMM, KC_DOT, KC_SLSH, KC_UNDS,
      DF(1)  , KC_NO, KC_NO, KC_NO, KC_LALT,         KC_NO , /*|*/ KC_NO  ,         KC_RALT, KC_NO  , KC_NO , KC_NO  , KC_NO  ,
                                    KC_SPC , KC_ENT, KC_NO , /*|*/ KC_NO  , KC_ENT, KC_SPC
  ),

  /* Base layer
   *
   * The main design elements are:
   * - Modifiers on the home row keys.
   * - Left-hand layer access, with the right hand accessing keys.

   * Notes:
   * - Most modifiers are made accessible on the home row. Settings are set so
   *   that fast typing will not trigger the modifiers.
   *   Getting used to it required some time. But I eventually found it really
   *   convenient.
   * - Since the SYM and shift keys are very easy to press together, accessing
   *   shifted special keys is also very easy (e.g. curly brackets).
   * - There are no directional keys. Use the MOVEMENT layer instead.
   * - Provide quick access to `-`, used often in the terminal.
   * - Provide quick access to `'`, used often for coding and writing.
   * - The presence of `[` in the baInput_254ee183087d0b32se layer is to enable `Ctrl+[` to escape in
   *   (n)vi(m) or tmux.
   *
   */
#define LC(KC) LCTL_T(KC)
#define RC(KC) RCTL_T(KC)
#define LS(KC) LSFT_T(KC)
#define RS(KC) RSFT_T(KC)
   [BASE] = LAYOUT_moonlander(
       _______, _______ , _______ , _______     , _______       , _______, _______,     _______, _______, _______        , _______, _______ , _______    , _______,
       _______, _______ , _______ , _______     , _______       , _______, _______,     _______, _______, _______        , _______, _______ , _______    , KC_LBRC,
       _______, LC(KC_A), LS(KC_S), LT(SYM,KC_D), LT(NUM,KC_F)  , _______, _______,     _______, _______, _______        , _______, RS(KC_L), RC(KC_SCLN), _______,
       _______, _______ , _______ , _______     , _______       , _______,                       _______, _______        , _______, _______, _______     , _______,
       DF(0)  , _______ , _______ , _______     , _______       ,          TT(FN) ,     KC_CAPS,          _______        , _______, _______ , _______    , _______,
                                                  LGUI_T(KC_SPC), _______, TT(MOV),     TT(MOV), _______, _______
   ),

   /* Symbols
    *
    * ,-----------------------------------------.     ,------------------------------------------.
    * |     |     |     |     |     |     |     |     |      |  ^  |  &  |  *  |  \  |     |     |
    * |-----+-----+-----+-----+-----+-----------|     |------+-----+-----+-----+-----+-----+-----|
    * |     |     |     |     |     |     |     |     |      |  @  |  ~  |  (  |  )  |  `  |     |
    * |-----+-----+-----+-----+-----+-----|-----|     |------|-----+-----+-----+-----+-----+-----|
    * |     |     |     |     |     |     |     |     |      |  #  |  =  |  [  |  ]  |  $  |     |
    * |-----+-----+-----+-----+-----+-----|-----'     `------|-----+-----+-----+-----+-----+-----|
    * |     |     |     |     |     |     |                  |     |     |  <  |  >  |  %  |     |
    * `------------------------------------                  ------------------------------------|
    * |     |     |     |     |     |                              |     |     |     |     |     |
    * `-----------------------------'                              `-----------------------------'
    *                               ,-----------.     ,------------.
    *                               |           |     |            |
    *                         ,-----+-----------|     |------------+-----.
    *                         |     |     |     |     |      |     |     |
    *                         |     |     |     |     |      |     |     |
    *                         |     |     |     |     |      |     |     |
    *                         `-----------------'     `------------------'
    */
    [SYMBOLS] = LAYOUT_moonlander(
        _______, _______, _______, _______, _______, _______, _______,     _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_BSLS, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,     _______, KC_AT  , KC_EXLM, KC_LPRN, KC_RPRN, KC_GRV , _______,
        _______, _______, _______, _______, _______, _______, _______,     _______, KC_HASH, KC_EQL , KC_LBRC, KC_RBRC, KC_DLR , _______,
        _______, _______, _______, _______, _______, _______,                       _______, _______, KC_LT  , KC_GT  , KC_PERC, _______,
        _______, _______, _______, _______, _______,          _______,     _______,          _______, _______, _______, _______, _______,
                                            _______, _______, _______,     _______, _______, _______
    ),

   /* Numeric keypad
    *
    * Modelled after the standard Apple keyboard numeric keypad.
    *
    * ,-----------------------------------------.     ,------------------------------------------.
    * |     |     |     |     |     |     |     |     |      |     |     |  =  |  /  |  *  |     |
    * |-----+-----+-----+-----+-----+-----------|     |------+-----+-----+-----+-----+-----+-----|
    * |     |     |     |     |     |     |     |     |      |     |  7  |  8  |  9  |  -  |     |
    * |-----+-----+-----+-----+-----+-----|-----|     |------|-----+-----+-----+-----+-----+-----|
    * |     |     |     |     |     |     |     |     |      |     |  4  |  5  |  6  |  +  |     |
    * |-----+-----+-----+-----+-----+-----|-----'     `------|-----+-----+-----+-----+-----+-----|
    * |     |     |     |     |     |     |                  |     |  1  |  2  |  3  |     |     |
    * `------------------------------------                  ------------------------------------|
    * |     |     |     |     |     |                              |     |  0  |  .  |     |     |
    * `-----------------------------'                              `-----------------------------'
    *                               ,-----------.     ,------------.
    *                               |           |     |            |
    *                         ,-----+-----------|     |------------+-----.
    *                         |     |     |     |     |      |     |     |
    *                         |     |     |     |     |      |     |     |
    *                         |     |     |     |     |      |     |     |
    *                         `-----------------'     `------------------'
    */
    [NUMERIC] = LAYOUT_moonlander(
        _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, KC_EQL , KC_SLSH, KC_ASTR, _______,
        _______, _______, _______, _______, _______, _______, _______,     _______, _______, KC_7   , KC_8   , KC_9   , KC_MINS, _______,
        _______, _______, _______, _______, _______, _______, _______,     _______, _______, KC_4   , KC_5   , KC_6   , KC_PLUS, _______,
        _______, _______, _______, _______, _______, _______,                       _______, KC_1   , KC_2   , KC_3   , _______, _______,
        _______, _______, _______, _______, _______,          _______,     _______,          _______, KC_0   , KC_DOT , _______, _______,
                                            _______, _______, _______,     _______, _______, _______
    ),

   /* Movement
    *
    * This immitates vim-style movement through standard keys.
    *
    * TODO: Fix for Linux
    *
    * ,-----------------------------------------.     ,------------------------------------------.
    * |     |     |     |     |     |     |     |     |      |     |     |     |     |     |     |
    * |-----+-----+-----+-----+-----+-----------|     |------+-----+-----+-----+-----+-----+-----|
    * |     |     |     |     |     |     |     |     |      |     |     |     |     |     |     |
    * |-----+-----+-----+-----+-----+-----|-----|     |------|-----+-----+-----+-----+-----+-----|
    * |     |     |     |     |     |     |     |     |      |     |     |     |     |     |     |
    * |-----+-----+-----+-----+-----+-----|-----'     `------|-----+-----+-----+-----+-----+-----|
    * |     |     |     |     |     |     |                  |     |     |     |     |     |     |
    * `------------------------------------                  ------------------------------------|
    * |     |     |     |     |     |                              |     |     |     |     |     |
    * `-----------------------------'                              `-----------------------------'
    *                               ,-----------.     ,------------.
    *                               |           |     |            |
    *                         ,-----+-----------|     |------------+-----.
    *                         |     |     |     |     |      |     |     |
    *                         |     |     |     |     |      |     |     |
    *                         |     |     |     |     |      |     |     |
    *                         `-----------------'     `------------------'
    */
    [MOVEMENT] = LAYOUT_moonlander(
        _______, _______, _______   , _______, KC_END    , _______, _______,     _______, _______, _______, _______, _______, KC_HOME, _______,
        _______, _______, A(KC_RGHT), _______, _______   , _______, _______,     _______, _______, KC_PGUP, _______, TG(MOV), _______, _______,
        _______, _______, _______   , KC_PGDN, _______   , _______, _______,     _______, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_END , _______,
        _______, _______, _______   , _______, _______   , _______,                       _______, _______, _______, _______, _______, _______,
        _______, _______, _______   , _______, A(KC_LEFT),          _______,     _______,          _______, _______, _______, _______, _______,
                                                  _______, _______, _______,     _______, _______, _______
    ),

   /* Function
    *
    * Function and other special keys.
    *
    * TODO: Add media and other keys.
    *
    * ,-----------------------------------------.     ,-----------------------------------------------.
    * |     | F1  | F2  | F3  | F4  | F5  |     |     |      | F6  | F7  | F8  | F9  |     | RGB_TOG  |
    * |-----+-----+-----+-----+-----+-----------|     |------+-----+-----+-----+-----+-----+----------|
    * |     |     |     |     |     |     |     |     |      |     | F7  | F8  | F9  |     | RGB_MOD  |
    * |-----+-----+-----+-----+-----+-----|-----|     |------|-----+-----+-----+-----+-----+----------|
    * |     |     |     |     |     |     |     |     |      |     | F4  | F5  | F6  |     | RGB_RMOD |
    * |-----+-----+-----+-----+-----+-----|-----'     `------|-----+-----+-----+-----+-----+----------|
    * |     |     |     |     |     |     |                  |     | F1  | F2  | F3  |     |          |
    * `------------------------------------                  -----------------------------------------|
    * |     |     |     |     |     |                              |     |     |     |     |          |
    * `-----------------------------'                              `----------------------------------'
    *                               ,-----------.     ,------------.
    *                               |           |     |            |
    *                         ,-----+-----------|     |------------+-----.
    *                         |     |     |     |     |      |     |     |
    *                         |     |     |     |     |      |     |     |
    *                         |     |     |     |     |      |     |     |
    *                         `-----------------'     `------------------'
    */
    [FUNCTION] = LAYOUT_moonlander(
        _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , _______,     _______, KC_F6  , KC_F7  , KC_F8  , KC_F9  , _______, RGB_TOG,
        _______, _______, _______, _______, _______, _______, _______,     _______, _______, KC_F7  , KC_F8  , KC_F9  , _______, RGB_MOD,
        _______, _______, _______, _______, _______, _______, _______,     _______, _______, KC_F4  , KC_F5  , KC_F6  , _______, RGB_RMOD,
        _______, _______, _______, _______, _______, _______,                       _______, KC_F1  , KC_F2  , KC_F3  , _______, _______,
        _______, _______, _______, _______, _______,          _______,     _______,          _______, _______, _______, _______, _______,
                                            _______, _______, _______,     _______, _______, _______
    ),
};
// clang-format on

// bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
//   switch (keycode) {
//     case LC(KC_A):
//     case LS(KC_S):
//     case RS(KC_L):
//     case LS(KC_L):
//       return true;
//     default:
//       return false;
//   }
// }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Use this once to set the default layer.
    // set_single_persistent_default_layer(BASE);
    return true;
}
