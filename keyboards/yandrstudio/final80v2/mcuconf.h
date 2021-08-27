#pragma once

#include_next <mcuconf.h>

#undef STM32_I2C_USE_I2C1
#define STM32_I2C_USE_I2C1                  TRUE

#undef STM32_PWM_USE_TIM3
#define STM32_PWM_USE_TIM3                  TRUE
