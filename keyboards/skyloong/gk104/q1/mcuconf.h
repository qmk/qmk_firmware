// Copyright 2023 JZ-Skyloong (@JZ-Skyloong)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include_next <mcuconf.h>

#undef STM32_SPI_USE_SPI2
#define STM32_SPI_USE_SPI2 TRUE

#undef STM32_SPI_USE_DMA
#define STM32_SPI_USE_DMA TRUE

#undef STM32_SPI_USE_SPI1
#define STM32_SPI_USE_SPI1 TRUE


