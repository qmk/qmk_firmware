#pragma once

#define VENDOR_ID 0x4454
#define PRODUCT_ID 0x5444
#define DEVICE_VER 0x0001

#define MANUFACTURER "IktaS"
#define PRODUCT "Pill60"
#define DESCRIPTION "QMK keyboard firmware for Pill60"

#define MATRIX_ROWS 5
#define MATRIX_COLS 14
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 1

/* Backlighting include */

#define BACKLIGHT_LEVELS 5
#define BREATHING_PERIOD 6

/* Encoder */
#define ENCODERS_PAD_A \
    { B9 }
#define ENCODERS_PAD_B \
    { B8 }
#define ENCODER_RESOLUTION 2

/* OLED */
#define I2C_DRIVER I2CD1
#define I2C1_SCL_BANK GPIOB
#define I2C1_SDA_BANK GPIOB
#define I2C1_SCL 6
#define I2C1_SDA 7