#pragma once

#include "dactyl_manuform.h"

#define XXX KC_NO

#define LAYOUT_6x6( \
    L21, L22, L23, L24, L25,                           R21, R22, R23, R24, R25, \
    L31, L32, L33, L34, L35,                           R31, R32, R33, R34, R35, \
    L41, L42, L43, L44, L45,                           R41, R42, R43, R44, R45, \
              L53, L54, L55,                           R51, R52, R53 \
) { \
    { XXX, XXX, XXX, XXX, XXX, XXX }, \
    { XXX, XXX, XXX, XXX, XXX, XXX }, \
    { XXX, L21, L22, L23, L24, L25 }, \
    { XXX, L31, L32, L33, L34, L35 }, \
    { XXX, L41, L42, L43, L44, L45 }, \
    { XXX, XXX, XXX, L53, L54, L55 }, \
    { XXX, XXX, XXX, XXX, XXX, XXX }, \
\
    { XXX, XXX, XXX, XXX, XXX, XXX }, \
    { XXX, XXX, XXX, XXX, XXX, XXX }, \
    { XXX, R21, R22, R23, R24, R25 }, \
    { XXX, R31, R32, R33, R34, R35 }, \
    { XXX, R41, R42, R43, R44, R45 }, \
    { XXX, R51, R52, R53, XXX, XXX }, \
    { XXX, XXX, XXX, XXX, XXX, XXX } \
}
