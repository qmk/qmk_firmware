#include "../../config.h"

/* WS2812B RGB Underglow LED */
#define ws2812_PORTREG  PORTF
#define ws2812_DDRREG   DDRF
#define ws2812_pin PF5        // Based on wiring depicted in ws2812_wiring.jpg
#define RGBLED_NUM 16         // Number of LEDs. Change this to match your use case.
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
