#pragma once


#include "config_common.h"

#undef PRODUCT
#undef RGB_DI_PIN
#undef RGBLED_NUM


#define USE_SERIAL

#define EE_HANDS

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


// This uses the same coordinate system as the program that defines
// the case model, but not the same coordinates.
// Numbers increase going to the right and away from the user on the
// right-hand side of the keyboard. This is mirrored for the
// left-hand side.
// The matrix is constructed for ease of soldering, with the columns
// of the thumb cluster extending along the sides of the finger
// cluster so that everything can be contained in a 6x6 pattern.

#define LAYOUT_62key( \
    LA_20, LA_10, LF_35, LF_25, LF_15, LF_05,            \
    LF_55, LF_45, LF_34, LF_24, LF_14, LF_04,            \
    LF_54, LF_44, LF_33, LF_23, LF_13, LF_03,            \
    LF_53, LF_43, LF_32, LF_22, LF_12,                   \
                         LF_21,        LT_21, LT_22,     \
                                    LT_10, LT_11, LT_12, \
                                       LT_01, LT_02,     \
                                                         \
           RF_05, RF_15, RF_25, RF_35, RA_10, RA_20,     \
           RF_04, RF_14, RF_24, RF_34, RF_45, RF_55,     \
           RF_03, RF_13, RF_23, RF_33, RF_44, RF_54,     \
                  RF_12, RF_22, RF_32, RF_43, RF_53,     \
       RT_22, RT_21,     RF_21,                          \
    RT_12, RT_11, RT_10,                                 \
       RT_02, RT_01                                      \
  ) \
  { \
    { LA_20, LA_10, LF_35, LF_25, LF_15, LF_05 }, \
    { LF_55, LF_45, LF_34, LF_24, LF_14, LF_04 }, \
    { LF_54, LF_44, LF_33, LF_23, LF_13, LF_03 }, \
    { LF_53, LF_43, LF_32, LF_22, LF_12, LT_22 }, \
    { KC_NO, KC_NO, LT_21, LF_21, LT_11, LT_12 }, \
    { KC_NO, KC_NO, LT_10, KC_NO, LT_01, LT_02 }, \
                                                  \
    { RA_20, RA_10, RF_35, RF_25, RF_15, RF_05 }, \
    { RF_55, RF_45, RF_34, RF_24, RF_14, RF_04 }, \
    { RF_54, RF_44, RF_33, RF_23, RF_13, RF_03 }, \
    { RF_53, RF_43, RF_32, RF_22, RF_12, RT_22 }, \
    { KC_NO, KC_NO, RT_21, RF_21, RT_11, RT_12 }, \
    { KC_NO, KC_NO, RT_10, KC_NO, RT_01, RT_02 }, \
  }
