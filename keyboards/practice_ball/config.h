// Copyright 2023 ZiTe (@ZiTe)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define PMW33XX_CS_PIN B6 // SPI CS pin.

/* Optional. */
#define PMW33XX_CPI 1600      // The CPI range is 100-12000, in increments of 100. Defaults to 1600 CPI.
#define PMW33XX_CLOCK_SPEED 2000000 // Sets the clock speed that the sensor runs at. Defaults to 2000000
#define MOUSE_EXTENDED_REPORT // Use -32767 to 32767, instead of just -127 to 127.
// #define POINTING_DEVICE_TASK_THROTTLE_MS 10

#define RGBLIGHT_DEFAULT_VAL 32
