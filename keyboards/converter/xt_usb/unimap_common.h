/*
Copyright 2018 Jun Wako <wakojun@gmail.com>

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
#ifndef UNIMAP_TRNAS_H
#define UNIMAP_TRNAS_H

#include <stdint.h>
#include <avr/pgmspace.h>
#include "unimap.h"


/* Mapping to Universal keyboard layout
 *
 * Universal keyboard layout
 *         ,-----------------------------------------------.
 *         |F13|F14|F15|F16|F17|F18|F19|F20|F21|F22|F23|F24|
 * ,---.   |-----------------------------------------------|     ,-----------.     ,-----------.
 * |Esc|   |F1 |F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|     |PrS|ScL|Pau|     |VDn|VUp|Mut|
 * `---'   `-----------------------------------------------'     `-----------'     `-----------'
 * ,-----------------------------------------------------------. ,-----------. ,---------------.
 * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|JPY|Bsp| |Ins|Hom|PgU| |NmL|  /|  *|  -|
 * |-----------------------------------------------------------| |-----------| |---------------|
 * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  | |Del|End|PgD| |  7|  8|  9|  +|
 * |-----------------------------------------------------------| `-----------' |---------------|
 * |CapsL |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '| ^a|Retn|               |  4|  5|  6|KP,|
 * |-----------------------------------------------------------|     ,---.     |---------------|
 * |Shft|  <|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /| RO|Shift |     |Up |     |  1|  2|  3|KP=|
 * |-----------------------------------------------------------| ,-----------. |---------------|
 * |Ctl|Gui|Alt|MHEN|     Space      |HENK|KANA|Alt|Gui|App|Ctl| |Lef|Dow|Rig| |  #|  0|  .|Ent|
 * `-----------------------------------------------------------' `-----------' `---------------'
 *
 * IBM XT keyobard layout
 * ,-------.  ,--------------------------------------------------------------------------.
 * | F1| F2|  |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  BS  |NumLck |ScrLck |
 * |-------|  |--------------------------------------------------------------------------|
 * | F3| F4|  | Tab |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ] |   |  7|  8|  9|  -|
 * |-------|  |------------------------------------------------------|Ent|---------------|
 * | F5| F6|  | Ctrl |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|  `|   |  4|  5|  6|   |
 * |-------|  |----------------------------------------------------------------------|   |
 * | F7| F8|  |Shif|  \|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift|PrS|  1|  2|  3|  +|
 * |-------|  |----------------------------------------------------------------------|   |
 * | F9|F10|  |  Alt  |               Space                  |CapsLck|   0   |   .   |   |
 * `-------'  `--------------------------------------------------------------------------'
 * Scan code set 1
 * ,-------.  ,--------------------------------------------------------------------------.
 * | 3B| 3C|  | 01| 02| 03| 04| 05| 06| 07| 08| 09| 0A| 0B| 0C| 0D|  0E  |  45   |  46   |
 * |-------|  |--------------------------------------------------------------------------|
 * | 3D| 3E|  | 0F  | 10| 11| 12| 13| 14| 15| 16| 17| 18| 19| 1A| 1B |   | 47| 48| 49| 4A|
 * |-------|  |------------------------------------------------------| 1C|---------------|
 * | 3F| 40|  | 1D   | 1E| 1F| 20| 21| 22| 23| 24| 25| 26| 27| 28| 29|   | 4B| 4C| 4D|   |
 * |-------|  |----------------------------------------------------------------------|   |
 * | 41| 42|  | 2A | 2B| 2C| 2D| 2E| 2F| 30| 31| 32| 33| 34| 35|  36 |*37| 4F| 50| 51| 4E|
 * |-------|  |----------------------------------------------------------------------|   |
 * | 43| 44|  |  38   |              39                      |  40   |  52   |  53   |   |
 * `-------'  `--------------------------------------------------------------------------'
 */
#define UNIMAP_XT( \
    K3B,K3C,  K01,K02,K03,K04,K05,K06,K07,K08,K09,K0A,K0B,K0C,K0D,K0E,    K45,    K46, \
    K3D,K3E,  K0F,K10,K11,K12,K13,K14,K15,K16,K17,K18,K19,K1A,K1B,    K47,K48,K49,K4A, \
    K3F,K40,  K1D,K1E,K1F,K20,K21,K22,K23,K24,K25,K26,K27,K28,K29,K1C,K4B,K4C,K4D,     \
    K41,K42,  K2A,K2B,K2C,K2D,K2E,K2F,K30,K31,K32,K33,K34,K35,K36,K54,K4F,K50,K51,K4E, \
    K43,K44,  K38,                    K39,                    K3A,    K52,    K53      \
) UNIMAP( \
            NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO,                                      \
    K01,    K3B,K3C,K3D,K3E,K3F,K40,K41,K42,K43,K44,NO, NO,       K54,K46,NO,       NO, NO, NO,  \
    K29,K02,K03,K04,K05,K06,K07,K08,K09,K0A,K0B,K0C,K0D,NO, K0E,  NO, NO, NO,   K45,NO, NO, K4A, \
    K0F,K10,K11,K12,K13,K14,K15,K16,K17,K18,K19,K1A,K1B,    K2B,  NO, NO, NO,   K47,K48,K49,K4E, \
    K3A,K1E,K1F,K20,K21,K22,K23,K24,K25,K26,K27,K28,    NO, K1C,                K4B,K4C,K4D,NO,  \
    K2A,NO, K2C,K2D,K2E,K2F,K30,K31,K32,K33,K34,K35,    NO, K36,      NO,       K4F,K50,K51,NO,  \
    K1D,NO, NO, NO,         K39,        NO, NO, NO, NO, NO, NO,   NO, NO, NO,       K52,K53,NO   \
)

const uint8_t PROGMEM unimap_trans[MATRIX_ROWS][MATRIX_COLS] = {
    { UNIMAP_NO,    UNIMAP_ESC,   UNIMAP_1,     UNIMAP_2,     UNIMAP_3,     UNIMAP_4,     UNIMAP_5,     UNIMAP_6     }, /* 00-07 */
    { UNIMAP_7,     UNIMAP_8,     UNIMAP_9,     UNIMAP_0,     UNIMAP_MINUS, UNIMAP_EQUAL, UNIMAP_BSPACE,UNIMAP_TAB   }, /* 08-0F */
    { UNIMAP_Q,     UNIMAP_W,     UNIMAP_E,     UNIMAP_R,     UNIMAP_T,     UNIMAP_Y,     UNIMAP_U,     UNIMAP_I     }, /* 10-17 */
    { UNIMAP_O,     UNIMAP_P,     UNIMAP_LBRC,  UNIMAP_RBRC,  UNIMAP_ENTER, UNIMAP_LCTL,  UNIMAP_A,     UNIMAP_S,    }, /* 18-1F */
    { UNIMAP_D,     UNIMAP_F,     UNIMAP_G,     UNIMAP_H,     UNIMAP_J,     UNIMAP_K,     UNIMAP_L,     UNIMAP_SCLN  }, /* 20-27 */
    { UNIMAP_QUOTE, UNIMAP_GRAVE, UNIMAP_LSHIFT,UNIMAP_BSLASH,UNIMAP_Z,     UNIMAP_X,     UNIMAP_C,     UNIMAP_V,    }, /* 28-2F */
    { UNIMAP_B,     UNIMAP_N,     UNIMAP_M,     UNIMAP_COMMA, UNIMAP_DOT,   UNIMAP_SLASH, UNIMAP_RSHIFT,UNIMAP_PAST  }, /* 30-37 */
    { UNIMAP_LALT,  UNIMAP_SPACE, UNIMAP_CAPS,  UNIMAP_F1,    UNIMAP_F2,    UNIMAP_F3,    UNIMAP_F4,    UNIMAP_F5    }, /* 38-3F */
    { UNIMAP_F6,    UNIMAP_F7,    UNIMAP_F8,    UNIMAP_F9,    UNIMAP_F10,   UNIMAP_NLCK,  UNIMAP_SLCK,  UNIMAP_P7    }, /* 40-47 */
    { UNIMAP_P8,    UNIMAP_P9,    UNIMAP_PMNS,  UNIMAP_P4,    UNIMAP_P5,    UNIMAP_P6,    UNIMAP_PPLS,  UNIMAP_P1    }, /* 48-4F */
    { UNIMAP_P2,    UNIMAP_P3,    UNIMAP_P0,    UNIMAP_PDOT,  UNIMAP_PSCR,  UNIMAP_PAUSE, UNIMAP_NUHS,  UNIMAP_F11   }, /* 50-57 */
    { UNIMAP_F12,   UNIMAP_PEQL,  UNIMAP_LGUI,  UNIMAP_RGUI,  UNIMAP_APP,   UNIMAP_NO,    UNIMAP_NO,    UNIMAP_NO    }, /* 58-5F */
    { UNIMAP_UP,    UNIMAP_LEFT,  UNIMAP_DOWN,  UNIMAP_RIGHT, UNIMAP_F13,   UNIMAP_F14,   UNIMAP_F15,   UNIMAP_F16   }, /* 60-67 */
    { UNIMAP_F17,   UNIMAP_F18,   UNIMAP_F19,   UNIMAP_F20,   UNIMAP_F21,   UNIMAP_F22,   UNIMAP_F23,   UNIMAP_PENT  }, /* 68-6F */
    { UNIMAP_KANA,  UNIMAP_INSERT,UNIMAP_DELETE,UNIMAP_RO,    UNIMAP_HOME,  UNIMAP_END,   UNIMAP_F24,   UNIMAP_PGUP  }, /* 70-77 */
    { UNIMAP_PGDN,  UNIMAP_HENK,  UNIMAP_RCTL,  UNIMAP_MHEN,  UNIMAP_RALT,  UNIMAP_JYEN,  UNIMAP_PCMM,  UNIMAP_PSLS  }, /* 78-7F */
};
// unused unimap codes: NUHS, VOLD, VOLU, MUTE

#endif
