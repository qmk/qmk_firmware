// Copyright 2023 Peter.Falken (@PeterFalken)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "peterfalken.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Layer 0, default layer
 _________________________________________________________________________________________________________________________________  ________
|        |        |        |        |        |        |        |        |        |        |        |        |        |            ||        |
|  ESC   |   F1   |   F2   |   F3   |   F4   |   F5   |   F6   |   F7   |   F8   |   F9   |  F10   |  F11   |  F12   |  DELETE    ||  HOME  |
|________|________|________|________|________|________|________|________|________|________|________|________|________|____________||________|
|   ~    |   !    |   @    |   #    |   $    |   %    |   ^    |   &    |   *    |   (    |   )    |   _    |   +    |            ||        |
|   `    |   1    |   2    |   3    |   4    |   5    |   6    |   7    |   8    |   9    |   0    |   -    |   =    | BACKSPACE  ||  PGUP  |
|________|________|________|________|________|________|________|________|________|________|________|________|________|____________||________|
|            |        |        |        |        |        |        |        |        |        |        |  [     |   ]    |   |    ||        |
|     TAB    |   Q    |   W    |   E    |   R    |   T    |   Y    |   U    |   I    |   O    |   P    |  {     |   }    |   \    ||  PGDN  |
|____________|________|________|________|________|________|________|________|________|________|________|________|________|________||________|
  |            |        |        |        |        |        |        |        |        |        |   :    |   "    |            |   |        |
  |    CAPS    |   A    |   S    |   D    |   F    |   G    |   H    |   J    |   K    |   L    |   ;    |   '    |   ENTER    |   |  END   |
  |____________|________|________|________|________|________|________|________|________|________|________|________|____________|___|________|
  |                |        |        |        |        |        |        |        |   <    |    >   |   ?    |            |        |
  |     SHIFT      |   Z    |   X    |   C    |   V    |   B    |   N    |   M    |   ,    |    .   |   /    |   SHIFT    |   UP   |
  |________________|________|________|________|________|________|________|________|________|________|________|____________|________|________
  |            |        |       |        |                 |                 |        |        |             |   |        |        |        |
  |    MO.1    |  RCTL  |  LALT |  LGUI  |      SPACE      |      SPACE      |  RGUI  |  RALT  |    RCTRL    |   |  LEFT  |  DOWN  | RIGHT  |
  |____________|________|_______|________|_________________|_________________|________|________|_____________|   |________|________|________|
   */

    [_QWERTY] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,     KC_HOME,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,    KC_PGUP,
        KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,  KC_PGDN,
            CK_CW,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,          KC_END,
            KC_LSFT,     KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,     KC_RSFT,   KC_UP,
            MO(1),  KC_LCTL,  KC_LALT, KC_LGUI,   KC_SPC,         KC_SPC,           KC_RGUI, KC_RALT, KC_RCTL,           KC_LEFT, KC_DOWN, KC_RGHT
    ),

    /* Layer 1, function layer
 _________________________________________________________________________________________________________________________________  ________
|        |        |        |        |        |        |        |        |        |        |        |        |        |            || PLAY/  |
|    ▽   |    ▽   |  M.AP  |  M.AL  |  LPAD  |    ▽   |    ▽   |    ▽   |    ▽   |    ▽   |    ▽   |    ▽   |    ▽   |      ▽     || PAUSE  |
|________|________|________|________|________|________|________|________|________|________|________|________|________|____________||________|
|        |        |        |        |        |        |        |        |        |        |  LED   |  LED   |  LED   |            || VOLUME |
|  TO.0  |  TO.1  |  TO.2  |  TO.3  |    ▽   |    ▽   |    ▽   |    ▽   |    ▽   |    ▽   | TOGGLE |  DOWN  |  UP    |      ▽     ||   UP   |
|________|________|________|________|________|________|________|________|________|________|________|________|________|____________||________|
|            |        |        |        |        |        |        |        |        |        |        |        |        |        || VOLUME |
|PRINT SCREEN|    ▽   |    ▽   |    ▽   |    ▽   |    ▽   |  HOME  |  PGDN  |  PGUP  |  END   |    ▽   |    ▽   |    ▽   |  SLEP  ||  DOWN  |
|____________|________|________|________|________|________|________|________|________|________|________|________|________|________||________|
  |            |        |        |        |        |        |        |        |        |        |        |        |            |   |        |
  |      ▽     |    ▽   |    ▽   |    ▽   |    ▽   |    ▽   |  LEFT  |  DOWN  |   UP   | RIGHT  |    ▽   |    ▽   |      ▽     |   |  MUTE  |
  |____________|________|________|________|________|________|________|________|________|________|________|________|____________|___|________|
  |                |        |        |        |        |        |        |        |        |        |        |            |        |
  |        ▽       |   UN   |   CU   |   CO   |   PA   |   MV   |    ▽   |    ▽   |    ▽   |    ▽   |    ▽   |      ▽     |  PGUP  |
  |________________|________|________|________|________|________|________|________|________|________|________|____________|________|________
  |            |        |       |        |                 |                 |        |        |             |   |        |        |        |
  |      ▽     |    ▽   |   ▽   |    ▽   |        ▽        |        ▽        |    ▽   |    ▽   |    TO.0     |   |  HOME  |  PGDN  |  END   |
  |____________|________|_______|________|_________________|_________________|________|________|_____________|   |________|________|________|

   * `QK_BOOT' resets the controller and puts the board into firmware flashing mode.
   * If this key is hit accidentally, just unplug the board and plug it back in.
   */

    [_LOWER] = LAYOUT(
        KC_TRNS,  KC_TRNS,   CK_M1, KC_MCTL, KC_LPAD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_MPLY,
        TO(0),      TO(1),   TO(2),   TO(3), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_TOG, RGB_VAD, RGB_VAI, KC_TRNS,   KC_VOLU,
        KC_PSCR,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_TRNS, KC_TRNS, KC_TRNS, CK_SLP,  KC_VOLD,
            KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS,         KC_MUTE,
            KC_TRNS,   KC_TRNS,    CK_CU,    CK_CO,    CK_PA,  CK_MV, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS,   KC_PGUP,
            KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,        KC_TRNS, KC_TRNS,    TO(0),           KC_HOME, KC_PGDN, KC_END
    ),

    [_RAISE] = LAYOUT(
        QK_BOOT,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
          TO(0),     TO(1),   TO(2),   TO(3), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
        KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
            KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS,
            KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS,   KC_TRNS,
            KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,        KC_TRNS, KC_TRNS,   TO(0),           KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [_ADJUST] = LAYOUT(
        QK_BOOT,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
        TO(0),     TO(1),   TO(2),   TO(3), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
        KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
            KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS,
            KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS,   KC_TRNS,
            KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,        KC_TRNS, KC_TRNS,   TO(0),           KC_TRNS, KC_TRNS, KC_TRNS
    ),

};
