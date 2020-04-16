#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x3060
#define DEVICE_VER      0x0001
#define MANUFACTURER    zk-phi
#define PRODUCT         Equilibrium
#define DESCRIPTION     A row-staggered 35%

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_ROW_PINS { B2, B6, B3, F6, B1, F7, F5, F4 }
#define MATRIX_COLS 6
#define MATRIX_COL_PINS { D4, C6, D7, E6, B4, B5 }
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCING_DELAY 5

/* ws2812 RGB MATRIX */
#define RGB_DI_PIN D3
#define DRIVER_LED_TOTAL 67 // Number of LEDs
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 140

#if defined(RGBLIGHT_ENABLE) && !defined(IOS_DEVICE_ENABLE)
// USB_MAX_POWER_CONSUMPTION value
//  120  RGBoff
//  330  RGB 6
//  300  RGB 32
#define USB_MAX_POWER_CONSUMPTION 400
#else
// fix iPhone and iPad power adapter issue
// iOS device need lessthan 100
#define USB_MAX_POWER_CONSUMPTION 100
#endif
