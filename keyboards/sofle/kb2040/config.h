// Copyright 2022 @filterpaper
// SPDX-License-Identifier: GPL-2.0+

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID 0xFEED
#define PRODUCT_ID 0x0000
#define DEVICE_VER 0x0001
#define MANUFACTURER marcoster
#define PRODUCT sofle2040

//* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 10
#define MATRIX_COLS 6

// wiring of each half
#define MATRIX_ROW_PINS \
    { GP5, GP6, GP7, GP8, GP9 }
#define MATRIX_COL_PINS \
    { GP27, GP26, GP18, GP20, GP19, GP10 }
#define DIODE_DIRECTION COL2ROW

#define TAPPING_TERM 100
#define DEBOUNCE 5

/* encoder support */
#define ENCODERS_PAD_A \
    { GP29 }
#define ENCODERS_PAD_B \
    { GP28 }
#define ENCODERS_PAD_A_RIGHT \
    { GP28 }
#define ENCODERS_PAD_B_RIGHT \
    { GP29 }
#define ENCODER_RESOLUTION 2

#define TAP_CODE_DELAY 10

/* I2C support */
#define I2C1_SDA_PIN GP2
#define I2C1_SCL_PIN GP3
#define I2C_DRIVER I2CD2

#undef SOFT_SERIAL_PIN
#define SOFT_SERIAL_PIN GP1
#define SERIAL_PIO_USE_PIO1

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP17
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U

#define WAIT_FOR_USB 1
#define NKRO_ENABLE 1
