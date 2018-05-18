#include "vortex.h"
#include "proto.h"
#include "quantum.h"
#include "raw_hid.h"
#include "debug.h"

const uint8_t keymap_layouts[NUM_LAYOUTS][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_core(
        1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13,
        14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
        26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37,
        38, 39, 40, 41, 42, 43, 44, 45, 46, 47
    ),
};

const char *layout_names =
    "core,"     // vortex core layout
;
