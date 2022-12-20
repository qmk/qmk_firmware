#pragma once

#include "quantum.h"

#define XXX KC_NO

#define LAYOUT_5x7( \
    L11, L12, L13, L14, L15, L16, L17, \
    L21, L22, L23, L24, L25, L26, L27, \
    L31, L32, L33, L34, L35, L36, L37, \
    L41, L42, L43, L44, L45, L46, \
    L51, L52, L53, L54, \
                        L55, L56, \
                                  L65, L66, \
                                  L63, L64, \
         R11, R12, R13, R14, R15, R16, R17, \
         R21, R22, R23, R24, R25, R26, R27, \
         R31, R32, R33, R34, R35, R36, R37, \
              R42, R43, R44, R45, R46, R47, \
                        R54, R55, R56, R57, \
              R52, R53, \
    R62, R63, \
    R64, R65 \
) { \
    { L11, L12, L13, L14, L15, L16, L17 }, \
    { L21, L22, L23, L24, L25, L26, L27 }, \
    { L31, L32, L33, L34, L35, L36, L37 }, \
    { L41, L42, L43, L44, L45, L46, XXX }, \
    { L51, L52, L53, L54, L55, L56, XXX }, \
    { XXX, XXX, L63, L64, L65, L66, XXX }, \
    { R11, R12, R13, R14, R15, R16, R17 }, \
    { R21, R22, R23, R24, R25, R26, R27 }, \
    { R31, R32, R33, R34, R35, R36, R37 }, \
    { XXX, R42, R43, R44, R45, R46, R47 }, \
    { XXX, R52, R53, R54, R55, R56, R57 }, \
    { XXX, R62, R63, R64, R65, XXX, XXX } \
}
