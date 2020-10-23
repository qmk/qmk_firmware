#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x0000
#define PRODUCT_ID      0x0000
#define DEVICE_VER      0x0001
#define MANUFACTURER    Santy
#define PRODUCT         SantyBoard
#define DESCRIPTION     Normal 60% but the space is divided into 4

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

#define MATRIX_ROW_PINS { B8, A0, A1, A2, B13 }
#define MATRIX_COL_PINS { A4, A5, A6, A7, B15, B14, B9, B7, B6, B5, B4, B3, B2, B1, B0 }

#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* 1 Encoder */
// the first encoder (esc) has A8 (bottom right) and A15(bottom left)
// while the second has B10 (bottom right) and B11 (bottom left)
#define ENCODERS_PAD_A { A15, B10 }
#define ENCODERS_PAD_B { A8, B11 }

// in case the encoders are working opposite as intended (clockwise vold for example) do the following:
// if encoder #2 is flipped for example just swap the B11 and B10 in the encoders_pad_b define 

#define TAP_CODE_DELAY 10
#define ENCODER_RESOLUTION 4

#define FORCE_NKRO

// define the things for the RGB strip

// The data pin for the LED strip
#define RGB_DI_PIN B12											
// the number of LEDs connected. I have seen that about 9 or 10 would be pushing the max. I put 10 just so it compiles
#define RGBLED_NUM 10
// underglow animations
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_HUE_STEP 5
#define RGBLIGHT_SAT_STEP 10
#define RGBLIGHT_VAL_STEP 10
// enable lighting layers
#define RGBLIGHT_LAYERS
// override the default max of 8 layer profiles
#define RGBLIGHT_MAX_LAYERS 32
// so that the power draw doesn't exceed what is available
//#define USB_MAX_POWER_CONSUMPTION 900     // Limit device max power consumption.
#define RGBSTRIP_CURRENT_LIMIT 400        // Strip current limit in mA.
#define RGBSTRIP_MAX_CURRENT_PER_LIGHT 60 // mA per light when at max brightness.

