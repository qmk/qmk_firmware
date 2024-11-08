// Copyright 2024 splitkb.com (support@splitkb.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#if HAL_USE_SPI == TRUE
#    define SPI_USE_WAIT TRUE
#    define SPI_SELECT_MODE SPI_SELECT_MODE_PAD
#endif

#include_next <halconf.h>