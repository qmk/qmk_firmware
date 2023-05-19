#pragma once
#include_next <mcuconf.h>

#ifdef RGBLIGHT_ENABLE
    #undef STM32_PWM_USE_TIM3
    #define STM32_PWM_USE_TIM3 TRUE
#endif

#undef STM32_I2C_USE_I2C1
#define STM32_I2C_USE_I2C1 TRUE
