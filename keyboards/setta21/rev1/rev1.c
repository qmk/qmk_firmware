#include "rev1.h"

#ifdef RGB_MATRIX_ENABLE
    led_config_t g_led_config = { {
    // Key Matrix to LED Index
        { 14,13, 7, 6, 0,20 },
        {    12, 8, 5, 1,19 },
        { 15,11, 9, 4, 2,18 },
        { 16,   10,    3,17 }
    }, {
    // LED Index to Physical Position
        {   0, 179 }, {  21, 179 }, {  43, 179 }, {  64, 179 }, {  43, 134 }, {  21, 134 }, {   0, 134 }, {   0,  90 }, {  21,  90 }, {  43,  90 },
        {  64, 112 }, {  43,  45 }, {  21,  45 }, {   0,  45 }, {  11,   0 }, {  43,   0 }, {  64,  23 }, {  64, 224 }, {  43, 224 }, {  21, 224 },
        {   0, 224 }
    }, {
    // LED Index to Flag
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4
} };
#endif

void matrix_init_kb(void) {
	matrix_init_user();
};
