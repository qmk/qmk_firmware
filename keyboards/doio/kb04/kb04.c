#include "kb04.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    {  0,      1,      2,      3,      4},
}, {
    {0  ,  0}, {75 ,  0}, {149,  0}, {224,  0}, {112,  64},
}, {
    1, 1, 1, 1, 1
} };
#endif
