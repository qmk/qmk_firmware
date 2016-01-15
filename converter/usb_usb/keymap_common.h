/*
Copyright 2014 Jun Wako <wakojun@gmail.com>

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
#ifndef KEYMAP_COMMON_H
#define KEYMAP_COMMON_H

#include <stdint.h>
#include <stdbool.h>
#include "keycode.h"
#include "action.h"
#include "action_macro.h"
#include "report.h"
#include "print.h"
#include "debug.h"
#include "keymap.h"


extern const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS];
extern const uint16_t fn_actions[];


/*         ,---------------. ,---------------. ,---------------.
 *         |F13|F14|F15|F16| |F17|F18|F19|F20| |F21|F22|F23|F24|
 * ,---.   |---------------| |---------------| |---------------| ,-----------. ,---------------. ,-------.
 * |Esc|   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| |PrS|ScL|Pau| |VDn|VUp|Mut|Pwr| | Help  |
 * `---'   `---------------' `---------------' `---------------' `-----------' `---------------' `-------'
 * ,-----------------------------------------------------------. ,-----------. ,---------------. ,-------.
 * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|JPY|Bsp| |Ins|Hom|PgU| |NmL|  /|  *|  -| |Stp|Agn|
 * |-----------------------------------------------------------| |-----------| |---------------| |-------|
 * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  | |Del|End|PgD| |  7|  8|  9|  +| |Mnu|Und|
 * |-----------------------------------------------------------| `-----------' |---------------| |-------|
 * |CapsL |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  :|  #|Retn|               |  4|  5|  6|KP,| |Sel|Cpy|
 * |-----------------------------------------------------------|     ,---.     |---------------| |-------|
 * |Shft|  <|  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /| RO|Shift |     |Up |     |  1|  2|  3|KP=| |Exe|Pst|
 * |-----------------------------------------------------------| ,-----------. |---------------| |-------|
 * |Ctl|Gui|Alt|MHEN|HNJ| Space  |H/E|HENK|KANA|Alt|Gui|App|Ctl| |Lef|Dow|Rig| |  0    |  .|Ent| |Fnd|Cut|
 * `-----------------------------------------------------------' `-----------' `---------------' `-------'
 *
 *
 * App:         Windows Menu key
 * Gui:         Windows key, Mac ⌘ key or Meta key
 *
 * Pwr:         Power for Unix and Mac
 * VDn,Vup,Mut: Volume control for Unix and Mac
 * Stp,Agn..:   for Unix
 *
 * KP,:         Brazilian Keypad Comma
 * KP=:         Keypad = for Mac
 * <,#:         ISO keys(UK legend)
 * JPY:         Japanese Yen(￥)
 * RO:          Japanese ろ or Brazilian /
 * MHEN:        Japanese 無変換 Non Conversion
 * HENK:        Japanese 変換 Conversion
 * KANA:        Japanese かな Hiragana/Katakana
 *              https://en.wikipedia.org/wiki/Keyboard_layout#Japanese
 * H/E:         Korean 한/영 Hangul/English
 * HNJ:         Korean 한자 Hanja
 *              https://en.wikipedia.org/wiki/Keyboard_layout#Hangul_.28for_Korean.29
 *
 * TODO: use same keycode to pass through instead of KC_NO?
 */
#define KEYMAP_ALL( \
            K68,K69,K6A,K6B,K6C,K6D,K6E,K6F,K70,K71,K72,K73,                                              \
    K29,    K3A,K3B,K3C,K3D,K3E,K3F,K40,K41,K42,K43,K44,K45,      K46,K47,K48,  K81,K80,K7F,K66, K75,     \
    K35,K1E,K1F,K20,K21,K22,K23,K24,K25,K26,K27,K2D,K2E,K89,K2A,  K49,K4A,K4B,  K53,K54,K55,K56, K78,K79, \
    K2B,K14,K1A,K08,K15,K17,K1C,K18,K0C,K12,K13,K2F,K30,    K31,  K4C,K4D,K4E,  K5F,K60,K61,K57, K76,K7A, \
    K39,K04,K16,K07,K09,K0A,K0B,K0D,K0E,K0F,K33,K34,    K32,K28,                K5C,K5D,K5E,K85, K77,K7C, \
    KE1,K64,K1D,K1B,K06,K19,K05,K11,K10,K36,K37,K38,    K87,KE5,      K52,      K59,K5A,K5B,K67, K74,K7D, \
    KE0,KE3,KE2,K8B,K91,    K2C,    K90,K8A,K88,KE6,KE7,K65,KE4,  K50,K51,K4F,  K62,    K63,K58, K7E,K7B  \
) { \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_##K04, KC_##K05, KC_##K06, KC_##K07,   /* 00-07 */ \
      KC_##K08, KC_##K09, KC_##K0A, KC_##K0B, KC_##K0C, KC_##K0D, KC_##K0E, KC_##K0F }, /* 08-0F */ \
    { KC_##K10, KC_##K11, KC_##K12, KC_##K13, KC_##K14, KC_##K15, KC_##K16, KC_##K17,   /* 10-17 */ \
      KC_##K18, KC_##K19, KC_##K1A, KC_##K1B, KC_##K1C, KC_##K1D, KC_##K1E, KC_##K1F }, /* 18-1F */ \
    { KC_##K20, KC_##K21, KC_##K22, KC_##K23, KC_##K24, KC_##K25, KC_##K26, KC_##K27,   /* 20-27 */ \
      KC_##K28, KC_##K29, KC_##K2A, KC_##K2B, KC_##K2C, KC_##K2D, KC_##K2E, KC_##K2F }, /* 28-2F */ \
    { KC_##K30, KC_##K31, KC_##K32, KC_##K33, KC_##K34, KC_##K35, KC_##K36, KC_##K37,   /* 30-37 */ \
      KC_##K38, KC_##K39, KC_##K3A, KC_##K3B, KC_##K3C, KC_##K3D, KC_##K3E, KC_##K3F }, /* 38-3F */ \
    { KC_##K40, KC_##K41, KC_##K42, KC_##K43, KC_##K44, KC_##K45, KC_##K46, KC_##K47,   /* 40-47 */ \
      KC_##K48, KC_##K49, KC_##K4A, KC_##K4B, KC_##K4C, KC_##K4D, KC_##K4E, KC_##K4F }, /* 48-4F */ \
    { KC_##K50, KC_##K51, KC_##K52, KC_##K53, KC_##K54, KC_##K55, KC_##K56, KC_##K57,   /* 50-57 */ \
      KC_##K58, KC_##K59, KC_##K5A, KC_##K5B, KC_##K5C, KC_##K5D, KC_##K5E, KC_##K5F }, /* 58-5F */ \
    { KC_##K60, KC_##K61, KC_##K62, KC_##K63, KC_##K64, KC_##K65, KC_##K66, KC_##K67,   /* 60-67 */ \
      KC_##K68, KC_##K69, KC_##K6A, KC_##K6B, KC_##K6C, KC_##K6D, KC_##K6E, KC_##K6F }, /* 68-6F */ \
    { KC_##K70, KC_##K71, KC_##K72, KC_##K73, KC_##K74, KC_##K75, KC_##K76, KC_##K77,   /* 70-77 */ \
      KC_##K78, KC_##K79, KC_##K7A, KC_##K7B, KC_##K7C, KC_##K7D, KC_##K7E, KC_##K7F }, /* 78-7F */ \
    { KC_##K80, KC_##K81, KC_NO,    KC_NO,    KC_NO,    KC_##K85, KC_NO,    KC_##K87,   /* 80-87 */ \
      KC_##K88, KC_##K89, KC_##K8A, KC_##K8B, KC_NO,    KC_NO,    KC_NO,    KC_NO    }, /* 88-8F */ \
    { KC_##K90, KC_##K91, KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,      /* 90-97 */ \
      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, /* 98-9F */ \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,      /* A0-A7 */ \
      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, /* A8-AF */ \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,      /* B0-B7 */ \
      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, /* B8-BF */ \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,      /* C0-C7 */ \
      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, /* C8-CF */ \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,      /* D0-D7 */ \
      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, /* D8-DF */ \
    { KC_##KE0, KC_##KE1, KC_##KE2, KC_##KE3, KC_##KE4, KC_##KE5, KC_##KE6, KC_##KE7,   /* E0-E7 */ \
      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, /* E8-EF */ \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,      /* F0-F7 */ \
      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, /* F8-FF */ \
}

/* ,---.   ,---------------. ,---------------. ,---------------. ,-----------.
 * |Esc|   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| |PrS|ScL|Pau|
 * `---'   `---------------' `---------------' `---------------' `-----------'
 * ,-----------------------------------------------------------. ,-----------. ,---------------.
 * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|    Bsp| |Ins|Hom|PgU| |NmL|  /|  *|  -|
 * |-----------------------------------------------------------| |-----------| |---------------|
 * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  | |Del|End|PgD| |  7|  8|  9|  +|
 * |-----------------------------------------------------------| `-----------' |-----------|   |
 * |CapsL |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|  Return|               |  4|  5|  6|  +|
 * |-----------------------------------------------------------|     ,---.     |---------------|
 * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /|Shift     |     |Up |     |  1|  2|  3|   |
 * |-----------------------------------------------------------| ,-----------. |-----------|   |
 * |Ctl|Gui|Alt|           Space               |Alt|Gui|App|Ctl| |Lef|Dow|Rig| |      0|  .|Ent|
 * `-----------------------------------------------------------' `-----------' `---------------'
 */
#define KEYMAP( \
    K29,K3A,K3B,K3C,K3D,K3E,K3F,K40,K41,K42,K43,K44,K45,      K46,K47,K48,                   \
    K35,K1E,K1F,K20,K21,K22,K23,K24,K25,K26,K27,K2D,K2E,K2A,  K49,K4A,K4B,  K53,K54,K55,K56, \
    K2B,K14,K1A,K08,K15,K17,K1C,K18,K0C,K12,K13,K2F,K30,K31,  K4C,K4D,K4E,  K5F,K60,K61,     \
    K39,K04,K16,K07,K09,K0A,K0B,K0D,K0E,K0F,K33,K34,    K28,                K5C,K5D,K5E,K57, \
    KE1,K1D,K1B,K06,K19,K05,K11,K10,K36,K37,K38,        KE5,      K52,      K59,K5A,K5B,     \
    KE0,KE3,KE2,        K2C,                KE6,KE7,K65,KE4,  K50,K51,K4F,  K62,    K63,K58  \
) KEYMAP_ALL( \
            NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO,                                               \
    K29,    K3A,K3B,K3C,K3D,K3E,K3F,K40,K41,K42,K43,K44,K45,      K46,K47,K48,  NO, NO, NO, NO,  NO,      \
    K35,K1E,K1F,K20,K21,K22,K23,K24,K25,K26,K27,K2D,K2E,NO, K2A,  K49,K4A,K4B,  K53,K54,K55,K56, NO, NO,  \
    K2B,K14,K1A,K08,K15,K17,K1C,K18,K0C,K12,K13,K2F,K30,    K31,  K4C,K4D,K4E,  K5F,K60,K61,K57, NO, NO,  \
    K39,K04,K16,K07,K09,K0A,K0B,K0D,K0E,K0F,K33,K34,    NO, K28,                K5C,K5D,K5E,NO,  NO, NO,  \
    KE1,NO, K1D,K1B,K06,K19,K05,K11,K10,K36,K37,K38,    NO, KE5,      K52,      K59,K5A,K5B,NO,  NO, NO,  \
    KE0,KE3,KE2,NO, NO,     K2C,    NO, NO, NO, KE6,KE7,K65,KE4,  K50,K51,K4F,  K62,    K63,K58, NO, NO   \
)

/* ,---.   ,---------------. ,---------------. ,---------------. ,-----------.
 * |Esc|   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| |PrS|ScL|Pau|
 * `---'   `---------------' `---------------' `---------------' `-----------'
 * ,-----------------------------------------------------------. ,-----------. ,---------------.
 * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|    Bsp| |Ins|Hom|PgU| |NmL|  /|  *|  -|
 * |-----------------------------------------------------------| |-----------| |---------------|
 * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]| Retn| |Del|End|PgD| |  7|  8|  9|  +|
 * |------------------------------------------------------`    | `-----------' |-----------|   |
 * |CapsL |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  :|  #|    |               |  4|  5|  6|   |
 * |-----------------------------------------------------------|     ,---.     |---------------|
 * |Shft|  <|  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /|Shift     |     |Up |     |  1|  2|  3|Ent|
 * |-----------------------------------------------------------| ,-----------. |-----------|   |
 * |Ctl|Gui|Alt|           Space               |Alt|Gui|App|Ctl| |Lef|Dow|Rig| |      0|  .|   |
 * `-----------------------------------------------------------' `-----------' `---------------'
 */
#define KEYMAP_ISO( \
    K29,    K3A,K3B,K3C,K3D,K3E,K3F,K40,K41,K42,K43,K44,K45,  K46,K47,K48,                   \
    K35,K1E,K1F,K20,K21,K22,K23,K24,K25,K26,K27,K2D,K2E,K2A,  K49,K4A,K4B,  K53,K54,K55,K56, \
    K2B,K14,K1A,K08,K15,K17,K1C,K18,K0C,K12,K13,K2F,K30,K28,  K4C,K4D,K4E,  K5F,K60,K61,K57, \
    K39,K04,K16,K07,K09,K0A,K0B,K0D,K0E,K0F,K33,K34,K32,                    K5C,K5D,K5E,     \
    KE1,K64,K1D,K1B,K06,K19,K05,K11,K10,K36,K37,K38,    KE5,      K52,      K59,K5A,K5B,K58, \
    KE0,KE3,KE2,        K2C,                KE6,KE7,K65,KE4,  K50,K51,K4F,  K62,    K63      \
) KEYMAP_ALL( \
            NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO,                                               \
    K29,    K3A,K3B,K3C,K3D,K3E,K3F,K40,K41,K42,K43,K44,K45,      K46,K47,K48,  NO, NO, NO, NO,  NO,      \
    K35,K1E,K1F,K20,K21,K22,K23,K24,K25,K26,K27,K2D,K2E,NO, K2A,  K49,K4A,K4B,  K53,K54,K55,K56, NO, NO,  \
    K2B,K14,K1A,K08,K15,K17,K1C,K18,K0C,K12,K13,K2F,K30,    K32,  K4C,K4D,K4E,  K5F,K60,K61,K57, NO, NO,  \
    K39,K04,K16,K07,K09,K0A,K0B,K0D,K0E,K0F,K33,K34,    K32,K28,                K5C,K5D,K5E,NO,  NO, NO,  \
    KE1,K64,K1D,K1B,K06,K19,K05,K11,K10,K36,K37,K38,    NO, KE5,      K52,      K59,K5A,K5B,NO,  NO, NO,  \
    KE0,KE3,KE2,NO, NO,     K2C,    NO, NO, NO, KE6,KE7,K65,KE4,  K50,K51,K4F,  K62,    K63,K58, NO, NO   \
)

/* ,---.   ,---------------. ,---------------. ,---------------. ,-----------.
 * |Esc|   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| |PrS|ScL|Pau|
 * `---'   `---------------' `---------------' `---------------' `-----------'
 * ,-----------------------------------------------------------. ,-----------. ,---------------.
 * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  ^|JPY|Bsp| |Ins|Hom|PgU| |NmL|  /|  *|  -|
 * |-----------------------------------------------------------| |-----------| |---------------|
 * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  @|  [| Retn| |Del|End|PgD| |  7|  8|  9|  +|
 * |------------------------------------------------------`    | `-----------' |-----------|   |
 * |CapsL |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  :|  ]|    |               |  4|  5|  6|   |
 * |-----------------------------------------------------------|     ,---.     |---------------|
 * |Shft    |  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /| RO|Shift |     |Up |     |  1|  2|  3|Ent|
 * |-----------------------------------------------------------| ,-----------. |-----------|   |
 * |Ctl|Gui|Alt|MHEN|      Space      |HENK|KNA|Alt|Gui|App|Ctl| |Lef|Dow|Rig| |      0|  .|   |
 * `-----------------------------------------------------------' `-----------' `---------------'
 */
#define KEYMAP_JIS( \
    K29,    K3A,K3B,K3C,K3D,K3E,K3F,K40,K41,K42,K43,K44,K45,      K46,K47,K48,                   \
    K35,K1E,K1F,K20,K21,K22,K23,K24,K25,K26,K27,K2D,K2E,K89,K2A,  K49,K4A,K4B,  K53,K54,K55,K56, \
    K2B,K14,K1A,K08,K15,K17,K1C,K18,K0C,K12,K13,K2F,K30,    K28,  K4C,K4D,K4E,  K5F,K60,K61,K57, \
    K39,K04,K16,K07,K09,K0A,K0B,K0D,K0E,K0F,K33,K34,K32,                        K5C,K5D,K5E,     \
    KE1,K1D,K1B,K06,K19,K05,K11,K10,K36,K37,K38,        K87,KE5,      K52,      K59,K5A,K5B,K58, \
    KE0,KE3,KE2,K8B,    K2C,        K8A,K88,KE6,KE7,K65,KE4,      K50,K51,K4F,  K62,    K63      \
) KEYMAP_ALL( \
            NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO,                                               \
    K29,    K3A,K3B,K3C,K3D,K3E,K3F,K40,K41,K42,K43,K44,K45,      K46,K47,K48,  NO, NO, NO, NO,  NO,      \
    K35,K1E,K1F,K20,K21,K22,K23,K24,K25,K26,K27,K2D,K2E,K89,K2A,  K49,K4A,K4B,  K53,K54,K55,K56, NO, NO,  \
    K2B,K14,K1A,K08,K15,K17,K1C,K18,K0C,K12,K13,K2F,K30,    K32,  K4C,K4D,K4E,  K5F,K60,K61,K57, NO, NO,  \
    K39,K04,K16,K07,K09,K0A,K0B,K0D,K0E,K0F,K33,K34,    K32,K28,                K5C,K5D,K5E,NO,  NO, NO,  \
    KE1,NO, K1D,K1B,K06,K19,K05,K11,K10,K36,K37,K38,    K87,KE5,      K52,      K59,K5A,K5B,NO,  NO, NO,  \
    KE0,KE3,KE2,K8B,NO,     K2C,    NO, K8A,K88,KE6,KE7,K65,KE4,  K50,K51,K4F,  K62,    K63,K58, NO, NO   \
)
#endif
