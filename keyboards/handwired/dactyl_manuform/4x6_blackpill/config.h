#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define PRODUCT_ID      0x0048
#define DEVICE_VER      0x0001
#undef  MANUFACTURER
#define MANUFACTURER    Path Nirvana
#define PRODUCT         Dactyl-Manuform (4x6) blackpill

/* key matrix size */
#define MATRIX_ROWS 8 // Rows are doubled-up
#define MATRIX_COLS 12

#define MATRIX_ROWS_PER_SIDE (MATRIX_ROWS / 2)
#define MATRIX_COLS_PER_SIDE (MATRIX_COLS / 2)
/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 */
#define DIODE_DIRECTION COL2ROW

// wiring
#define MATRIX_COL_PINS_MCU \
    { B3, B4, B8, B9, A6, A7 }  // orig from ferris { B8, B4, B3, A15, A14 }
#define MATRIX_ROW_PINS_MCU \
    { A1, A2, A3, A5 }      // orig from ferris B7, B6, B5, A2
#define MATRIX_COL_PINS_MCP \
    { A0, A1, A2, A3, A4, A5 } //  pins on the mcp23017
#define MATRIX_ROW_PINS_MCP \
    { B0, B1, B2, B3 }      //  pins on the mcp23017

//#define MATRIX_IO_DELAY 5 // default is 30, reducing this to 5 just increases the matrix scan rate from 1015 to 1063. not worth it

/* i2c settings check docs/i2c_driver.md for details */
#define I2C_DRIVER I2CD1
#define I2C1_SCL_BANK GPIOB  // B6 and B7 used
#define I2C1_SCL 6
#define I2C1_SDA_BANK GPIOB
#define I2C1_SDA 7

#define I2C1_CLOCK_SPEED 400000
#define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_2


#define RGB_DI_PIN B1
#define RGBLED_NUM 48
#define DRIVER_LED_TOTAL 10
#define RGB_DISABLE_WHEN_USB_SUSPENDED false  // for measure current
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 220

#define WS2812_PWM_DRIVER PWMD3
#define WS2812_PWM_CHANNEL 4
#define WS2812_PWM_PAL_MODE 2
#define WS2812_DMA_STREAM STM32_DMA1_STREAM2
#define WS2812_DMA_CHANNEL 5

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

// #define DEBUG_MATRIX_SCAN_RATE // useful for debugging with hid_listen