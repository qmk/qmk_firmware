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

#pragma once

#include "quantum.h"

#if defined(KEYBOARD_converter_usb_usb_ble)
#    include "ble.h"
#elif defined(KEYBOARD_converter_usb_usb_hasu)
#    include "hasu.h"
#elif defined(KEYBOARD_converter_usb_usb_pro_micro)
#    include "pro_micro.h"
#endif

#define XXX KC_NO

#define ______ KC_TRNS

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
              k68, k69, k6A, k6B, k6C, k6D, k6E, k6F, k70, k71, k72, k73, \
    k29,      k3A, k3B, k3C, k3D, k3E, k3F, k40, k41, k42, k43, k44, k45,       k46, k47, k48,  k81, k80, k7F, k66,  k75, \
\
    k35, k1E, k1F, k20, k21, k22, k23, k24, k25, k26, k27, k2D, k2E, k89, k2A,  k49, k4A, k4B,  k53, k54, k55, k56,  k78, k79, \
    k2B, k14, k1A, k08, k15, k17, k1C, k18, k0C, k12, k13, k2F, k30, k31,       k4C, k4D, k4E,  k5F, k60, k61, k57,  k76, k7A, \
    k39, k04, k16, k07, k09, k0A, k0B, k0D, k0E, k0F, k33, k34, k32, k28,                       k5C, k5D, k5E, k85,  k77, k7C, \
    kE1, k64, k1D, k1B, k06, k19, k05, k11, k10, k36, k37, k38, k87, kE5,            k52,       k59, k5A, k5B, k67,  k74, k7D, \
    kE0, kE3, kE2, k8B, k91,      k2C, k90, k8A, k88, kE6, kE7, k65, kE4,       k50, k51, k4F,  k62,      k63, k58,  k7E, k7B \
) { \
    { XXX, XXX, XXX, XXX, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E, k2F }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E, k3F }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D, k4E, k4F }, \
    { k50, k51, k52, k53, k54, k55, k56, k57, k58, k59, k5A, k5B, k5C, k5D, k5E, k5F }, \
    { k60, k61, k62, k63, k64, k65, k66, k67, k68, k69, k6A, k6B, k6C, k6D, k6E, k6F }, \
    { k70, k71, k72, k73, k74, k75, k76, k77, k78, k79, k7A, k7B, k7C, k7D, k7E, k7F }, \
    { k80, k81, XXX, XXX, XXX, k85, XXX, k87, k88, k89, k8A, k8B, XXX, XXX, XXX, XXX }, \
    { k90, k91, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX }, \
    { kE0, kE1, kE2, kE3, kE4, kE5, kE6, kE7, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX } \
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
#define LAYOUT_fullsize_ansi( \
    k29,      k3A, k3B, k3C, k3D, k3E, k3F, k40, k41, k42, k43, k44, k45,  k46, k47, k48, \
\
    k35, k1E, k1F, k20, k21, k22, k23, k24, k25, k26, k27, k2D, k2E, k2A,  k49, k4A, k4B,  k53, k54, k55, k56, \
    k2B, k14, k1A, k08, k15, k17, k1C, k18, k0C, k12, k13, k2F, k30, k31,  k4C, k4D, k4E,  k5F, k60, k61, k57, \
    k39, k04, k16, k07, k09, k0A, k0B, k0D, k0E, k0F, k33, k34,      k28,                  k5C, k5D, k5E, \
    kE1,      k1D, k1B, k06, k19, k05, k11, k10, k36, k37, k38,      kE5,       k52,       k59, k5A, k5B, k58, \
    kE0, kE3, kE2,                k2C,                kE6, kE7, k65, kE4,  k50, k51, k4F,  k62,      k63 \
) { \
    { XXX, XXX, XXX, XXX, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E, k2F }, \
    { k30, k31, XXX, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E, k3F }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D, k4E, k4F }, \
    { k50, k51, k52, k53, k54, k55, k56, k57, k58, k59, k5A, k5B, k5C, k5D, k5E, k5F }, \
    { k60, k61, k62, k63, XXX, k65, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX }, \
    { kE0, kE1, kE2, kE3, kE4, kE5, kE6, kE7, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX } \
}

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
#define LAYOUT_fullsize_iso( \
    k29,      k3A, k3B, k3C, k3D, k3E, k3F, k40, k41, k42, k43, k44, k45,  k46, k47, k48, \
\
    k35, k1E, k1F, k20, k21, k22, k23, k24, k25, k26, k27, k2D, k2E, k2A,  k49, k4A, k4B,  k53, k54, k55, k56, \
    k2B, k14, k1A, k08, k15, k17, k1C, k18, k0C, k12, k13, k2F, k30,       k4C, k4D, k4E,  k5F, k60, k61, k57, \
    k39, k04, k16, k07, k09, k0A, k0B, k0D, k0E, k0F, k33, k34, k32, k28,                  k5C, k5D, k5E, \
    kE1, k64, k1D, k1B, k06, k19, k05, k11, k10, k36, k37, k38,      kE5,       k52,       k59, k5A, k5B, k58, \
    kE0, kE3, kE2,                k2C,                kE6, kE7, k65, kE4,  k50, k51, k4F,  k62,      k63 \
) { \
    { XXX, XXX, XXX, XXX, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E, k2F }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E, k3F }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D, k4E, k4F }, \
    { k50, k51, k52, k53, k54, k55, k56, k57, k58, k59, k5A, k5B, k5C, k5D, k5E, k5F }, \
    { k60, k61, k62, k63, k64, k65, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,}, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,}, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX }, \
    { kE0, kE1, kE2, kE3, kE4, kE5, kE6, kE7, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX } \
}

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
#define LAYOUT_fullsize_jis( \
    k29,      k3A, k3B, k3C, k3D, k3E, k3F, k40, k41, k42, k43, k44, k45,       k46, k47, k48, \
\
    k35, k1E, k1F, k20, k21, k22, k23, k24, k25, k26, k27, k2D, k2E, k89, k2A,  k49, k4A, k4B,  k53, k54, k55, k56, \
    k2B, k14, k1A, k08, k15, k17, k1C, k18, k0C, k12, k13, k2F, k30,            k4C, k4D, k4E,  k5F, k60, k61, k57, \
    k39, k04, k16, k07, k09, k0A, k0B, k0D, k0E, k0F, k33, k34, k32, k28,                       k5C, k5D, k5E, \
    kE1,      k1D, k1B, k06, k19, k05, k11, k10, k36, k37, k38, k87, kE5,            k52,       k59, k5A, k5B, k58, \
    kE0, kE3, kE2, k8B,      k2C,           k8A, k88, kE6, kE7, k65, kE4,       k50, k51, k4F,  k62,      k63 \
) { \
    { XXX, XXX, XXX, XXX, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E, k2F }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E, k3F }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D, k4E, k4F }, \
    { k50, k51, k52, k53, k54, k55, k56, k57, k58, k59, k5A, k5B, k5C, k5D, k5E, k5F }, \
    { k60, k61, k62, k63, XXX, k65, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, k87, k88, k89, k8A, k8B, XXX, XXX, XXX, XXX }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX }, \
    { kE0, kE1, kE2, kE3, kE4, kE5, kE6, kE7, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX } \
}
