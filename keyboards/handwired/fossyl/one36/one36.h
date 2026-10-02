#pragma once

#include "fossyl.h"

#define XXX KC_NO

#define LAYOUT( \
    L00, L01, L02, L03, L04, L05, L06, L07, L08, L09, L10, L11, \
    L20, L21, L22, L23, L24, L25, L26, L27, L28, L29, L30, L31, \
         L41, L42, L43, L44, L45, L46, L47, L48, L49, L50, \
                             L65, L66\
) { \
    { L00, L01, L02, L03, L04, L05, L06, L07, L08, L09, L10, L11}, \
    { L20, L21, L22, L23, L24, L25, L26, L27, L28, L29, L30, L31}, \
    { XXX, L41, L42, L43, L44, L45, L46, L47, L48, L49, L50, XXX}, \
    { XXX, XXX, XXX, XXX, XXX, L65, L66, XXX, XXX, XXX, XXX, XXX} \
}
