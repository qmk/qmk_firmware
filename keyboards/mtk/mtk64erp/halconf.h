// Copyright 2024 mentako-ya
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* OLED */
#ifdef OLED_ENABLE
#    undef HAL_USE_I2C
#    define HAL_USE_I2C TRUE
#endif

/* Trackball */
#ifdef POINTING_DEVICE_ENABLE
#    undef HAL_USE_SPI
#    define HAL_USE_SPI TRUE
#endif

#include_next "halconf.h"
