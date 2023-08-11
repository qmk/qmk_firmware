/* Copyright 2020 QMK Contributors
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include_next <mcuconf.h>

// The SysTick timer from the normal quantum/stm32 uses TIM2 -- the WS2812 pin used
// on the Planck requires the use of TIM2 to run PWM -- rework which timers are
// allocated for PWM usage.
#undef STM32_PWM_USE_TIM2
#define STM32_PWM_USE_TIM2 TRUE

#undef STM32_DAC_USE_DAC1_CH1
#define STM32_DAC_USE_DAC1_CH1 TRUE
#undef STM32_DAC_USE_DAC1_CH2
#define STM32_DAC_USE_DAC1_CH2 TRUE
#undef STM32_GPT_USE_TIM6
#define STM32_GPT_USE_TIM6 TRUE
#undef STM32_GPT_USE_TIM7
#define STM32_GPT_USE_TIM7 TRUE
#undef STM32_GPT_USE_TIM8
#define STM32_GPT_USE_TIM8 TRUE

// As mentioned above, we need to reallocate the SysTick timer used from
// TIM2 to TIM3.
#undef STM32_ST_USE_TIMER
#define STM32_ST_USE_TIMER 3

// enable i2c
#undef STM32_I2C_USE_I2C1
#define STM32_I2C_USE_I2C1 TRUE

// use the watchdog timer
#undef STM32_WDG_USE_IWDG
#define STM32_WDG_USE_IWDG TRUE
#undef STM32_IWDG_IS_WINDOWED
#define STM32_IWDG_IS_WINDOWED TRUE
