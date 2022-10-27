/* Copyright 2018 @TurboMech /u/TurboMech <discord> @A9entOran9e#6134
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

#define _BL 0 //Base layer
#define _FN1 1 //Function layer

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* BL
____________________________________________________________________________________________________________________________________________________________________________
|        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
| ESC    |   F1   |   F2   |   F3   |   F4   |   F5   |   F6   |   F7   |   F8   |   F9   |  F10   |  F11   |  F12   | DEL    | PRT SC | SCR LK | PAUSE  |  P UP  | P DOWN |
|________|________|________|________|________|________|________|________|________|________|________|________|________|________|________|________|________|________|________|
|        |        |        |        |        |        |        |        |        |        |        |        |        |      BACK       |  NUM   |        |        |        |
|  ~`    |   1    |   2    |   3    |   4    |   5    |   6    |   7    |   8    |   9    |   0    |  _ -   | =  +   |      SPACE      |  LOCK  |   /    |  *     |   -    |
|________|________|________|________|________|________|________|________|________|________|________|________|________|_________________|________|________|________|________|
|            |        |        |        |        |        |        |        |        |        |        |  [     |   ]    |             |        |        |        |        |
|    TAB     |   Q    |   W    |   E    |   R    |   T    |   Y    |   U    |   I    |   O    |   P    |  {     |   }    |  |   \      |   7    |   8    |   9    |        |
|____________|________|________|________|________|________|________|________|________|________|________|________|________|_____________|________|________|________|   +    |
|              |        |        |        |        |        |        |        |        |        |   ;    |   '    |                    |        |        |        |        |
|   CAPS LOCK  |   A    |   S    |   D    |   F    |   G    |   H    |   J    |   K    |   L    |   :    |   "    |       ENTER        |   4    |   5    |   6    |        |
|______________|________|________|________|________|________|________|________|________|________|________|________|____________________|________|________|________|________|
|                  |        |        |        |        |        |        |        |   ,    |    .   |   /    |                |        |        |        |        |        |
|  SHIFT           |   Z    |   X    |   C    |   V    |   B    |   N    |   M    |   <    |    >   |   ?    |       SHIFT    |   UP   |   1    |   2    |   3    |        |
|__________________|________|________|________|________|________|________|________|________|________|________|________________|________|________|________|________| ENTER  |
|          |          |          |                                                        |        |        |   MO   |        |        |        |        |        |        |
| CTRL     |   LGUI   | L ALT    |                      SPACE                             | R ALT  | R CTRL |  _FN   |  LEFT  |  DOWN  | RIGHT  |   0    |   .    |        |
|__________|__________|__________|________________________________________________________|________|________|________|________|________|________|________|________|________|
 */

  [_BL] = LAYOUT_default(
    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_PSCR,    KC_SCRL, KC_PAUS, KC_PGUP, KC_PGDN,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,           KC_BSPC,    KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_BSLS,    KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,                   KC_ENT,     KC_P4,   KC_P5,   KC_P6,
    SC_LSPO,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          SC_RSPC, KC_UP,      KC_P1,   KC_P2,   KC_P3,   KC_PENT,
    KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, KC_RCTL, MO(1),   KC_LEFT, KC_DOWN, KC_RGHT,    KC_P0,   KC_PDOT
  ),

/* FN_1
____________________________________________________________________________________________________________________________________________________________________________
|        |        |        |        |        |        |        |        |        |        |        |        |        |        |  VOL   |  VOL   | NEXT   |        |        |
| QK_BOOT  |        |        |        |        |        |        |        |        |        |        |        |        |  MUTE  |  DOWN  |   UP   | TRACK  |  HOME  |  END   |
|________|________|________|________|________|________|________|________|________|________|________|________|________|________|________|________|________|________|________|
|        |  RGB   |  RGB   |  RGB   |  RGB   |  RGB   |  RGB   |  RGB   |  RGB   |        |        |        |        |                 |        |        |        |        |
|        | TOGGLE |  MODE  |INCREASE|DECREASE|  HUE   |  HUE   |  SAT   |  SAT   |        |        |        |        |      DELETE     |        |        |        |        |
|________|________|________|________|________|INCREASE|DECREASE|INCREASE|DECREASE|________|________|________|________|_________________|________|________|________|________|
|            | BACK   | BACK   |        |        |        |        |        |        |        |        |        |        |             |        |        |        |        |
|            | LIGHT  | LIGHT  |        |        |        |        |        |        |        |        |        |        |             |        |        |        |        |
|____________| TOGGLE |INCREASE|DECREASE|________|________|________|________|________|________|________|________|________|_____________|________|________|________|        |
|              |        |        |        |        |        |        |        |        |        |        |        |                    |        |        |        |        |
|              |        |        |        |        |        |        |        |        |        |        |        |                    |        |        |        |        |
|______________|________|________|________|________|________|________|________|________|________|________|________|____________________|________|________|________|________|
|                  |        |        |        |        |        |        |        |        |        |        |                |        |        |        |        |        |
|                  |        |        |        |        |        |        |        |        |        |        |                |        |        |        |        |        |
|__________________|________|________|________|________|________|________|________|________|________|________|________________|________|________|________|________|        |
|          |          |          |                                                        |        |        |        |        |        |        |        |        |        |
|          |          |          |                                                        |        |        |        |        |        |        |        |        |        |
|__________|__________|__________|________________________________________________________|________|________|________|________|________|________|________|________|________|
 */

	[_FN1] = LAYOUT_default(
    QK_BOOT,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MUTE, KC_VOLD,    KC_VOLU, KC_MNXT, KC_HOME, KC_END,
    _______, RGB_TOG, RGB_MOD, RGB_VAI, RGB_VAD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, _______, _______, _______, _______,          KC_DEL,     _______, _______, _______, _______,
    _______, BL_TOGG, BL_INC,  BL_DEC,  _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,    _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,    _______, _______, _______,
    _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,    _______, _______, _______, _______,
    _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______,    _______, _______
  ),

};

