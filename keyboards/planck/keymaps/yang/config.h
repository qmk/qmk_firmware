#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

/* ws2812 RGB LED */
#define ws2812_PORTREG  PORTD
#define ws2812_DDRREG   DDRD
#define ws2812_pin PD1
#define RGBLED_NUM 28     // Number of LEDs
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17

#endif
