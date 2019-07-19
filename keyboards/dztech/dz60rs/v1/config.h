#pragma once
#include "config_common.h"
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x1300
#define DEVICE_VER      0x0001
#define MANUFACTURER    DZTECH
#define PRODUCT         DZ60RSV1
#define DESCRIPTION     DZ60 Rgb Solder keyboard PCB

#define MATRIX_ROWS 5
#define MATRIX_COLS 14
#define MATRIX_ROW_PINS { B0, B1, B2, B3, F1 }
#define MATRIX_COL_PINS { F7, F6, F5, F4, C7, F0, B7, D2, D3, D5, D4, D6, D7, B4}
#define UNUSED_PINS
#define DIODE_DIRECTION COL2ROW

#define DEBOUNCE 3
#define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
#define RGB_DISABLE_WHEN_USB_SUSPENDED true // turn off effects when suspended
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN	
#define DISABLE_RGB_MATRIX_BAND_SAT
#define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#define DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#define DISABLE_RGB_MATRIX_SPLASH
#define DISABLE_RGB_MATRIX_MULTISPLASH
#define DISABLE_RGB_MATRIX_SOLID_SPLASH
#define DISABLE_RGB_MATRIX_SOLID_MULTISPLASH
#define DISABLE_RGB_MATRIX_DIGITAL_RAIN

#define DRIVER_ADDR_1 0b1110100
#define DRIVER_ADDR_2 0b1110111
#define DRIVER_COUNT 2
#if defined (hhkb)
#define DRIVER_1_LED_TOTAL 32
#define DRIVER_2_LED_TOTAL 30
#elif defined (hhkb_iso)
#define DRIVER_1_LED_TOTAL 32
#define DRIVER_2_LED_TOTAL 31
#elif defined (ansi)
#define DRIVER_1_LED_TOTAL 31
#define DRIVER_2_LED_TOTAL 32
#elif defined (ansi_split_bs) || defined (ansi_split_rsft)
#define DRIVER_1_LED_TOTAL 32
#define DRIVER_2_LED_TOTAL 32
#elif defined (ansi_split_bs_rsft)
#define DRIVER_1_LED_TOTAL 33
#define DRIVER_2_LED_TOTAL 32
#elif defined (iso)
#define DRIVER_1_LED_TOTAL 31
#define DRIVER_2_LED_TOTAL 33
#elif defined (iso_split_bs) || defined(iso_split_rsft)
#define DRIVER_1_LED_TOTAL 32
#define DRIVER_2_LED_TOTAL 33
#elif defined (iso_split_bs_rsft)
#define DRIVER_1_LED_TOTAL 33
#define DRIVER_2_LED_TOTAL 33
#else
#define DRIVER_1_LED_TOTAL 36
#define DRIVER_2_LED_TOTAL 36
#endif
#define DRIVER_LED_TOTAL (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)

