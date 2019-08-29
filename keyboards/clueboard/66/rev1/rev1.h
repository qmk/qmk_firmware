#pragma once

#include "quantum.h"

/* Clueboard matrix layout
 * ,-----------------------------------------------------------.  ,---.
 * | 00| 01| 02| 03| 04| 05| 06| 07| 08| 09| 0A| 0B| 0C| 0D| 0E|  | 0F|
 * |-----------------------------------------------------------|  |---|
 * |   10| 11| 12| 13| 14| 15| 16| 17| 18| 19| 1A| 1B| 1C|   1D|  | 1F|
 * |-----------------------------------------------------------|  `---'
 * |    20| 21| 22| 23| 24| 25| 26| 27| 28| 29| 2A| 2B| 2C|  2D|
 * |------------------------------------------------------------.
 * |  30| 31| 32| 33| 34| 35| 36| 37| 38| 39| 3A| 3B| 3C|  3D|3E|
 * |------------------------------------------------------------------.
 * |  40| 41|  42|  43|   45|       46|   49|  4A|  4B| 4C| 4D| 4E| 4F|
 * `------------------------------------------------------------------'
 * ,-----------------------------------------------------------.  ,---.
 * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Yen| BS|  |Ins|
 * |-----------------------------------------------------------|  |---|
 * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|  |Del|
 * |-----------------------------------------------------------|  `---'
 * |Caps  |  A|  S|  D|  F|  G|  H|  J|  k|  L|  ;|  '| # | Ent|
 * |--------------------------------------------------------------.
 * |Shift| \|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|  \|Shift| Up|
 * |------------------------------------------------------------------.
 * |Ctrl|Alt|Gui |MHen| Space| Space|Henk|Gui |Ctrl|  Fn|Left|Down|Rgt|
 * `------------------------------------------------------------------'
 */
// The first section contains all of the arguements
// The second converts the arguments into a two-dimensional array

#define LAYOUT_all( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D,      k1F, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E, \
    k40, k41, k42, k43,      k45, k46,           k49, k4A, k4B, k4C, k4D, k4E, k4F \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, 	k0E, 	  k0F }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, 	KC_NO,    k1F }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E }, \
    { k40, k41, k42, k43, KC_NO,    k45, k46, KC_NO,    KC_NO,    k49, k4A, k4B, k4C, k4D, k4E, k4F }  \
}

#define LAYOUT_66_ansi( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C,    k0E,   k0F, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D,      k1F, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B,     k2D, \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B,    k3D,   k3E, \
    k40, k41, k42,                k46,                k4A, k4B, k4C, k4D, k4E, k4F \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, KC_NO, 	k0E, 	  k0F }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, 	KC_NO,    k1F }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, KC_NO, k2D }, \
    { k30, KC_NO, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, KC_NO, k3D, k3E }, \
    { k40, k41, k42, KC_NO, KC_NO, KC_NO, k46, KC_NO, KC_NO, KC_NO, k4A, k4B, k4C, k4D, k4E, k4F }  \
}

#define LAYOUT_66_iso( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C,    k0E,   k0F, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C,           k1F, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B,    k3D,   k3E, \
    k40, k41, k42,                k46,                k4A, k4B, k4C, k4D, k4E, k4F \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, KC_NO, k0E, k0F }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, KC_NO, KC_NO, k1F }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, KC_NO, k3D, k3E }, \
    { k40, k41, k42, KC_NO, KC_NO, KC_NO, k46, KC_NO, KC_NO, KC_NO, k4A, k4B, k4C, k4D, k4E, k4F }  \
}

#define KEYMAP LAYOUT_all
#define LAYOUT LAYOUT_all
