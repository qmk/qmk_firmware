/* Copyright 2017 Wunder
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
#include "xd75.h"

// Layer shorthand
#define _BASE 0
#define _FUNC 1
#define XXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY: but turkish f
 * .-----------------------------------------------------------------------------------------------------------------------.
 * | * +   | 1 "   | 2 "   | 3 ^   | 4 $   | 5 %   | 6 &   | 7 / { | 8 ( [ | 9 ) ] | 0 = } | / ? \ | - _   |BackSpc| Delete|
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * | Escape| F   @ | G     |       | I     | O     | D     | R     | N     | H     | P     | Q     | W   ~ |  Home | Pg Up |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |  Tab  | U     |       | E     | A     |       | T     | K     | M     | L     | Y     |     # | X   ` |  End  | Pg Dn |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+---------------+-------+-------|
 * | Shift | J     |       | V     | C     |       | Z     | S     | B     | . :   | , ;   | < > | | Shift |   Up  |CapsLck|
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * | Funct |  Ctrl |  Meta |  Alt  |     Space     |     Enter     |      AltGr    |   OS  |  Ctrl |  Left |  Down | Right |
 * '-----------------------------------------------------------------------------------------------------------------------'
 */

 [_BASE] = { /* QWERTY */
  { KC_GRV, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSPC,KC_DEL },
  { KC_ESC, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_HOME,KC_PGUP},
  { KC_TAB, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,KC_BSLS,KC_END, KC_PGDN},
  { KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_NUBS,KC_RSFT,KC_UP,  KC_CAPS},
  { MO(_FN),KC_LCTL,KC_LGUI,KC_LALT,KC_SPC, XXX,    KC_ENT, XXX,    KC_RALT,XXX,    KC_RGUI,KC_RCTL,KC_LEFT,KC_DOWN,KC_RGHT},
 },

/* FUNCTION
 * .-----------------------------------------------------------------------------------------------------------------------.
 * |BootKbd|   F1  |   F2  |   F3  |   F4  |   F5  |   F6  |   F7  |   F8  |   F9  |  F10  |  F11  |  F12  |PrntScr|  Ins  |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |       | Sleep |       | Led - | Led + |       |       |       |       |       | Vol X | Vol - | Vol + |       |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |       |       |       |       |       |       |       |       |  Wake |       |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+---------------+-------+-------|
 * |       |       |       |       |       |       |       |       |       |       |       |       |       | MuStop|       |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |       |       |       |       |       |       |       | MuPrev| MuTog | MuNext|
 * '-----------------------------------------------------------------------------------------------------------------------'
 */
 
 [_FUNC] = { /* FUNCTION */
  { RESET,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, KC_PSCR,KC_INS },
  { _______,KC_SLEP,KC_13,  BL_DEC, BL_INC, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, KC_MUTE,KC_VOLD,KC_VOLU,KC_F19, KC_F20 },
  { _______,KC_F21 ,KC_F22, KC_F23, KC_F24, XXX,    XXX,    XXX,    XXX,    XXX,    XXX,    XXX,    XXX,    KC_WAKE,_______},
  { _______,XXX,    XXX,    XXX,    XXX,    XXX,    XXX,    XXX,    XXX,    XXX,    XXX,    XXX,    _______,KC_MSTP,_______},
  { _______,_______,_______,_______,XXX,    _______,XXX,    _______,XXX,    _______,_______,_______,KC_MPRV,KC_MPLY,KC_MNXT},
 }
};
