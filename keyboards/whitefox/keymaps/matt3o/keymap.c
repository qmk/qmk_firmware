/*
Copyright 2015 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "whitefox.h"

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: Default Layer
     * ,---------------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|  `|Ins|
     * |---------------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|Backs|Del|
     * |---------------------------------------------------------------|
     * |CapsLo|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Enter   |PgU|
     * |---------------------------------------------------------------|
     * |Shif|   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Up |PgD|
     * |---------------------------------------------------------------|
     * |Ctrl|Gui |Alt |         Space    |Fn0 |Alt |Gui |  |Lef|Dow|Rig|
     * `---------------------------------------------------------------'
     */
    [0] = KEYMAP( \
        ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSLS,GRV, MUTE,\
        TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSPC,     DEL, \
        FN0, A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,NUHS,ENT,      PGUP,\
        LSFT,NUBS,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,RSFT,     UP,  PGDN,\
        LCTL,LGUI,LALT,               SPC,           RALT,FN1, RCTL,     LEFT,DOWN,RGHT \
    ),
    [1] = KEYMAP( \
        TRNS,F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, TRNS,TRNS,TRNS,\
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,DEL ,     INS ,\
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     VOLU,\
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     PGUP,VOLD,\
        TRNS,TRNS,TRNS,               TRNS,          TRNS,TRNS,TRNS,     HOME,PGDN,END  \
    ),
    [2] = KEYMAP( \
        SLEP,P1,  P2,  P3,  P4,  P5,  P6,  P7,  P8,  P9,  P0,  TRNS,TRNS,TRNS,TRNS,FN2, \
        TRNS,TRNS,FN5 ,FN6 ,TRNS,FN7 ,TRNS,TRNS,TRNS,TRNS,PSCR,TRNS,TRNS,TRNS,     FN3, \
        CAPS,TRNS,TRNS,TRNS,FN4 ,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,\
        TRNS,TRNS,TRNS,TRNS,CALC,TRNS,TRNS,TRNS,MAIL,TRNS,TRNS,TRNS,TRNS,     TRNS,TRNS,\
        TRNS,TRNS,TRNS,               TRNS,          TRNS,TRNS,TRNS,     TRNS,TRNS,TRNS \
    ),
};

/* Give numbers some descriptive names */
#define ACTION_LEDS_ALL 1
#define ACTION_LEDS_GAME 2

const uint16_t fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(1),
    [1] = ACTION_LAYER_MOMENTARY(2),
    [2] = ACTION_FUNCTION(ACTION_LEDS_ALL),
    [3] = ACTION_FUNCTION(ACTION_LEDS_GAME),

    [4] = ACTION_USAGE_CONSUMER(0x1B4),
    [5] = ACTION_USAGE_CONSUMER(0x196),
    [6] = ACTION_USAGE_CONSUMER(0x1A6),
    [7] = ACTION_USAGE_CONSUMER(0x1A0),

};

/* custom action function */
void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
	/*
  (void)opt;
  switch(id) {
    case ACTION_LEDS_ALL:
        if(record->event.pressed) {
          // signal the LED controller thread
          chMBPost(&led_mailbox, LED_MSG_GAME_TOGGLE, TIME_IMMEDIATE);
        }
      break;
    case ACTION_LEDS_GAME:
      if(record->event.pressed) {
        // signal the LED controller thread
        chMBPost(&led_mailbox, LED_MSG_ALL_TOGGLE, TIME_IMMEDIATE);
      }
      break;
  }
  */
}
