#pragma once

#include "config_common.h"
#define PRODUCT_ID      0x3632
#define DEVICE_VER      0x0001
#define PRODUCT  DMOTE (62-key)
#define MATRIX_ROWS 12
#define MATRIX_COLS 6

// MCUs are flipped on each side, relative to the shape of the case,
// but for ease of mounting, the pinout is not flipped with the controller.
// The same finger on each hand uses a column connected to the pin with the
// same silk-screen label on each Pro Micro.

// Pin use:
//
//  MCU | Silk | DMOTE
// -----+------+----------
//   D3 | TX0  |
//   D2 | RX1  |
//   D1 | 2    | LED strip input (dominant half only)
//   D0 | 3    | Serial interface between halves
//   D4 | 4    | Outermost pinky-finger column
//   C6 | 5    | Column
//   D7 | 6    | Column
//   E6 | 7    | Column
//   B4 | 8    | Column
//   B5 | 9    | Outermost index-finger column
// -----+------+----------
//   F4 | A3   |
//   F5 | A2   |
//   F6 | A1   | Top row (furthest from user)
//   F7 | A0   | Row
//   B1 | 15   | Row
//   B3 | 14   | Row
//   B2 | 16   | Row
//   B6 | 10   | Bottom row (closest to user)
#define MATRIX_ROW_PINS { F6, F7, B1, B3, B2, B6 }
#define MATRIX_COL_PINS { D4, C6, D7, E6, B4, B5 }

#define DIODE_DIRECTION COL2ROW

// WS2812 RGB LED, normally used to indicate keyboard state:
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_KNIGHT_LENGTH 2
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_CHRISTMAS_STEP 1
#define RGB_DI_PIN D1
#define RGBLED_NUM 6           // Used when chaining strips
#define RGBLED_SPLIT { 3, 3 }  // Used when not chaining strips
#define ws2812_PORTREG  PORTD
#define ws2812_DDRREG   DDRD
