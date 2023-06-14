#pragma once

#include_next <halconf.h>

#undef HAL_USE_I2C
#define HAL_USE_I2C TRUE

#undef HAL_USE_SPI
#define HAL_USE_SPI TRUE
#define SPI_USE_WAIT TRUE
#define SPI_SELECT_MODE SPI_SELECT_MODE_PAD

#undef PAL_USE_CALLBACKS
#define PAL_USE_CALLBACKS TRUE

#define print_str print
#define print_log uprintf

#include_next <halconf.h>

