#pragma once

#include_next <mcuconf.h>

#undef STM32_PWM_USE_TIM5
#define STM32_PWM_USE_TIM5 TRUE
