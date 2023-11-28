// Copyright 2023 MaiTheSan
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include_next <mcuconf.h>

#undef STM32_SPI_USE_SPI1
#define STM32_SPI_USE_SPI1 TRUE
