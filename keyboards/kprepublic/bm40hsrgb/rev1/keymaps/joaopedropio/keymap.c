/* Copyright 2020 João Pedro Pio
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
  _COLEMAK_DMH,
  _SYMBOLS,
  _PROGRAMMING,
  _SYSTEM,
  _GAMER,
  _GAMER_NUMBERS,
  _RGB
};

enum combos {
    COMBO_LCTL,
    COMBO_LGUI,
    COMBO_LALT,
    COMBO_LCTLALT,
    COMBO_RCTL,
    COMBO_RGUI,
    COMBO_RALT,
    COMBO_RCTLALT,
    COMBO_LACUTE,
    COMBO_LTILDE,
    COMBO_LCIRCUMFLEX,
    COMBO_RACUTE,
    COMBO_RTILDE,
    COMBO_RCIRCUMFLEX,
    COMBO_LENGTH // nifty trick to avoid manually specifying how many combos you have
};

// Layers
#define LT2_SPC LT(2,KC_SPC)
#define LT1_ENT LT(1,KC_ENT)
#define RGBLYR  MO(_RGB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Colemak-DHm (Layers 1 and 2 has mod taps)
    ┏━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┓
    ┃    Q    ┃    W    ┃    F    ┃    P    ┃    B    ┃         ┃         ┃    J    ┃    L    ┃    U    ┃    Y    ┃    ;    ┃
    ┣━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┫
    ┃    A    ┃    R    ┃    S    ┃    T    ┃    G    ┃  MAC ↓  ┃  MAC ↑  ┃    M    ┃    N    ┃    E    ┃    I    ┃    O    ┃
    ┣━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┫
    ┃    Z    ┃    X    ┃    C    ┃    D    ┃    V    ┃  MAC ←  ┃  MAC →  ┃    K    ┃    H    ┃    ,    ┃    .    ┃    /    ┃
    ┣━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┻━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┫
    ┃RGB_LAYER┃         ┃  ESC    ┃  Shift  ┃LT2/SPACE┃                   ┃LT1/ENTER┃   BSCP  ┃   TAB   ┃         ┃  GAMER  ┃
    ┗━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┛
    */

	[_COLEMAK_DMH] = LAYOUT_planck_mit(
        KC_Q,    KC_W,    KC_F,   KC_P,    KC_B,    XXXXXXX,       XXXXXXX,        KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,
        KC_A,    KC_R,    KC_S,   KC_T,    KC_G,    LGUI(KC_DOWN), LGUI(KC_UP),    KC_M,    KC_N,    KC_E,    KC_I,    KC_O,
        KC_Z,    KC_X,    KC_C,   KC_D,    KC_V,    LGUI(KC_LEFT), LGUI(KC_RIGHT), KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH,
        RGBLYR , XXXXXXX, KC_ESC, KC_LSFT, LT2_SPC,           XXXXXXX,             LT1_ENT, KC_BSPC, KC_TAB,  XXXXXXX, TO(_GAMER)
    ),

    /* Symbols (This layer has mode taps. This draw don't show it for clarity)
    ┏━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┓
    ┃    !    ┃    @    ┃    #    ┃    $    ┃    %    ┃         ┃         ┃    ^    ┃    &    ┃    *    ┃    (    ┃    )    ┃
    ┣━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┫
    ┃    1    ┃    2    ┃    3    ┃    4    ┃    5    ┃         ┃         ┃    6    ┃    7    ┃    8    ┃    9    ┃    0    ┃
    ┣━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┫
    ┃         ┃         ┃         ┃         ┃         ┃         ┃         ┃         ┃    ←    ┃    ↓    ┃    ↑	  ┃    →    ┃
    ┣━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┻━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┫
    ┃         ┃         ┃         ┃         ┃  MO(3)  ┃                   ┃         ┃         ┃         ┃         ┃         ┃
    ┗━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┛
    */

    [_SYMBOLS] = LAYOUT_planck_mit(
        KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,     _______, _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        _______, _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        _______, _______, _______, _______, _______,     _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,
        _______, _______, _______, _______, MO(_SYSTEM),     _______,      _______, _______, _______, _______, _______
    ),

    /* Programming (This layer has mode taps. This draw don't show it for clarity)
    ┏━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┓
    ┃    Q    ┃    W    ┃    F    ┃    P    ┃    B    ┃         ┃         ┃    "    ┃    {    ┃    }    ┃    \    ┃    |    ┃
    ┣━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┫
    ┃    A    ┃    R    ┃    S    ┃    T    ┃    G    ┃         ┃         ┃    ~    ┃    [    ┃    ]    ┃    `    ┃    '    ┃
    ┣━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┫
    ┃    Z    ┃    X    ┃    C    ┃    D    ┃    V    ┃         ┃         ┃         ┃    -    ┃    _    ┃    =    ┃    +    ┃
    ┣━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┻━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┫
    ┃RGB_LAYER┃         ┃  ESC    ┃  Shift  ┃LT2/SPACE┃                   ┃  MO(3)  ┃         ┃         ┃         ┃         ┃
    ┗━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┛
    */


    [_PROGRAMMING] = LAYOUT_planck_mit(
        LCTL(KC_Q),LCTL(KC_W),LCTL(KC_F),KC_WH_L,KC_WH_R,    _______, _______,       KC_DQUO, KC_LCBR, KC_RCBR, KC_BSLS, KC_PIPE,
        LCTL(KC_A),LCTL(KC_R),LCTL(KC_S),KC_WH_D,KC_WH_U,    _______, _______,       KC_TILD, KC_LBRC, KC_RBRC, KC_GRV,  KC_QUOT,
        LCTL(KC_Z),LCTL(KC_X),LCTL(KC_C),KC_D,LCTL(KC_V),    _______, _______,       _______, KC_MINS, KC_UNDS, KC_EQL,  KC_PLUS,
        _______,      _______, _______, _______, _______,        _______,        MO(_SYSTEM), _______, _______, _______, _______
    ),

    /* System
    ┏━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┓
    ┃   F1    ┃   F2    ┃   F3    ┃   F4    ┃  PRTSCR ┃         ┃         ┃  RESET  ┃         ┃         ┃         ┃         ┃
    ┣━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┫
    ┃   F5    ┃   F6    ┃   F7    ┃   F8    ┃         ┃         ┃         ┃         ┃         ┃         ┃         ┃         ┃
    ┣━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┫
    ┃   F9    ┃   F10   ┃   F11   ┃   F12   ┃         ┃         ┃         ┃         ┃         ┃         ┃         ┃         ┃
    ┣━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┻━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┫
    ┃         ┃         ┃         ┃         ┃         ┃                   ┃         ┃         ┃         ┃         ┃         ┃
    ┗━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┛
    */

	[_SYSTEM] = LAYOUT_planck_mit(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_PSCR, _______, _______, QK_BOOT, _______, _______, _______, _______,
        KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______, _______, _______, _______, _______, _______, _______, _______,
        KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,      _______,     _______, _______, _______, _______, _______
    ),


    /* Gamer
    ┏━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┓
    ┃   TAB   ┃    Q    ┃    W    ┃    E    ┃    R    ┃    T    ┃    Y    ┃    U    ┃    I    ┃    O    ┃    P    ┃  BKSP   ┃
    ┣━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┫
    ┃   ESC   ┃    A    ┃    S    ┃    D    ┃    F    ┃    G    ┃    H    ┃    J    ┃    K    ┃    L    ┃    ;    ┃    '    ┃
    ┣━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┫
    ┃  SHIFT  ┃    Z    ┃    X    ┃    C    ┃    V    ┃    B    ┃    N    ┃    M    ┃    ,    ┃    .    ┃    /    ┃  ENTER  ┃
    ┣━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┻━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┫
    ┃   CTRL  ┃         ┃         ┃  ALT    ┃   MO(5) ┃       SPACE       ┃         ┃         ┃         ┃         ┃ COLEMAK ┃
    ┗━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┛
    */

	[_GAMER] = LAYOUT_planck_mit(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,                           KC_T, KC_Y, KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,                           KC_G, KC_H, KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,                           KC_B, KC_N, KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
        KC_LCTL, _______, _______, KC_LALT, MO(_GAMER_NUMBERS),   KC_SPC,   _______, _______, _______, _______, TO(_COLEMAK_DMH)
    ),

    /* Gamer Numbers
    ┏━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┓
    ┃         ┃    1    ┃    2    ┃    3    ┃    4    ┃         ┃         ┃         ┃         ┃         ┃         ┃         ┃
    ┣━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┫
    ┃         ┃         ┃         ┃         ┃         ┃         ┃         ┃         ┃         ┃         ┃         ┃         ┃
    ┣━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┫
    ┃         ┃         ┃         ┃         ┃         ┃         ┃         ┃         ┃         ┃         ┃         ┃         ┃
    ┣━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┻━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┫
    ┃         ┃         ┃         ┃         ┃         ┃                   ┃         ┃         ┃         ┃         ┃         ┃
    ┗━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┛
    */

	[_GAMER_NUMBERS] = LAYOUT_planck_mit(
        _______,    KC_1,    KC_2,    KC_3,    KC_4, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,       _______,    _______, _______, _______, _______, _______
    ),

    /* RGB
    ┏━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┓
    ┃         ┃         ┃         ┃         ┃         ┃         ┃         ┃RGBTOGGLE┃RGBMODE- ┃RGBMODE+ ┃ COLOUR -┃ COLOUR +┃
    ┣━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┫
    ┃         ┃         ┃         ┃         ┃         ┃         ┃         ┃         ┃RGBBRGHT-┃RGBBRGHT+┃ RGBSAT- ┃ RGBSAT+ ┃
    ┣━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┫
    ┃         ┃         ┃         ┃         ┃         ┃         ┃         ┃         ┃         ┃         ┃         ┃         ┃
    ┣━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┻━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┫
    ┃         ┃         ┃         ┃         ┃         ┃                   ┃         ┃         ┃         ┃         ┃         ┃
    ┗━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┛
    */

    [_RGB] = LAYOUT_planck_mit(
		_______, _______, _______, _______, _______, _______, _______, RGB_TOG, RGB_RMOD, RGB_MOD, RGB_HUD, RGB_HUI,
		_______, _______, _______, _______, _______, _______, _______, _______, RGB_VAD,  RGB_VAI, RGB_SAD, RGB_SAI,
		_______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______,
		_______, _______, _______, _______, _______,      _______,     _______, _______,  _______, _______, _______
    )
};

uint16_t COMBO_LEN = COMBO_LENGTH; // nifty trick continued

// define keys that make up combos
// home row combos - left hand combos
const uint16_t PROGMEM ts_combo[] = {KC_T, KC_S, COMBO_END};
const uint16_t PROGMEM tr_combo[] = {KC_T, KC_R, COMBO_END};
const uint16_t PROGMEM sr_combo[] = {KC_S, KC_R, COMBO_END};
const uint16_t PROGMEM tsr_combo[] = {KC_T, KC_S, KC_R, COMBO_END};

// home row combos - right-hand combos
const uint16_t PROGMEM ne_combo[] = {KC_N, KC_E, COMBO_END};
const uint16_t PROGMEM ni_combo[] = {KC_N, KC_I, COMBO_END};
const uint16_t PROGMEM ei_combo[] = {KC_E, KC_I, COMBO_END};
const uint16_t PROGMEM nei_combo[] = {KC_N, KC_E, KC_I, COMBO_END};

// accentuation - left hand combos
const uint16_t PROGMEM lu_combo[] = {KC_L, KC_U, COMBO_END};
const uint16_t PROGMEM ly_combo[] = {KC_L, KC_Y, COMBO_END};
const uint16_t PROGMEM uy_combo[] = {KC_U, KC_Y, COMBO_END};

// accentuation - right-hand combos
const uint16_t PROGMEM pf_combo[] = {KC_P, KC_F, COMBO_END};
const uint16_t PROGMEM pw_combo[] = {KC_P, KC_W, COMBO_END};
const uint16_t PROGMEM fw_combo[] = {KC_F, KC_W, COMBO_END};

// map combo names to their keys and the key they trigger
combo_t key_combos[] = {
    // home row combos
    [COMBO_LCTL] = COMBO(ts_combo, KC_LCTL),
    [COMBO_LALT] = COMBO(tr_combo, KC_LALT),
    [COMBO_LGUI] = COMBO(sr_combo, KC_LGUI),
    [COMBO_LCTLALT] = COMBO(tsr_combo, LCTL(KC_LALT)),
    [COMBO_RCTL] = COMBO(ne_combo, KC_LCTL),
    [COMBO_RALT] = COMBO(ni_combo, KC_LALT),
    [COMBO_RGUI] = COMBO(ei_combo, KC_LGUI),
    [COMBO_RCTLALT] = COMBO(nei_combo, LCTL(KC_LALT)),

    // accentuation
    [COMBO_RACUTE] = COMBO(lu_combo, KC_QUOT),
    [COMBO_RTILDE] = COMBO(uy_combo, KC_TILD),
    [COMBO_RCIRCUMFLEX] = COMBO(ly_combo, KC_CIRC),
    [COMBO_LACUTE] = COMBO(pf_combo, KC_QUOT),
    [COMBO_LTILDE] = COMBO(fw_combo, KC_TILD),
    [COMBO_LCIRCUMFLEX] = COMBO(pw_combo, KC_CIRC)
};

static bool is_w_pressed = false;
static bool crazy_layer_shift = false;
static bool current_rgb_enabled = true;
static uint8_t last_layer = _COLEMAK_DMH;
static uint8_t current_rgb_mode = 1;
static uint8_t gamer_rgb_mode = 4;
static uint16_t current_rgb_hue = 255;
static uint16_t current_rgb_sat = 255;
static uint16_t current_rgb_val = 255;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_2) {
        if (crazy_layer_shift && !record->event.pressed) {
            unregister_code(KC_W);
            crazy_layer_shift = false;
        }
        is_w_pressed = record->event.pressed;
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t layer = get_highest_layer(state);
    uint8_t current = rgblight_get_mode();
    if (current != gamer_rgb_mode) {
        current_rgb_mode = current;
        current_rgb_enabled = rgblight_is_enabled();
        current_rgb_hue = rgblight_get_hue();
        current_rgb_sat = rgblight_get_sat();
        current_rgb_val = rgblight_get_val();
    }
    switch (layer) {
        case _GAMER:
        case _GAMER_NUMBERS:
            rgblight_enable_noeeprom();
            rgblight_mode_noeeprom(gamer_rgb_mode);
            rgblight_sethsv_noeeprom(255, 255, 80);
            if (is_w_pressed) {
                unregister_code(KC_2);
                register_code(KC_W);
                crazy_layer_shift = true;
            }
            break;
        default:
            if (current_rgb_enabled) {
                rgblight_enable();
            } else {
                rgblight_disable();
            }
            rgblight_mode_noeeprom(current_rgb_mode);
            rgblight_sethsv_noeeprom(current_rgb_hue, current_rgb_sat, current_rgb_val);
    }
    last_layer = layer;
    return state;
}
