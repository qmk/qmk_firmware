/*
Copyright 2011 Jun Wako <wakojun@gmail.com>

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
 * Keymap for PFU HHKB Pro
 */
#include <stdint.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include "host.h"
#include "usb_keycodes.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "keymap.h"


// Convert physical keyboard layout to matrix array.
// This is a macro to define keymap easily in keyboard layout form.
#define KEYMAP( \
    K31, K30, K00, K10, K11, K20, K21, K40, K41, K60, K61, K70, K71, K50, K51, \
    K32, K01, K02, K13, K12, K23, K22, K42, K43, K62, K63, K73, K72, K52, \
    K33, K04, K03, K14, K15, K24, K25, K45, K44, K65, K64, K74, K53, \
    K34, K05, K06, K07, K16, K17, K26, K46, K66, K76, K75, K55, K54, \
         K35, K36,           K37,                K57, K56 \
) \
{ \
    { KB_##K00, KB_##K01, KB_##K02, KB_##K03, KB_##K04, KB_##K05, KB_##K06, KB_##K07 }, \
    { KB_##K10, KB_##K11, KB_##K12, KB_##K13, KB_##K14, KB_##K15, KB_##K16, KB_##K17 }, \
    { KB_##K20, KB_##K21, KB_##K22, KB_##K23, KB_##K24, KB_##K25, KB_##K26, KB_NO    }, \
    { KB_##K30, KB_##K31, KB_##K32, KB_##K33, KB_##K34, KB_##K35, KB_##K36, KB_##K37 }, \
    { KB_##K40, KB_##K41, KB_##K42, KB_##K43, KB_##K44, KB_##K45, KB_##K46, KB_NO    }, \
    { KB_##K50, KB_##K51, KB_##K52, KB_##K53, KB_##K54, KB_##K55, KB_##K56, KB_##K57 }, \
    { KB_##K60, KB_##K61, KB_##K62, KB_##K63, KB_##K64, KB_##K65, KB_##K66, KB_NO    }, \
    { KB_##K70, KB_##K71, KB_##K72, KB_##K73, KB_##K74, KB_##K75, KB_##K76, KB_NO    } \
}

#define KEYCODE(layer, row, col) (pgm_read_byte(&keymaps[(layer)][(row)][(col)]))


// Assign Fn key(0-7) to a layer to which switch with the Fn key pressed.
static const uint8_t PROGMEM fn_layer[] = {
    0,              // Fn0
    1,              // Fn1
    2,              // Fn2
    3,              // Fn3
    3,              // Fn4
    4,              // Fn5
    0,              // Fn6
    0               // Fn7
};

// Assign Fn key(0-7) to a keycode sent when release Fn key without use of the layer.
// See layer.c for details.
static const uint8_t PROGMEM fn_keycode[] = {
    KB_NO,          // Fn0
    KB_NO,          // Fn1
    KB_SLSH,        // Fn2
    KB_SCLN,        // Fn3
    KB_NO,          // Fn4
    KB_SPC,         // Fn5
    KB_NO,          // Fn6
    KB_NO           // Fn7
};

static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: Default Layer
     * ,-----------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|  `|
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|Backs|
     * |-----------------------------------------------------------|
     * |Contro|  A|  S|  D|  F|  G|  H|  J|  K|  L|Fn3|  '|Return  |
     * |-----------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|Fn2|Shift |Fn1|
     * `-----------------------------------------------------------'
     *       |Gui|Alt  |Fn5                    |Alt  |Fn4|
     *       `-------------------------------------------'
     */
    KEYMAP(ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSLS,GRV, \
           TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSPC, \
           LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   FN3, QUOT,ENT, \
           LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, FN2, RSFT,FN1, \
                LGUI,LALT,          FN5,                RALT,FN4),

    /* Layer 1: HHKB mode (HHKB Fn)
     * ,-----------------------------------------------------------.
     * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
     * |-----------------------------------------------------------|
     * |Caps |   |   |   |   |   |   |   |Psc|Slk|Pus|Up |   |Backs|
     * |-----------------------------------------------------------|
     * |Contro|VoD|VoU|Mut|   |   |  *|  /|Hom|PgU|Lef|Rig|Enter   |
     * |-----------------------------------------------------------|
     * |Shift   |   |   |   |   |   |  +|  -|End|PgD|Dow|Shift |xxx|
     * `-----------------------------------------------------------'
     *      |Gui |Alt  |Space                  |Alt  |xxx|
     *      `--------------------------------------------'
     */ 
    KEYMAP(PWR, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, INS, DEL, \
           CAPS,NO,  NO,  NO,  NO,  NO,  NO,  NO,  PSCR,SLCK,BRK, UP,  NO,  BSPC, \
           LCTL,VOLD,VOLU,MUTE,NO,  NO,  PAST,PSLS,HOME,PGUP,LEFT,RGHT,ENT, \
           LSFT,NO,  NO,  NO,  NO,  NO,  PPLS,PMNS,END, PGDN,DOWN,RSFT,FN1, \
                LGUI,LALT,          SPC,                RALT,FN7),

    /* Layer 2: Vi mode (Slash)
     * ,-----------------------------------------------------------.
     * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
     * |-----------------------------------------------------------|
     * |Tab  |Hom|PgD|Up |PgU|End|Hom|PgD|PgUlEnd|   |   |   |Backs|
     * |-----------------------------------------------------------|
     * |Contro|   |Lef|Dow|Rig|   |Lef|Dow|Up |Rig|   |   |Return  |
     * |-----------------------------------------------------------|
     * |Shift   |   |   |   |   |   |Hom|PgD|PgUlEnd|xxx|Shift |   |
     * `-----------------------------------------------------------'
     *       |Gui|Alt  |Space                  |Alt  |Gui|
     *       `-------------------------------------------'
     */
    KEYMAP(ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, INS, DEL, \
           TAB, HOME,PGDN,UP,  PGUP,END, HOME,PGDN,PGUP,END, NO,  NO,  NO,  BSPC, \
           LCTL,NO,  LEFT,DOWN,RGHT,NO,  LEFT,DOWN,UP,  RGHT,NO,  NO,  ENT, \
           LSFT,NO,  NO,  NO,  NO,  NO,  HOME,PGDN,PGUP,END, FN2, RSFT,NO, \
                LGUI,LALT,          SPC,                RALT,RGUI),

    /* Layer 3: Mouse mode (Semicolon)
     * ,-----------------------------------------------------------.
     * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
     * |-----------------------------------------------------------|
     * |Tab  |MwL|MwU|McU|MwD|MwR|MwL|MwD|MwU|MwR|   |   |   |Backs|
     * |-----------------------------------------------------------|
     * |Contro|   |McL|McD|McR|   |McL|McD|McU|McR|xxx|   |Return  |
     * |-----------------------------------------------------------|
     * |Shift   |Mb4|Mb5|Mb1|Mb2|Mb3|Mb2|Mb1|Mb4|Mb5|   |Shift |   |
     * `-----------------------------------------------------------'
     *      |Gui |Alt  |Mb1                    |Alt  |Gui|
     *      `--------------------------------------------'
     * Mc: Mouse Cursor / Mb: Mouse Button / Mw: Mouse Wheel 
     */
#ifdef HOST_IWRAP
// iWRAP does not support mouse wheel, use these keycodes to remap as wheel
#define KB_KPPL KB_KP_PLUS
#define KB_KPMI KB_KP_MINUS
#define KB_KPAS KB_KP_ASTERISK
#define KB_KPSL KB_KP_SLASH
    KEYMAP(ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, INS, DEL, \
           TAB, KPAS,KPPL,MS_U,KPMI,KPSL,KPAS,KPPL,KPMI,KPSL,NO,  NO,  NO,  BSPC, \
           LCTL,NO,  MS_L,MS_D,MS_R,NO,  MS_L,MS_D,MS_U,MS_R,FN3, NO,  ENT, \
           LSFT,BTN4,BTN5,BTN1,BTN2,BTN3,BTN2,BTN1,NO,  NO,  NO,  RSFT,NO, \
                LGUI,LALT,          BTN1,               RALT,FN4),
#else
    KEYMAP(ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, INS, DEL, \
           TAB, WH_L,WH_U,MS_U,WH_D,WH_R,WH_L,WH_D,WH_U,WH_R,NO,  NO,  NO,  BSPC, \
           LCTL,NO,  MS_L,MS_D,MS_R,NO,  MS_L,MS_D,MS_U,MS_R,FN3, NO,  ENT, \
           LSFT,BTN4,BTN5,BTN1,BTN2,BTN3,BTN2,BTN1,BTN4,BTN5,NO,  RSFT,NO, \
                LGUI,LALT,          BTN1,               RALT,FN4),
#endif

    /* Layer 4: Matias half keyboard style (Space)
     * ,-----------------------------------------------------------.
     * |  -|  0|  9|  8|  7|  6|  5|  4|  3|  2|  1|   |   |   |Esc|
     * |-----------------------------------------------------------|
     * |Backs|  P|  O|  I|  U|  Y|  T|  R|  E|  W|  Q|   |   |Tab  |
     * |-----------------------------------------------------------|
     * |Contro|  ;|  L|  K|  J|  H|  G|  F|  D|  S|  A|Con|Control |
     * |-----------------------------------------------------------|
     * |Shift   |  /|  .|  ,|  M|  N|  B|  V|  C|  X|  Z|Shift |   |
     * `-----------------------------------------------------------'
     *      |Gui |Alt  |xxxxxxxxxxxxxxxxxxxxxxx|Alt  |Gui|
     *      `--------------------------------------------'
     */
/*
    KEYMAP(MINS,0,   9,   8,   7,   6,   5,   4,   3,   2,   1,   NO,  NO,  NO,  ESC, \
           BSPC,P,   O,   I,   U,   Y,   T,   R,   E,   W,   Q,   NO,  NO,  TAB, \
           LCTL,SCLN,L,   K,   J,   H,   G,   F,   D,   S,   A,   RCTL,RCTL, \
           LSFT,SLSH,DOT, COMM,M,   N,   B,   V,   C,   X,   Z,   RSFT,NO, \
                LGUI,LALT,          FN5,                RALT,RGUI)
*/
    /* Mouse mode (Space) */
#ifdef HOST_IWRAP
    KEYMAP(ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, INS, DEL, \
           TAB, KPAS,KPPL,MS_U,KPMI,KPSL,KPAS,KPPL,KPMI,KPSL,NO,  NO,  NO,  BSPC, \
           LCTL,NO,  MS_L,MS_D,MS_R,NO,  MS_L,MS_D,MS_U,MS_R,FN3, NO,  ENT, \
           LSFT,BTN4,BTN5,BTN1,BTN2,BTN3,BTN2,BTN1,BTN4,BTN5,NO,  RSFT,NO, \
                LGUI,LALT,          FN5,                RALT,RGUI),
#else
    KEYMAP(ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, INS, DEL, \
           TAB, WH_L,WH_U,MS_U,WH_D,WH_R,WH_L,WH_D,WH_U,WH_R,NO,  NO,  NO,  BSPC, \
           LCTL,NO,  MS_L,MS_D,MS_R,NO,  MS_L,MS_D,MS_U,MS_R,FN3, NO,  ENT, \
           LSFT,BTN4,BTN5,BTN1,BTN2,BTN3,BTN2,BTN1,BTN4,BTN5,NO,  RSFT,NO, \
                LGUI,LALT,          FN5,                RALT,RGUI),
#endif
};


uint8_t keymap_get_keycode(uint8_t layer, uint8_t row, uint8_t col)
{
    return KEYCODE(layer, row, col);
}

uint8_t keymap_fn_layer(uint8_t fn_bits)
{
    return pgm_read_byte(&fn_layer[biton(fn_bits)]);
}

uint8_t keymap_fn_keycode(uint8_t fn_bits)
{
    return pgm_read_byte(&fn_keycode[(biton(fn_bits))]);
}
