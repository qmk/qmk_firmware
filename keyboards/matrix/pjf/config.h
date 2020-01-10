/**
 * config.h
 *
 */

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0x4D58   // MX
#define PRODUCT_ID      0x00FF
#define DEVICE_VER      0x0001
#define MANUFACTURER    matrix
#define PRODUCT         Project FF
#define DESCRIPTION     compact 1800 without F row

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 16

#define MATRIX_ROW_PINS { A0, A1, A3, A2, A4, A5}
#define MATRIX_COL_PINS { C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14, C15}
#define UNUSED_PINS

#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* rgb light */
#define RGBLED_NUM      8
#define RGB_DI_PIN      B8
#define RGBLIGHT_ANIMATIONS

#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
