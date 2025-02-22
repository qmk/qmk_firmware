/* Copyright 2024 XD Boards <copyright@xdboards.xyz>
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

enum layers {
    _QWERTY,
    _SYMBOLS,
    _NUMBERS,
    _FUNCTION,
    _RGB
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
    * ┌─────┬─────┬─────┬─────┬─────┬─────┐                                      ┌─────┬─────┬─────┬─────┬─────┬─────┐
    * │ ESC │  Q  │  W  │  E  │  R  │  T  │                                      │  Y  │  U  │  I  │  O  │  P  │ Bsp │
    * ├─────┼─────┼─────┼─────┼─────┼─────┤                                      ├─────┼─────┼─────┼─────┼─────┼─────┤
    * │ Tab │  A  │  S  │  D  │  F  │  G  │                                      │  H  │  J  │  K  │  L  │  ;  │ CTL │
    * ├─────┼─────┼─────┼─────┼─────┼─────┤                                      ├─────┼─────┼─────┼─────┼─────┼─────┤
    * │Shift│  Z  │  X  │  C  │  V  │  B  │                                      │  N  │  M  │  ,  │  .  │  /  │Shift│
    * └─────┴─────┴─────┴─────┴─────┴─────┘    ┌─────┐                 ┌─────┐   └─────┴─────┴─────┴─────┴─────┴─────┘
    *               ┌─────┐                    │Mute │                 │P Scr│                   ┌─────┐
    *               │ ALT ├─────┐              └─────┘                 └─────┘             ┌─────┤ Alt │
    *               ├─────┤  (  ├─────┐                                              ┌─────┤  )  ├─────┤
    *               │ GUI ├─────┤  {  ├─────┐                                  ┌─────┤  }  ├─────┤ App │
    *               └─────┤Space├─────┤  [  │                                  │  ]  ├─────┤ Ent ├─────┘
    *                     └─────┤ Fnc ├─────┤                                  ├─────┤ Sym ├─────┘
    *                           └─────┤Qwert│                                  │ Num ├─────┘
    *                                 └─────┘                                  └─────┘
    */
    [_QWERTY] = LAYOUT(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_RCTL,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                                                        KC_MUTE,                   KC_PSCR,
                          KC_LALT, KC_LPRN, KC_LCBR,  KC_LBRC,                        KC_RBRC,  KC_RCBR,  KC_RPRN,  KC_RALT,
                          KC_LGUI, KC_SPC,TO(_FUNCTION),TO(_QWERTY),                  TO(_NUMBERS),TO(_SYMBOLS),KC_ENT, KC_APP
    ),
    /*
     * ┌─────┬─────┬─────┬─────┬─────┬─────┐                                      ┌─────┬─────┬─────┬─────┬─────┬─────┐
     * │  `  │  !  │  @  │  #  │  $  │  %  │                                      │  +  │  "  │  '  │  |  │  \  │ Bsp │
     * ├─────┼─────┼─────┼─────┼─────┼─────┤                                      ├─────┼─────┼─────┼─────┼─────┼─────┤
     * │ Tab │  ^  │  &  │  *  │  (  │  )  │                                      │  =  │  <  │  >  │  :  │  ;  │ Ctl │
     * ├─────┼─────┼─────┼─────┼─────┼─────┤                                      ├─────┼─────┼─────┼─────┼─────┼─────┤
     * │Shift│  _  │  [  │  ]  │  {  │  }  │                                      │  -  │  ~  │  ,  │  .  │  ?  │Shift│
     * └─────┴─────┴─────┴─────┴─────┴─────┘    ┌─────┐                 ┌─────┐   └─────┴─────┴─────┴─────┴─────┴─────┘
     *               ┌─────┐                    │Mute │                 │P Scr│                   ┌─────┐
     *               │ ALT ├─────┐              └─────┘                 └─────┘             ┌─────┤ Alt │
     *               ├─────┤  (  ├─────┐                                              ┌─────┤  )  ├─────┤
     *               │ GUI ├─────┤  {  ├─────┐                                  ┌─────┤  }  ├─────┤ App │
     *               └─────┤Space├─────┤  [  │                                  │  ]  ├─────┤ Ent ├─────┘
     *                     └─────┤ Fnc ├─────┤                                  ├─────┤ Sym ├─────┘
     *                           └─────┤Qwert│                                  │ Num ├─────┘
     *                                 └─────┘                                  └─────┘
     */
    [_SYMBOLS] = LAYOUT(
       KC_GRAVE, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                            KC_PLUS, KC_DQUO, KC_QUOTE,KC_PIPE, KC_BSLS, KC_BSPC,
       KC_TAB,   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,                            KC_EQUAL,KC_LT,   KC_GT,   KC_COLN, KC_SCLN, KC_RCTL,
       KC_LSFT,  KC_UNDS, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR,                            KC_MINUS,KC_TILD, KC_COMM, KC_DOT,  KC_QUES, KC_NUM,
                                                       KC_MUTE,                   KC_PSCR,
                         KC_LALT, KC_LPRN, KC_LCBR, KC_LBRC,                          KC_RBRC,  KC_RCBR,  KC_RPRN,  KC_RALT,
                         KC_LGUI, KC_SPC,TO(_FUNCTION),TO(_QWERTY),                   TO(_NUMBERS),TO(_SYMBOLS),KC_ENT, KC_APP
    ),
    /*
     * ┌─────┬─────┬─────┬─────┬─────┬─────┐                                      ┌─────┬─────┬─────┬─────┬─────┬─────┐
     * │ Esc │  1  │  2  │  3  │  4  │  5  │                                      │  +  │  7  │  8  │  9  │  *  │ Bsp │
     * ├─────┼─────┼─────┼─────┼─────┼─────┤                                      ├─────┼─────┼─────┼─────┼─────┼─────┤
     * │ Ctl │  6  │  7  │  8  │  9  │  0  │                                      │  =  │  4  │  5  │  6  │  \  │  :  │
     * ├─────┼─────┼─────┼─────┼─────┼─────┤                                      ├─────┼─────┼─────┼─────┼─────┼─────┤
     * │Shift│     │     │     │     │     │                                      │  -  │  1  │  2  │  3  │  /  │Nm Lk│
     * └─────┴─────┴─────┴─────┴─────┴─────┘    ┌─────┐                 ┌─────┐   └─────┴─────┴─────┴─────┴─────┴─────┘
     *               ┌─────┐                    │Mute │                 │P Scr│                   ┌─────┐
     *               │ ALT ├─────┐              └─────┘                 └─────┘             ┌─────┤  0  │
     *               ├─────┤     ├─────┐                                              ┌─────┤  .  ├─────┤
     *               │ GUI ├─────┤     ├─────┐                                  ┌─────┤  ,  ├─────┤ App │
     *               └─────┤Space├─────┤     │                                  │     ├─────┤ Ent ├─────┘
     *                     └─────┤ Fnc ├─────┤                                  ├─────┤ Sym ├─────┘
     *                           └─────┤Qwert│                                  │ Num ├─────┘
     *                                 └─────┘                                  └─────┘
     */
    [_NUMBERS] = LAYOUT(
       KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_PPLS,  KC_P7,   KC_P8,   KC_P9,   KC_PAST, KC_BSPC,
       KC_LCTL, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,                               KC_PEQL,  KC_P4,   KC_P5,   KC_P6,   KC_BSLS, KC_COLN,
       KC_LSFT, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                              KC_PMNS,  KC_P1,   KC_P2,   KC_P3,   KC_PSLS, KC_NUM,
                                                       KC_MUTE,                   KC_PSCR,
                         KC_LALT, KC_NO,   KC_NO,   KC_NO,                           KC_NO,  KC_PCMM, KC_PDOT,  KC_P0,
                         KC_LGUI, KC_SPC,TO(_FUNCTION),TO(_QWERTY),                   TO(_NUMBERS),TO(_SYMBOLS),KC_ENT, KC_APP
    ),
    /*
     * ┌─────┬─────┬─────┬─────┬─────┬─────┐                                      ┌─────┬─────┬─────┬─────┬─────┬─────┐
     * │  F1 │  F2 │  F3 │  F4 │  F5 │  F6 │                                      │  F7 │  F8 │  F9 │ F10 │ F11 │ F12 │
     * ├─────┼─────┼─────┼─────┼─────┼─────┤                                      ├─────┼─────┼─────┼─────┼─────┼─────┤
     * │Caps │     │     │  ↑  │     │     │                                      │ Ins │ Home│Pg Up│Pause│     │     │
     * ├─────┼─────┼─────┼─────┼─────┼─────┤                                      ├─────┼─────┼─────┼─────┼─────┼─────┤
     * │Shift│     │  ←  │  ↓  │  →  │     │                                      │ Del │ End │Pg Dn│     │     │     │
     * └─────┴─────┴─────┴─────┴─────┴─────┘    ┌─────┐                 ┌─────┐   └─────┴─────┴─────┴─────┴─────┴─────┘
     *               ┌─────┐                    │Mute │                 │P Scr│                   ┌─────┐
     *               │ ALT ├─────┐              └─────┘                 └─────┘             ┌─────┤  0  │
     *               ├─────┤     ├─────┐                                              ┌─────┤  .  ├─────┤
     *               │ GUI ├─────┤     ├─────┐                                  ┌─────┤     ├─────┤ App │
     *               └─────┤Space├─────┤     │                                  │     ├─────┤ Ent ├─────┘
     *                     └─────┤ RGB ├─────┤                                  ├─────┤ Sym ├─────┘
     *                           └─────┤Qwert│                                  │ Num ├─────┘
     *                                 └─────┘                                  └─────┘
     */
    [_FUNCTION] = LAYOUT(
       KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                              KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
       KC_CAPS,   KC_NO,   KC_NO,   KC_UP,   KC_NO,   KC_NO,                              KC_INS,  KC_HOME, KC_PGUP, KC_PAUS, KC_NO,   KC_NO,
       KC_LSFT, KC_NO,   KC_LEFT, KC_DOWN, KC_RIGHT,KC_NO,                              KC_DEL,  KC_END,  KC_PGDN, KC_NO,   KC_NO,   KC_RSFT,
                                                       KC_MUTE,                   KC_PSCR,
                         KC_LALT, KC_NO,   KC_NO,   KC_NO,                           KC_NO,  KC_NO,  KC_DOT,  KC_0,
                         KC_LGUI, KC_SPC,MO(_RGB),TO(_QWERTY),                   TO(_NUMBERS),TO(_SYMBOLS),KC_ENT, KC_APP
    ),
/*
 * ┌─────┬─────┬─────┬─────┬─────┬─────┐                                      ┌─────┬─────┬─────┬─────┬─────┬─────┐
 * │     │     │     │     │     │     │                                      │     │     │     │     │     │     │
 * ├─────┼─────┼─────┼─────┼─────┼─────┤                                      ├─────┼─────┼─────┼─────┼─────┼─────┤
 * │     │Mode↑│Hue ↑│Sat ↑│Val ↑│Spd ↑│                                      │     │     │     │     │     │     │
 * ├─────┼─────┼─────┼─────┼─────┼─────┤                                      ├─────┼─────┼─────┼─────┼─────┼─────┤
 * │OnOff│Mode↓│Hue ↓│Sat ↓│Val ↓│Spd ↓│                                      │     │     │     │     │     │     │
 * └─────┴─────┴─────┴─────┴─────┴─────┘    ┌─────┐                 ┌─────┐   └─────┴─────┴─────┴─────┴─────┴─────┘
 *               ┌─────┐                    │     │                 │     │                   ┌─────┐
 *               │     ├─────┐              └─────┘                 └─────┘             ┌─────┤     │
 *               ├─────┤     ├─────┐                                              ┌─────┤     ├─────┤
 *               │     ├─────┤     ├─────┐                                  ┌─────┤     ├─────┤     │
 *               └─────┤     ├─────┤     │                                  │     ├─────┤     ├─────┘
 *                     └─────┤     ├─────┤                                  ├─────┤     ├─────┘
 *                           └─────┤     │                                  │     ├─────┘
 *                                 └─────┘                                  └─────┘
 */
    [_RGB] = LAYOUT(
       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
       KC_NO,   RM_NEXT, RM_HUEU, RM_SATU, RM_VALU, RM_SPDU,                            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
       RM_TOGG, RM_PREV, RM_HUED, RM_SATD, RM_VALD, RM_SPDD,                            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                                                       KC_NO,                     KC_NO,
                         KC_NO  , KC_NO,   KC_NO,   KC_NO,                           KC_NO  , KC_NO,   KC_NO,   KC_NO,
                         KC_NO  , KC_NO,   KC_NO,   KC_NO,                           KC_NO  , KC_NO,   KC_NO,   KC_NO
    )
};
// clang-format on
