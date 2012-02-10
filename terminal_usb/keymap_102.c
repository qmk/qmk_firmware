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

#include <stdint.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include "usb_keycodes.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "keymap.h"




/* 
 * IBM Terminal keyboard 1392595(102keys)
 * http://geekhack.org/showthread.php?10737-What-Can-I-Do-With-a-Terminal-Model-M
 * http://www.seasip.info/VintagePC/ibm_1391406.html
 *
 * Keymap array:
 *     8 bytes
 *   +---------+
 *  0|         |
 *  :|         | 0x00-0x87
 *  ;|         |
 * 17|         |
 *   +---------+
 */
#define KEYMAP( \
    K08,    K07,K0F,K17,K1F,K27,K2F,K37,K3F,K47,K4F,K56,K5E,      K57,K5F,K62,                   \
                                                                                                 \
    K0E,K16,K1E,K26,K25,K2E,K36,K3D,K3E,K46,K45,K4E,K55,K5D,K66,  K67,K6E,K6F,  K76,K77,K7E,K84, \
    K0D,K15,K1D,K24,K2D,K2C,K35,K3C,K43,K44,K4D,K54,K5B,    K5C,  K64,K65,K6D,  K6C,K75,K7D,K7C, \
    K14,K1C,K1B,K23,K2B,K34,K33,K3B,K42,K4B,K4C,K52,    K53,K5A,                K6B,K73,K74,K7B, \
    K12,K13,K1A,K22,K21,K2A,K32,K31,K3A,K41,K49,K4A,    K51,K59,      K63,      K69,K72,K7A,K79, \
    K11,    K19,            K29,                    K39,    K58,  K61,K60,K6A,  K68,K70,K71,K78  \
) { \
    { KB_NO,    KB_NO,    KB_NO,    KB_NO,    KB_NO,    KB_NO,    KB_NO,    KB_##K07 }, \
    { KB_##K08, KB_NO,    KB_NO,    KB_NO,    KB_NO,    KB_##K0D, KB_##K0E, KB_##K0F }, \
    { KB_NO,    KB_##K11, KB_##K12, KB_##K13, KB_##K14, KB_##K15, KB_##K16, KB_##K17 }, \
    { KB_NO,    KB_##K19, KB_##K1A, KB_##K1B, KB_##K1C, KB_##K1D, KB_##K1E, KB_##K1F }, \
    { KB_NO,    KB_##K21, KB_##K22, KB_##K23, KB_##K24, KB_##K25, KB_##K26, KB_##K27 }, \
    { KB_NO,    KB_##K29, KB_##K2A, KB_##K2B, KB_##K2C, KB_##K2D, KB_##K2E, KB_##K2F }, \
    { KB_NO,    KB_##K31, KB_##K32, KB_##K33, KB_##K34, KB_##K35, KB_##K36, KB_##K37 }, \
    { KB_NO,    KB_##K39, KB_##K3A, KB_##K3B, KB_##K3C, KB_##K3D, KB_##K3E, KB_##K3F }, \
    { KB_NO,    KB_##K41, KB_##K42, KB_##K43, KB_##K44, KB_##K45, KB_##K46, KB_##K47 }, \
    { KB_NO,    KB_##K49, KB_##K4A, KB_##K4B, KB_##K4C, KB_##K4D, KB_##K4E, KB_##K4F }, \
    { KB_NO,    KB_##K51, KB_##K52, KB_##K53, KB_##K54, KB_##K55, KB_##K56, KB_##K57 }, \
    { KB_##K58, KB_##K59, KB_##K5A, KB_##K5B, KB_##K5C, KB_##K5D, KB_##K5E, KB_##K5F }, \
    { KB_NO,    KB_##K61, KB_##K62, KB_##K63, KB_##K64, KB_##K65, KB_##K66, KB_##K67 }, \
    { KB_##K68, KB_##K69, KB_##K6A, KB_##K6B, KB_##K6C, KB_##K6D, KB_##K6E, KB_##K6F }, \
    { KB_##K70, KB_##K71, KB_##K72, KB_##K73, KB_##K74, KB_##K75, KB_##K76, KB_##K77 }, \
    { KB_##K78, KB_##K79, KB_##K7A, KB_##K7B, KB_##K7C, KB_##K7D, KB_##K7E, KB_NO    }, \
    { KB_NO,    KB_NO,    KB_NO,    KB_NO,    KB_##K84, KB_NO,    KB_NO,    KB_NO,   }, \
}


// Assign Fn key(0-7) to a layer to which switch with the Fn key pressed.
static const uint8_t PROGMEM fn_layer[] = {
    1,              // Fn0
    2,              // Fn1
    3,              // Fn2
    0,              // Fn3
    0,              // Fn4
    0,              // Fn5
    0,              // Fn6
    0               // Fn7
};

// Assign Fn key(0-7) to a keycode sent when release Fn key without use of the layer.
// See layer.c for details.
static const uint8_t PROGMEM fn_keycode[] = {
    KB_SCLN,        // Fn0
    KB_SLSH,        // Fn1
    KB_ESC,         // Fn2
    KB_NO,          // Fn3
    KB_NO,          // Fn4
    KB_NO,          // Fn5
    KB_NO,          // Fn6
    KB_NO           // Fn7
};


static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: default
     * ,---.   ,---------------. ,---------------. ,---------------. ,-----------.
     * |Esc|   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| |PrS|ScL|Pau|
     * `---'   `---------------' `---------------' `---------------' `-----------'
     * ,-----------------------------------------------------------. ,-----------. ,---------------.
     * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|BS | |Ins|Hom|PgU| |NmL|  /|  *|  -|
     * |-----------------------------------------------------------| |-----------| |---------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \| |Del|End|PgD| |  7|  8|  9|   |
     * |-----------------------------------------------------------| `-----------' |-----------|  +|
     * |CapsLo|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|  #|Retu|               |  4|  5|  6|   |
     * |-----------------------------------------------------------|     ,---.     |---------------|
     * |Shif|  \|  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /|Shift     |     |Up |     |  1|  2|  3|   |
     * |-----------------------------------------------------------| ,-----------. |-----------|Ent|
     * |Ctrl|    |Alt |          Space              |Alt |    |Ctrl| |Lef|Dow|Rig| |      0|  .|   |
     * `----'    `---------------------------------------'    `----' `-----------' `---------------'
     */
    KEYMAP(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,             PSCR,SLCK,BRK,
    GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, JYEN,BSPC,  INS, HOME,PGUP,  NLCK,PSLS,PAST,PMNS,
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,     BSLS,  DEL, END, PGDN,  P7,  P8,  P9,  PPLS,
    LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   FN0, QUOT,     NUHS,ENT,                    P4,  P5,  P6,  PCMM,
    LSFT,NUBS,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, FN1,      RO,  FN2,        UP,         P1,  P2,  P3,  PENT,
    LGUI,     LALT,               SPC,                          RALT,     RCTL,  LEFT,DOWN,RGHT,  NO,  P0,  PDOT,NO
    ),

    /* 1: Mouse keys
     * ,-----------------------------------------------------------.
     * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Backspa|
     * |-----------------------------------------------------------|
     * |Tab  |MwL|MwU|McU|WwU|WwR|MwL|MwD|MwU|MwR|   |   |   |    \|
     * |-----------------------------------------------------------|
     * |CapsLo|   |McL|McD|McR|   |McL|McD|McU|McR|Fn0|   |Return  |
     * |-----------------------------------------------------------|
     * |Shift   |VoD|VoU|Mut|Mb2|Mb3|Mb2|Mb1|VoD|VoU|Mut|Shift     |
     * |-----------------------------------------------------------|
     * |Ctrl |    |Alt |         Mb1                |Alt |    |Ctrl|
     * `-----'    `--------------------------------------'    `----'
     * Mc = mouse cursor, Mw = mouse wheel, Mb = mouse button
     * Vo = Volume, Mut = Mute
     */
    KEYMAP(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,                PSCR,SLCK,BRK,
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F8,  F10, F11, F12, NO,  BSPC,     INS, HOME,PGUP,    NLCK,PSLS,PAST,PMNS,
    TAB, WH_L,WH_D,MS_U,WH_U,WH_R,WH_L,WH_D,WH_U,WH_R,NO,  NO,  NO,       BSLS,     DEL, END, PGDN,    P7,  P8,  P9,  PPLS,
    LCTL,NO,  MS_L,MS_D,MS_R,NO,  MS_L,MS_D,MS_U,MS_R,FN0, NO,       NO,  ENT,                         P4,  P5,  P6,  PCMM,
    LSFT,NO,  VOLD,VOLU,MUTE,BTN2,BTN3,BTN2,BTN1,VOLD,VOLU,MUTE,     NO,  RSFT,          UP,           P1,  P2,  P3,  PENT,
    LGUI,     LALT,               BTN1,                         RALT,     RCTL,     LEFT,DOWN,RGHT,    NO,  P0,  PDOT,NO
    ),

    /* 2: Cursor keys
     * ,-----------------------------------------------------------.
     * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Backspa|
     * |-----------------------------------------------------------|
     * |Tab  |Hom|PgU| Up|PgU|End|Hom|PgD|PgU|End|   |   |   |    \|
     * |-----------------------------------------------------------|
     * |CapsLo|   |Lef|Dow|Rig|   |Lef|Dow| Up|Rig|   |   |Return  |
     * |-----------------------------------------------------------|
     * |Shift   |   |   |   |   |   |Hom|PgD|PgU|End|Fn1|Shift     |
     * |-----------------------------------------------------------|
     * |Ctrl |    |Alt |         Space              |Alt |    |Ctrl|
     * `-----'    `--------------------------------------'    `----'
     */
    KEYMAP(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,                PSCR,SLCK,BRK,
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F8,  F10, F11, F12, NO,  BSPC,     INS, HOME,PGUP,    NLCK,PSLS,PAST,PMNS,
    TAB, NO,  NO,  NO,  NO,  NO,  HOME,PGDN,PGUP,END, NO,  NO,  NO,       BSLS,     DEL, END, PGDN,    P7,  P8,  P9,  PMNS,
    LCTL,NO,  NO,  NO,  NO,  NO,  LEFT,DOWN,UP,  RGHT,NO,  NO,       NO,  ENT,                         P4,  P5,  P6,  PCMM,
    LSFT,NO,  VOLD,VOLU,MUTE,NO,  NO,  HOME,PGDN,PGUP,END, FN1,      NO,  RSFT,          UP,           P1,  P2,  P3,  PENT,
    LGUI,     LALT,               SPC,                          RALT,     RCTL,     LEFT,DOWN,RGHT,    NO,  P0,  PDOT,NO
    ),

    /* 3: HHKB
     * ,-----------------------------------------------------------.
     * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
     * |-----------------------------------------------------------|
     * |Caps |   |   |   |   |   |   |   |Psc|Slk|Pus|Up |   |Backs|
     * |-----------------------------------------------------------|
     * |Contro|VoD|VoU|Mut|   |   |  *|  /|Hom|PgU|Lef|Rig|Enter   |
     * |-----------------------------------------------------------|
     * |Shift   |   |   |   |   |   |  +|  -|End|PgD|Dow|Fn2       |
     * |-----------------------------------------------------------|
     * |Ctrl |    |Alt |         Space              |Alt |    |Ctrl|
     * `-----'    `--------------------------------------'    `----'
     */
    KEYMAP(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,                PSCR,SLCK,BRK,
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F8,  F10, F11, F12, NO,  BSPC,     INS, HOME,PGUP,    NLCK,PSLS,PAST,PMNS,
    CAPS,NO,  NO,  NO,  NO,  NO,  NO,  NO,  PSCR,SLCK,BRK, UP,  NO,       BSLS,     DEL, END, PGDN,    P7,  P8,  P9,  PPLS,
    LCTL,VOLD,VOLU,MUTE,NO,  NO,  PAST,PSLS,HOME,PGUP,LEFT,RGHT,     NO,  ENT,                         P4,  P5,  P6,  PCMM,
    LSFT,NO,  NO,  NO,  NO,  NO,  NO,  PPLS,PMNS,END, PGDN,DOWN,     NO,  FN2,           UP,           P1,  P2,  P3,  PENT,
    LGUI,     LALT,               SPC,                          RALT,     RCTL,     LEFT,DOWN,RGHT,    NO,  P0,  PDOT,NO
    ),
};


uint8_t keymap_get_keycode(uint8_t layer, uint8_t row, uint8_t col)
{
    return pgm_read_byte(&keymaps[(layer)][(row)][(col)]);
}

uint8_t keymap_fn_layer(uint8_t fn_bits)
{
    return pgm_read_byte(&fn_layer[biton(fn_bits)]);
}

uint8_t keymap_fn_keycode(uint8_t fn_bits)
{
    return pgm_read_byte(&fn_keycode[(biton(fn_bits))]);
}
