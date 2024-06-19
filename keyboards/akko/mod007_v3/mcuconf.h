// Copyright 2024 jonylee@hfd (@jonylee1986)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include_next <mcuconf.h>

#undef WB32_SPI_USE_QSPI
#define WB32_SPI_USE_QSPI TRUE
