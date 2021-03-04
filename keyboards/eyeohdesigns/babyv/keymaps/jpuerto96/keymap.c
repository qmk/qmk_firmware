/* Copyright 2020 Eye Oh! Designs
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    QWERTY,
    FUNCTN,
    NUMBRS,
};

// Left-hand HR Mods
#define ALT_A ALT_T(KC_A)
#define GUI_S GUI_T(KC_S)
#define SFT_D SFT_T(KC_D)
#define CTL_F CTL_T(KC_F)

// Right-hand HR Mods
#define CTL_J  CTL_T(KC_J)
#define SFT_K  SFT_T(KC_K)
#define GUI_L  GUI_T(KC_L)
#define ALT_SC ALT_T(KC_SCLN)

#define RAISE MO(FUNCTN)
#define LOWER MO(NUMBRS)

#define ____ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   [QWERTY] = LAYOUT_1u(
        RGB_HUI,  KC_Q,    KC_W,    KC_E,       KC_R,       KC_T,    KC_Y,    KC_U,       KC_I,       KC_O,     KC_P,   RGB_HUD,
        RGB_SAI,  ALT_A,   GUI_S,   SFT_D,      CTL_F,      KC_G,    KC_H,    CTL_J,      SFT_K,      GUI_L,    ALT_SC, RGB_SAD,
        RGB_VAI, KC_Z,    KC_X,    KC_C,       KC_V,       KC_B,    KC_N,    KC_M,       KC_COMM,    KC_DOT,   KC_SLSH, RGB_VAD,
        RGB_TOG,                   LOWER,      KC_TAB,     KC_SPC,  KC_ENT,  KC_BSPC,     RAISE,                          RGB_MODE_FORWARD
    ),
    [FUNCTN] = LAYOUT_1u(
        ____,    KC_EXLM, KC_AT,   KC_HASH,    KC_DLR,     KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN,  KC_RPRN,  ____,
        ____,    KC_F1,   KC_F2,   KC_F3,      KC_F4,  	   KC_F5,   KC_MINS, KC_EQL,     KC_LCBR,    KC_RCBR,  KC_QUOT,  RESET,
        ____,    KC_F6,   KC_F7,   KC_F8,      KC_F9,      KC_F10,  KC_UNDS, KC_PLUS,    KC_LBRC,    KC_RBRC,  KC_BSLS,  ____,
        ____,                      ____,       ____,       ____,    ____,    ____,       ____,                           ____
    ),
    [NUMBRS] = LAYOUT_1u(
        ____,    KC_1,    KC_2,    KC_3,       KC_4,       KC_5,    KC_6,    KC_7,       KC_8,       KC_9,     KC_0,     ____,
        ____,    KC_PIPE, KC_GRV,  KC_TILD,    ____,       ____,    ____,    KC_LEFT,    KC_DOWN,    KC_UP,    KC_RIGHT, ____,
        ____,    ____,    ____,    ____,       ____,       ____,    ____,    ____,       ____,       ____,     ____,     ____,
        ____,                      ____,       ____,       ____,    ____,    ____,       ____,                           ____
    ),
};
