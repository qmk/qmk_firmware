/* Copyright 2023 David Hoelscher (@customMK)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
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

#undef STM32_LSE_ENABLED
#define STM32_LSE_ENABLED TRUE

#undef STM32_RTCSEL
#define STM32_RTCSEL STM32_RTCSEL_LSE

// Used for underglow
#undef STM32_PWM_USE_TIM1 //timer 1 channel 3
#define STM32_PWM_USE_TIM1 TRUE

// Used for backlight
//#undef STM32_PWM_USE_TIM2 //timer 2 channel ?
//#define STM32_PWM_USE_TIM2 TRUE

// Used for backlight
#undef STM32_PWM_USE_TIM3 //timer 3 channel 1
#define STM32_PWM_USE_TIM3 TRUE

// Used for backlight
//#undef STM32_GPT_USE_TIM3 //timer 3 channel 1
//#define STM32_GPT_USE_TIM3 TRUE

// Used for backlight
#undef STM32_PWM_USE_TIM4 //timer 4 channel ?
#define STM32_PWM_USE_TIM4 TRUE

// Used for backlight
#undef STM32_GPT_USE_TIM5 //timer 5 channel ?
#define STM32_GPT_USE_TIM5 TRUE

// Used for FRAM and flash in example code
#undef STM32_SPI_USE_SPI1
#define STM32_SPI_USE_SPI1 TRUE

// Used for OLED
#undef STM32_I2C_USE_I2C1
#define STM32_I2C_USE_I2C1 TRUE

