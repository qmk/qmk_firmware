// Copyright 2023 Cole Smith (@boardsource)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include_next <mcuconf.h>

#undef RP_PWM_USE_PWM6
#define RP_PWM_USE_PWM6 TRUE

#undef RP_SPI_USE_SPI1
#define RP_SPI_USE_SPI1 TRUE
