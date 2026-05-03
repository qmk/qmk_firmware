/* Copyright 2026 rkey-device/ (@rkey-device)
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

/* 12 MHz crystal on board */
#undef STM32_PLLMUL_VALUE
#define STM32_PLLMUL_VALUE      6

#undef STM32_SPI_USE_SPI1
#define STM32_SPI_USE_SPI1 TRUE

#undef STM32_PPRE2
#define STM32_PPRE2 STM32_PPRE2_DIV1 // Должно быть DIV1

#undef STM32_DMA_USE_CHANNELS
#define STM32_DMA_USE_CHANNELS TRUE

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

#undef STM32_SPI_SPI1_TX_DMA_STREAM
#define STM32_SPI_SPI1_TX_DMA_STREAM STM32_DMA_STREAM_ID(1, 3)


// #undef STM32_PWM_USE_TIM3
// #define STM32_PWM_USE_TIM3 TRUE

// #undef STM32_PWM_TIM3_CH2_DMA_STREAM
// #define STM32_PWM_TIM3_CH2_DMA_STREAM STM32_DMA_STREAM_ID(1, 3)
