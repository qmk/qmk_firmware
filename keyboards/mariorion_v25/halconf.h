#pragma once

#undef HAL_USE_PWM
#define HAL_USE_PWM TRUE

#undef HAL_USE_SPI
#define HAL_USE_SPI FALSE

#include_next "halconf.h"