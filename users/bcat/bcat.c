#include "quantum.h"

#if defined(RGBLIGHT_ENABLE)
/* Adjust RGB static hue ranges for shorter gradients than default. */
const uint8_t RGBLED_GRADIENT_RANGES[] PROGMEM = {255, 127, 63, 31, 15};
#endif
