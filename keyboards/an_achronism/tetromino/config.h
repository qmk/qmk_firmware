// Copyright 2022 an_achronism (@an-achronism)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define WS2812_PIO_USE_PIO1 // Use PIO1 on Pi Pico for RGB LEDs
#define RGB_DI_PIN GP26 // Use GPIO26 (pin 31) for LED matrix logic
#define DRIVER_LED_TOTAL 70
/* The following line is now specified in info.json under the rgblight struct,
so has been moved there instead: */
// #define RGBLED_NUM 70
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 255
#define RGB_MATRIX_STARTUP_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
