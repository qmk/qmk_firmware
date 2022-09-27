#pragma once

#include_next <halconf.h>

#undef HAL_USE_SPI
#define HAL_USE_SPI TRUE

#undef SPI_USE_WAIT
#define SPI_USE_WAIT TRUE
