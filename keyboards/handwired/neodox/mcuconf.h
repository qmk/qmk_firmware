// Copyright 2022 MatteoDM <matteodalmo@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include_next <mcuconf.h>

/* Used for tft display */
#undef RP_SPI_USE_SPI0
#define RP_SPI_USE_SPI0         TRUE

/* Used for backlight display */
#undef RP_PWM_USE_PWM6
#define RP_PWM_USE_PWM6         TRUE


