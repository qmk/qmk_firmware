/* Copyright 2022 Selene ToyKeeper
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

#include "toykeeper.h"

#define MY_LAYOUT LAYOUT

// wrap base layers to avoid the need to keep several copies in sync
#define MY_LAYOUT_wrapper(...) MY_LAYOUT(__VA_ARGS__)
#define MY_LAYOUT_base_wrapper(...) MY_LAYOUT_base(__VA_ARGS__)
#define MY_LAYOUT_base(                             K01, K02, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, \
      K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, \
        K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A \
  ) MY_LAYOUT_wrapper( \
  QK_GESC, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                      KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , K1C    , \
  KC_TAB , K11    , K12    , K13    , K14    , K15    , KC_MYCM,    KC_WSCH, K16    , K17    , K18    , K19    , K1A    , K1B    , \
  KC_PGUP, K21    , K22    , K23    , K24    , K25    , K01    ,    K02    , K26    , K27    , K28    , K29    , K2A    , K2B    , \
  KC_PGDN, K31    , K32    , K33    , K34    , K35    , TK_SINS,    KC_F14 , K36    , K37    , K38    , K39    , K3A    , KC_END , \
                                         TK_LCLK,                                 TK_RCLK,    \
                                            KC_BSPC,                           KC_SPC ,       \
                                               KC_LSPO,                     KC_RSPC,          \
                                                  TK_LGUI,               TK_RGUI,             \
                                      TK_LPLM,                                        TK_RPLM )

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// base layers: qwerty, dvorak, undvorak, colemak-dh-tk
[L_QWERTY  ] = MY_LAYOUT_base_wrapper(__QWERTY__),
[L_DVORAK  ] = MY_LAYOUT_base_wrapper(__DVORAK__),
[L_UNDVORAK] = MY_LAYOUT_base_wrapper(__UNDVORAK__),
[L_COLEMAK ] = MY_LAYOUT_base_wrapper(__COLEMAK_DH_TK__),

// Moon (left palm key)
[L_LPALM] = MY_LAYOUT(
  TK_SESC, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                      KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_BSLS,
  KC_MPLY, KC_MNXT, KC_MPRV, KC_UP  , _______, _______, DM_PLY1,    DM_PLY2, _______, KC_WH_U, KC_MS_U, KC_WH_D, _______, _______,
  KC_HOME, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, KC_F11 ,    KC_F12 , KC_WH_L, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_R, KC_ENT ,
  KC_END , _______, KC_BTN1, KC_BTN3, KC_BTN2, _______, KC_INS ,    KC_DEL , TK_WARP, KC_BTN1, KC_BTN3, KC_BTN2, _______, KC_HOME,
                                         _______,                                 _______,
                                            KC_DEL ,                           _______,
                                               _______,                     _______,
                                                  _______,               _______,
                                      _______,                                        TK_BOTH  ),

// Star (right palm key)
[L_RPALM] = MY_LAYOUT(
  KC_GRV , KC_MYCM, KC_WSCH, KC_F13 , KC_F14 , KC_F15 ,                      KC_F16 , KC_F17 , KC_F18 , KC_F19 , KC_F20 , KC_BSLS,
  KC_MPLY, KC_MNXT, KC_MPRV, KC_UP  , _______, _______, DM_PLY1,    DM_PLY2, _______, KC_WH_U, KC_MS_U, KC_WH_D, _______, _______,
  KC_HOME, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, KC_F21 ,    KC_F22 , KC_WH_L, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_R, KC_ENT ,
  KC_END , _______, KC_BTN1, KC_BTN3, KC_BTN2, _______, KC_INS ,    KC_DEL , TK_WARP, KC_BTN1, KC_BTN3, KC_BTN2, _______, KC_HOME,
                                         _______,                                 _______,
                                            KC_DEL ,                           _______,
                                               _______,                     _______,
                                                  _______,               _______,
                                      TK_BOTH,                                        _______  ),

// Void (both Fn keys pressed)
[L_BOTH] = MY_LAYOUT(
  QK_BOOT, KC_MYCM, KC_WSCH, KC_F13 , KC_F14 , KC_F15 ,                      KC_F16 , KC_F17 , KC_F18 , KC_F19 , KC_F20 , _______,
  TK_INFO, _______, RGB_HUI, RGB_SAI, RGB_VAI, _______, DM_REC1,    DM_REC2, _______, RGB_MOD, RGB_SPI, RGB_TOG, _______, _______,
  _______, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , TK_DF_3,    TK_DF_2, KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_ENT ,
  _______, _______, _______, _______, _______, _______, TK_DF_0,    TK_DF_1, NK_TOGG, _______, _______, _______, _______, KC_HOME,
                                         _______,                                 KC_APP ,
                                            _______,                           _______,
                                               _______,                     _______,
                                                  _______,               _______,
                                      _______,                                        _______  ),

/*
[L_NUMPAD] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                      _______, KC_P7  , KC_P8  , KC_P9  , KC_PMNS, _______,
  _______, _______, _______, _______, _______, _______, _______,    _______, _______, KC_P4  , KC_P5  , KC_P6  , KC_PPLS, _______,
  _______, _______, _______, _______, _______, _______, _______,    _______, _______, KC_P1  , KC_P2  , KC_P3  , KC_PEQL, _______,
  _______, _______, _______, _______, _______, _______, _______,    _______, _______, KC_P0  , KC_PDOT, KC_PAST, KC_PSLS, KC_PENT,
                                         _______,                                 _______,
                                            _______,                           _______,
                                               _______,                     _______,
                                                  _______,               _______,
                                      _______,                                        _______  ),
  */

/* empty, copy/paste and fill in the blanks
[L_EMPTY] = MY_LAYOUT(
  _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______,
                                         _______,                                 _______,
                                            _______,                           _______,
                                               _______,                     _______,
                                                  _______,               _______,
                                      _______,                                        _______  ),
  */

};

// colors + positions of various keys
const uint8_t layer_indicator_colors[][6] = {
    // layer , x, y,   r,   g,   b
    { L_LPALM   , 1,3, 255,200,200 },
    { L_RPALM   , 6,7, 255,200,200 },
    { L_BOTH    , 1,3, 255,255, 30 },
    { L_BOTH    , 6,7, 255,255, 30 },
    { 0         , 0,0,   0,  0,  0 },  // stop
};
const uint8_t mod_indicator_coords[][3] = {
    // mod, x, y
    { 1, 0, 2, },  // L Shift
    { 1, 7, 6, },  // R Shift
    { 2, 0, 0, },  // L Ctrl
    { 2, 7, 4, },  // R Ctrl
    { 3, 0, 1, },  // L Alt
    { 3, 7, 5, },  // R Alt
    { 4, 0, 3, },  // L GUI
    { 4, 7, 7, },  // R GUI
    { 0, 0, 0, },  // stop
};

