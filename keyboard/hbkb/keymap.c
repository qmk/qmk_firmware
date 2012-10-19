/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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

/* 
 * Keymap for Macway mod
 */
#include <stdint.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include "keycode.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "keymap.h"


/*
 * Layout: 59key
 * ,-----------------------------------------------------------.
 * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|  `|
 * |-----------------------------------------------------------|
 * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]| BS  |
 * |-----------------------------------------------------------|
 * |Contro|  A|  S|  D|  F|  G|  H|  J|  K|  L|Fn3|  '|Return  |
 * |-----------------------------------------------------------|
 * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|Fn2|Shift     |
 * |-----------------------------------------------------------|
 * |Ctrl |   |Alt  |           Fn4             |Alt  |   |Fn1  |
 * `-----'   `---------------------------------------'   `-----'
 *
 * Matrix: 12x8
 *    |       0 |       1 |       2 |       3 |       4 |       5 |       6 |       7
 * ---+---------+---------+---------+---------+---------+---------+---------+---------
 *  0 |         |         | LCTRL   |         |         |         | RCTRL   |        
 *  1 |         | LSHIFT  |         |         |         |         | RSHIFT  |        
 *  2 |         | Tab     | Grave   | 1       | Q       | A       | Z       |        
 *  3 |         | Cpslck  |         | 2       | W       | S       | X       |        
 *  4 |         |         |         | 3       | E       | D       | C       |        
 *  5 | G       | T       | 5       | 4       | R       | F       | V       | B      
 *  6 |         | Bckspc  |         |         | Key*1   | Bckslsh | Enter   | Space  
 *  7 | H       | Y       | 6       | 7       | U       | J       | M       | N      
 *  8 |         | Rbrckt  | Equal   | 8       | I       | K       | Comma   |
 *  9 |         |         |         | 9       | O       | L       | Dot     |        
 *  A |         | Lbrckt  | Minus   | 0       | P       | Smcolon |         | Slash  
 *  B | LALT    |         |         |         |         |         |         | RALT   
 *  Key*1 This key locates between Equal and Backspace.
 *
 *  Original matrix here: http://geekhack.org/showthread.php?7767-Wireless-Model-M&p=133911&viewfull=1#post133911
 */
#define KEYMAP( \
    K22, K23, K33, K43, K53, K52, K72, K73, K83, K93, KA3, KA2, K82, K64, K61, \
    K21, K24, K34, K44, K54, K51, K71, K74, K84, K94, KA4, KA1, K81, K65, \
    K31, K25, K35, K45, K55, K50, K70, K75, K85, K95, KA5, KA0, K66, \
    K11, K26, K36, K46, K56, K57, K77, K76, K86, K96, KA7, K16, \
    K02, KB0,      K67,      KB7, K06 \
) { \
    { KC_NO,    KC_NO,    KC_##K02, KC_NO,    KC_NO,    KC_NO,    KC_##K06, KC_NO    }, \
    { KC_NO,    KC_##K11, KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_##K16, KC_NO    }, \
    { KC_NO,    KC_##K21, KC_##K22, KC_##K23, KC_##K24, KC_##K25, KC_##K26, KC_NO    }, \
    { KC_NO,    KC_##K31, KC_NO,    KC_##K33, KC_##K34, KC_##K35, KC_##K36, KC_NO    }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_##K43, KC_##K44, KC_##K45, KC_##K46, KC_NO    }, \
    { KC_##K50, KC_##K51, KC_##K52, KC_##K53, KC_##K54, KC_##K55, KC_##K56, KC_##K57 }, \
    { KC_NO,    KC_##K61, KC_NO,    KC_NO,    KC_##K64, KC_##K65, KC_##K66, KC_##K67 }, \
    { KC_##K70, KC_##K71, KC_##K72, KC_##K73, KC_##K74, KC_##K75, KC_##K76, KC_##K77 }, \
    { KC_NO,    KC_##K81, KC_##K82, KC_##K83, KC_##K84, KC_##K85, KC_##K86, KC_NO    }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_##K93, KC_##K94, KC_##K95, KC_##K96, KC_NO    }, \
    { KC_##KA0, KC_##KA1, KC_##KA2, KC_##KA3, KC_##KA4, KC_##KA5, KC_NO,    KC_##KA7 }, \
    { KC_##KB0, KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_##KB7 }, \
}

#define KEYCODE(layer, row, col) (pgm_read_byte(&keymaps[(layer)][(row)][(col)]))


// Assign Fn key(0-7) to a layer to which switch with the Fn key pressed.
static const uint8_t PROGMEM fn_layer[] = {
    0,              // Fn0
    1,              // Fn1
    2,              // Fn2
    3,              // Fn3
    4,              // Fn4
    0,              // Fn5
    0,              // Fn6
    0               // Fn7
};

// Assign Fn key(0-7) to a keycode sent when release Fn key without use of the layer.
// See layer.c for details.
static const uint8_t PROGMEM fn_keycode[] = {
    KC_NO,          // Fn0
    KC_NO,          // Fn1
    KC_SLSH,        // Fn2
    KC_SCLN,        // Fn3
    KC_SPC,         // Fn4
    KC_NO,          // Fn5
    KC_NO,          // Fn6
    KC_NO           // Fn7
};

static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: Default Layer
     * ,-----------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|  `|
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]| BS  |
     * |-----------------------------------------------------------|
     * |Contro|  A|  S|  D|  F|  G|  H|  J|  K|  L|Fn3|  '|Return  |
     * |-----------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|Fn2|Shift     |
     * |-----------------------------------------------------------|
     * |Ctrl |   |Alt  |           Fn4             |Alt  |   |Fn1  |
     * `-----'   `---------------------------------------'   `-----'
     */
    KEYMAP(ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSLS,GRV, \
           TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSPC, \
           LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   FN3, QUOT,ENT, \
           LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, FN2, FN1, \
           LGUI,     LALT,          FN4,           RALT,     FN1),


    /* Layer 1: HHKB mode (HHKB Fn)
     * ,-----------------------------------------------------------.
     * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
     * |-----------------------------------------------------------|
     * |Caps |   |   |   |   |   |   |   |Psc|Slk|Pus|Up |   |     |
     * |-----------------------------------------------------------|
     * |Contro|VoD|VoU|Mut|   |   |  *|  /|Hom|PgU|Lef|Rig|        |
     * |-----------------------------------------------------------|
     * |Shift   |   |   |   |   |   |  +|  -|End|PgD|Dow|Shift     |
     * |-----------------------------------------------------------|
     * |Ctrl |   |Alt  |           Space           |Alt  |   |Fn1  |
     * `-----'   `---------------------------------------'   `-----'
     */ 
    KEYMAP(ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, INS, DEL, \
           CAPS,NO,  NO,  NO,  NO,  NO,  NO,  NO,  PSCR,SLCK,BRK, UP,  NO,  NO, \
           LCTL,VOLD,VOLU,MUTE,NO,  NO,  PAST,PSLS,HOME,PGUP,LEFT,RGHT,NO, \
           LSFT,NO,  NO,  NO,  NO,  NO,  PPLS,PMNS,END, PGDN,DOWN,FN1, \
           LGUI,     LALT,          SPC,           RALT,     FN1),


    /* Layer 2: Vi mode (Quote/Rmeta)
     * ,-----------------------------------------------------------.
     * |  `| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|   |   |
     * |-----------------------------------------------------------|
     * |  \  |Hom|PgD|Up |PgU|End|Hom|PgD|PgU|End|   |   |   |     |
     * |-----------------------------------------------------------|
     * |Contro|   |Lef|Dow|Rig|   |Lef|Dow|Up |Rig|   |   |        |
     * |-----------------------------------------------------------|
     * |Shift   |   |   |   |   |   |Hom|PgD|PgU|End|xxx|Shift     |
     * |-----------------------------------------------------------|
     * |Ctrl |   |Alt  |           Space           |Alt  |   |Fn1  |
     * `-----'   `---------------------------------------'   `-----'
     */
    KEYMAP(GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, NO,  NO, \
           BSLS,HOME,PGDN,UP,  PGUP,END, HOME,PGDN,PGUP,END, NO,  NO,  NO,  NO, \
           LCTL,NO,  LEFT,DOWN,RGHT,NO,  LEFT,DOWN,UP,  RGHT,NO,  NO,  NO, \
           LSFT,NO,  NO,  NO,  NO,  NO,  HOME,PGDN,PGUP,END, FN2, RSFT, \
           LGUI,     LALT,          SPC,           RALT,     NO),



    /* Layer 3: Mouse mode (Semicolon)
     * ,-----------------------------------------------------------.
     * |  `| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|   |   |
     * |-----------------------------------------------------------|
     * |  \  |MwL|MwD|McU|MwU|MwR|MwL|MwD|MwU|MwR|   |   |   |     |
     * |-----------------------------------------------------------|
     * |Contro|   |McL|McD|McR|   |McL|McD|McU|McR|xxx|   |        |
     * |-----------------------------------------------------------|
     * |Shift   |   |   |Mb1|Mb2|Mb3|Mb2|Mb1|   |   |   |Shift     |
     * |-----------------------------------------------------------|
     * |Ctrl |   |Alt  |           Space           |Alt  |   |     |
     * `-----'   `---------------------------------------'   `-----'
     * Mc: Mouse Cursor / Mb: Mouse Button / Mw: Mouse Wheel 
     */
    KEYMAP(GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, NO, NO, \
           BSLS,WH_L,WH_D,MS_U,WH_U,WH_R,WH_L,WH_D,WH_U,WH_R,NO,  NO,  NO,  NO, \
           LCTL,NO,  MS_L,MS_D,MS_R,NO,  MS_L,MS_D,MS_U,MS_R,FN3, NO,  NO, \
           LSFT,NO,  NO,  BTN1,BTN2,BTN3,BTN2,BTN1,NO,  NO,  NO,  RSFT, \
           LGUI,     LALT,          BTN1,          RALT,     NO),


    /* Layer 4: Matias half keyboard style (Space)
     * ,-----------------------------------------------------------.
     * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Delete |
     * |-----------------------------------------------------------|
     * |Backs|  P|  O|  I|  U|  Y|  T|  R|  E|  W|  Q|   |   |Tab  |
     * |-----------------------------------------------------------|
     * |Contro|  ;|  L|  K|  J|  H|  G|  F|  D|  S|  A|Con|Control |
     * |-----------------------------------------------------------|
     * |Shift   |  /|  .|  ,|  M|  N|  B|  V|  C|  X|  Z|Shift     |
     * |-----------------------------------------------------------|
     * |Ctrl |   |Alt  |           Fn4             |Alt  |   |     |
     * `-----'   `---------------------------------------'   `-----'
     */
    KEYMAP(MINS,0,   9,   8,   7,   6,   5,   4,   3,   2,   1,   NO,  NO,  NO, ESC, \
           BSPC,P,   O,   I,   U,   Y,   T,   R,   E,   W,   Q,   NO,  NO,  TAB, \
           LCTL,SCLN,L,   K,   J,   H,   G,   F,   D,   S,   A,   RCTL,RCTL, \
           LSFT,SLSH,DOT, COMM,M,   N,   B,   V,   C,   X,   Z,   RSFT, \
           LGUI,     LALT,          FN4,           RALT,     NO),

};


uint8_t keymap_get_keycode(uint8_t layer, uint8_t row, uint8_t col)
{
    return KEYCODE(layer, row, col);
}

uint8_t keymap_fn_layer(uint8_t index)
{
    return pgm_read_byte(&fn_layer[index]);
}

uint8_t keymap_fn_keycode(uint8_t index)
{
    return pgm_read_byte(&fn_keycode[index]);
}
