/**
 * config.h
 *
 */

#pragma once

#define EARLY_INIT_PERFORM_BOOTLOADER_JUMP TRUE

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 16

#define DEF_PIN(port, pin) (((port) << 8) | pin)
#define GET_PORT(pp) (((pp) >> 8) & 0xFF)
#define GET_PIN(pp) ((pp) & 0xFF)

#define ROW1_MASK 0x80
#define ROW2_MASK 0x40
#define ROW3_MASK 0x01
#define ROW4_MASK 0x04
#define ROW5_MASK 0x10
#define ROW6_MASK 0x20
#define ROW_PORT TCA6424_PORT2

#define COL1_MASK 0x02
#define COL2_MASK 0x80
#define COL3_MASK 0x40
#define COL4_MASK 0x20
#define COL5_MASK 0x10
#define COL6_MASK 0x08
#define COL7_MASK 0x04
#define COL8_MASK 0x02
#define COL9_MASK 0x01
#define COL10_MASK 0x80
#define COL11_MASK 0x40
#define COL12_MASK 0x20
#define COL13_MASK 0x10
#define COL14_MASK 0x08
#define COL15_MASK 0x04
#define COL16_MASK 0x02

// Note: MATRIX_ROW_PINS only works with standard pin names.
#define MATRIX_M20_ROW_PINS { \
    DEF_PIN(TCA6424_PORT2, 7), \
    DEF_PIN(TCA6424_PORT2, 6), \
    DEF_PIN(TCA6424_PORT2, 0), \
    DEF_PIN(TCA6424_PORT2, 2), \
    DEF_PIN(TCA6424_PORT2, 4), \
    DEF_PIN(TCA6424_PORT2, 5) }

// Note: MATRIX_COL_PINS only works with standard pin names.
#define MATRIX_M20_COL_PINS { \
    DEF_PIN(TCA6424_PORT2, 1), \
    DEF_PIN(TCA6424_PORT1, 7), \
    DEF_PIN(TCA6424_PORT1, 6), \
    DEF_PIN(TCA6424_PORT1, 5), \
    DEF_PIN(TCA6424_PORT1, 4), \
    DEF_PIN(TCA6424_PORT1, 3), \
    DEF_PIN(TCA6424_PORT1, 2), \
    DEF_PIN(TCA6424_PORT1, 1), \
    DEF_PIN(TCA6424_PORT1, 0), \
    DEF_PIN(TCA6424_PORT0, 7), \
    DEF_PIN(TCA6424_PORT0, 6), \
    DEF_PIN(TCA6424_PORT0, 5), \
    DEF_PIN(TCA6424_PORT0, 4), \
    DEF_PIN(TCA6424_PORT0, 3), \
    DEF_PIN(TCA6424_PORT0, 2), \
    DEF_PIN(TCA6424_PORT0, 1) }



#define DIODE_DIRECTION COL2ROW

// i2c setting
#define I2C1_SCL_PIN B8
#define I2C1_SDA_PIN B9
#define I2C1_CLOCK_SPEED 400000
#define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_2

#define IS31FL3731_I2C_ADDRESS_1 IS31FL3731_I2C_ADDRESS_GND
#define IS31FL3731_LED_COUNT 20
