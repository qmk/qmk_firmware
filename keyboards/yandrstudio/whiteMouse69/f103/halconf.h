#pragma once
#include_next <halconf.h>

#undef HAL_USE_SPI
#define HAL_USE_SPI    TRUE

#undef  SPI_SELECT_MODE
#define SPI_SELECT_MODE SPI_SELECT_MODE_PAD

