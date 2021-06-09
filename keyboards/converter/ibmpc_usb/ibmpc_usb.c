/*
Copyright 2019 Markus Fritsche <fritsche.markus@gmail.com>

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

#include "ibmpc_usb.h"

const uint8_t PROGMEM map_cs1[MATRIX_ROWS][MATRIX_COLS] = {
    { KC_NO,    KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6     }, /* 00-07 */
    { KC_7,     KC_8,     KC_9,     KC_0,     KC_MINUS, KC_EQUAL, KC_BSPACE,KC_TAB   }, /* 08-0F */
    { KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I     }, /* 10-17 */
    { KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_ENTER, KC_LCTL,  KC_A,     KC_S,    }, /* 18-1F */
    { KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN  }, /* 20-27 */
    { KC_QUOTE, KC_GRAVE, KC_LSHIFT,KC_BSLASH,KC_Z,     KC_X,     KC_C,     KC_V,    }, /* 28-2F */
    { KC_B,     KC_N,     KC_M,     KC_COMMA, KC_DOT,   KC_SLASH, KC_RSHIFT,KC_PAST  }, /* 30-37 */
    { KC_LALT,  KC_SPACE, KC_CAPS,  KC_F1,      KC_F2,    KC_F3,    KC_F4,    KC_F5    }, /* 38-3F */
    { KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_NLCK,  KC_SLCK,  KC_P7    }, /* 40-47 */
    { KC_P8,    KC_P9,    KC_PMNS,  KC_P4,    KC_P5,    KC_P6,    KC_PPLS,  KC_P1    }, /* 48-4F */
    { KC_P2,    KC_P3,    KC_P0,    KC_PDOT,  KC_PSCR,  KC_PAUSE, KC_NUHS,  KC_F11   }, /* 50-57 */
    { KC_F12,   KC_PEQL,  KC_LGUI,  KC_RGUI,  KC_APP,   KC_MUTE,  KC_VOLD,  KC_VOLU  }, /* 58-5F */
    { KC_UP,    KC_LEFT,  KC_DOWN,  KC_RIGHT, KC_F13,   KC_F14,   KC_F15,   KC_F16   }, /* 60-67 */
    { KC_F17,   KC_F18,   KC_F19,   KC_F20,   KC_F21,   KC_F22,   KC_F23,   KC_PENT  }, /* 68-6F */
    { KC_KANA,  KC_INSERT,KC_DELETE,KC_RO,    KC_HOME,  KC_END,   KC_F24,   KC_PGUP  }, /* 70-77 */
    { KC_PGDN,  KC_HENK,  KC_RCTL,  KC_MHEN,  KC_RALT,  KC_JYEN,  KC_PCMM,  KC_PSLS  }, /* 78-7F */
};


/*
 * Scan Code Set 2:
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
 * |CapsL |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '| ^a|Entr|               |  4|  5|  6|KP,|
 * |-----------------------------------------------------------|     ,---.     |---------------|
 * |Shft|  <|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /| RO|Shift |     |Up |     |  1|  2|  3|Ent|
 * |-----------------------------------------------------------| ,-----------. |---------------|
 * |Ctl|Gui|Alt|MHEN|     Space      |HENK|KANA|Alt|Gui|App|Ctl| |Lef|Dow|Rig| |  #|  0|  .|KP=|
 * `-----------------------------------------------------------' `-----------' `---------------'
 *
 *         ,-----------------------------------------------.
 *         | 08| 10| 18| 20| 28| 30| 38| 40| 48| 50| 57| 5F|
 * ,---.   |-----------------------------------------------|     ,-----------.     ,-----------.
 * | 76|   | 05| 06| 04| 0C| 03| 0B| 83| 0A| 01| 09| 78| 07|     |+7C| 7E|+77|     |*21|*32|*23|
 * `---'   `-----------------------------------------------'     `-----------'     `-----------'
 * ,-----------------------------------------------------------. ,-----------. ,---------------.
 * | 0E| 16| 1E| 26| 25| 2E| 36| 3D| 3E| 46| 45| 4E| 55| 6A| 66| |*70|*6C|*7D| | 77|*4A| 7C| 7B|
 * |-----------------------------------------------------------| |-----------| |---------------|
 * | 0D  | 15| 1D| 24| 2D| 2C| 35| 3C| 43| 44| 4D| 54| 5B|  5D | |*71|*69|*7A| | 6C| 75| 7D| 79|
 * |-----------------------------------------------------------| `-----------' |---------------|
 * | 58   | 1C| 1B| 23| 2B| 34| 33| 3B| 42| 4B| 4C| 52| ^a| 5A |               | 6B| 73| 74| 6D|
 * |-----------------------------------------------------------|     ,---.     |---------------|
 * | 12 | 61| 1A| 22| 21| 2A| 32| 31| 3A| 41| 49| 4A| 51|  59  |     |*75|     | 69| 72| 7A|*5A|
 * |-----------------------------------------------------------| ,-----------. |---------------|
 * | 14|*1F| 11| 67 |     29         | 64 | 13 |*11|*27|*2F|*14| |*6B|*72|*74| | 68| 70| 71| 63|
 * `-----------------------------------------------------------' `-----------' `---------------'
 * *: E0-prefixed codes. See cs2_e0code() for remapping to unimap array.
 * +: Special codes sequence
 * ^a: ISO hash key and US backslash use identical code 5D.
 * 51, 63, 68, 6A, 6D: Hidden keys in IBM model M [6]
 */
const uint8_t PROGMEM map_cs2[MATRIX_ROWS][MATRIX_COLS] = {
    { KC_PAUS,  KC_F9,    KC_F7,    KC_F5,    KC_F3,    K0C,      KC_F2,    KC_F12   }, /* 00-07 */
    { KC_F13,   KC_F10,   KC_F8,    KC_F6,    KC_F4,    KC_TAB,   KC_GRV,   KC_RALT  }, /* 08-0F */
    { KC_F14,   KC_LALT,  KC_LSHIFT,KC_KANA,  KC_LCTL,  KC_Q,     KC_1,     KC_RCTL  }, /* 10-17 */
    { KC_F15,   KC_LGUI,  KC_Z,     KC_S,     KC_A,     KC_W,     KC_2,     KC_RGUI  }, /* 18-1F */
    { KC_F16,   KC_C,     KC_X,     KC_D,     KC_E,     KC_4,     KC_3,     KC_END   }, /* 20-27 */
    { KC_F17,   KC_SPACE, KC_V,     KC_F,     KC_T,     KC_R,     KC_5,     KC_HOME  }, /* 28-2F */
    { KC_F18,   KC_N,     KC_B,     KC_H,     KC_G,     KC_Y,     KC_6,     KC_DEL   }, /* 30-37 */
    { KC_F19,   KC_INS,   KC_M,     KC_J,     KC_U,     KC_7,     KC_8,     KC_DOWN  }, /* 38-3F */
    { KC_F20,   KC_COMMA, KC_K,     KC_I,     KC_O,     KC_0,     KC_9,     KC_RIGHT }, /* 40-47 */
    { KC_F21,   KC_DOT,   KC_SLASH, KC_L,     KC_SCOLON,KC_P,     KC_MINUS, KC_UP    }, /* 48-4F */
    { KC_F22,   KC_RO,    KC_QUOTE, KC_LEFT,  KC_LBRC,  KC_EQUAL, KC_PGDN,  KC_F23   }, /* 50-57 */
    { KC_CAPS,  KC_RSHIFT,KC_ENTER, KC_RBRC,  KC_APP,   KC_BSLASH,KC_PGUP,  KC_F24   }, /* 58-5F */
    { KC_PSLS,  KC_NUBS,  KC_PENT,  KC_PEQL,  KC_HENK,  KC_VOLD,  KC_BSPACE,KC_MHEN  }, /* 60-67 */
    { KC_NUHS,  KC_P1,    KC_JYEN,  KC_P4,    KC_P7,    KC_PCMM,  KC_VOLU,  KC_MUTE  }, /* 68-6F */
    { KC_P0,    KC_PDOT,  KC_P2,    KC_P5,    KC_P6,    KC_P8,    KC_ESC,   KC_NLCK  }, /* 70-77 */
    { KC_F11,   KC_PPLS,  KC_P3,    KC_PMNS,  KC_PAST,  KC_P9,    KC_SLCK,  KC_PSCR  }, /* 78-7F */
};


/*
 * Scan Code Set 3:
 *               ,-----------------------------------------------.
 *               |F13|F14|F15|F16|F17|F18|F19|F20|F21|F22|F23|F24|
 *               |-----------------------------------------------|
 *               |F1 |F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|
 *               `-----------------------------------------------'
 * ,-------. ,-----------------------------------------------------------. ,-----------. ,---------------.
 * |Mut|HEN| |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|JPY| BS| |  /|PgU|PgD| |Esc|NmL|ScL|  *|
 * |-------| |-----------------------------------------------------------| |-----------| |---------------|
 * |VUp|Pau| |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \| |End|Ins|Del| |  7|  8|  9|  +|
 * |-------| |-----------------------------------------------------------| `-----------' |-----------|---|
 * |VDn|MHE| |CapsL |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|  #| Ret| |JPY|Up |  #| |  4|  5|  6|  -|
 * |-------| |-----------------------------------------------------------| ,-----------. |---------------|
 * |PrS|App| |Shif|  \|  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /| RO| Shift| |Lef|Hom|Rig| |  1|  2|  3|Ent|
 * |-------| |-----------------------------------------------------------| `-----------' |-----------|---|
 * |Gui|Gui| |Ctrl|    |Alt |          Space              |Alt |    |Ctrl| | RO|Dow|KAN| |  ,|  0|  .|  =|
 * `-------' `----'    `---------------------------------------'    `----'  ---`---'---  `---------------'
 *
 *               ,-----------------------------------------------.
 *               | 08| 10| 18| 20| 28| 30| 38| 40| 48| 50| 57| 5F|
 *               |-----------------------------------------------|
 *               | 07| 0F| 17| 1F| 27| 2F| 37| 3F| 47| 4F| 56| 5E|
 *               `-----------------------------------------------'
 * ,-------. ,-----------------------------------------------------------. ,-----------. ,---------------.
 * | 05| 06| | 0E| 16| 1E| 26| 25| 2E| 36| 3D| 3E| 46| 45| 4E| 55| 5D| 66| | 67| 6E| 6F| | 76| 77| 7E|*84|
 * |-------| |-----------------------------------------------------------| |-----------| |---------------|
 * | 04| 0C| | 0D  | 15| 1D| 24| 2D| 2C| 35| 3C| 43| 44| 4D| 54| 5B|  5C | | 64| 65| 6D| | 6C| 75| 7D| 7C|
 * |-------| |-----------------------------------------------------------| `-----------' |---------------|
 * | 03| 0B| | 14   | 1C| 1B| 23| 2B| 34| 33| 3B| 42| 4B| 4C| 52| 53| 5A | |-26| 63|-25| | 6B| 73| 74| 7B|
 * |-------| |-----------------------------------------------------------| ,-----------. |---------------|
 * |*83| 0A| | 12 | 13| 1A| 22| 21| 2A| 32| 31| 3A| 41| 49| 4A| 51|  59  | | 61| 62| 6A| | 69| 72| 7A| 79|
 * |-------| |-----------------------------------------------------------| `-----------' |---------------|
 * | 01| 09| | 11  |   |19  |        29                   |39  |   | 58  | |-16| 60|-1E| | 68| 70| 71| 78|
 * `-------' `-----'   `---------------------------------------'   `-----'  ---`---'---  `---------------'
 * *: Special codes remapped 83->02, 84->7F
 * -: G80-2551 specific 80-prefixed codes remapped: 26->5D, 25->53, 16->51, 1E->00
 * 51, 5C, 5D, 68, 78: Hidden keys in IBM 122-key terminal keyboard [7]
 */
const uint8_t PROGMEM map_cs3[MATRIX_ROWS][MATRIX_COLS] = {
    { KC_KANA,  KC_LGUI,  KC_PSCR,  KC_VOLD,  KC_VOLU,  KC_MUTE,  KC_HENK,  K0C    }, /* 00-07 */
    { KC_F13,   KC_RGUI,  KC_APP,   KC_MHEN,  KC_PAUS,  KC_TAB,   KC_GRV,   KC_F2    }, /* 08-0F */
    { KC_F14,   KC_LCTL,  KC_LSHIFT,KC_NUBS,  KC_CAPS,  KC_Q,     KC_1,     KC_F3    }, /* 10-17 */
    { KC_F15,   KC_LALT,  KC_Z,     KC_S,     KC_A,     KC_W,     KC_2,     KC_F4    }, /* 18-1F */
    { KC_F16,   KC_C,     KC_X,     KC_D,     KC_E,     KC_4,     KC_3,     KC_F5    }, /* 20-27 */
    { KC_F17,   KC_SPACE, KC_V,     KC_F,     KC_T,     KC_R,     KC_5,     KC_F6    }, /* 28-2F */
    { KC_F18,   KC_N,     KC_B,     KC_H,     KC_G,     KC_Y,     KC_6,     KC_F7    }, /* 30-37 */
    { KC_F19,   KC_RALT,  KC_M,     KC_J,     KC_U,     KC_7,     KC_8,     KC_F8    }, /* 38-3F */
    { KC_F20,   KC_COMMA, KC_K,     KC_I,     KC_O,     KC_0,     KC_9,     KC_F9    }, /* 40-47 */
    { KC_F21,   KC_DOT,   KC_SLASH, KC_L,     KC_SCOLON,KC_P,     KC_MINUS, KC_F10   }, /* 48-4F */
    { KC_F22,   KC_RO,    KC_QUOTE, KC_NUHS,  KC_LBRC,  KC_EQUAL, KC_F11,   KC_F23   }, /* 50-57 */
    { KC_RCTL,  KC_RSHIFT,KC_ENTER, KC_RBRC,  KC_BSLASH,KC_JYEN,  KC_F12,   KC_F24   }, /* 58-5F */
    { KC_DOWN,  KC_LEFT,  KC_HOME,  KC_UP,    KC_END,   KC_INS,   KC_BSPACE,KC_PSLS  }, /* 60-67 */
    { KC_PCMM,  KC_P1,    KC_RIGHT, KC_P4,    KC_P7,    KC_DEL,   KC_PGUP,  KC_PGDN  }, /* 68-6F */
    { KC_P0,    KC_PDOT,  KC_P2,    KC_P5,    KC_P6,    KC_P8,    KC_ESC,   KC_NLCK  }, /* 70-77 */
    { KC_PEQL,  KC_PENT,  KC_P3,    KC_PMNS,  KC_PPLS,  KC_P9,    KC_SLCK,  KC_PAST  }, /* 78-7F */
};



