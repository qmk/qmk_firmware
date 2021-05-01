/**
 * config.h
 *
 */

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID  0x4D58   // MX
#define PRODUCT_ID 0x0065   // noah 65
#define DEVICE_VER 0x0001
#define MANUFACTURER matrix
#define PRODUCT NOAH
#define DESCRIPTION 65% keybaord of the Matrix abel family

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

#define MATRIX_ROW_PINS {  B0,  A1, C14, C13,  A0}
#define MATRIX_COL_PINS { C15, B10,  B7,  B6,  B5,  B4, A15, A10,  A9,  A8, B15, B14, B13, B12,  B2}
#define UNUSED_PINS

#define DIODE_DIRECTION COL2ROW
#define DEBOUNCE    5

// i2c setting
#define USE_I2CV1
#define I2C1_SCL 8
#define I2C1_SDA 9
#define I2C1_CLOCK_SPEED 400000
#define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_2
#define PAL_MODE_STM32_ALTERNATE_OPENDRAIN (PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN)

// rgb matrix setting
#define DRIVER_ADDR_1 0b1110100
#define DRIVER_ADDR_2 0b1110110
#define DRIVER_COUNT 2
#define DRIVER_1_LED_TOTAL 36
#define DRIVER_2_LED_TOTAL 36
#define DRIVER_LED_TOTAL (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)

/* indicator rgb */
#define RGBLED_NUM 7
#define RGB_DI_PIN B1
#define RGBLIGHT_ANIMATIONS

// tapping setting
//#define TAPPING_TERM 200
//#define RETRO_TAPPING
//#define PERMISSIVE_HOLD
