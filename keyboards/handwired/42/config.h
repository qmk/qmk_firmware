#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID 0xFEED
#define PRODUCT_ID 0x0000
#define DEVICE_VER 0x0004
#define MANUFACTURER nglgzz
#define PRODUCT 42
#define DESCRIPTION Splittable

#define BACKLIGHT_PIN C13
// According to the STM32F303xC datasheet C13 uses TIM1_CH1N to drive the PWM,
// and TIM1_CH1N is an alternate function that is available on port 4 for C13.
// This translates to:
//   TIM1 -> PWM_DRIVER
//   CH1  -> PWM_CHANNEL
//   N    -> USE_COMPLEMENTARY
//   AF4  -> PAL_MODE
#define BACKLIGHT_PWM_DRIVER PWMD1
#define BACKLIGHT_PWM_CHANNEL 1
#define BACKLIGHT_PWM_USE_COMPLEMENTARY 1
#define BACKLIGHT_PAL_MODE 4
// The backlight state depends on how the LED is wired on the Proton C.
#define BACKLIGHT_ON_STATE 0
#define BACKLIGHT_LEVELS 10

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
/* COL2ROW, ROW2COL */
#define MATRIX_ROWS 8
#define MATRIX_COLS 6
#define DIODE_DIRECTION COL2ROW

#define DEBOUNCE 5
#define TAPPING_TERM 100

/*
 * LEFT SIDE - connected to the Proton C.
 */
#define LEFT_MATRIX_ROWS 4
#define LEFT_MATRIX_COLS 6

#define MATRIX_ROW_PINS \
    { B3, B2, B1, B0 }
#define MATRIX_COL_PINS \
    { B15, B14, B13, A0, A1, A2 }

/*
 * RIGHT SIDE - connected to the IO expander.
 */
// Address of the MCP23017. All 3 address pins are connected to ground.
#define I2C_ADDRESS 0x40
#define I2C_DRIVER I2CD1

// Register addresses. Used to set pins to input/output.
#define I2C_IODIRA 0x00
#define I2C_IODIRB 0x01

// GPIO ports used for reading/writing to pins.
#define I2C_GPIOA 0x12
#define I2C_GPIOB 0x13

#define RIGHT_MATRIX_ROWS 4
#define RIGHT_MATRIX_COLS 6

// Pins on the expander used for rows and columns. Rows are set on the A port,
// and columns are set on the B port.
#define I2C_MATRIX_COL_PINS 0b00111111
#define I2C_MATRIX_ROW_PINS 0b00001111

#define i2c_writeRows(rows) i2c_writeReg(I2C_ADDRESS, I2C_GPIOA, rows, 1, 2)
#define i2c_writeCols(cols) i2c_writeReg(I2C_ADDRESS, I2C_GPIOB, cols, 1, 2)
#define i2c_readCols(cols) i2c_readReg(I2C_ADDRESS, I2C_GPIOB, cols, 1, 10)
