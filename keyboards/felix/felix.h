#pragma once

#include "quantum.h"

#define LAYOUT_ortho_5x4( \
    K000, K001, K002, K003, \
    K100, K101, K102, K103, \
    K200, K201, K202, K203, \
    K300, K301, K302, K303, \
    K400, K401, K402, K403  \
) { \
    { K000, K001, K002, K003 }, \
    { K100, K101, K102, K103 }, \
    { K200, K201, K202, K203 }, \
    { K300, K301, K302, K303 }, \
    { K400, K401, K402, K403 }  \
}

#define LAYOUT LAYOUT_ortho_5x4
