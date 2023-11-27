/* Copyright 2021 QMK
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include_next <mcuconf.h>

// for i2c expander, and ISSI
#undef STM32_I2C_USE_I2C1
#define STM32_I2C_USE_I2C1 TRUE

// for indicator LEDs
#undef STM32_PWM_USE_TIM3
#define STM32_PWM_USE_TIM3 TRUE
#undef STM32_PWM_USE_TIM4
#define STM32_PWM_USE_TIM4 TRUE

// for audio
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
