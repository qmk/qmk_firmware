#pragma once

#include_next <mcuconf.h>

#undef STM32_PWM_USE_TIM3
#define STM32_PWM_USE_TIM3 TRUE

#undef STM32_I2C_USE_I2C1
#define STM32_I2C_USE_I2C1 TRUE

//#undef STM32_SPI_USE_SPI2
//#define STM32_SPI_USE_SPI2 FALSE

#undef STM32_PWM_USE_TIM1
#define STM32_PWM_USE_TIM1 TRUE
