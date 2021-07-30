#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0x445A
#define PRODUCT_ID      0x1120
#define DEVICE_VER      0x0001
#define MANUFACTURER    DZTECH
#define PRODUCT         DZ60RGB

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 14

/* Keyboard Matrix Assignments */
#define MATRIX_ROW_PINS { B1, B10, B11, B14, B12 }
#define MATRIX_COL_PINS { A6, A7, B0, B13, B15, A8, A15, B3, B4, B5, B8, B9, C13, C14 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

#ifdef RGB_MATRIX_ENABLE
#   define RGB_DISABLE_WHEN_USB_SUSPENDED // turn off effects when suspended
#   define RGB_MATRIX_KEYPRESSES
#   define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#   define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#   define DISABLE_RGB_MATRIX_HUE_BREATHING
#   define DISABLE_RGB_MATRIX_HUE_PENDULUM
#   define DISABLE_RGB_MATRIX_HUE_WAVE
#   define DISABLE_RGB_MATRIX_BAND_SAT
#   define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#   define DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#   define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#   define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#   define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#   define DISABLE_RGB_MATRIX_SPLASH
#   define DISABLE_RGB_MATRIX_SOLID_SPLASH
#   define DRIVER_ADDR_1 0b1010000
#   define DRIVER_ADDR_2 0b1010000 // this is here for compliancy reasons.
#   define DRIVER_COUNT 2
#   define DRIVER_1_LED_TOTAL 63
#   define DRIVER_LED_TOTAL DRIVER_1_LED_TOTAL
#endif
