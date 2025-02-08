#pragma once

#undef HAL_USE_I2C 
#define HAL_USE_I2C true

#include_next <halconf.h>