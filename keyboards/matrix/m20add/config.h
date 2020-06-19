/**
 * config.h
 *
 */

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID  0x4D58   // MX
#define PRODUCT_ID 0x20AD   // 8XV2.0 Additional
#define DEVICE_VER 0x0001
#define MANUFACTURER MATRIX
#define PRODUCT 8XV2.0 Additional
#define DESCRIPTION Matrix 8XV2.0 Additional keyboard

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 16

#define DEF_PIN(port, pin) (((port) << 8) | pin)
#define GET_PORT(pp) (((pp) >> 8) & 0xFF)
#define GET_PIN(pp) ((pp) & 0xFF)

#define MATRIX_ROW_PINS { \
    DEF_PIN(TCA6424_PORT2, 7), \
    DEF_PIN(TCA6424_PORT2, 6), \
    DEF_PIN(TCA6424_PORT2, 0), \
    DEF_PIN(TCA6424_PORT2, 2), \
    DEF_PIN(TCA6424_PORT2, 4), \
    DEF_PIN(TCA6424_PORT2, 5) }

#define MATRIX_COL_PINS { \
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

#define UNUSED_PINS


#define DIODE_DIRECTION COL2ROW
#define DEBOUNCE    5

// i2c setting
#define USE_I2CV1
#define I2C1_SCL 8
#define I2C1_SDA 9
#define I2C1_CLOCK_SPEED 400000
#define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_2

// rgb light setting
#define RGB_DI_PIN B4  // reserved pin for future usage
#define RGBLED_NUM 20
#define RGBLIGHT_ANIMATIONS

#define DRIVER_ADDR_1 0b1110100
#define DRIVER_COUNT 1
#define DRIVER_LED_TOTAL RGBLED_NUM

#define EARLY_INIT_PERFORM_BOOTLOADER_JUMP FALSE    // disable jump to system bootloader
