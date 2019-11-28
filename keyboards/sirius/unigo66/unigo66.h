/*
Copyright 2017 Balz Guenat <balz.guenat@gmail.com>

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

#ifndef USB_USB_H
#define USB_USB_H

#include "quantum.h"

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
#define LAYOUT_all( \
            K68,K69,K6A,K6B,K6C,K6D,K6E,K6F,K70,K71,K72,K73,                                              \
    K29,    K3A,K3B,K3C,K3D,K3E,K3F,K40,K41,K42,K43,K44,K45,      K46,K47,K48,  K81,K80,K7F,K66, K75,     \
    K35,K1E,K1F,K20,K21,K22,K23,K24,K25,K26,K27,K2D,K2E,K89,K2A,  K49,K4A,K4B,  K53,K54,K55,K56, K78,K79, \
    K2B,K14,K1A,K08,K15,K17,K1C,K18,K0C,K12,K13,K2F,K30,    K31,  K4C,K4D,K4E,  K5F,K60,K61,K57, K76,K7A, \
    K39,K04,K16,K07,K09,K0A,K0B,K0D,K0E,K0F,K33,K34,    K32,K28,                K5C,K5D,K5E,K85, K77,K7C, \
    KE1,K64,K1D,K1B,K06,K19,K05,K11,K10,K36,K37,K38,    K87,KE5,      K52,      K59,K5A,K5B,K67, K74,K7D, \
    KE0,KE3,KE2,K8B,K91,    K2C,    K90,K8A,K88,KE6,KE7,K65,KE4,  K50,K51,K4F,  K62,    K63,K58, K7E,K7B  \
) { \
    { KC_NO, KC_NO, KC_NO, KC_NO, K04,   K05,   K06,   K07,      /* 00-07 */ \
      K08,   K09,   K0A,   K0B,   K0C,   K0D,   K0E,   K0F    }, /* 08-0F */ \
    { K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,      /* 10-17 */ \
      K18,   K19,   K1A,   K1B,   K1C,   K1D,   K1E,   K1F    }, /* 18-1F */ \
    { K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,      /* 20-27 */ \
      K28,   K29,   K2A,   K2B,   K2C,   K2D,   K2E,   K2F    }, /* 28-2F */ \
    { K30,   K31,   K32,   K33,   K34,   K35,   K36,   K37,      /* 30-37 */ \
      K38,   K39,   K3A,   K3B,   K3C,   K3D,   K3E,   K3F    }, /* 38-3F */ \
    { K40,   K41,   K42,   K43,   K44,   K45,   K46,   K47,      /* 40-47 */ \
      K48,   K49,   K4A,   K4B,   K4C,   K4D,   K4E,   K4F    }, /* 48-4F */ \
    { K50,   K51,   K52,   K53,   K54,   K55,   K56,   K57,      /* 50-57 */ \
      K58,   K59,   K5A,   K5B,   K5C,   K5D,   K5E,   K5F    }, /* 58-5F */ \
    { K60,   K61,   K62,   K63,   K64,   K65,   K66,   K67,      /* 60-67 */ \
      K68,   K69,   K6A,   K6B,   K6C,   K6D,   K6E,   K6F    }, /* 68-6F */ \
    { K70,   K71,   K72,   K73,   K74,   K75,   K76,   K77,      /* 70-77 */ \
      K78,   K79,   K7A,   K7B,   K7C,   K7D,   K7E,   K7F    }, /* 78-7F */ \
    { K80,   K81,   KC_NO, KC_NO, KC_NO, K85,   KC_NO, K87,      /* 80-87 */ \
      K88,   K89,   K8A,   K8B,   KC_NO, KC_NO, KC_NO, KC_NO  }, /* 88-8F */ \
    { K90,   K91,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    /* 90-97 */ \
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO  }, /* 98-9F */ \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    /* A0-A7 */ \
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO  }, /* A8-AF */ \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    /* B0-B7 */ \
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO  }, /* B8-BF */ \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    /* C0-C7 */ \
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO  }, /* C8-CF */ \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    /* D0-D7 */ \
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO  }, /* D8-DF */ \
    { KE0,   KE1,   KE2,   KE3,   KE4,   KE5,   KE6,   KE7,      /* E0-E7 */ \
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO  }, /* E8-EF */ \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    /* F0-F7 */ \
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO  }, /* F8-FF */ \
}

#define LAYOUT( \
  K29,K1E,K1F,K20,K21,K22,K2D,    K2E,K23,K24,K25,K26,K27,K2A,\
  K2B,K14,K1A,K08,K15,K17,K4B,    K2F,K1C,K18,K0C,K12,K13,K31,\
  K39,K04,K16,K07,K09,K0A,            K0B,K0D,K0E,K0F,K33,K34,\
  KE1,K1D,K1B,K06,K19,K05,K4E,    K30,K11,K10,K36,K37,K52,KE5,\
  KE0,KE3,KE2,                                    K50,K51,K4F,\
                      K2C,K49,    K4A,K28,        \
                      KE6,K4C,    K4D,KE4         \
) LAYOUT_all( \
            KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,                                              \
    K29,    KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,      KC_NO,KC_NO,KC_NO,  KC_NO,KC_NO,KC_NO,KC_NO, KC_NO,     \
    KC_NO,K1E,K1F,K20,K21,K22,K23,K24,K25,K26,K27,K2D,K2E,KC_NO,K2A,  K49,K4A,K4B,  KC_NO,KC_NO,KC_NO,KC_NO, KC_NO,KC_NO, \
    K2B,K14,K1A,K08,K15,K17,K1C,K18,K0C,K12,K13,K2F,K30,    K31,  K4C,K4D,K4E,  KC_NO,KC_NO,KC_NO,KC_NO, KC_NO,KC_NO, \
    K39,K04,K16,K07,K09,K0A,K0B,K0D,K0E,K0F,K33,K34,    KC_NO,K28,                KC_NO,KC_NO,KC_NO,KC_NO, KC_NO,KC_NO, \
    KE1,KC_NO,K1D,K1B,K06,K19,K05,K11,K10,K36,K37,KC_NO,    KC_NO,KE5,      K52,      KC_NO,KC_NO,KC_NO,KC_NO, KC_NO,KC_NO, \
    KE0,KE3,KE2,KC_NO,KC_NO,    K2C,    KC_NO,KC_NO,KC_NO,KE6,KC_NO,KC_NO,KE4,  K50,K51,K4F,  KC_NO,      KC_NO,KC_NO, KC_NO,KC_NO  \
)

#define LAYOUT_beta_pcb( \
  K1E, K1F, K30, K2F, K45, K3B, KE6,          KE2, K3A, K39, K14, K04, K09, K07, \
  K29, K15, K3C, K3D, K3E, K3F, K58,          K50, K2C, K11, K05, K55, K10, K06, \
  K31, K5F, K5E, K61, K2A, K38,                    K4C, K57, K53, K5B, K5A, K08, \
  K35, K5D, K17, K1B, K1A, K52, K56,          K51, K4D, K23, K1C, K13, K2E, K0C, \
  K5C, K0A, K0F,                                                  K36, K0E, K37, \
                           KE4, K49,          K4B, KE0,                          \
                                KE5,          KE1\
) LAYOUT_all( \
            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                          \
    K29,    K3A,K3B,K3C,K3D,K3E,K3F,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,K45,                 KC_NO,KC_NO,KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO, \
    K35,K1E,K1F,KC_NO,KC_NO,KC_NO,K23,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,K2E,KC_NO, K2A,    K49,KC_NO,K4B,  K53,KC_NO,K55,K56,     KC_NO, KC_NO,  \
    KC_NO,K14,K1A,K08,K15,K17,K1C,KC_NO,K0C,KC_NO,K13,K2F,K30,       K31,              K4C,K4D,KC_NO,  K5F,KC_NO,K61,K57,     KC_NO, KC_NO,  \
    K39,K04,KC_NO,K07,K09,K0A,KC_NO,KC_NO,K0E,K0F,KC_NO,KC_NO,    KC_NO,    KC_NO,                     K5C,K5D,K5E,KC_NO,     KC_NO, KC_NO,  \
    KE1,KC_NO, KC_NO,K1B,K06,KC_NO,K05,K11,K10,K36,K37,K38, KC_NO, KE5,                   K52,         KC_NO,K5A,K5B,KC_NO,   KC_NO, KC_NO,  \
    KE0,KC_NO,KE2,KC_NO,KC_NO,K2C,KC_NO,KC_NO,KC_NO,KE6,KC_NO,KC_NO, KE4,             K50,K51,KC_NO,   KC_NO,    KC_NO,K58,   KC_NO, KC_NO   \
)
#endif