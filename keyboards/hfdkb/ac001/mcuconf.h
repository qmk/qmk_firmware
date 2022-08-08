#pragma once

#include_next <mcuconf.h>

#undef WB32_SPI_USE_QSPI
#define WB32_SPI_USE_QSPI TRUE

#undef WB32_I2C_USE_I2C1
#define WB32_I2C_USE_I2C1 TRUE
