#pragma once

/* ws2812 RGB LED */
#define RGB_DI_PIN D3

#ifdef RGBLIGHT_ENABLE
#    define RGBLED_NUM 12  // Number of LEDs
#endif

#ifdef RGB_MATRIX_ENABLE
#    define RGBLED_NUM 54  // Number of LEDs
#    define DRIVER_LED_TOTAL RGBLED_NUM
#endif
