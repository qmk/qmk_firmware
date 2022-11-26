/* Copyright 2021-2022 Selene ToyKeeper
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

#define MY_LAYOUT LAYOUT_65_ansi_blocker_split_bs

// wrap base layers to avoid the need to keep several copies in sync
#define MY_LAYOUT_wrapper(...) MY_LAYOUT(__VA_ARGS__)
#define MY_LAYOUT_base_wrapper(...) MY_LAYOUT_base(__VA_ARGS__)
#define MY_LAYOUT_base(                             K01, K02, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, \
      K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, \
        K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A \
  ) MY_LAYOUT_wrapper( \
    QK_GESC, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , K01    , K02    , KC_BSLS,  KC_GRV , TK_STAR, \
    KC_TAB , K11    , K12    , K13    , K14    , K15    , K16    , K17    , K18    , K19    , K1A    , K1B    , K1C    , KC_BSPC,  KC_PGUP, \
    KC_LCTL, K21    , K22    , K23    , K24    , K25    , K26    , K27    , K28    , K29    , K2A    , K2B    ,      KC_ENT ,      KC_PGDN, \
    KC_LSPO, K31    , K32    , K33    , K34    , K35    , K36    , K37    , K38    , K39    , K3A    ,      KC_RSPC,     KC_UP  ,  KC_END , \
    TK_MOON, KC_LGUI, TK_LALT,                   KC_SPC ,                            TK_RCTL, TK_RGUI,          KC_LEFT, KC_DOWN,  KC_RGHT  \
    )

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* empty, copy/paste and fill in the blanks
[L_EMPTY] = MY_LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      _______,     _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      _______,     _______, _______,
    _______, _______, _______,                   _______,                            _______, _______,          _______, _______, _______
    ), */

// base layers: qwerty, dvorak, undvorak, colemak-dh-tk
[L_QWERTY  ] = MY_LAYOUT_base_wrapper(__QWERTY__),
[L_DVORAK  ] = MY_LAYOUT_base_wrapper(__DVORAK__),
[L_UNDVORAK] = MY_LAYOUT_base_wrapper(__UNDVORAK__),
[L_COLEMAK ] = MY_LAYOUT_base_wrapper(__COLEMAK_DH_TK__),

// Number Pad(s)
[L_NUMPAD] = MY_LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , _______,      _______,     _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      _______,     _______, _______,
    _______, _______, _______,                   _______,                            _______, _______,          _______, _______, _______
    ),

// Mouse (lower right corner)
[L_MOUSE] = MY_LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_WH_U,
    TK_WARP, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      KC_BTN3,     KC_WH_D,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      KC_BTN1,     KC_MS_U, KC_BTN2,
    _______, _______, _______,                   _______,                            _______, _______,          KC_MS_L, KC_MS_D, KC_MS_R
    ),

// Fn1 / Moon (lower left corner)
[L_FN1] = MY_LAYOUT(
    TK_SESC, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , TK_BSTG, _______, _______,
    KC_MPLY, KC_MNXT, KC_MPRV, TK_ANY , _______, _______, _______, KC_WH_U, KC_MS_U, KC_WH_D, _______, _______, _______, KC_DEL , KC_WH_U,
    TK_WARP, DM_PLY2, DM_REC2, _______, _______, _______, KC_WH_L, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_R, _______,      KC_BTN3,     KC_WH_D,
    KC_BTN3, DM_PLY1, DM_REC1, _______, _______, _______, TK_WARP, KC_BTN1, KC_BTN3, KC_BTN2, _______,      KC_BTN1,     KC_MS_U, KC_BTN2,
    _______, KC_BTN1, KC_BTN2,                   KC_DEL ,                            _______, _______,          KC_MS_L, KC_MS_D, KC_MS_R
    ),

// Fn2 / Star (upper right corner)
[L_FN2] = MY_LAYOUT(
    QK_BOOT, KC_MYCM, KC_WSCH, KC_F13 , KC_F14 , KC_F15 , KC_F16 , KC_F17 , KC_F18 , KC_F19 , KC_F20 , KC_F21 , KC_F22 , KC_INS , TK_SINS, _______,
    TK_INFO, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_INS , KC_DEL , KC_F13 ,
    KC_CAPS, _______, _______, _______, _______, TK_IUUI, _______, _______, _______, _______, _______, _______,      _______,     KC_WSCH,
    TK_DF_3, _______, _______, _______, _______, _______, NK_TOGG, _______, _______, _______, _______,      _______,     KC_PGUP, KC_MYCM,
    TK_DF_0, TK_DF_1, TK_DF_2,                   _______,                            KC_APP , TG(L_MOUSE),      KC_HOME, KC_PGDN, KC_END
    )

};

