/* Copyright 2017 Valentin Brosseau
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
#include "keymap_bepo.h"

// Layer shorthand
#define _BP 0
#define _FN 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Native BepoDev for compatible computer
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | ESC    | "      | <      | >      | (      | )      | %      | VOL-   | VOL+   | @      | +      | -      | /      | *      | =      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | B      | E_ACUT | P      | O      | $      | E_GRAV | DEL    | E_CIRC | V      | D      | L      | J      | Z      | C_CEDIL|
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | RALT   | A      | U      | I      | E      | ,      | BACKSP | ENTER  | C      | T      | S      | R      | N      | M      | W      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | LSHIFT | A_GRAV | Y      | X      | .      | K      | BACKSP | ENTER  | ’      | Q      | G      | H      | F      | UP     | RSHIFT |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | LALT   | LCTRL  | FN     | LGUI   | SPACE  | SPACE  | RALT   | RALT   | SPACE  | SPACE  | RGUI   | FN     | LEFT   | DOWN   | RIGHT  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_BP] = LAYOUT_ortho_5x15( /* BepoDev */
  KC_ESC,  BP_DQUO,    BP_LDAQ,    BP_RDAQ, BP_LPRN, BP_RPRN,    BP_PERC,    KC_VOLD, KC_VOLU, BP_AT,   BP_PLUS, BP_MINS,  BP_SLSH,  BP_ASTR, BP_EQL,
  KC_TAB,  BP_B,       BP_EACU,    BP_P,    BP_O,    BP_DLR,     BP_EGRV,    KC_DEL,  BP_DCIR, BP_V,    BP_D,    BP_L,     BP_J,     BP_Z,    BP_CCED,
  KC_RALT, BP_A,       BP_U,       BP_I,    BP_E,    BP_COMM,    KC_BSPC,    KC_ENT,  BP_C,    BP_T,    BP_S,    BP_R,     BP_N,     BP_M,    BP_W,
  KC_LSFT, BP_AGRV,    BP_Y,       BP_X,    BP_DOT,  BP_K,       KC_BSPC,    KC_ENT,  BP_QUOT, BP_Q,    BP_G,    BP_H,     BP_F,     KC_UP,   KC_RSFT,
  KC_LALT, KC_LCTL,    MO(_FN),    KC_LGUI, KC_SPC,  KC_SPC,     KC_RALT,    KC_RALT, KC_SPC,  KC_SPC,  KC_RGUI, MO(_FN),  KC_LEFT,  KC_DOWN, KC_RGHT
 ),

/* FUNCTION
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        | F1     | F2     | F3     | F4     | F5     | F6     | F7     | F8     | P/     | P*     | F9     | F10    | F11    | F12    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        | P7     | P8     | P9     | -      | RGB_TOG| RGB_MOD| RGB_HUI|
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | PREV   | PLAY   | NEXT   | STOP   |        |        |        | P4     | P5     | P6     | +      | RGB_SAI| RGB_SAD| RGB_VAI|
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | VOL-   | MUTE   | VOL+   |        |        |        |        | P1     | P2     | P3     | ENT    | RGB_VAD| Home   | RGB_HUD|
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | QK_BOOT  |        | FN     |        |        |        |        |        | P0     | P0     | .      | FN     |        | End    |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_FN] = LAYOUT_ortho_5x15( /* FUNCTION */
  KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_SLSH, KC_ASTR, KC_F9,   KC_F10,  KC_F11,  KC_F12,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P7,   KC_P8,   KC_P9,   KC_MINS, RGB_TOG, RGB_MOD, RGB_HUI,
  KC_TRNS, KC_MPRV, KC_MPLY, KC_MNXT, KC_MSTP, KC_TRNS, KC_TRNS, KC_TRNS, KC_P4,   KC_P5,   KC_P6,   KC_PLUS, RGB_SAI, RGB_SAD, RGB_VAI,
  KC_TRNS, KC_VOLD, KC_MUTE, KC_VOLU, KC_APP,  KC_TRNS, KC_TRNS, KC_TRNS, KC_P1,   KC_P2,   KC_P3,   KC_ENT,  RGB_VAD, KC_HOME, RGB_HUD,
  QK_BOOT, KC_TRNS, MO(_FN), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_KP_0, KC_KP_0, KC_PDOT, MO(_FN), KC_TRNS, KC_END,  KC_TRNS
 )
};
