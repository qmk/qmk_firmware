// Copyright 2018-2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include_next <mcuconf.h>

// Used for RGB
//#undef RP_ADC_USE_ADC1
//#define RP_ADC_USE_ADC1 TRUE

// Used for EEPROM
#undef RP_SPI_USE_SPI0
#define RP_SPI_USE_SPI0 TRUE
