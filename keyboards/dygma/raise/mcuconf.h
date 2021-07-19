#pragma once

#include_next <mcuconf.h>

#undef STM32_I2C_USE_I2C1
#define STM32_I2C_USE_I2C1 TRUE

#undef STM32_I2C_BUSY_TIMEOUT
#define STM32_I2C_BUSY_TIMEOUT 5
