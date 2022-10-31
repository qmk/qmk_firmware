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


#define _QWERTY 0 //BASE layer
#define _FUNCTION 1 //Function layer
#define _WINDOWS 2 //Windows layer

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EXPOSE,                   // Expose (LCTRL + UP)
  LAUNCH,
  DOCK,
  SCRCAP,
  CS1,
  CS2,
  QALL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Base Layer
____________________________________________________________________________________________________________________________________________________________________________
|        | SCREEN | SCREEN |        |        |SHOW    | TOGGLE |SCREEN  |CUSTOM  |CUSTOM  |PREVIOUS| PLAY/  |  NEXT  |        |        |        |        |        |        |
| ESC    |BRIGHTEN|  DIM   | EXPOSE |LAUNCHPA|DESKTOP | DOCK   |CAPTURE |SHORTCUT|SHORTCUT| TRACK  |  PAUSE | TRACK  |  MUTE  | VOL DN | VOL UP | PG UP  |PG DOWN |  POWER |
|________|________|________|________|________|________|________|________|___1____|___2____|________|________|________|________|________|________|________|________|________|
|        |        |        |        |        |        |        |        |        |        |        |        |        |      BACK       |        |        |        |        |
|  ~`    |   1    |   2    |   3    |   4    |   5    |   6    |   7    |   8    |   9    |   0    |  _ -   | =  +   |      SPACE      | DELETE |   /    |  *     |   -    |
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
|          |          |          |                                                        |        |        |   TT   |        |        |        |        |        |        |
| CTRL     |  L ALT   | L GUI    |                      SPACE                             | R GUI  | R CTRL |  _FN   |  LEFT  |  DOWN  | RIGHT  |   0    |   .    |        |
|__________|__________| COMMAND  |________________________________________________________|COMMAND |________|________|________|________|________|________|________|________|
 */

	[_QWERTY] = LAYOUT_default(
		KC_ESC,  KC_F14,  KC_F15, EXPOSE, LAUNCH, KC_F11, DOCK,  SCRCAP, CS1,    CS2,    KC_MRWD, KC_MPLY, KC_MFFD, KC_MUTE, KC_VOLD, KC_VOLU, KC_PGUP, KC_PGDN, KC_PWR,
		KC_GRV,  KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,  KC_7,   KC_8,   KC_9,   KC_0,     KC_MINS, KC_EQL,       KC_BSPC,     KC_DEL,  KC_PSLS, KC_PAST, KC_PMNS,
      KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC, KC_RBRC,     KC_BSLS,     KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
       KC_CAPS,  KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,   KC_QUOT,          KC_ENT,     KC_P4,   KC_P5,   KC_P6,
        SC_LSPO,  KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT, KC_SLSH,      SC_RSPC,        KC_UP,   KC_P1,   KC_P2,   KC_P3,   KC_PENT,
		KC_LCTL, KC_LALT, KC_LGUI,                   KC_SPC,                           KC_RGUI,  KC_RCTL,  TT(1),  KC_LEFT, KC_DOWN, KC_RIGHT, KC_P0,   KC_PDOT
  ),
/* FN1 - SEE readme.md
____________________________________________________________________________________________________________________________________________________________________________
|        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
| QUIT   |   F1   |   F2   |   F3   |   F4   |  F5    |   F6   |   F7   |   F8   |   F9   |  F10   |  F11   |   F12  |        |        |        |  HOME  |  END   | QK_BOOT  |
|_ALL____|________|________|________|________|________|________|________|________|________|________|________|________|________|________|________|________|________|________|
|        |  RGB   |  RGB   |  RGB   |  RGB   |  RGB   |  RGB   |  RGB   |  RGB   |        |        |        |        |                 |        |        |        |        |
|        | TOGGLE |  MODE  |INCREASE|DECREASE|  HUE   |  HUE   |  SAT   |        |        |        |        |        |      DELETE     |        |        |        |        |
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


	[_FUNCTION] = LAYOUT_default(
		QALL,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, _______, _______, _______, KC_HOME, KC_END,  QK_BOOT,
    _______, RGB_TOG, RGB_MOD, RGB_VAI, RGB_VAD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, _______, _______, _______, _______,      KC_DEL,     _______, _______, _______, _______,
      _______, BL_TOGG,  BL_INC,  BL_DEC,  _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______,   _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,     _______, _______, _______,
         _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______,         _______,  _______, _______, _______, _______,
    _______, _______, _______,                  _______,                                 _______,  TO(2),  _______,  _______, _______,  _______, _______, _______

  ),

/* Windows layer
____________________________________________________________________________________________________________________________________________________________________________
|        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
| ESC    |   F1   |   F2   |   F3   |   F4   |   F5   |   F6   |   F7   |   F8   |   F9   |  F10   |  F11   |  F12   | DELETE |  HOME  |   END  |  P UP  | P DOWN |  MENU  |
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
|          |          |          |                                                        |        |        |   TO   |        |        |        |        |        |        |
| L GUI    |  L ALT   | L CTL    |                      SPACE                             | R CTL  | R ALT  |LAYER 0 |  LEFT  |  DOWN  | RIGHT  |   0    |   .    |        |
|__________|__________|__________|________________________________________________________|________|________|________|________|________|________|________|________|________|
 */


	[_WINDOWS] = LAYOUT_default(
    KC_ESC,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_HOME, KC_END,  KC_PGUP, KC_PGDN, KC_MENU,
    KC_GRV,  KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS, KC_EQL,       KC_BSPC,      KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
      KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC, KC_RBRC,     KC_BSLS,     KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
       KC_CAPS,  KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,   KC_QUOT,          KC_ENT,     KC_P4,   KC_P5,   KC_P6,
        SC_LSPO,  KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT, KC_SLSH,      SC_RSPC,        KC_UP,   KC_P1,   KC_P2,   KC_P3,   KC_PENT,
    KC_LGUI, KC_LALT, KC_LCTL,                   KC_SPC,                           KC_RCTL,  KC_RALT,  TO(0),  KC_LEFT, KC_DOWN,  KC_RIGHT, KC_P0,   KC_PDOT
  ),
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
    // dynamically generate these.
      case EXPOSE:
        SEND_STRING(SS_DOWN(X_LCTL) SS_TAP(X_UP) SS_UP(X_LCTL));
        return false;
      case LAUNCH:
        SEND_STRING(SS_DOWN(X_LCTL) SS_TAP(X_L) SS_UP(X_LCTL));
        return false;
      case DOCK:
        SEND_STRING(SS_DOWN(X_LALT) SS_DOWN(X_LGUI) SS_TAP(X_D) SS_UP(X_LGUI) SS_UP(X_LALT));
        return false;
      case SCRCAP:  //screen capture
        SEND_STRING(SS_DOWN(X_LCTL) SS_TAP(X_S) SS_UP(X_LCTL));
        return false;
      case CS1:  //custom shortcut 1
        SEND_STRING(SS_DOWN(X_LALT) SS_DOWN(X_LGUI) SS_TAP(X_1) SS_UP(X_LGUI) SS_UP(X_LALT));
        return false;
      case CS2:  //custom shortcut 2
        SEND_STRING(SS_DOWN(X_LALT) SS_DOWN(X_LGUI) SS_TAP(X_2) SS_UP(X_LGUI) SS_UP(X_LALT));
        return false;
      case QALL:  //quit all applications
        SEND_STRING(SS_DOWN(X_LALT) SS_DOWN(X_LGUI) SS_TAP(X_Q) SS_UP(X_LGUI) SS_UP(X_LALT));
        return false;
    }
  }
  return true;
};
