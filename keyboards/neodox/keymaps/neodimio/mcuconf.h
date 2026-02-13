// Copyright 2018-2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include_next <mcuconf.h>

#define RP2040_MCUCONF


// Used for tft display
#undef RP_SPI_USE_SPI0
#define RP_SPI_USE_SPI0         TRUE

// Used for split comms
#undef RP_SIO_USE_UART0
#define RP_SIO_USE_UART0        TRUE

// Used for backlight display
#undef RP_PWM_USE_PWM6
#define RP_PWM_USE_PWM6         TRUE


