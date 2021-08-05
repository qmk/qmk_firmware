/* Copyright 2017 @TurboMech /u/TurboMech <discord> @A9entOran9e#6134
 *           2021 QMK
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
#include "turbomech.h"

#define _QWERTY 0 //BASE layer
#define _FUNCTION 1 //Function layer

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* BL
 * ,- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -.
 * |   Esc   |   Scrn  |   Scrn  | Expose  |Launchpad|   Show  |Dock Hide|  Screen | Shortcut| Shortcut| Shortcut| Shortcut|   Play  |  Mute   | Vol Up  | Vol Down|
 * |         |Brght Up | Brght Dn|         |         | Desktop |  Toggle | Capture |         |         |         |         |   Pause |         |         |         |
 * |- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - - - - - - -+- - - - -|
 * |    `    |    1    |    2    |    3    |    4    |    5    |    6    |    7    |    8    |    9    |    0    |    -    |    +    |     Backspace     |  POWER  |
 * |         |         |         |         |         |         |         |         |         |         |         |         |         |                   |         |
 * |- - - - - - - +- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - - - - +- - - - -|
 * |     TAB      |    Q    |    W    |    E    |    R    |    T    |    Y    |    U    |    I    |    O    |    P    |    [    |     ]   |      \       | Shortcut|
 * |              |         |         |         |         |         |         |         |         |         |         |         |         |              |         |
 * |- - - - - - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - - - - - - - -+- - - - -|
 * |      CAPS       |    A    |    S    |    D    |    F    |    G    |    H    |    J    |    K    |    L    |    ;    |    '    |        Enter        |   Page  |
 * |                 |         |         |         |         |         |         |         |         |         |         |         |                     |    Up   |
 * |- - - - - - - - - - - +- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - - - - - +- - - - -+- - - - -+
 * |        Shift         |    Z    |    X    |    C    |    V    |    B    |    N    |    M    |    ,    |    .    |    /    |     Shift      |   Up    |  Page   |
 * |                      |         |         |         |         |         |         |         |         |         |         |                |         |  Down   |
 * |- - - - - +- - - - - - +- - - - - - + - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -|
 * |  Control |   Option   |     Gui    |                             Space                            |   Gui   |   Opt   |    Fn   |  Left   |   Down  |  Right  |
 * |          |    /Alt    |            |                                                              |         |   Alt   |         |         |         |         |
 * `- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -'
 */

    [_QWERTY] = LAYOUT_75_ansi(
        KC_ESC,  KC_F14,  KC_F15,  C(KC_UP), C(KC_L), KC_F11,  A(G(KC_D)), C(KC_S), C(S(KC_O)), C(G(KC_1)), C(G(KC_2)), C(G(KC_3)), KC_MPLY, KC_MUTE, KC_VOLD, KC_VOLU,
        KC_GRV,  KC_1,    KC_2,    KC_3,     KC_4,    KC_5,    KC_6,       KC_7,    KC_8,       KC_9,       KC_0,       KC_MINS,    KC_EQL,           KC_BSPC, KC_POWER,
        KC_TAB,  KC_Q,    KC_W,    KC_E,     KC_R,    KC_T,    KC_Y,       KC_U,    KC_I,       KC_O,       KC_P,       KC_LBRC,    KC_RBRC, KC_BSLS,          C(G(KC_N)),
        KC_CAPS, KC_A,    KC_S,    KC_D,     KC_F,    KC_G,    KC_H,       KC_J,    KC_K,       KC_L,       KC_SCLN,    KC_QUOT,             KC_ENT,           KC_PGUP,
        KC_LSPO,          KC_Z,    KC_X,     KC_C,    KC_V,    KC_B,       KC_N,    KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,             KC_RSPC, KC_UP,   KC_PGDN,
        KC_LCTL, KC_LALT, KC_LGUI,                             KC_SPC,                                      KC_RGUI,    KC_RALT,    MO(1),   KC_LEFT, KC_DOWN, KC_RGHT
    ),

/* FN1 - SEE readme.md
 * ,- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -.
 * |   Quit  |   F1    |    F2   |   F3    |   F4    |   F5    |    F6   |   F7    |    F8   |    F9   |   F10   |   F11   |   F12   |  Trns   |  Trns   |   DFU   |
 * |   All   |         |         |         |         |         |         |         |         |         |         |         |         |         |         |  Reset  |
 * |- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - - - - - - -+- - - - -|
 * |   Trns  |   Trns  |   Trns  |   Trns  |   Trns  |   Trns  |   Trns  |   Trns  |   Trns  |   Trns  |   Trns  |   Trns  |   Trns  |       Delete      |   Lock  |
 * |         |         |         |         |         |         |         |         |         |         |         |         |         |                   |Shortcut |
 * |- - - - - - - +- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - - - - +- - - - -|
 * |     Trns     |   RGB   |   RGB   |   RGB   |   RGB   | RGB Hue | RGB Hue | RGB Sat | RGB Sat |  Trns   |   Trns  |   Trns  |   Trns  |     Trns     |   Trns  |
 * |              |  Toggle |   Mode  | Increase| Decrease| Increase| Decrease| Increase| Decrease|         |         |         |         |              |         |
 * |- - - - - - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - - - - - - - -+- - - - -|
 * |      Trns       |   Trns  |   Trns  |   Trns  |   Trns  |   Trns  |  Trns   |  Trns   |   Trns  |   Trns  |  Trns   |   Trns  |        Trns         |   Trns  |
 * |                 |         |         |         |         |         |         |         |         |         |         |         |                     |         |
 * |- - - - - - - - - - - +- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - - - - - +- - - - -+- - - - -+
 * |         Trns         |Backlight|Backlight|Backlight|Backlight|   Trns  |  Trns   |   Trns  |   Trns  |   Trns  |   Trns  |     Trns       |  Trns   |  Trns   |
 * |                      |  Toggle | Increase| Decrease|   Step  |         |         |         |         |         |         |                |         |         |
 * |- - - - - +- - - - - - +- - - - - - + - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -|
 * |   Trns   |    Trns    |    Trns    |                             Trns                             |  Trns   |  Trns   |  Trns   |  Trns   |   Trns  |  Trns   |
 * |          |            |            |                                                              |         |         |         |         |         |         |
 * `- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -'
 */

    [_FUNCTION] = LAYOUT_75_ansi(
        A(G(KC_Q)), KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, KC_RESET,
        _______,    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_DEL,  C(A(G(KC_S))),
        _______,    RGB_TOG, RGB_MOD, RGB_VAI, RGB_VAD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, _______, _______, _______, _______, _______,          _______,
        _______,    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,             BL_TOGG, BL_INC,  BL_DEC,  BL_STEP, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______,    _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),

};
