#pragma once

#undef HAL_USE_SPI
#define HAL_USE_SPI FALSE

#undef HAL_USE_I2C
#define HAL_USE_I2C TRUE

#undef HAL_USE_ADC
#define HAL_USE_ADC TRUE

#include_next <halconf.h>