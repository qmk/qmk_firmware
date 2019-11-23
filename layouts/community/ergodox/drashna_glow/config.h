#pragma once

#include "../drashna/config.h"

#undef PRODUCT
#define PRODUCT DrashnaDox - Hacked ErgoDox EZ Glow

#undef RGB_MATRIX_LED_PROCESS_LIMIT
#undef RGB_MATRIX_LED_FLUSH_LIMIT

#if defined(RGBLIGHT_ENABLE) && defined(RGB_MATRIX_ENABLE)
#    define RGBLIGHT_LIMIT_VAL 175
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS (RGBLIGHT_LIMIT_VAL + 25)
#endif

#undef RGBLIGHT_SLEEP
