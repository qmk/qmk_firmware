#pragma once

#include_next <mcuconf.h>

#undef STM32_SPI_USE_SPI1
#define STM32_SPI_USE_SPI1 FALSE

#undef STM32_SPI_USE_SPI2
#define STM32_SPI_USE_SPI2 TRUE



#define STM32_I2C_USE_I2C1 TRUE
#define STM32_I2C_USE_I2C2 FALSE
