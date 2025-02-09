#pragma once

#define SERIAL_PIO_USE_PIO1

/******************************************************************
 * Trackball Setup
 ******************************************************************/

// Enable if you have a trackball
#define SPLIT_POINTING_ENABLE

/*
 * Undomment ONLY ONE of the following defines
 */
// Using a single trackball on the right hand side
// #define POINTING_DEVICE_RIGHT

// Using a sinble trackball on the left hand side
// #define POINTING_DEVICE_LEFT

// Rocking dual trackballs!
#define POINTING_DEVICE_COMBINED

#ifdef POINTING_DEVICE_COMBINED
#    define POINTING_DEVICE_INVERT_Y_RIGHT
#endif // POINTING_DEVICE_COMBINED
       //
#ifdef POINTING_DEVICE_RIGHT
#    define POINTING_DEVICE_INVERT_Y
#endif // POINTING_DEVICE_RIGHT

#define POINTING_DEVICE_TASK_THROTTLE_MS 10
#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
#define AUTO_MOUSE_TIME 600

#define MASTER_RIGHT

#define SPI_SCK_PIN GP2
#define SPI_MOSI_PIN GP3
#define SPI_MISO_PIN GP0
#define PMW33XX_CS_PIN GP6
#define PMW33XX_LIFTOFF_DISTANCE 0x02

#define MOUSE_EXTENDED_REPORT
#define WHEEL_EXTENDED_REPORT
#define POINTING_DEVICE_DEBUG

#define SCROLL_DIVISOR_H 30.0
#define SCROLL_DIVISOR_V 30.0

/*
 * OLED
 */
#define I2C_DRIVER I2CD1
#define I2C1_SCL_PIN GP15
#define I2C1_SDA_PIN GP14

/*
 * Reset
 */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP17
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U
#define PERMISSIVE_HOLD
#define QUICK_TAP_TERM_PER_KEY

/*
 * Font
 */
#define OLED_FONT_H "lib/crosses-font.c"

