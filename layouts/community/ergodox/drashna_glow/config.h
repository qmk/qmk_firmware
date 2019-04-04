#pragma once

#include "../drashna/config.h"

#undef PRODUCT
#define PRODUCT         DrashnaDox - Hacked ErgoDox EZ Glow

#undef DEBOUNCE
#define DEBOUNCE 5

#ifdef RGB_MATRIX_ENABLE
// #define RGB_MATRIX_KEYPRESSES // reacts to keypresses (will slow down matrix scan by a lot)
// #define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (not recommened)
// #define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
#define RGB_DISABLE_WHEN_USB_SUSPENDED  true// turn off effects when suspended
// #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200 // limits maximum brightness of LEDs to 200 out of 255. If not defined maximum brightness is set to 255
// #define EECONFIG_RGB_MATRIX (uint32_t *)16
#endif

#undef DEBOUNCE
#define DEBOUNCE 1
