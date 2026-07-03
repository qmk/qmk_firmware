// Copyright 2023 Dane Lipscombe (@dlip)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include_next <mcuconf.h>
#undef RP_SPI_USE_SPI0
#define RP_SPI_USE_SPI0 TRUE
