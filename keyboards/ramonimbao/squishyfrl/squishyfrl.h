/* Copyright 2021 Ramon Imbao
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "quantum.h"

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */

#define ___ KC_NO

#define LAYOUT_ansi( \
    k85, k86, k87, k88, k89, k8a, k8b, k8c, k8d, k8e, k8f, k8g, k8h,    k8i,    k4k, k4l, k4m, \
    k95,   k96, k97, k98, k99, k9a, k9b, k9c, k9d, k9e, k9f, k9g, k9h,   k9j,   k5k, k5l, k5m, \
    ka5,    ka6, ka7, ka8, ka9, kaa, kab, kac, kad, kae, kaf, kag,     kai,                    \
    kb5,      kb7, kb8, kb9, kba, kbb, kbc, kbd, kbe, kbf, kbg,     kbi, kbj,        k6l,      \
    kc5,  kc6,  kc7,                kcd,                kcf,  kcg,  kch,  kci,  k7k, k7l, k7m  \
) { \
    /*             0    1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16   17   18   19   20 */ \
    /*             0    1    2    3    4    5    6    7    8    9    a    b    c    d    e    f    g    h    i    j    k  */ \
    /* 0 | 0 */ { ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, k4k, k4l, k4m, ___, ___, ___ }, \
    /* 1 | 1 */ { ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, k5k, k5l, k5m, ___, ___, ___ }, \
    /* 2 | 2 */ { ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, k6l, ___ }, \
    /* 3 | 3 */ { ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, k7k, k7l, k7m }, \
    /* 4 | 4 */ { k85, k86, k87, k88, k89, k8a, k8b, k8c, k8d, k8e, k8f, k8g, k8h, k8i, ___, ___, ___, ___, ___, ___, ___ }, \
    /* 5 | 5 */ { k95, k96, k97, k98, k99, k9a, k9b, k9c, k9d, k9e, k9f, k9g, k9h, ___, k9j, ___, ___, ___, ___, ___, ___ }, \
    /* 6 | 6 */ { ka5, ka6, ka7, ka8, ka9, kaa, kab, kac, kad, kae, kaf, kag, ___, kai, ___, ___, ___, ___, ___, ___, ___ }, \
    /* 7 | 7 */ { kb5, ___, kb7, kb8, kb9, kba, kbb, kbc, kbd, kbe, kbf, kbg, ___, kbi, kbj, ___, ___, ___, ___, ___, ___ }, \
    /* 8 | 8 */ { kc5, kc6, kc7, ___, ___, ___, ___, ___, kcd, ___, kcf, kcg, ___, kch, kci, ___, ___, ___, ___, ___, ___ }, \
}

#define LAYOUT_iso( \
    k85, k86, k87, k88, k89, k8a, k8b, k8c, k8d, k8e, k8f, k8g, k8h,    k8i,    k4k, k4l, k4m, \
    k95,   k96, k97, k98, k99, k9a, k9b, k9c, k9d, k9e, k9f, k9g, k9h,          k5k, k5l, k5m, \
    ka5,    ka6, ka7, ka8, ka9, kaa, kab, kac, kad, kae, kaf, kag, kai,   k9j,                 \
    kb5, kb6, kb7, kb8, kb9, kba, kbb, kbc, kbd, kbe, kbf, kbg,     kbi,  kbj,       k6l,      \
    kc5,  kc6,  kc7,                kcd,                kcf,  kcg,  kch,  kci,  k7k, k7l, k7m  \
) { \
    /*             0    1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16   17   18   19   20 */ \
    /*             0    1    2    3    4    5    6    7    8    9    a    b    c    d    e    f    g    h    i    j    k  */ \
    /* 0 | 0 */ { ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, k4k, k4l, k4m, ___, ___, ___ }, \
    /* 1 | 1 */ { ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, k5k, k5l, k5m, ___, ___, ___ }, \
    /* 2 | 2 */ { ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, k6l, ___ }, \
    /* 3 | 3 */ { ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, k7k, k7l, k7m }, \
    /* 4 | 4 */ { k85, k86, k87, k88, k89, k8a, k8b, k8c, k8d, k8e, k8f, k8g, k8h, k8i, ___, ___, ___, ___, ___, ___, ___ }, \
    /* 5 | 5 */ { k95, k96, k97, k98, k99, k9a, k9b, k9c, k9d, k9e, k9f, k9g, k9h, ___, k9j, ___, ___, ___, ___, ___, ___ }, \
    /* 6 | 6 */ { ka5, ka6, ka7, ka8, ka9, kaa, kab, kac, kad, kae, kaf, kag, ___, kai, ___, ___, ___, ___, ___, ___, ___ }, \
    /* 7 | 7 */ { kb5, kb6, kb7, kb8, kb9, kba, kbb, kbc, kbd, kbe, kbf, kbg, ___, kbi, kbj, ___, ___, ___, ___, ___, ___ }, \
    /* 8 | 8 */ { kc5, kc6, kc7, ___, ___, ___, ___, ___, kcd, ___, kcf, kcg, ___, kch, kci, ___, ___, ___, ___, ___, ___ }, \
}


#define LAYOUT_all( \
    k85, k86, k87, k88, k89, k8a, k8b, k8c, k8d, k8e, k8f, k8g, k8h, k8i, k8j,  k4k, k4l, k4m, \
    k95,   k96, k97, k98, k99, k9a, k9b, k9c, k9d, k9e, k9f, k9g, k9h,   k9j,   k5k, k5l, k5m, \
    ka5,    ka6, ka7, ka8, ka9, kaa, kab, kac, kad, kae, kaf, kag,     kai,                    \
    kb5, kb6, kb7, kb8, kb9, kba, kbb, kbc, kbd, kbe, kbf, kbg,     kbi, kbj,        k6l,      \
    kc5,  kc6,  kc7,    kc8,        kcd,        kce,    kcf,  kcg,  kch,  kci,  k7k, k7l, k7m  \
) { \
    /*              0    1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16   17   18   19   20 */ \
    /*              0    1    2    3    4    5    6    7    8    9    a    b    c    d    e    f    g    h    i    j    k  */ \
    /* 0 | 0 */ { ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, k4k, k4l, k4m, ___, ___, ___ }, \
    /* 1 | 1 */ { ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, k5k, k5l, k5m, ___, ___, ___ }, \
    /* 2 | 2 */ { ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, k6l, ___ }, \
    /* 3 | 3 */ { ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, k7k, k7l, k7m }, \
    /* 4 | 4 */ { k85, k86, k87, k88, k89, k8a, k8b, k8c, k8d, k8e, k8f, k8g, k8h, k8i, k8j, ___, ___, ___, ___, ___, ___ }, \
    /* 5 | 5 */ { k95, k96, k97, k98, k99, k9a, k9b, k9c, k9d, k9e, k9f, k9g, k9h, ___, k9j, ___, ___, ___, ___, ___, ___ }, \
    /* 6 | 6 */ { ka5, ka6, ka7, ka8, ka9, kaa, kab, kac, kad, kae, kaf, kag, ___, kai, ___, ___, ___, ___, ___, ___, ___ }, \
    /* 7 | 7 */ { kb5, kb6, kb7, kb8, kb9, kba, kbb, kbc, kbd, kbe, kbf, kbg, ___, kbi, kbj, ___, ___, ___, ___, ___, ___ }, \
    /* 8 | 8 */ { kc5, kc6, kc7, kc8, ___, ___, ___, ___, kcd, kce, kcf, kcg, ___, kch, kci, ___, ___, ___, ___, ___, ___ }, \
}
